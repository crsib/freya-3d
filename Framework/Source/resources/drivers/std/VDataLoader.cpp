#include "VDataLoader.h"

#include <vector>
#include <core/memory/MemoryAllocator.h>

#include "core/filesystem/Filesystem.h"
#include "core/taskmanager/Task.h"
#include "core/taskmanager/TaskManager.h"

#include "core/EngineCore.h"
#include "framework/Structures.h"
#include <iostream>
//#include <stdint.h>

namespace resources
{

namespace __internal
{
template<>
resources::Resource* 	createResource(framework::VBOData*	resource)
{
	resources::Resource* res = new resources::Resource;
	if(resource == NULL)
		return res;
	res->m_Resource = dynamic_cast<EngineSubsystem*>(resource);
	if(res->m_Resource == NULL)
		throw resources::ResourceException ("Failed to create resource");
	return res;
}

template<>
resources::Resource* 	setResource(Resource* res,framework::VBOData*	resource)
{
	res->m_Resource = dynamic_cast<EngineSubsystem*>(resource);
	if(res->m_Resource == NULL)
		throw resources::ResourceException ("Failed to create resource");
	return res;
}

}

namespace drivers
{

namespace __std
{
VDataLoader::VDataLoader()
{

}

void VDataLoader::destroy(Resource *res)
{
	if(!res->ready())
		return; //It will never finish then))
	framework::VBOData* data = res->get<framework::VBOData*>();
	if(data->indicies)
		core::EngineCore::getRenderingDriver()->destroyVertexBufferObject(data->indicies);
	if(data->vertex_data)
		core::EngineCore::getRenderingDriver()->destroyVertexBufferObject(data->vertex_data);
	delete data;
	resources::__internal::destroyResource(res);
}

VDataLoader::~VDataLoader()
{
}

Resource *VDataLoader::loadSynchronous(const EString & ID)
{
	core::filesystem::Filesystem*	fs = core::EngineCore::getFilesystem();
	//Parse id
	size_t sem_pos = ID.find_last_of(':');
	EString	fn = ID.substr(sem_pos + 1);
	if(fs->fileExists(fn))
	{
		framework::VBOData* data	= new framework::VBOData;

		//std::cout << "Loading " << fn << std::endl;

		size_t sz;
		void* raw_data = fs->read(fn,&sz);
		//std::cout << "\tFile size is: " << sz << std::endl;
		size_t offset = 0;
		//Read first 16 bits of data
		memcpy(&data->num_batches,reinterpret_cast<char*>(raw_data) + offset, sizeof(uint16_t));
		offset += sizeof(uint16_t);
		//std::cout << "\tNumber of batches: " << data->num_batches << std::endl;

		data->batches = new framework::__VBO_BatchHeader[data->num_batches];
		for(size_t i = 0; i < data->num_batches; i++)
		{
			memcpy(&data->batches[i].assembly_type,reinterpret_cast<char*>(raw_data) + offset,8);
			offset += 8;
			//std::cout << "\t\tBatch " << i << "\n\t\t\tAssembly type: " << data->batches[i].assembly_type
//					<< "\n\t\t\tIndex count: " << data->batches[i].index_count
//					<< "\n\t\t\tOffset: "<< data->batches[i].buffer_offset << std::endl;
			//Now, the most difficult part. Reading buffer layout
			typedef std::vector<renderer::VertexElement*, core::memory::MemoryAllocator<renderer::VertexElement*> > vlayout;
			vlayout layout;
			bool finished = false;
			while(!finished)
			{
				uint32_t _[4];
				memcpy(_,reinterpret_cast<char*>(raw_data) + offset,4*sizeof(uint32_t));
				offset += 4*sizeof(uint32_t);
				//std::cout << "stream data: " << _[0] << " " << _[1] << " " << _[2] << " " << _[3] << " "  << std::endl;
				renderer::VertexElement* elem = new renderer::VertexElement(_[0],(renderer::VertexFormat::USAGE)_[1],(renderer::VertexFormat::TYPE)_[3],_[4]);
				layout.push_back(elem);
				if(elem->usage == renderer::VertexFormat::UNUSED)
					finished = true;
			}
			//std::cout << "\t\t\tLayout items: " << layout.size() << std::endl;
			data->batches[i].layout = new renderer::VertexElement[layout.size()];
			for(size_t j = 0; j < layout.size(); j++)
			{
				data->batches[i].layout[j].streamID = layout[j]->streamID;
				data->batches[i].layout[j].usage	= layout[j]->usage;
				data->batches[i].layout[j].type		= layout[j]->type;
				data->batches[i].layout[j].offset	= layout[j]->offset;
				delete layout[j];
			}
		}
		memcpy(&data->number_of_indicies,reinterpret_cast<char*>(raw_data) + offset,sizeof(uint16_t));
		offset += sizeof(uint16_t);
		//This part will be different in async loader
		if(data->number_of_indicies)
		{
			data->indicies = core::EngineCore::getRenderingDriver()->createVertexBufferObject();
			data->indicies->setData(renderer::VBOTarget::INDEX,renderer::VBOUsage::STATIC_DRAW,data->number_of_indicies*sizeof(uint16_t),NULL);
			memcpy(data->indicies->map(renderer::VBOAccess::WRITE_ONLY),reinterpret_cast<char*>(raw_data) + offset,data->number_of_indicies*sizeof(uint16_t));
			data->indicies->unmap();
			offset += data->number_of_indicies*sizeof(uint16_t);
			//std::cout << "\t\tNumber of indicies: " << data->number_of_indicies << std::endl;
		}
		memcpy(&data->size_of_vertex_data,reinterpret_cast<char*>(raw_data) + offset,sizeof(uint32_t));
		offset += sizeof(uint32_t);
		data->vertex_data = core::EngineCore::getRenderingDriver()->createVertexBufferObject();
		data->vertex_data->setData(renderer::VBOTarget::VERTEX,renderer::VBOUsage::STATIC_DRAW,data->size_of_vertex_data,NULL);
		memcpy(data->vertex_data->map(renderer::VBOAccess::WRITE_ONLY),reinterpret_cast<char*>(raw_data) + offset,data->size_of_vertex_data);
		data->vertex_data->unmap();
		//std::cout << "\t\tSize of vertex buffer: " << data->size_of_vertex_data << std::endl;
		core::memory::Free(raw_data,core::memory::GENERIC_POOL);
		Resource* res = resources::__internal::createResource(data);
		resources::__internal::finalizeResource(res);
		return res;
	}
	else
		throw ResourceException(EString("File ") + fn + " not found");
	return NULL;
}

bool
VDataLoader::unique() const
{
	return true;
}

EString
VDataLoader::id() const
{
	return "vbo";
}

namespace __internal
{
class VDataLoaderTask : public core::taskmanager::Task
{
public:
	VDataLoaderTask(){}
	core::filesystem::Filesystem*	fs;
	int								vboState;
	EString							fn;
	resources::Resource*			res;
	size_t							ind_offset;
	size_t 							vert_offset;
	framework::VBOData* 			data;
	void*							raw_data;
	int
	operator () ()
	{
		switch(vboState)
		{
			case 0:
			{
				//std::cout << "Loading " << fn << std::endl;

				size_t sz;
				raw_data = fs->read(fn,&sz);
				//std::cout << "\tFile size is: " << sz << std::endl;
				size_t offset = 0;
				//Read first 16 bits of data
				memcpy(&data->num_batches,reinterpret_cast<char*>(raw_data) + offset, sizeof(uint16_t));
				offset += sizeof(uint16_t);
				//std::cout << "\tNumber of batches: " << data->num_batches << std::endl;

				data->batches = new framework::__VBO_BatchHeader[data->num_batches];
				for(size_t i = 0; i < data->num_batches; i++)
				{
					memcpy(&data->batches[i].assembly_type,reinterpret_cast<char*>(raw_data) + offset,8);
					offset += 8;
					//std::cout << "\t\tBatch " << i << "\n\t\t\tAssembly type: " << data->batches[i].assembly_type
//							<< "\n\t\t\tIndex count: " << data->batches[i].index_count
//							<< "\n\t\t\tOffset: "<< data->batches[i].buffer_offset << std::endl;
					//Now, the most difficult part. Reading buffer layout
					typedef std::vector<renderer::VertexElement*, core::memory::MemoryAllocator<renderer::VertexElement*> > vlayout;
					vlayout layout;
					bool finished = false;
					while(!finished)
					{
						uint32_t _[4];
						memcpy(_,reinterpret_cast<char*>(raw_data) + offset,4*sizeof(uint32_t));
						offset += 4*sizeof(uint32_t);
						//std::cout << "stream data: " << _[0] << " " << _[1] << " " << _[2] << " " << _[3] << " "  << std::endl;
						renderer::VertexElement* elem = new renderer::VertexElement(_[0],(renderer::VertexFormat::USAGE)_[1],(renderer::VertexFormat::TYPE)_[3],_[4]);
						layout.push_back(elem);
						if(elem->usage == renderer::VertexFormat::UNUSED)
							finished = true;
					}
					//std::cout << "\t\t\tLayout items: " << layout.size() << std::endl;
					data->batches[i].layout = new renderer::VertexElement[layout.size()];
					for(size_t j = 0; j < layout.size(); j++)
					{
						data->batches[i].layout[j].streamID = layout[j]->streamID;
						data->batches[i].layout[j].usage	= layout[j]->usage;
						data->batches[i].layout[j].type		= layout[j]->type;
						data->batches[i].layout[j].offset	= layout[j]->offset;
						delete layout[j];
					}
				}
				memcpy(&data->number_of_indicies,reinterpret_cast<char*>(raw_data) + offset,sizeof(uint16_t));
				offset += sizeof(uint16_t);
				//This part will be different in async loader
				ind_offset = offset;
				offset += data->number_of_indicies*sizeof(uint16_t);
				memcpy(&data->size_of_vertex_data,reinterpret_cast<char*>(raw_data) + offset,sizeof(uint32_t));
				offset += sizeof(uint32_t);
				vert_offset = offset;
				vboState = 1;
				return MAIN_THREAD;
			}
			break;
			case 1:
			{
				if(data->number_of_indicies)
				{
					data->indicies = core::EngineCore::getRenderingDriver()->createVertexBufferObject();
					data->indicies->setData(renderer::VBOTarget::INDEX,renderer::VBOUsage::STATIC_DRAW,data->number_of_indicies*sizeof(uint16_t),NULL);
					memcpy(data->indicies->map(renderer::VBOAccess::WRITE_ONLY),reinterpret_cast<char*>(raw_data) + ind_offset,data->number_of_indicies*sizeof(uint16_t));
					data->indicies->unmap();
					//std::cout << "\t\tNumber of indicies: " << data->number_of_indicies << std::endl;
				}
				data->vertex_data = core::EngineCore::getRenderingDriver()->createVertexBufferObject();
				data->vertex_data->setData(renderer::VBOTarget::VERTEX,renderer::VBOUsage::STATIC_DRAW,data->size_of_vertex_data,NULL);
				memcpy(data->vertex_data->map(renderer::VBOAccess::WRITE_ONLY),reinterpret_cast<char*>(raw_data) + vert_offset,data->size_of_vertex_data);
				data->vertex_data->unmap();
				//std::cout << "\t\tSize of vertex buffer: " << data->size_of_vertex_data << std::endl;
				core::memory::Free(raw_data,core::memory::GENERIC_POOL);
			}
			break;
		}
		resources::__internal::finalizeResource(res);
		return DONE;
	}
};
}

Resource *VDataLoader::loadAsynchronous(const EString & ID)
{
	core::filesystem::Filesystem*	fs = core::EngineCore::getFilesystem();
	//Parse id
	size_t sem_pos = ID.find_last_of(':');
	EString	fn = ID.substr(sem_pos + 1);
	if(fs->fileExists(fn))
	{
		framework::VBOData* data	= new framework::VBOData;

		//std::cout << "Loading " << fn << std::endl;

		__internal::VDataLoaderTask* task = new __internal::VDataLoaderTask();
		task->res 		= resources::__internal::createResource(data);
		task->data 		= data;
		task->fs   		= fs;
		task->vboState 	= 0;
		task->fn		= fn;
		core::EngineCore::getTaskManager()->addAsynchronousTask(task);
		return task->res;
	}
	else
		throw ResourceException(EString("File ") + fn + " not found");
	return NULL;
}

}
}
}

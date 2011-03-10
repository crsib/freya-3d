#include "ShaderLoaderDriver.h"

#include "renderer/DriverSubsystems/Shader.h"

#include "core/memory/MemoryAllocator.h"

#include <vector>

#include "core/EStringList.h"

#include "core/filesystem/Filesystem.h"
#include "core/taskmanager/Task.h"
#include "core/taskmanager/TaskManager.h"

namespace resources
{

namespace __internal
{
template<>
resources::Resource* 	createResource(renderer::Shader*	resource)
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
resources::Resource* 	setResource(Resource* res,renderer::Shader*	resource)
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

namespace __internal
{
class ShaderTokenizer : public ::EngineSubsystem
{
	static void Tokenize(const EString& str,
			EStringList& tokens,
			const EString& delimiters = ":")
	{
		// Skip delimiters at beginning.
		EString::size_type lastPos = str.find_first_not_of(delimiters, 0);
		// Find first "non-delimiter".
		EString::size_type pos     = str.find_first_of(delimiters, lastPos);

		while (EString::npos != pos || EString::npos != lastPos)
		{
			// Found a token, add it to the vector.
			tokens.push_back(str.substr(lastPos, pos - lastPos));
			// Skip delimiters.  Note the "not_of"
			lastPos = str.find_first_not_of(delimiters, pos);
			// Find next "non-delimiter"
			pos = str.find_first_of(delimiters, lastPos);
		}
	}

public:
	ShaderTokenizer(const EString& id)
	{
		EStringList tocks;
		ShaderTokenizer::Tokenize(id,tocks);
		EString prefix = core::CoreInstance->getRenderingDriver()->getShaderAPIName();
		prefix = "/Shaders/" + prefix + "/";
		if(tocks[0] == "shader")
		{
			size_t i = 1;
			bool vert = false;
			bool frag = false;
			bool geom = false;
			for(i ; i < tocks.size(); i++)
			{
				if(tocks[i] == "vertex")
				{
					vert = true;
				}
				else if(tocks[i] == "fragment")
				{
					frag = true;
				}
				else if(tocks[i] == "geometry")
				{
					geom = true;
				}
				else
				{
					if(vert)
					{
						vert = false;
						if(tocks[i][0] == '/')
						{
							//This must be a full path
							if(core::CoreInstance->getFilesystem()->fileExists(tocks[i]))
							{
								VertexPathes.push_back(tocks[i]);
							}
							else
								throw resources::ResourceException(EString("File ") + tocks[i] + " not found");
						}
						else
						{
							EString path = prefix + "vertex/" + tocks[i];
							if(core::CoreInstance->getFilesystem()->fileExists(path))
							{
								VertexPathes.push_back(path);
							}
							else
								throw resources::ResourceException(EString("File ") + path + " not found");

						}

					} //if(vert)
					else if(frag)
					{
						frag = false;
						if(tocks[i][0] == '/')
						{
							//This must be a full path
							if(core::CoreInstance->getFilesystem()->fileExists(tocks[i]))
							{
								FragmentPathes.push_back(tocks[i]);
							}
							else
								throw resources::ResourceException(EString("File ") + tocks[i] + " not found");
						}
						else
						{
							EString path = prefix + "fragment/" + tocks[i];
							if(core::CoreInstance->getFilesystem()->fileExists(path))
							{
								FragmentPathes.push_back(path);
							}
							else
								throw resources::ResourceException(EString("File ") + path + " not found");

						}

					} //esle if frag
					else if(geom)
					{
						geom = false;
						if(tocks[i][0] == '/')
						{
							//This must be a full path
							if(core::CoreInstance->getFilesystem()->fileExists(tocks[i]))
							{
								GeometryPathes.push_back(tocks[i]);
							}
							else
								throw resources::ResourceException(EString("File ") + tocks[i] + " not found");
						}
						else
						{
							EString path = prefix + "geometry/" + tocks[i];
							if(core::CoreInstance->getFilesystem()->fileExists(path))
							{
								GeometryPathes.push_back(path);
							}
							else
								throw resources::ResourceException(EString("File ") + path + " not found");

						}

					}//else if(geom)
					else
					{
						//General case
						if(tocks[i][0] == '/')
							throw resources::ResourceException(EString("Malformed resource url ") + id);
						EString tmpv = prefix + "vertex/" + tocks[i] + ".vert";
						if(core::CoreInstance->getFilesystem()->fileExists(tmpv))
						{
							VertexPathes.push_back(tmpv);
							vert = true;
						}

						EString tmpf = prefix + "fragment/" + tocks[i] + ".frag";
						if(core::CoreInstance->getFilesystem()->fileExists(tmpf))
						{
							FragmentPathes.push_back(tmpf);
							vert = true;
						}

						EString tmpg = prefix + "geometry/" + tocks[i] + ".geom";
						if(core::CoreInstance->getFilesystem()->fileExists(tmpg))
						{
							GeometryPathes.push_back(tmpg);
							vert = true;
						}

						if(!vert)
							throw resources::ResourceException(EString("Neither of ") + tmpv + "/" + tmpf + "/" + tmpg + " found");

						vert = false;
					}
				}
			}
		}
		else
			throw resources::ResourceException(EString("Malformed resource url ") + id);
		NumFiles = VertexPathes.size() + FragmentPathes.size() + GeometryPathes.size();
		if(NumFiles == 0)
			throw resources::ResourceException(EString("Malformed resource url ") + id);
	}

	virtual ~ShaderTokenizer()
	{
	}

	int 			NumFiles;
	EStringList		VertexPathes;
	EStringList		FragmentPathes;
	EStringList		GeometryPathes;
};

class ShaderLoaderTask : public core::taskmanager::Task
{
public:
	ShaderTokenizer*	pathes;
	EStringList			VertSources;
	EStringList			FragSources;
	EStringList			GeomSources;
	Resource*			resource;
	unsigned			mode;

	ShaderLoaderTask()
	: mode (0)
	  {
	  }
	virtual ~ShaderLoaderTask()
	{
		delete pathes;
	}


	virtual int
	operator() ()
	{
		switch(mode)
		{
			case 0:
				for(size_t i = 0; i < pathes->VertexPathes.size(); i++)
				{
					size_t sz;
					char* file = reinterpret_cast<char*>(core::CoreInstance->getFilesystem()->read(pathes->VertexPathes[i],&sz));
					EString src(file,sz);
					VertSources.push_back(src);
					core::memory::Free(file,core::memory::GENERIC_POOL);
				}
				for(size_t i = 0; i < pathes->FragmentPathes.size(); i++)
				{
					size_t sz;
					char* file = reinterpret_cast<char*>(core::CoreInstance->getFilesystem()->read(pathes->FragmentPathes[i],&sz));
					EString src(file,sz);
					FragSources.push_back(src);
					core::memory::Free(file,core::memory::GENERIC_POOL);
				}
				for(size_t i = 0; i < pathes->GeometryPathes.size(); i++)
				{
					size_t sz;
					char* file = reinterpret_cast<char*>(core::CoreInstance->getFilesystem()->read(pathes->GeometryPathes[i],&sz));
					EString src(file,sz);
					GeomSources.push_back(src);
					core::memory::Free(file,core::memory::GENERIC_POOL);
				}
				mode = 1;
				return ShaderLoaderTask::MAIN_THREAD;
				break;
			case 1:
			{
				renderer::Shader* shader = core::CoreInstance->getRenderingDriver()->createShader();
				if(shader)
				{
					for(size_t i = 0; i < VertSources.size(); i++)
					{
						shader->addShader(renderer::ShaderType::VERTEX,VertSources[i]);
					}
					for(size_t i = 0; i < FragSources.size(); i++)
					{
						shader->addShader(renderer::ShaderType::FRAGMENT,FragSources[i]);
					}
					for(size_t i = 0; i < GeomSources.size(); i++)
					{
						shader->addShader(renderer::ShaderType::GEOMETRY,GeomSources[i]);
					}

					shader->link();
					if(!shader->isOk())
						throw resources::ResourceException("Failed to link shader resource");

					resources::__internal::setResource(resource,shader);
					resources::__internal::finalizeResource(resource);
					return ShaderLoaderTask::DONE;
				}
				else
					throw resources::ResourceException("Failed to create shader resource");
			}
			break;
		}
		return ShaderLoaderTask::DONE;
	}
};
}

ShaderLoaderDriver::ShaderLoaderDriver()
{

}

EString
ShaderLoaderDriver::id() const
{
	return "shader";
}

ShaderLoaderDriver::~ShaderLoaderDriver()
{
}



Resource *ShaderLoaderDriver::loadAsynchronous(const EString & ID)
{
	__internal::ShaderLoaderTask*	task = new __internal::ShaderLoaderTask;
	task->pathes	= new __internal::ShaderTokenizer(ID);
	task->resource  = resources::__internal::createResource((renderer::Shader*) NULL);
	core::CoreInstance->getTaskManager()->addAsynchronousTask(task);
	return task->resource;
}

void ShaderLoaderDriver::destroy(Resource *res)
{
	if(!res->ready())
		return; //It will never finish then))
	renderer::Shader* tex = res->get<renderer::Shader*>();
	core::CoreInstance->getRenderingDriver()->destroyShader(tex);
	resources::__internal::destroyResource(res);
}

bool
ShaderLoaderDriver::unique() const
{
	return true;
}

Resource *ShaderLoaderDriver::loadSynchronous(const EString & ID)
{
	resources::drivers::__std::__internal::ShaderTokenizer tok(ID);
	renderer::Shader* shader = core::CoreInstance->getRenderingDriver()->createShader();
	if(shader)
	{
		for(size_t i = 0; i < tok.VertexPathes.size(); i++)
		{
			size_t sz;
			char* file = reinterpret_cast<char*>(core::CoreInstance->getFilesystem()->read(tok.VertexPathes[i],&sz));
			EString src(file,sz);
			shader->addShader(renderer::ShaderType::VERTEX,src);
			core::memory::Free(file,core::memory::GENERIC_POOL);
		}
		for(size_t i = 0; i < tok.FragmentPathes.size(); i++)
		{
			size_t sz;
			char* file = reinterpret_cast<char*>(core::CoreInstance->getFilesystem()->read(tok.FragmentPathes[i],&sz));
			EString src(file,sz);
			shader->addShader(renderer::ShaderType::FRAGMENT,src);
			core::memory::Free(file,core::memory::GENERIC_POOL);
		}
		for(size_t i = 0; i < tok.GeometryPathes.size(); i++)
		{
			size_t sz;
			char* file = reinterpret_cast<char*>(core::CoreInstance->getFilesystem()->read(tok.GeometryPathes[i],&sz));
			EString src(file,sz);
			shader->addShader(renderer::ShaderType::GEOMETRY,src);
			core::memory::Free(file,core::memory::GENERIC_POOL);
		}

		shader->link();
		if(!shader->isOk())
			throw resources::ResourceException("Failed to link shader resource");

		Resource* res = resources::__internal::createResource(shader);
		resources::__internal::finalizeResource(res);
		return res;
	}
	else
		throw resources::ResourceException("Failed to create shader resource");
	return NULL;
}

}
}
}

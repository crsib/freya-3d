/*
 * FileLoaderDriver.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 9, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef FILELOADERDRIVER_H_
#define FILELOADERDRIVER_H_

/*
 *
 */
#include "resources/ResourceManagerDriver.h"
#include "core/drivermodel/DriverID.h"
#include "framework/Structures.h"
#include "core/EngineCore.h"
#include "core/filesystem/Filesystem.h"
#include "core/taskmanager/TaskManager.h"

namespace resources
{

namespace __internal
{
template<>
resources::Resource* 	createResource(framework::File*	resource)
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
resources::Resource* 	setResource(Resource* res,framework::File*	resource)
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

class FileLoaderDriver : public resources::ResourceManagerDriver
{
private:
	friend class FileLoaderDriverID;
	friend class resources::ResourceManager;
	FileLoaderDriver( );
	virtual ~FileLoaderDriver( );
public:
	virtual bool		unique() const;
	virtual EString 	id() const;
	virtual Resource*	loadSynchronous(const EString& ID);
	virtual Resource*	loadAsynchronous(const EString& ID);
	virtual void 		destroy(Resource* res);
};

class  FileLoaderDriverID : public core::drivermodel::DriverID
{
public:
	virtual core::drivermodel::Driver*		create() const
	{
		return new FileLoaderDriver;
	}
	virtual
	EString							id() const
	{
		return 	"file";
	}
};

}

}

}

inline
resources::drivers::__std::FileLoaderDriver::FileLoaderDriver()
{
}



inline
resources::drivers::__std::FileLoaderDriver::~FileLoaderDriver()
{
}



inline
bool resources::drivers::__std::FileLoaderDriver::unique() const
{
	return true;
}



inline
EString resources::drivers::__std::FileLoaderDriver::id() const
{
	return "file";
}



inline resources::Resource *resources::drivers::__std::FileLoaderDriver::loadSynchronous(const EString & ID)
{
	core::filesystem::Filesystem*	fs = core::EngineCore::getFilesystem();
	//Parse id
	size_t sem_pos = ID.find_last_of(':');
	EString	fn = ID.substr(sem_pos + 1);
	if(fs->fileExists(fn))
	{
		framework::FilePtr	file = new framework::File;
		file->data = fs->read(fn,&file->size);
		Resource* res = resources::__internal::createResource(file);
		resources::__internal::finalizeResource(res);
		return res;
	}
	else
		throw ResourceException(EString("File ") + fn + " not found");
	return NULL;
}

namespace resources
{
namespace drivers
{
namespace __std
{
namespace __internal
{
class FileLoaderTask : public core::taskmanager::Task
{
public:
	core::filesystem::Filesystem* fs;
	EString						  fn;
	resources::Resource*		  res;
	int operator()
					()
	{
		if(fs->fileExists(fn))
		{
			framework::FilePtr	file = new framework::File;
			file->data = fs->read(fn,&file->size);
			resources::__internal::setResource(res,file);
			resources::__internal::finalizeResource(res);
		}
		else
			throw ResourceException(EString("File ") + fn + " not found");
		return core::taskmanager::Task::DONE;
	}
};
}
}
}
}

inline resources::Resource *resources::drivers::__std::FileLoaderDriver::loadAsynchronous(const EString & ID)
{
	core::filesystem::Filesystem*	fs = core::EngineCore::getFilesystem();
		//Parse id
	size_t sem_pos = ID.find_last_of(':');
	EString	fn = ID.substr(sem_pos + 1);
	resources::drivers::__std::__internal::FileLoaderTask*	task = new resources::drivers::__std::__internal::FileLoaderTask;
	task->fn = fn;
	task->fs = fs;
	task->res = resources::__internal::createResource((framework::FilePtr)NULL);
	core::EngineCore::getTaskManager()->addAsynchronousTask(task);
	return task->res;
}




inline void resources::drivers::__std::FileLoaderDriver::destroy(resources::Resource *res)
{
	if(!res->ready())
		return; //It will never finish then))
	framework::File* tex = res->get<framework::File*>();
	core::memory::Free(tex->data,core::memory::GENERIC_POOL);
	resources::__internal::destroyResource(res);
}



#endif /* FILELOADERDRIVER_H_ */

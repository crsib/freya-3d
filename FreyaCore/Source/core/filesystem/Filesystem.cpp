#include "core/filesystem/FilesystemInternal.h"
#include <boost/filesystem.hpp>

#include "core/filesystem/FilesystemDriver.h"

#include "core/filesystem/FilesystemDriverFactory.h"

#include "core/EngineException.h"

#include "core/filesystem/FilesystemException.h"

#include "core/EngineCore.h"

#ifdef __APPLE__
#	include <CoreFoundation/CoreFoundation.h>
#endif

namespace core
{
namespace filesystem
{
//============================== Default constructor==============================

FilesystemInternal::FilesystemInternal()
{
	m_Factory = new FilesystemDriverFactory();
	m_Mutex = core::EngineCore::createMutex();
}

//==============================~Default constructor==============================

//============================== Derived constructors==============================

//==============================~Derived constructors==============================

//============================== Destructor==============================

FilesystemInternal::~FilesystemInternal()
{
	for(Drivers::iterator it = m_AllDrivers.begin();it != m_AllDrivers.end();++it)
	{
		delete static_cast<core::filesystem::FilesystemDriver*>(*it);
	}
	delete m_Factory;
	core::EngineCore::destroyMutex(m_Mutex);
}

//==============================~Destructor==============================

//============================== Method: mount==============================

/**********************************************************************
 * Mounts filesytem of type {type} to path {path}
 **********************************************************************/

void		FilesystemInternal::mount(const EString& type, const EString& path)
{
	core::drivermodel::Driver* d;
	try
	{
		synchronize(m_Mutex)
		{
			d =	m_Factory->createDriver(type);
		}
	}
	catch(const EngineException& ex)
	{
		throw;
	}
	if(d == NULL )
		throw FilesystemException(EString("Driver type \"") + type + "\" is not registered" );
	try
	{
#ifdef __APPLE__
		//First of all check, whether we have relative path
		if(path[0] != '/')
		{
			CFBundleRef mainBundle = CFBundleGetMainBundle();
			CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
			CFStringRef str = CFURLCopyFileSystemPath( resourcesURL, kCFURLPOSIXPathStyle );
			CFRelease(resourcesURL);
			char _path[PATH_MAX];

			CFStringGetCString( str, _path, FILENAME_MAX, kCFStringEncodingASCII );
			CFRelease(str);
			EString full_path = EString(_path) + "/Contents/Resources/" + path;
			synchronize(m_Mutex)
			{
				static_cast<FilesystemDriver*>(d)->setMountPoint(full_path);
			}
		}
#else
		synchronize(m_Mutex)
		{
			static_cast<FilesystemDriver*>(d)->setMountPoint(path);
		}
#endif	
	}
	catch(const EngineException& ex)
	{
		throw;
	}
	synchronize(m_Mutex)
	{
		m_AllDrivers.push_back(d);
		if(static_cast<FilesystemDriver*>(d)->isWritable())
			m_WritableDrivers.push_back(d);
		else
			m_ReadOnlyDrivers.push_back(d);
	}
}

//==============================~Method: mount==============================

//============================== Method: mountHome==============================

//============================== Method: list==============================

/*********************************************************************
 * Lists files on filesystems
 *********************************************************************/

EStringList		FilesystemInternal::list()
{
	EStringList list;
	for(Drivers::iterator it = m_AllDrivers.begin();it != m_AllDrivers.end();it++)
	{
		EStringList t = static_cast<core::filesystem::FilesystemDriver*>(*it)->list();
		list.insert(list.begin(),t.begin(),t.end());
	}

	return list;
}

//==============================~Method: list==============================

//============================== Method: makeDir==============================

/************************************************************************
 * Same as in driver
 ************************************************************************/

void		FilesystemInternal::makeDir(const  EString& path, int to)
{
	FilesystemDriver* d;
	if(static_cast<unsigned>(to) < m_AllDrivers.size())
	{
		d = static_cast<FilesystemDriver*>(m_AllDrivers[to]);
		if(!d->isWritable())
		{
			if(static_cast<unsigned>(to) < m_WritableDrivers.size())
			{
				d = static_cast<FilesystemDriver*>(m_WritableDrivers[to]);
			}
			else
			{
				throw FilesystemException("[makeDir] error: driver does not exists");
			}
		}
	}
	else
	{
		throw FilesystemException("[makeDir] error: driver does not exists");
	}
	try
	{
		synchronize(m_Mutex)
		{
			d->makeDir(path);
		}
	}
	catch(...)
	{
		throw;
	}
}

//==============================~Method: makeDir==============================

//============================== Method: dirExists==============================

bool		FilesystemInternal::dirExists(const EString& path)
{
	for(Drivers::iterator it = m_AllDrivers.begin();it != m_AllDrivers.end();it++)
	{
			if(static_cast<core::filesystem::FilesystemDriver*>(*it)->dirExists(path))
				return true;
	}
	return false;
}

//==============================~Method: dirExists==============================

//============================== Method: fileExists==============================

bool		FilesystemInternal::fileExists(const EString& path)
{
	for(Drivers::iterator it = m_AllDrivers.begin();it != m_AllDrivers.end();it++)
	{
			if(static_cast<core::filesystem::FilesystemDriver*>(*it)->fileExists(path))
				return true;
	}
	return false;
}

//==============================~Method: fileExists==============================

//============================== Method: read==============================

void*		FilesystemInternal::read(const EString& path,int from)
{
		if(from == -1)
			from = where(path);
		if(
				(static_cast<unsigned>(from) < m_AllDrivers.size())
				&& (static_cast<core::filesystem::FilesystemDriver*>(m_AllDrivers[from]))->fileExists(path)
		)
		{
			return static_cast<core::filesystem::FilesystemDriver*>(m_AllDrivers[from])->read(path);
		}
		else
		{
			throw core::filesystem::FilesystemException(EString("File ") + path + " not found" );
		}

	return NULL;
}

//==============================~Method: read==============================

//============================== Method: read==============================

void* 		FilesystemInternal::read(const EString& path, size_t* sz,int from)
{
		if(from == -1)
			from = where(path);
		if(
				(static_cast<unsigned>(from) < m_AllDrivers.size())
				&& (static_cast<core::filesystem::FilesystemDriver*>(m_AllDrivers[from]))->fileExists(path)
		)
		{
			return static_cast<core::filesystem::FilesystemDriver*>(m_AllDrivers[from])->read(path,sz);
		}
		else
		{
			throw core::filesystem::FilesystemException(EString("File ") + path + " not found" );
		}
	return NULL;
}

//==============================~Method: read==============================

//============================== Method: fileSize==============================

size_t		FilesystemInternal::fileSize(const EString& path)
{
		int id = where(path);
		if(id == -1)
			throw core::filesystem::FilesystemException(EString("File ") + path + " not found" );
		return static_cast<FilesystemDriver*>(m_AllDrivers[id])->fileSize(path);
}

//==============================~Method: fileSize==============================

//============================== Method: write==============================

void		FilesystemInternal::write(const EString& path, const void* buf, size_t sz, int to)
{
	FilesystemDriver* d;
	if(static_cast<unsigned>(to) < m_AllDrivers.size())
	{
		d = static_cast<FilesystemDriver*>(m_AllDrivers[to]);
		if(!d->isWritable())
		{
			if(static_cast<unsigned>(to) < m_WritableDrivers.size())
			{
				d = static_cast<FilesystemDriver*>(m_WritableDrivers[to]);
			}
			else
			{
				throw FilesystemException("[write] error: driver does not exists");
			}
		}
	}
	else
	{
		throw FilesystemException("[write] error: driver does not exists");
	}
	try
	{
			d->write(path,buf,sz);
	}
	catch(...)
	{
		throw;
	}
}

//==============================~Method: write==============================

void		FilesystemInternal::remove(const EString& path,int to)
{
	FilesystemDriver* d;

	if(static_cast<unsigned>(to) < m_AllDrivers.size())
	{
		d = static_cast<FilesystemDriver*>(m_AllDrivers[to]);
		if(!d->isWritable())
		{
			if(static_cast<unsigned>(to) < m_WritableDrivers.size())
			{
				d = static_cast<FilesystemDriver*>(m_WritableDrivers[to]);
			}
			else
			{
				throw FilesystemException("[remove] error: selected driver is not writable");
			}
		}
	}
	else
	{
		throw FilesystemException("[remove] error: writable driver does not exists");
	}
	try
	{
		d->remove(path);
	}
	catch(...)
	{
		throw;
	}
}

int			FilesystemInternal::where(const EString& path,FilesystemInternal::SearchMode mode)
{
	int id = -1;
	switch(mode)
	{
	case EVERYWHERE:
		for(Drivers::iterator it = m_AllDrivers.begin();it != m_AllDrivers.end();it++)
		{
			if(static_cast<core::filesystem::FilesystemDriver*>(*it)->fileExists(path))
			{
				id = it-m_AllDrivers.begin();
				break;
			}
		}
		break;
	case ON_WRITABLE:
		for(Drivers::iterator it = m_AllDrivers.begin();it != m_WritableDrivers.end();it++)
		{
			if(static_cast<core::filesystem::FilesystemDriver*>(*it)->fileExists(path))
			{
				id = std::find(m_AllDrivers.begin(),m_AllDrivers.end(),*it) - m_AllDrivers.begin();
				break;
			}
		}
		break;
	case ON_READ_ONLY:
		for(Drivers::iterator it = m_ReadOnlyDrivers.begin();it != m_ReadOnlyDrivers.end();it++)
		{
			if(static_cast<core::filesystem::FilesystemDriver*>(*it)->fileExists(path))
			{
				id = std::find(m_AllDrivers.begin(),m_AllDrivers.end(),*it) - m_AllDrivers.begin();
				break;
			}
		}
		break;
	}
	return id;
}

void	FilesystemInternal::registerDriver(core::drivermodel::DriverID* driverID)
{
	m_Factory->registerDriver(driverID);
}

} //End of FilesystemInternal namespace
} //End of core namespace


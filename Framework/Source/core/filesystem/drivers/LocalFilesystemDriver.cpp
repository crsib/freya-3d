#include "core/filesystem/drivers/LocalFilesystemDriver.h"
#include "core/filesystem/FilesystemException.h"
#include <boost/filesystem/fstream.hpp>
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <iostream>
using std::cout;
using std::endl;

namespace core
{
namespace filesystem
{
namespace drivers
{
//============================== Derived constructors==============================

//==============================~Derived constructors==============================

//============================== Destructor==============================

LocalFilesystemDriver::~LocalFilesystemDriver()
{
	//Destructor stub
}

//==============================~Destructor==============================

//============================== Method: setMountPoint==============================

void		LocalFilesystemDriver::setMountPoint(const EString& path)
{
	m_MountPoint = fs::system_complete(fs::path(path.c_str()));
	if(!fs::exists(m_MountPoint))
		throw core::filesystem::FilesystemException(EString("Local filesystem driver error: Failed to mount driver as the mount point ") + path + (" does not exists"));
	if(!fs::is_directory(m_MountPoint))
		throw core::filesystem::FilesystemException(EString("Local filesystem driver error: Failed to mount driver as the mount point ") + path + (" is a not a directory"));
	//throw core::filesystem::FilesystemException("Done");
}

//==============================~Method: setMountPoint==============================

//============================== Method: id==============================

EString		LocalFilesystemDriver::id() const
{
	return EString("local");
}

//==============================~Method: id==============================

//============================== Method: isWritable==============================

bool		LocalFilesystemDriver::isWritable()
{
	return true;
}

//==============================~Method: isWritable==============================

//============================== Method: list==============================

//Stub recursive method
void	_list(EStringList& list,const fs::path& path,const EString& root)
{
	fs::directory_iterator end_itr;
	for ( fs::directory_iterator dir_itr( path );
	dir_itr != end_itr;
	++dir_itr )
	{
		try
		{
			if ( fs::is_regular_file( dir_itr->status() ) )
			{
				list.push_back(root +EString(dir_itr->path().filename().c_str()));
			}
			else if(fs::is_directory(dir_itr->status()))
			{
				list.push_back(EString(root + dir_itr->path().filename().c_str()));
				_list(list,dir_itr->path(),root + dir_itr->path().filename().c_str() + "/");
			}
		}
		catch ( const std::exception & ex )
		{
			throw core::filesystem::FilesystemException( EString(dir_itr->path().filename().c_str()) + " " + ex.what());
		}
	}
}

EStringList		LocalFilesystemDriver::list()
{
	EStringList list;
	_list(list,m_MountPoint,"/");
	return list;
}

//==============================~Method: list==============================

//============================== Method: makeDir==============================

void		LocalFilesystemDriver::makeDir(const EString& path)
{
	fs::path p,t = m_MountPoint / path.c_str();
	fs::path::iterator it;
	for(it = t.begin();it != t.end();++it)
	{
		p /= *it;
		if(fs::exists(p)&&!fs::is_directory(p))
			throw core::filesystem::FilesystemException("Failed to create a directory in filesystem as path is incorrect");
		if(!fs::exists(p))
		{
			try
			{
				fs::create_directory(p);
			}
			catch(const std::exception & ex)
			{
				throw core::filesystem::FilesystemException(EString("Local filesystem error: ") + ex.what());
			}
		}
	}
}

//==============================~Method: makeDir==============================

//============================== Method: dirExists==============================

bool		LocalFilesystemDriver::dirExists(const EString& path)
{
	fs::path p(m_MountPoint / path.c_str());
	return fs::exists(p) && fs::is_directory(p);
}

//==============================~Method: dirExists==============================

//============================== Method: fileExists==============================

bool		LocalFilesystemDriver::fileExists(const EString& path)
{
	fs::path p(m_MountPoint / path.c_str());
	return fs::exists(p) && !fs::is_directory(p);
}

//==============================~Method: fileExists==============================

//============================== Method: fileSize==============================

size_t		LocalFilesystemDriver::fileSize(const EString& path)
{
	fs::path p(m_MountPoint / path.c_str());
	if(fs::exists(p) && !fs::is_directory(p))
		return fs::file_size(p);
	else
		return 0;
}

//==============================~Method: fileSize==============================

//============================== Method: read==============================

void*		LocalFilesystemDriver::read(const EString& path)
{
	fs::path p(m_MountPoint / path.c_str());
	if(!fs::exists(p))
		throw core::filesystem::FilesystemException(EString("Failed to load file ") + path + " as it is not present in the filesystem");
	if(!fs::is_regular(p) || fs::is_empty(p))
		throw core::filesystem::FilesystemException(EString("Failed to load file ") + path + " as it is not a regular file");
	size_t sz = fs::file_size(p);
	void* _p = core::memory::Allocate(sz,core::memory::GENERIC_POOL);
	if(_p == NULL)
		throw core::filesystem::FilesystemException(EString("Failed to allocate memory for loading ") + path);
	//Ok, finaly, we have checked that the file is correct and allocated memory for it
	fs::fstream stream;
	stream.exceptions ( fs::fstream::eofbit | fs::fstream::failbit | fs::fstream::badbit );
	try
	{
		stream.open(p,std::ios_base::in | std::ios_base::binary);
		stream.read(reinterpret_cast<char*>(_p),sz);
		stream.close();
	}
	//catch(const fs::fstream::failure& ex)
	catch(const std::exception& ex)
	{
		throw core::filesystem::FilesystemException(EString("I/O error while reading a file ") + path + ": " + ex.what());
	}
	catch(...)
	{
		throw core::filesystem::FilesystemException();
	}
	return _p;
}
//==============================~Method: read==============================

//============================== Method: read==============================

void*		LocalFilesystemDriver::read(const EString& path,size_t* sz)
{
	fs::path p(m_MountPoint / path.c_str());
	if(!fs::exists(p))
		throw core::filesystem::FilesystemException(EString("Failed to load file ") + path + " as it is not present in the filesystem");
	if(!fs::is_regular(p) || fs::is_empty(p))
		throw core::filesystem::FilesystemException(EString("Failed to load file ") + path + " as it is not a regular file");
	*sz = fs::file_size(p);
	void* _p = core::memory::Allocate(*sz,core::memory::GENERIC_POOL);
	if(_p == NULL)
		throw core::filesystem::FilesystemException(EString("Failed to allocate memory for loading ") + path);
	//Ok, finaly, we have checked that the file is correct and allocated memory for it
	fs::fstream stream;
	stream.exceptions ( fs::fstream::eofbit | fs::fstream::failbit | fs::fstream::badbit );
	try
	{
		stream.open(p,std::ios_base::in | std::ios_base::binary);
		stream.read(reinterpret_cast<char*>(_p),*sz);
		stream.close();
	}
	catch(const fs::fstream::failure& ex)
	{
		throw core::filesystem::FilesystemException(EString("I/O error while reading a file ") + path + ": " + ex.what());
	}
	return _p;
}

//==============================~Method: read==============================

//============================== Method: write==============================

void		LocalFilesystemDriver::write(const EString& path,const void* buf,size_t sz)
{
	fs::path p(m_MountPoint / path.c_str());
	if((buf != NULL) && (sz > 0))
	{
		if(!fs::exists(p.parent_path()))
		{
			fs::path internal(path.c_str());
			makeDir(EString(internal.parent_path().string().c_str()));
		}
		fs::fstream stream;
		stream.exceptions ( fs::fstream::eofbit | fs::fstream::failbit | fs::fstream::badbit );
		try
		{
			stream.open(p,std::ios_base::out | std::ios_base::binary);
			stream.write(reinterpret_cast<const char*>(buf),sz);
			stream.close();
		}
		catch(const fs::fstream::failure& ex)
		{
			throw core::filesystem::FilesystemException(EString("I/O error while writing a file ") + path + ": " + ex.what());
		}
	}
}

//==============================~Method: write==============================

//============================== Method: remove=============================

void		LocalFilesystemDriver::remove(const EString& path)
{
	fs::path p(m_MountPoint / path.c_str());
	fs::remove_all(p);
}

//==============================~Method: remove=============================

} //End of drivers namespace
} //End of filesystem namespace
} //End of core namespace

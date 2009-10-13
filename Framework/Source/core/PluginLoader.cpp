#include "core/PluginLoader.h"
#include "core/drivermodel/Driver.h"
#include "core/drivermodel/DriverID.h"
#include "core/PluginCore.h"
#include "core/EngineCore.h"
#include "core/EngineSubsystem.h"
#include "core/EngineException.h"
#include "core/memory/MemoryAllocator.h"
#include "core/filesystem/Filesystem.h"
#include "resources/ResourceManager.h"
#include <map>
#include <vector>

#include <iostream>

//For dlopen
#ifdef _WIN32 
#define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#else
#	include <dlfcn.h>
#endif

#ifdef USE_BOOST_FILESYSTEM
#	include <boost/filesystem.hpp>
#endif

void load_static_plugins();

namespace core
{
	namespace memory
	{
		typedef void* (*ALLOCATE)(size_t,unsigned);
		typedef void  (*FREE)(void*,unsigned);
	}		
	namespace __internal
	{
		typedef unsigned (*DRIVERSCOUNTPTR)();
		typedef  unsigned (*DRIVERTYPEPTR)(unsigned);
		typedef void 	 (*SETMEMORYALLOCATORPTR)(core::memory::ALLOCATE,core::memory::FREE,core::PluginCore*);
		typedef const char* (*DRIVERNAMEPTR)(unsigned);
		typedef core::drivermodel::Driver* (*CREATEDRIVERPTR)(const char * );
		
		struct SOProcs : public EngineSubsystem
		{
			SOProcs() :  drivers_count(0), driver_type(0),set_memory_allocator(0),driver_name(0),create_driver(0)
			{
			}
			DRIVERSCOUNTPTR			drivers_count;
			DRIVERTYPEPTR			driver_type;
			SETMEMORYALLOCATORPTR	set_memory_allocator;
			DRIVERNAMEPTR			driver_name;
			CREATEDRIVERPTR			create_driver;
		};
		
		struct SOID : public EngineSubsystem
		{
			SOID() : path(""), loaded(0),handle(0)
			{
			}

			EString															path;
			SOProcs															procs;
			unsigned														loaded;
			void*															handle;
		};
		
		class _SOLibraryCache : public EngineSubsystem
		{
		public:
			static _SOLibraryCache* instance;
			//typedef std::map<EString, SOID*, std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString, SOID*> > > SOCache;
			//SOCache cache;
			std::vector<SOID*,core::memory::MemoryAllocator<SOID*> >	SOInfo;
		};
		
		_SOLibraryCache*	_SOLibraryCache::instance;
		
		//Crossplatform way to load library
		void*		loadSO(const char* so_name)
		{
#ifdef _WIN32
			HMODULE	so = LoadLibraryA(so_name);
			if(so)
				SetLastError( 0 );
				
			return reinterpret_cast<void*> (so);
#else
			return dlopen(so_name,RTLD_LOCAL | RTLD_LAZY);
#endif
		}
		
		void		freeSO(void* so)
		{
#ifdef _WIN32	
			FreeLibrary(reinterpret_cast<HMODULE>(so));
#else
			dlclose(so);
#endif
		}
		
		template<typename T> T soSym(void* so,const char* name)
		{
#ifdef _WIN32	
			return reinterpret_cast<T> (GetProcAddress(reinterpret_cast<HMODULE> (so),name));
#else
			return reinterpret_cast<T> (dlsym(so,name));
#endif			
		}
		
		//Fake driver id
		class FakeDriverID : public core::drivermodel::DriverID
		{
			EString m_Name;
			SOID*	soid;
		public:
			explicit FakeDriverID(SOID* _soid,const EString& name)
			{
				m_Name	= name;
				soid	= _soid;
				//m_DriverType = driverType;
			}
			virtual ~FakeDriverID(){}
			virtual core::drivermodel::Driver*		create() const
			{
				if(soid->loaded == 0)
				{
					soid->handle = __internal::loadSO(soid->path.c_str());
					if(soid->handle == NULL)
					{
#ifndef	_WIN32
						std::cout << dlerror() << std::endl;
#endif
						throw EngineException();//TODO: Replace tis wit a more apropriate exception
					}
					//Get pointers
					
					soid->procs.set_memory_allocator = __internal::soSym<__internal::SETMEMORYALLOCATORPTR>(soid->handle,"set_memory_allocator");
					if(soid->procs.set_memory_allocator == NULL)
					{
#ifndef	_WIN32
						std::cout << dlerror() << std::endl;
#endif
						throw EngineException();//TODO: Replace this wit a more apropriate exception						
					}
					
					soid->procs.create_driver = __internal::soSym<__internal::CREATEDRIVERPTR>(soid->handle,"create_driver");
					if(soid->procs.set_memory_allocator == NULL)
					{
#ifndef	_WIN32
						std::cout << dlerror() << std::endl;
#endif
						throw EngineException();//TODO: Replace this wit a more apropriate exception						
					}
					
					soid->loaded = 1;
					
					//Run desired methods
					(soid->procs.set_memory_allocator)(core::memory::Allocate,core::memory::Free,core::EngineCore::getPluginCore());

				}
				//if(m_DriverType == core::drivermodel::RENDERER)
				return (soid->procs.create_driver)(m_Name.c_str());
			}
			virtual EString							id() const
			{
				return m_Name;
			}
		};
	}
	
	PluginLoader::PluginLoader(int arcC,char** argV)
	{
		::load_static_plugins();
#ifdef USE_BOOST_FILESYSTEM
#ifdef _WIN32
		std::string soext(".dll");
#else 
		std::string soext(".so");
#endif
		boost::filesystem::path		exePath ( argV [0] );
		exePath.remove_filename();
#ifdef __APPLE__
		exePath /= "../Plugins";
#else
		exePath /= "Plugins";
#endif
		if(boost::filesystem::is_directory(exePath))
		{
			__internal::_SOLibraryCache::instance	=	new __internal::_SOLibraryCache;
			for(boost::filesystem::recursive_directory_iterator it(exePath); it != boost::filesystem::recursive_directory_iterator(); it++)
			{
				if (boost::filesystem::is_regular_file(it->status()))
				{
					std::string tmp = it->path().extension();
					std::transform(tmp.begin(), tmp.end(),tmp.begin(), tolower);
					if(tmp == soext)
					{
						tmp = it->path().file_string();
						const char* lib_path = tmp.c_str(); 
						std::cout << "Found plugin library: " << lib_path << std::endl;
						//Create a cahche entry
						__internal::SOID*	soid = new __internal::SOID;
						soid->path = lib_path;
						soid->handle = __internal::loadSO(lib_path);
						if(soid->handle == NULL)
						{
#ifndef	_WIN32
							std::cout << dlerror() << std::endl;
#endif
							throw EngineException();//TODO: Replace tis wit a more apropriate exception
						}
						//Get pointers
						soid->procs.drivers_count = __internal::soSym<__internal::DRIVERSCOUNTPTR>(soid->handle,"drivers_count");
						if(soid->procs.drivers_count == NULL)
						{
#ifndef	_WIN32
							std::cout << dlerror() << std::endl;
#endif
							throw EngineException();//TODO: Replace tis wit a more apropriate exception						
						}
						
						soid->procs.driver_name = __internal::soSym<__internal::DRIVERNAMEPTR>(soid->handle,"driver_name");
						if(soid->procs.driver_name == NULL)
						{
#ifndef	_WIN32
							std::cout << dlerror() << std::endl;
#endif
							throw EngineException();//TODO: Replace tis wit a more apropriate exception						
						}
						
						soid->procs.set_memory_allocator = __internal::soSym<__internal::SETMEMORYALLOCATORPTR>(soid->handle,"set_memory_allocator");
						if(soid->procs.set_memory_allocator == NULL)
						{
#ifndef	_WIN32
							std::cout << dlerror() << std::endl;
#endif
							throw EngineException();//TODO: Replace tis wit a more apropriate exception						
						}
						
						soid->procs.driver_type = __internal::soSym<__internal::DRIVERTYPEPTR>(soid->handle,"driver_type");
						if(soid->procs.driver_name == NULL)
						{
#ifndef	_WIN32
							std::cout << dlerror() << std::endl;
#endif
							throw EngineException();//TODO: Replace tis wit a more apropriate exception						
						}
						
						
						//Run desired methods
						(soid->procs.set_memory_allocator)(core::memory::Allocate,core::memory::Free,core::EngineCore::getPluginCore());
						unsigned lib_count = (soid->procs.drivers_count)();
						for(unsigned i = 0; i < lib_count; i++)
						{
							EString driverID = EString(soid->procs.driver_name(i));
							std::cout << "|--implements: "<< driverID << std::endl;
							//Create fake driver id
							__internal::FakeDriverID*		drvid = new __internal::FakeDriverID(soid,driverID);
							switch((soid->procs.driver_type)(i))
							{
								case core::drivermodel::FILESYSTEM:
									core::EngineCore::getFilesystem()->registerDriver(drvid);
									break;
								case core::drivermodel::RENDERER:
									core::EngineCore::registerRenderingDriver(drvid);
									break;
								case core::drivermodel::RESOURCE:
									core::EngineCore::getResourceManager()->registerDriver(drvid);
									break;
								case core::drivermodel::WINDOWMANAGER:
									core::EngineCore::registerWindowManager(drvid);
									break;
								case core::drivermodel::INPUT:
									
									break;

							}
						}
						if(soid->loaded == 0)
						{
							__internal::freeSO(soid->handle);
							soid->loaded = 0;
						}
						//Add SO to so info cache
						__internal::_SOLibraryCache::instance->SOInfo.push_back(soid);
					}
				}
			}
		}
		else
		{
			std::cout << "Plugins directory is not found" << std::endl;
		}
		   
		   
#else
#error "Other methods are not implemented"
#endif

	}
	
	PluginLoader::~PluginLoader()
	{
		//Free loaded libraries
		for(unsigned i = 0; i < __internal::_SOLibraryCache::instance->SOInfo.size();i++)
		{
			__internal::SOID* soid = __internal::_SOLibraryCache::instance->SOInfo[i];
			if(soid->loaded)
			{
				std::cout << "Freeing plugin " << soid->path << std::endl; 
				__internal::freeSO(soid->handle);
			}
			delete soid;
		}
		delete __internal::_SOLibraryCache::instance;
	}
}

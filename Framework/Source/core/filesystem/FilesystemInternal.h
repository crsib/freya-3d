#ifndef _FilesystemInternal_H_
#define _FilesystemInternal_H_

#include "core/EngineSubsystem.h"
#include "core/EString.h"
#include "core/EStringList.h"
#include "core/filesystem/Filesystem.h"
#include <vector>
#include "core/multithreading/Lock.h"

#ifdef _MSC_VER
#	pragma warning(disable:4275)
#	pragma warning(disable:4251)
#endif

namespace core
{
namespace drivermodel
{
class Driver;
class DriverID;
}
class EngineCore;
//!This namespace contains everything related to FilesystemInternal access
namespace filesystem
{
class FilesystemDriverFactory;
//!This is a FilesystemInternal representation class
/*!
 * This class implements Freya internal FilesystemInternal representation.
 * The major idea is that internally the Freya FilesystemInternal looks like homogeneous UNIX-like fs with some root directory.
 * Some kind of FilesystemInternal, managed by its driver can be easily mounted to the root directory.
 * File access afterwards is done using internal path, which makes it more portable.
 * Please note, that different drivers can contain files with the same internal path. FilesystemInternal uses FIFO method of determining which file to access.
 * FIFO access can be more or less overridden using FilesystemInternal::where
 * Please note, that FilesystemInternal class can be only created within EngineCore initialization process
 */
class FilesystemInternal : virtual public core::filesystem::Filesystem
{
	friend class core::EngineCore;
protected:
	FilesystemInternal();
	virtual ~FilesystemInternal();
public:
	//!Mounts filesytem of type {type} to path {path}
	/*!
	 * This method is used to mount driver described by id {type} assigned with path {path} to root directory.
	 * \param type is a FilesystemInternal driver id string
	 * \param path is a path to assign to driver
	 * \throw FilesystemInternalException if driver is not registered or for any reason could not be assigned with path
	 */
	virtual void mount(const EString& type, const EString& path = EString());

	//!Lists files on FilesystemInternal
	/*!
	 * Lists all files on all registered drivers
	 * \return List of all files
	 */
	virtual EStringList list();

	//Same as in driver
	//!Create a directory
	/*!
	 * Creates a directory in internal FilesystemInternal. Physically, directory is created on first writable driver
	 * \param path contains full internal path to create
	 * \param to specifies driver number to write to
	 * \throw FilesystemInternalException on any error (such as no writable driver is mounted)
	 */
	virtual void makeDir(const  EString& path, int to = 0);
	//!Check that directory exists
	/*!
	 * Checks that internal directory is present on any driver.
	 * All parent directories needed will be also created
	 * \param path contains full internal path to check for
	 * \return true if specified directory exists, false otherwise
	 */
	virtual bool dirExists(const EString& path);
	//!Check that file exists
	/*!
	 * Checks that file is present on any driver
	 * \param path contains full internal path to check for
	 * \return true if specified directory exists, false otherwise
	 */
	virtual bool fileExists(const EString& path);
	//!Read file
	/*!
	 * Reads file from {path} using {from} driver. In current implementation stream reading is not supported.
	 * \param path is an internal path, that describes file location
	 * \param from is ID of a driver to read file from or -1 if FIFO method is used [default]
	 * \throw FilesystemInternalException if file is not found
	 * \return Address of memory block containing file (caller is responsible of future memory management)
	 */
	virtual void* read(const EString& path,int from = -1);
	//!Read file (overloaded version)
	/*!
	 * Reads file from {path} using {from} driver. In current implementation stream reading is not supported.
	 * \param path is an internal path, that describes file location
	 * \param sz is a pointer to size_t type. After return, it contains size of file read
	 * \param from is ID of a driver to read file from or -1 if FIFO method is used [default]
	 * \throw FilesystemInternalException if file is not found or reading failed
	 * \return Address of memory block containing file (caller is responsible of future memory management)
	 */
	virtual void*  read(const EString& path, size_t* sz,int from = -1);
	//!Get file size
	/*!
	 * Returns a size of file decribed by {path}. This method only uses FIFO method of resolving conflicts.
	 * To override it one can use overloaded version of read file
	 * \param path is an internal path, that describes file location or reading failed
	 * \throw FilesystemInternalException if file is not found
	 * \return Size of file demanded
	 */
	virtual size_t fileSize(const EString& path);
	//! Write file
	/*!
	 * Writes a file to a writable driver
	 * \param path is an internal path, that describes file location
	 * \param buf is a pointer to memory buffer to be written
	 * \param sz is number of bytes to be written
	 * \param to is an global ID of an writable driver. 0 means writing on first writable driver
	 * \throw FilesystemInternalException  on either there are no writable drivers, either selected driver is not writable, either writing failed
	 */
	virtual void write(const EString& path, const void* buf, size_t sz, int to = 0);
	//!Remove FilesystemInternal object (file or directory)
	/*!
	 * Removes filesytem object described by path from file system (with all ancestors if needed)
	 * \param path is an internal path, that describes location of an object to be removed
	 * \param from is an global ID of an writable driver. 0 means writing on first writable driver
	 * \throw FilesystemInternalException  on either there are no writable drivers, either selected driver is not writable, either removing failed
	 */
	virtual void remove(const EString& path,int from = 0);

	
	//Returns -1 if file is not found on the FilesystemInternal
	//!Get global driver ID
	/*!
	 * \param path is an internal path, that describes location of an object to be searched
	 * \param mode describes wich mode to use while searching
	 * \return Global ID of a driver to search on
	 */
	virtual int where(const EString& path,SearchMode mode = core::filesystem::Filesystem::EVERYWHERE);

	//!Register FilesystemInternal driver
	/*!
	 * Registers user-written FilesystemInternal driver to be used with core::FilesystemInternal class
	 * \param driverID is an ID of a driver to be registered
	 */
	virtual void	registerDriver(core::drivermodel::DriverID* driverID);
private:
	typedef std::vector<core::drivermodel::Driver*, core::memory::MemoryAllocator<core::drivermodel::Driver*> > Drivers;

	Drivers 					m_AllDrivers;
	Drivers						m_ReadOnlyDrivers;
	Drivers						m_WritableDrivers;

	FilesystemDriverFactory*		m_Factory;
	core::multithreading::Mutex*	m_Mutex;
}; //End of FilesystemInternal class

} //End of FilesystemInternal namespace
} //End of core namespace
#endif //End of _FilesystemInternal_H_

#ifndef _FILESYSTEMDRIVER_H_
#define _FILESYSTEMDRIVER_H_

#include "core/drivermodel/Driver.h"
#include "core/EString.h"
#include "core/EStringList.h"

namespace core
{
namespace filesystem
{
//!This class is an interface to all filesystem drivers. Please not, that driver instancing is provided by FilesystemDriverFactory (thus, only by Filesystem)
class FilesystemDriver : public core::drivermodel::Driver
{
	friend class Filesystem;
protected:
	//Mount and initializes file system at mount point
	//Trows an exception on failure
	//!Set the mount point for a driver
	/*!
	 * Sets the mount point to driver and initializes it
	 * \param path is a reall platform specific path that can be used to mount driver
	 * \throw FilesystemException on any error occurred while mounting
	 */
	virtual void 	setMountPoint(const EString& path) = 0;
public:
	//!Get driver id
	/*!
	 * Gets driver specific id.
	 * \return Driver specific id
	 */
	virtual EString id() const = 0;

	//This method returns true, if writing is supported to this kind of filesystem
	//!Check for ability to perform write operation
	/*!
	 * \return true if writing is supported, false otherwise
	 */
	virtual bool isWritable() = 0;

	//!Lists files on driver
	/*!
	 * Lists all files registered on drivers
	 * \return List of all files
	 */
	virtual EStringList list() = 0;

	//!Create a directory
	/*!
	 * Creates a directory in internal filesystem. Physically, directory is created on first writable driver
	 * \param path contains full internal path to create
	 * \throw FilesystemException on any error
	 */
	virtual void makeDir(const EString& path) = 0;

	//!Check that directory exists
	/*!
	 * Checks that internal directory is present on the driver.
	 * All parent directories needed will be also created
	 * \param path contains full internal path to check for
	 * \return true if specified directory exists, false otherwise
	 */
	virtual bool dirExists(const EString& path) = 0;

	//!Check that file exists
	/*!
	 * Checks that file is present on the driver
	 * \param path contains full internal path to check for
	 * \return true if specified directory exists, false otherwise
	 */
	virtual bool fileExists(const EString& path) = 0;

	//!Get file size
	/*!
	 * Returns a size of file decribed by {path}.
	 * To override it one can use overloaded version of read file
	 * \param path is an internal path, that describes file location or reading failed
	 * \return Size of file demanded or 0 if file is not found
	 */
	virtual size_t fileSize(const EString& path) = 0;

	//!Read file
	/*!
	 * Reads file from {path}. In current implementation stream reading is not supported.
	 * \param path is an internal path, that describes file location
	 * \throw FilesystemException if file is not found or reading failed
	 * \return Address of memory block containing file (caller is responsible of future memory management)
	 */
	virtual void* read(const EString& path) = 0;

	//!Read file (overloaded version)
	/*!
	 * Reads file from {path}. In current implementation stream reading is not supported.
	 * \param path is an internal path, that describes file location
	 * \param sz is a pointer to size_t type. After return, it contains size of file read
	 * \throw FilesystemException if file is not found or reading failed
	 * \return Address of memory block containing file (caller is responsible of future memory management)
	 */
	virtual void* read(const EString& path, size_t* sz) = 0;

	//! Write file
	/*!
	 * Writes a file to a writable driver
	 * \param path is an internal path, that describes file location
	 * \param buf is a pointer to memory buffer to be written
	 * \param sz is number of bytes to be written
	 * \throw FilesystemException  on either selected driver is not writable, either writing failed
	 */
	virtual void write(const EString& path, const void* buf, size_t sz) = 0;

	//!Remove filesystem object (file or directory)
	/*!
	 * Removes filesytem object described by path from file system (with all ancestors if needed)
	 * \param path is an internal path, that describes location of an object to be removed
	 * \throw FilesystemException  on either selected driver is not writable, either removing failed
	 */
	virtual void remove(const EString& path) = 0;

}; //End of FilesystemDriver class

} //End of filesystem namespace
} //End of core namespace
#endif //End of _FILESYSTEMDRIVER_H_

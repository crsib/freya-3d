#Filesystem plugins

IF(BUILD_LOCAL_FILESYSTEM_DRIVER)
	SET(Boost_USE_MULTITHREADED YES)
	FIND_PACKAGE ( BoostSTLPort 1.40 REQUIRED COMPONENTS system filesystem )
	MESSAGE ("Boost flags for BoostFilesystemDriver \n\tinclude: ${Boost_INCLUDE_DIRS} \n\tlibs: ${Boost_LIBRARIES}" )
	INCLUDE_DIRECTORIES ( ${Boost_INCLUDE_DIRS} ../../..)
	
	SET(LOCAL_FILESYSTEM_DRIVER_SOURCE
	AppHomeFilesystem.h
	AppHomeFilesystem.cpp
	CurrentFilesystem.cpp
	CurrentFilesystem.h
	LocalFilesystemDriver.cpp
	LocalFilesystemDriver.h
	ids/AppHomeFilesystemDriverID.h
	ids/CurrentFilesystemDriverID.h
	ids/LocalFilesystemDriverID.h
	)
	
	
	IF(BUILD_SHARED_LOCAL_FILESYSTEM_DRIVER)
		MESSAGE("Building shared BoostFilesystemDriver")
		ADD_DEFINITIONS(-D_FREYA_SHARED_PLUGIN)
		ADD_LIBRARY(BoostFilesystemDriver MODULE ${LOCAL_FILESYSTEM_DRIVER_SOURCE} ids/LocalFilesystemDriverSharedBuild.cpp ../boost_stlport_fix.cpp)
		TARGET_LINK_LIBRARIES( BoostFilesystemDriver ${Boost_LIBRARIES} ${GLOBAL_LINK_LIBRARIES} )
		SET_TARGET_PROPERTIES ( BoostFilesystemDriver PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Plugins)
		AddPlugin( BoostFilesystemDriver )
	ELSE(BUILD_SHARED_LOCAL_FILESYSTEM_DRIVER)
		ADD_LIBRARY(BoostFilesystemDriver STATIC ${LOCAL_FILESYSTEM_DRIVER_SOURCE} ids/LocalFilesystemDriverStaticBuild.cpp)
		SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} BoostFilesystemDriver ${Boost_LIBRARIES} )
		SET_PROPERTY( GLOBAL PROPERTY FREYA_CORE_LINK_LIBRARIES_GLOBAL ${FREYA_CORE_LINK_LIBRARIES})
		AddFilesystemPlugin( BoostFilesystemDriver )
	ENDIF(BUILD_SHARED_LOCAL_FILESYSTEM_DRIVER)
ENDIF(BUILD_LOCAL_FILESYSTEM_DRIVER)

IF(BUILD_LZMA_FILESYSTEM_DRIVER)
	SET(LZMA_FILESYSTEM_DRIVER_SOURCE
		3party/7zip/7zAlloc.h
		3party/7zip/7zBuffer.h
		3party/7zip/7zCrc.h
		3party/7zip/7zDecode.h
		3party/7zip/7zExtract.h
		3party/7zip/7zHeader.h
		3party/7zip/7zIn.h
		3party/7zip/7zItem.h
		3party/7zip/7zMethodID.h
		3party/7zip/7zTypes.h
		3party/7zip/LzmaDecode.h
		3party/7zip/LzmaStateDecode.h
		3party/7zip/LzmaTypes.h
		3party/7zip/7zAlloc.cpp
		3party/7zip/7zBuffer.cpp
		3party/7zip/7zCrc.cpp
		3party/7zip/7zDecode.cpp
		3party/7zip/7zExtract.cpp
		3party/7zip/7zHeader.cpp
		3party/7zip/7zIn.cpp
		3party/7zip/7zItem.cpp
		3party/7zip/7zMethodID.cpp
		3party/7zip/LzmaDecode.cpp
		ids/LzmaFilesystemDriverID.h
		LzmaDriver.h
		LzmaDriver.cpp
	)
	
	IF(BUILD_SHARED_LZMA_FILESYSTEM_DRIVER)
		MESSAGE("Building shared BoostFilesystemDriver")
		ADD_DEFINITIONS(-D_FREYA_SHARED_PLUGIN)
		ADD_LIBRARY(LzmaFilesystemDriver MODULE ${LZMA_FILESYSTEM_DRIVER_SOURCE} ids/LzmaFilesystemDriverSharedBuild.cpp)
		TARGET_LINK_LIBRARIES( LzmaFilesystemDriver ${GLOBAL_LINK_LIBRARIES} )
		SET_TARGET_PROPERTIES ( LzmaFilesystemDriver PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Plugins)
		AddPlugin( LzmaFilesystemDriver )
	ELSE(BUILD_SHARED_LZMA_FILESYSTEM_DRIVER)
		ADD_LIBRARY(LzmaFilesystemDriver STATIC ${LZMA_FILESYSTEM_DRIVER_SOURCE} ids/LzmaFilesystemDriverStaticBuild.cpp)
		SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} LzmaFilesystemDriver )
		SET_PROPERTY( GLOBAL PROPERTY FREYA_CORE_LINK_LIBRARIES_GLOBAL ${FREYA_CORE_LINK_LIBRARIES})
		AddFilesystemPlugin( LzmaFilesystemDriver )
	ENDIF(BUILD_SHARED_LZMA_FILESYSTEM_DRIVER)
ENDIF(BUILD_LZMA_FILESYSTEM_DRIVER)
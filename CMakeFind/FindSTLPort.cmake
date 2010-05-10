# Look for a directory containing STLPort.
#
# The following values are defined
# STLPORT_INSTALL_DIR - STLPort's installation directory.
# STLPORT_INCLUDE_DIR - where to find vector, etc.
# STLPORT_LIBRARIES   - link against these to use STLPort
# STLPORT_FOUND       - True if the X11 extensions are available.


# Provide some common installation locations.
# Otherwise, the user will have to specify it in the cache.
FIND_PATH( STLPORT_INSTALL_DIR stlport/iostream
   /usr/local/STLPort-5.2.1
)

MESSAGE( "STLPORT_INSTALL: ${STLPORT_INSTALL_DIR}")

# Assume for the moment that the STLPORT_INSTALL directory contains
# both the subdirectory for header file includes (.../stlport) and
# the subdirectory for libraries (../lib).

IF(NOT WIN32)
	FIND_PATH( STLPORT_INCLUDE_DIR iostream
	${STLPORT_INSTALL_DIR}/stlport
	)
ELSE()
	#FIND_PATH( STLPORT_INCLUDE_DIR iostream
	#${STLPORT_INSTALL_DIR}/stlport
	#NO_DEFAULT_PATH)
	SET (STLPORT_INCLUDE_DIR "${STLPORT_INSTALL_DIR}/stlport")
ENDIF()

  FIND_LIBRARY( STLPORT_LIBRARY_DEBUG
    NAMES stlport_cygwin_debug
          stlport_cygwin_stldebug
          stlport_gcc_debug
          stlport_gcc_stldebug
		  stlportstld.5.2
		  stlportstld
		  #stlportd.5.2
	     # stlportd
    PATHS ${STLPORT_INSTALL_DIR}/lib ${STLPORT_INSTALL_DIR}/../lib
  )


  # if we only have debug libraries, use them.
  # that is surely better than nothing.
  FIND_LIBRARY( STLPORT_LIBRARY_RELEASE
    NAMES stlport_cygwin
          stlport_gcc
		  stlport
		  stlport.5.2
	  
    PATHS ${STLPORT_INSTALL_DIR}/lib ${STLPORT_INSTALL_DIR}/../lib
  )

	IF (STLPORT_LIBRARY_DEBUG AND STLPORT_LIBRARY_RELEASE)
      # if the generator supports configuration types then set
      # optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
      IF (CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
        SET(STLPORT_LIBRARY optimized ${STLPORT_LIBRARY_RELEASE} debug ${STLPORT_LIBRARY_DEBUG})
      ELSE()
        # if there are no configuration types and CMAKE_BUILD_TYPE has no value
        # then just use the release libraries
        SET(STLPORT_LIBRARY ${STLPORT_LIBRARY_RELEASE} )
      ENDIF()
      # FIXME: This probably should be set for both cases
      SET(STLPORT_LIBRARIES optimized ${STLPORT_LIBRARY_RELEASE} debug ${STLPORT_LIBRARY_DEBUG})
    ENDIF()

    # if only the release version was found, set the debug variable also to the release version
    IF (STLPORT_LIBRARY_RELEASE AND NOT STLPORT_LIBRARY_DEBUG)
      SET(STLPORT_LIBRARY_DEBUG ${STLPORT_LIBRARY_RELEASE})
      SET(STLPORT_LIBRARY       ${STLPORT_LIBRARY_RELEASE})
      SET(STLPORT_LIBRARIES     ${STLPORT_LIBRARY_RELEASE})
    ENDIF()

    # if only the debug version was found, set the release variable also to the debug version
    IF (STLPORT_LIBRARY_DEBUG AND NOT STLPORT_LIBRARY_RELEASE)
      SET(STLPORT_LIBRARY_RELEASE ${STLPORT_LIBRARY_DEBUG})
      SET(STLPORT_LIBRARY         ${STLPORT_LIBRARY_DEBUG})
      SET(STLPORT_LIBRARIES       ${STLPORT_LIBRARY_DEBUG})
    ENDIF()

#
# For GCC, should we consider using -nostdinc or -isystem to 
# point to the STLPort system header directory? It is quite
# important that we get the STLPort C++ header files and not
# those that come with GCC.
#


IF( STLPORT_INCLUDE_DIR )
  IF( STLPORT_LIBRARIES )
    SET( STLPORT_FOUND "YES" )

    # stlport_gcc needs pthread.
    IF(UNIX)
      SET( STLPORT_LIBRARIES
        ${STLPORT_LIBRARIES} pthread )
    ENDIF(UNIX)

  ENDIF( STLPORT_LIBRARIES )
ENDIF( STLPORT_INCLUDE_DIR )

MARK_AS_ADVANCED(
  STLPORT_INCLUDE_DIR
  STLPORT_INSTALL_DIR
  STLPORT_LIBRARIES
)

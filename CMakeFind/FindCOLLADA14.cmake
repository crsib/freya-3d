# FindCOLLADA14.cmake module
# Inspired by FindBoost and osg version of FindCOLLADA.cmake
# ============================================================================
#
# Variables used by this module, they can change the default behaviour and
# need to be set before calling find_package:
#
# COLLADA14_STATIC									 if true, then module will attempt to search static libraries
#
# Variables defined by this module:
#
# COLLADA14_FOUND									 true, if module has managed to find collada
# COLLADA14_INCLUDE_DIR								 where to find collada modules. Does not include path to 1.4
# COLLADA14_LIBRARIES								 libraries to be linked with
#
# ============================================================================
#
# (c) 2010 by Dmitry crsib Vedenko
#
# ============================================================================
#

FIND_PATH(COLLADA14_INCLUDE_DIR NAMES dae.h HINTS ${COLLADA14_DOM_ROOT}/include $ENV{COLLADA14_DIR}/include $ENV{COLLADA14_DIR} $ENV{INCLUDE})

IF(NOT COLLADA14_INCLUDE_DIR)
	MESSAGE(SEND_ERROR "Failed to find collada-dom")
ENDIF()

MESSAGE(STATUS " dae.h found at ${COLLADA14_INCLUDE_DIR}")

IF(NOT COLLADA14_STATIC) #Shared build required

#Search for both debug and release libraries
	FIND_LIBRARY(COLLADA14_LIBRARY_RELEASE 
		NAMES COLLADA14_dom collada14dom libcollada14dom21
		PATHS
		${COLLADA14_DOM_ROOT}/build/${COLLADA14_BUILDNAME}-1.4
		$ENV{COLLADA14_DIR}/build/${COLLADA14_BUILDNAME}-1.4
		${COLLADA14_INCLUDE_DIR}/../lib
	)

	FIND_LIBRARY(COLLADA14_LIBRARY_DEBUG
		NAMES COLLADA14_dom-d collada14dom-d libcollada14dom21-d
		PATHS
		${COLLADA14_DOM_ROOT}/build/${COLLADA14_BUILDNAME}-1.4
		$ENV{COLLADA14_DIR}/build/${COLLADA14_BUILDNAME}-1.4
		${COLLADA14_INCLUDE_DIR}/../lib
	)


ELSE(NOT COLLADA14_STATIC)
	FIND_LIBRARY(COLLADA14_LIBRARY_RELEASE 
		NAMES COLLADA14_dom-s collada14dom-s libcollada14dom21-s
		PATHS
		${COLLADA14_DOM_ROOT}/build/${COLLADA14_BUILDNAME}-1.4
		$ENV{COLLADA14_DIR}/build/${COLLADA14_BUILDNAME}-1.4
		${COLLADA14_INCLUDE_DIR}/../lib
	)

	FIND_LIBRARY(COLLADA14_LIBRARY_DEBUG
		NAMES COLLADA14_dom-sd collada14dom-sd libcollada14dom21-sd
		PATHS
		${COLLADA14_DOM_ROOT}/build/${COLLADA14_BUILDNAME}-1.4
		$ENV{COLLADA14_DIR}/build/${COLLADA14_BUILDNAME}-1.4
		${COLLADA14_INCLUDE_DIR}/../lib
	)
ENDIF(NOT COLLADA14_STATIC)

IF (COLLADA14_LIBRARY_DEBUG AND COLLADA14_LIBRARY_RELEASE)
# if the generator supports configuration types then set
# optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
IF (CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
    SET(COLLADA14_LIBRARY optimized ${COLLADA14_LIBRARY_RELEASE} debug ${COLLADA14_LIBRARY_DEBUG})
ELSE()
# if there are no configuration types and CMAKE_BUILD_TYPE has no value
# then just use the release libraries
    SET(COLLADA14_LIBRARY ${COLLADA14_LIBRARY_RELEASE} )
ENDIF()
# FIXME: This probably should be set for both cases
    SET(COLLADA14_LIBRARIES optimized ${COLLADA14_LIBRARY_RELEASE} debug ${COLLADA14_LIBRARY_DEBUG})
ENDIF()

# if only the release version was found, set the debug variable also to the release version
IF (COLLADA14_LIBRARY_RELEASE AND NOT COLLADA14_LIBRARY_DEBUG)
	SET(COLLADA14_LIBRARY_DEBUG ${COLLADA14_LIBRARY_RELEASE})
	SET(COLLADA14_LIBRARY       ${COLLADA14_LIBRARY_RELEASE})
    SET(COLLADA14_LIBRARIES     ${COLLADA14_LIBRARY_RELEASE})
ENDIF()

# if only the debug version was found, set the release variable also to the debug version
IF (COLLADA14_LIBRARY_DEBUG AND NOT COLLADA14_LIBRARY_RELEASE)
    SET(COLLADA14_LIBRARY_RELEASE ${COLLADA14_LIBRARY_DEBUG})
    SET(COLLADA14_LIBRARY         ${COLLADA14_LIBRARY_DEBUG})
    SET(COLLADA14_LIBRARIES       ${COLLADA14_LIBRARY_DEBUG})
ENDIF()

IF(COLLADA14_INCLUDE_DIR AND COLLADA14_LIBRARIES)
	SET(COLLADA14_FOUND YES)
ENDIF()

MARK_AS_ADVANCED(
  COLLADA14_INCLUDE_DIR
  COLLADA14_LIBRARIES
)
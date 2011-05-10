# Finds the International Components for Unicode (ICU) Library
#
# ICU_FOUND				true, if icu is found
# ICU_INCLUDE_DIR		contains the path to include dirs of ICU
# ICU_LIBRARIES			Libraries to link with
#
###############################################################
###############################################################
##### This file is a part of Freya 3D Engine ##################
###############################################################
###############################################################

find_path( ICU_INCLUDE_DIR NAMES unicode/utypes.h  DOC "Include directory for the ICU library" PATHS ENV{CPATH} $ENV{ASSIMP_DIR} $ENV{ASSIMP_DIR}/include $ENV{INCLUDE} $ENV{INCLUDE}
  /usr/include /usr/local/include /opt/local/include )

find_library( ICU_LIBRARY_COMMON NAMES icuuc DOC "Libraries to link against for the common parts of ICU" PATHS $ENV{LD_LIBRARY_PATH} $ENV{LIBRARY_PATH} $ENV{LIB}
  /usr/lib /usr/local/lib /opt/local/lib)
  
set(ICU_LIBRARIES ${ICU_LIBRARY_COMMON}  )
  
if( ICU_INCLUDE_DIR AND ICU_LIBRARIES)
	set(ICU_FOUND 1)
endif()

mark_as_advanced( ICU_INCLUDE_DIR )
mark_as_advanced( ICU_LIBRARIES )

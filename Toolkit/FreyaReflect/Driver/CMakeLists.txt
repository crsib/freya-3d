set(
DRIVER_INCLUDES 

####################
# version file     #
####################
./version.h

####################
# CppTree    	   #
####################
./CppTree/ASTParser.h
./CppTree/ASTTreeWalker.h
./CppTree/CppNode.h
./CppTree/CppTree.h
./CppTree/CppType.h

####################
# Generated        #
####################
"${CMAKE_SOURCE_DIR}/Build/Generated/SVN_Revision.h"
)
set(
DRIVER_SOURCES
####################
# CppTree    	   #
####################
./CppTree/ASTParser.cpp
./CppTree/ASTTreeWalker.cpp
./CppTree/CppNode.cpp
./CppTree/CppTree.cpp
./CppTree/CppType.cpp

####################
# main executable  #
####################
./driver.cpp  
)
######## Gen revision file ####################
FIND_PACKAGE(Subversion)
message( STATUS "Writing revision to ${CMAKE_SOURCE_DIR}/Build/Generated/SVN_Revision.h" )
IF(Subversion_FOUND)
    Subversion_WC_INFO(${PROJECT_SOURCE_DIR} Freya3D)
    MESSAGE("Current revision is ${Freya3D_WC_REVISION}")
    FILE(WRITE "${CMAKE_SOURCE_DIR}/Build/Generated/SVN_Revision.h" "#ifndef __SVN_REVISION_H_\n#define __SVN_REVISION_H_\n\n#define SVN_REVISION_INT ${Freya3D_WC_REVISION}\n#define SVN_REVISION_STRING \"${Freya3D_WC_REVISION}\"\n\n#endif\n")
ELSE()
    MESSAGE("SVN binary not found")
    FILE(WRITE "${CMAKE_SOURCE_DIR}/Build/Generates/SVN_Revision.h" "#ifndef __SVN_REVISION_H_\n#define __SVN_REVISION_H_\n\n#define SVN_REVISION_INT 0\n#define SVN_REVISION_STRING \"unrevisioned\"\n\n#endif\n")
ENDIF(Subversion_FOUND)

include_directories( "${CMAKE_SOURCE_DIR}/Build/Generated" )
include_directories( "./" )

SET_SOURCE_FILES_PROPERTIES("${CMAKE_SOURCE_DIR}/Build/Generates/SVN_Revision.h" PROPERTIES GENERATED YES)
SOURCE_GROUP("Generated" FILES "${CMAKE_SOURCE_DIR}/Build/Generates/SVN_Revision.h")


######## Find Clang Frontend #################

find_package( ClangFrontend REQUIRED)
include_directories( ${CLANGFRONTEND_INCLUDE_DIR} )
message ( STATUS "ClangFrontend: \n\tinclude: ${CLANGFRONTEND_INCLUDE_DIR} \n\tlibs: ${CLANGFRONTEND_LIBRARIES}" )

######## Create exec and link ################
find_package ( BoostSTLPort REQUIRED)
include_directories( ${Boost_INCLUDE_DIRS} )
include(GenerateProject)

#GenerateProject( ./ ${DRIVER_INCLUDES} )
#GenerateProject( ./ ${DRIVER_SOURCES} )

add_executable( freyareflect ${DRIVER_INCLUDES} ${DRIVER_SOURCES} )
target_link_libraries( freyareflect ${GLOBAL_LINK_LIBRARIES} ${CLANGFRONTEND_LIBRARIES} )
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

"${CMAKE_SOURCE_DIR}/Build/Generated/headers_package.cpp"
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
SET_SOURCE_FILES_PROPERTIES("${CMAKE_SOURCE_DIR}/Build/Generated/headers_package.cpp" PROPERTIES GENERATED YES )
SOURCE_GROUP("Generated" FILES "${CMAKE_SOURCE_DIR}/Build/Generates/SVN_Revision.h")

######## Find Clang Frontend #################

find_package( ClangFrontend REQUIRED )
include_directories( ${CLANGFRONTEND_INCLUDE_DIR} )
message ( STATUS "ClangFrontend: \n\tinclude: ${CLANGFRONTEND_INCLUDE_DIR} \n\tlibs: ${CLANGFRONTEND_LIBRARIES}" )

######## Create exec and link ################
find_package ( BoostSTLPort REQUIRED )
include_directories( ${Boost_INCLUDE_DIRS} )
include(GenerateProject)

#GenerateProject( ./ ${DRIVER_INCLUDES} )
#GenerateProject( ./ ${DRIVER_SOURCES} )

######## Header builder ######################
# Build zlib
add_subdirectory( "${CMAKE_SOURCE_DIR}/../../Framework/3party/zlib" ${CMAKE_SOURCE_DIR}/Build/Static)
include_directories( "${CMAKE_SOURCE_DIR}/../../Framework/3party/zlib" )
message ( STATUS "Configuring header packaging tool" )
add_executable( build_headers HeaderBuilder/main.cpp )
target_link_libraries ( build_headers ${GLOBAL_LINK_LIBRARIES} ${CLANGFRONTEND_LIBRARIES} zlib ) 
######## Generate packed headers
message ( STATUS "Configuring reflector" )
file(GLOB_RECURSE CLANG_HEADERS "${CMAKE_SOURCE_DIR}/Driver/clang/*" )
add_custom_command(OUTPUT "${CMAKE_SOURCE_DIR}/Build/Generated/headers_package.cpp"
                    COMMAND build_headers "${CMAKE_SOURCE_DIR}/clang/include/" "${CMAKE_SOURCE_DIR}/Build/Generated/headers_package.cpp"
                    DEPENDS  ${CLANG_HEADERS}
                    VERBATIM)
######## Freya reflect
add_executable( freyareflect ${DRIVER_INCLUDES} ${DRIVER_SOURCES} )
target_link_libraries( freyareflect ${GLOBAL_LINK_LIBRARIES} ${CLANGFRONTEND_LIBRARIES} zlib )
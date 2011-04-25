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
./CppTree/TreeMarker.h

####################
# Output modules   #
####################
./Output/XMLWriter.h

####################
# Generated        #
####################
#"${CMAKE_SOURCE_DIR}/Build/Generated/SVN_Revision.h"
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
./CppTree/TreeMarker.cpp

####################
# Output modules   #
####################
./Output/XMLWriter.cpp

####################
# main executable  #
####################
./driver.cpp  

"${CMAKE_SOURCE_DIR}/Build/Generated/headers_package.cpp"
)

include_directories( "${CMAKE_SOURCE_DIR}/Build/Generated" )
include_directories( "./" )

#SET_SOURCE_FILES_PROPERTIES("${CMAKE_SOURCE_DIR}/Build/Generates/SVN_Revision.h" PROPERTIES GENERATED YES)
SET_SOURCE_FILES_PROPERTIES("${CMAKE_SOURCE_DIR}/Build/Generated/headers_package.cpp" PROPERTIES GENERATED YES )
SOURCE_GROUP("Generated" FILES "${CMAKE_SOURCE_DIR}/Build/Generated/headers_package.cpp")

SOURCE_GROUP("Output" FILES "./Output/XMLWriter.cpp" "./Output/XMLWriter.h")

######## Find Clang Frontend #################

find_package( ClangFrontend REQUIRED )
include_directories( ${CLANGFRONTEND_INCLUDE_DIR} )
message ( STATUS "ClangFrontend: \n\tinclude: ${CLANGFRONTEND_INCLUDE_DIR} \n\tlibs: ${CLANGFRONTEND_LIBRARIES}" )

if( UNIX )
	set( CLANGFRONTEND_LIBRARIES ${CLANGFRONTEND_LIBRARIES} pthread dl )
endif()

######## Create exec and link ################
find_package ( Boost REQUIRED )
include_directories( ${Boost_INCLUDE_DIRS} )
include(GenerateProject)

#### LibXML2 #######
find_package( LibXml2d REQUIRED )
include_directories( ${LIBXML2_INCLUDE_DIR} )

#GenerateProject( ./ ${DRIVER_INCLUDES} )
#GenerateProject( ./ ${DRIVER_SOURCES} )

######## Header builder ######################
# Build zlib
add_subdirectory( "${CMAKE_SOURCE_DIR}/../../3party/zlib" ${CMAKE_BINARY_DIR}/zlib)
include_directories( "${CMAKE_SOURCE_DIR}/../../3party/zlib" )
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
target_link_libraries( freyareflect ${GLOBAL_LINK_LIBRARIES} ${CLANGFRONTEND_LIBRARIES} zlib ${LIBXML2_LIBRARIES} )

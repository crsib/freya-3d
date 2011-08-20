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
# IO modules       #
####################
./Output/XMLWriter.h
./Output/FreyaReflectWriter.h
./Input/XMLReader.h
####################
# Base             #
####################
./Base/CPP/CppModule.h
./Base/CPP/CppModuleBody.h
./Base/CPP/HeaderBlock.h
./Base/ReflectedElement.h
./Base/ReflectedClass.h
./Base/ReflectedScope.h
./Base/ReflectedEnum.h
./Base/ReflectionDatabaseGenerator.h
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
# IO modules       #
####################
./Output/XMLWriter.cpp
./Output/FreyaReflectWriter.cpp
./Input/XMLReader.cpp
####################
# Base             #
####################
./Base/CPP/CppModule.cpp
./Base/CPP/CppModuleBody.cpp
./Base/CPP/HeaderBlock.cpp
./Base/ReflectedClass.cpp
./Base/ReflectedScope.cpp
./Base/ReflectedEnum.cpp
./Base/ReflectedElement.cpp
./Base/ReflectionDatabaseGenerator.cpp
####################
# main executable  #
####################
./driver.cpp  

"${CMAKE_SOURCE_DIR}/Build/Generated/headers_package.cpp"
)
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/Build/Generated)
	file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/Build/Generated)
endif()

include_directories( "${CMAKE_SOURCE_DIR}/Build/Generated" )
include_directories( "./" )

#SET_SOURCE_FILES_PROPERTIES("${CMAKE_SOURCE_DIR}/Build/Generates/SVN_Revision.h" PROPERTIES GENERATED YES)
set_source_files_properties("${CMAKE_SOURCE_DIR}/Build/Generated/headers_package.cpp" PROPERTIES GENERATED YES )

if(MSVC)
	source_group("Generated" FILES "${CMAKE_SOURCE_DIR}/Build/Generated/headers_package.cpp")
	source_group("IO" FILES ./Output/XMLWriter.cpp ./Output/XMLWriter.h
							./Output/FreyaReflectWriter.h ./Output/FreyaReflectWriter.cpp
							./Input/XMLReader.cpp ./Input/XMLReader.h
				)
	source_group("CppTree" FILES 	./CppTree/ASTParser.h
									./CppTree/ASTTreeWalker.h
									./CppTree/CppNode.h
									./CppTree/CppTree.h
									./CppTree/CppType.h
									./CppTree/TreeMarker.h
									./CppTree/ASTParser.cpp
									./CppTree/ASTTreeWalker.cpp
									./CppTree/CppNode.cpp
									./CppTree/CppTree.cpp
									./CppTree/CppType.cpp
									./CppTree/TreeMarker.cpp
				)
	source_group("Base" FILES 		./Base/CPP/CppModule.h
									./Base/CPP/CppModuleBody.h
									./Base/CPP/HeaderBlock.h
									./Base/ReflectedClass.h
									./Base/ReflectedScope.h
									./Base/ReflectedElement.h
									./Base/ReflectedEnum.h
									./Base/ReflectionDatabaseGenerator.h
									./Base/CPP/CppModule.cpp
									./Base/CPP/CppModuleBody.cpp
									./Base/CPP/HeaderBlock.cpp
									./Base/ReflectedClass.cpp
									./Base/ReflectedScope.cpp
									./Base/ReflectedElement.cpp
									./Base/ReflectedEnum.cpp
									./Base/ReflectionDatabaseGenerator.cpp
				)
	source_group("App" FILES ./driver.cpp ./version.h)
endif()

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

if(EXISTS "${CMAKE_SOURCE_DIR}/../../CMakeExports/freya_reflect.cmake")
	file(REMOVE "${CMAKE_SOURCE_DIR}/../../CMakeExports/freya_reflect.cmake")
endif()

export(TARGETS freyareflect FILE "${CMAKE_SOURCE_DIR}/../../CMakeExports/freya_reflect.cmake")
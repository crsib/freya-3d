
set(FREYAREFLECT_INCLUDES 
	Include/FreyaReflect.h
	Include/internal.h
	Include/CppNode.h
	Include/NamespaceNode.h
	Include/ContextPolicy.hpp
)
set(FREYAREFLECT_SOURCES 
	Source/FreyaReflect.cpp
	Source/Strings.cpp
	Source/ASTParser.cpp
	Source/CppNode.cpp
	Source/CppType.cpp
	Source/translation_unit_parser.h
	Source/translation_unit_skipper.h
)
if(MSVC)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4522 /wd4800 /wd4065 /wd4715 /wd4616 /wd4244 /wd4355 /wd4554")
endif()
find_package(BoostSTLPort 1.43 REQUIRED COMPONENTS system filesystem wave regex thread)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(LINK_DEPENDENCIES ${LINK_DEPENDENCIES} ${Boost_LIBRARIES})
endif()
add_subdirectory( 3party )
add_definitions("-D_SHARED_BUILD")
add_library(FreyaReflect	SHARED ${FREYAREFLECT_INCLUDES} ${FREYAREFLECT_SOURCES})
target_link_libraries(FreyaReflect ${LINK_DEPENDENCIES} ${GLOBAL_LINK_LIBRARIES} elsa smbase ast elkhound)
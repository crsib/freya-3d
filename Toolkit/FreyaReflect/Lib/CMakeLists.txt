
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
	Source/translation_unit_parser.h
	Source/translation_unit_skipper.h
)

find_package(BoostSTLPort 1.43 REQUIRED COMPONENTS system filesystem wave regex thread)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(LINK_DEPENDENCIES ${LINK_DEPENDENCIES} ${Boost_LIBRARIES})
endif()
add_definitions("-D_SHARED_BUILD")
add_library(FreyaReflect	SHARED ${FREYAREFLECT_INCLUDES} ${FREYAREFLECT_SOURCES})
target_link_libraries(FreyaReflect ${LINK_DEPENDENCIES} ${GLOBAL_LINK_LIBRARIES})
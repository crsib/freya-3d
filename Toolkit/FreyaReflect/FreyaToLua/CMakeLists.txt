set(FREYATOLUA_SOURCES
main.cpp
)

find_package(BoostSTLPort 1.43 REQUIRED COMPONENTS program_options)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(LINK_DEPENDENCIES ${LINK_DEPENDENCIES} ${Boost_LIBRARIES})
endif()

add_executable(freya2lua ${FREYATOLUA_SOURCES})
target_link_libraries(freya2lua FreyaReflect ${LINK_DEPENDENCIES} ${GLOBAL_LINK_LIBRARIES}) 
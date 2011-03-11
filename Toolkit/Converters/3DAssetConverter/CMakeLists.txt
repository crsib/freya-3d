#
# 3DAssetConverter
#

set(3DAC_SOURCE_DIR ${Converters_SOURCE_DIR}/3DAssetConverter)
set(3DAC_BINARY_DIR ${CMAKE_BINARY_DIR}/Toolkit/Converters/3DAssetConverter)

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# FIXME: Minimize :)
set (3DAC_LINK_WITH_LIBRARIES ${RUNTIME_LINK_LIBRARIES} ${GLOBAL_LINK_LIBRARIES})

find_package(Assimp REQUIRED)
if (ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
    set(3DAC_LINK_WITH_LIBRARIES ${3DAC_LINK_WITH_LIBRARIES} ${ASSIMP_LIBRARY})
endif()

include_directories(${CMAKE_SOURCE_DIR}/Framework/include/)
include_directories(${3DAC_SOURCE_DIR}/dll/include)

message(STATUS "ENV{INCLUDE}: " $ENV{INCLUDE} ";")
message(STATUS "ENV{LIB}: " $ENV{LIB} ";")

link_directories(${3DAC_BINARY_DIR})

add_subdirectory(dll)
add_subdirectory(cli)
add_subdirectory(tests)
#
# 3DAssetConverter-DLL
#

include(3dac-dll.list)

set(3DAC_DLL_NAME "freya-3dac-dll")

add_library (${3DAC_DLL_NAME} SHARED ${3DAC_DLL_HEADER_FILES} ${3DAC_DLL_SOURCE_FILES}) 
target_link_libraries(${3DAC_DLL_NAME} ${3DAC_LINK_WITH_LIBRARIES})

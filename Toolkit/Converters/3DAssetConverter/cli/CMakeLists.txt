#
# 3DAssetConverter-CLI
#

include(3dac-cli.list)

set(3DAC_CLI_NAME "freya-3dac")

include_directories(${3DAC_SOURCE_DIR}/dll/include)

if(APPLE)
	add_executable(${3DAC_CLI_NAME} MACOSX_BUNDLE 
        ${3DAC_HEADER_FILES} ${3DAC_SOURCE_FILES})
else(APPLE)

	if(WIN32)
		add_executable(${3DAC_CLI_NAME} ${3DAC_HEADER_FILES} 
            ${3DAC_SOURCE_FILES})
	endif(WIN32)
    
endif(APPLE)

target_link_libraries(${3DAC_CLI_NAME} freya-3dac-dll)
target_link_libraries(${3DAC_CLI_NAME} ${RUNTIME_LINK_LIBRARIES} ${GLOBAL_LINK_LIBRARIES})

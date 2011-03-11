#
# 3DAssetConverter-Tests
#

set(3DAC_TESTS_MAIN "freya-3dac-tests-main")

if(APPLE)
    add_executable(${3DAC_TESTS_MAIN} MACOSX_BUNDLE main.cpp)
else(APPLE)
    if(WIN32)
        add_executable(${3DAC_TESTS_MAIN} ${3D_ASSET_CONVERTER_HEADER_FILES} main.cpp)
    endif(WIN32)
endif(APPLE)

target_link_libraries(${3DAC_TESTS_MAIN} freya-3dac-dll)

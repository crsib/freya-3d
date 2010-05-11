#TODO, FIXME: Fix platform, fix libcollada linking

include(colladaconverter.list)

include_directories(${CMAKE_SOURCE_DIR}/../../../Freya/Framework/include/)
include_directories(${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/include/)
include_directories(${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/include/1.4)
include_directories(${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/include/boost-1_43)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set(LINK_LIBRARIES ${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/lib/libcollada14dom21-sd.lib;${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/lib/stlportstld.5.2.lib;${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/lib/pcre_d.lib;${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/lib/pcrecpp_d.lib;${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/lib/boost_system-vc100-mt-gdp.lib;${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/lib/boost_filesystem-vc100-mt-gdp.lib)

link_directories(/lib/)

if(APPLE)
	add_executable(ColladaConverter MACOSX_BUNDLE 
        ${COLLADA_CONVERTER_HEADER_FILES} ${COLLADA_CONVERTER_SOURCE_FILES})
else(APPLE)

	if(WIN32)
		add_executable(ColladaConverter ${COLLADA_CONVERTER_HEADER_FILES} 
            ${COLLADA_CONVERTER_SOURCE_FILES})

	endif(WIN32)

endif(APPLE)

target_link_libraries(ColladaConverter ${LINK_LIBRARIES})


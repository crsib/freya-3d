#TODO, FIXME: Fix platform, fix libcollada linking

include(colladaconverter.list)

include_directories(${CMAKE_SOURCE_DIR}/../../../Freya/Framework/include/)
include_directories(${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/include/1.4)

set(LINK_WITH_LIBRARIES ${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/lib/libcollada14dom21-sd.lib;${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/lib/pcrecpp_d.lib;)
   
# -> Need to set Working directory in Bin

find_package(STLPort REQUIRED)
if (STLPORT_FOUND)
    include_directories(${STLPORT_INCLUDE_DIR})
    include_directories(${STLPORT_INCLUDE_DIR}/../) # I include <stlport/*> way.
    
    
    add_definitions(-D_STLP_DEBUG) # !!FIXME!! Disable for release version!!
    
    
    set(LINK_WITH_LIBRARIES ${LINK_WITH_LIBRARIES} ${STLPORT_LIBRARIES})
endif()

find_package(BoostSTLPort 1.40 REQUIRED COMPONENTS filesystem system)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(LINK_WITH_LIBRARIES ${LINK_WITH_LIBRARIES} ${Boost_LIBRARIES})
endif()

find_package(PCRE REQUIRED)
if (PCRE_FOUND)
    include_directories(${PCRE_INCLUDE_DIR})
    set(LINK_WITH_LIBRARIES ${LINK_WITH_LIBRARIES} ${PCRE_LIBRARIES})
endif()

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

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

target_link_libraries(ColladaConverter ${LINK_WITH_LIBRARIES})


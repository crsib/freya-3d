#TODO, FIXME: Fix platform, fix libcollada linking

include(colladaconverter.list)

#set(LINK_WITH_LIBRARIES ${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/lib/libcollada14dom21-sd.lib;${CMAKE_SOURCE_DIR}/../../../Freya_MSVC10/lib/pcrecpp_d.lib;)
   
# -> Need to set Working directory in Bin

find_package(STLPort REQUIRED)
if (STLPORT_FOUND)
    include_directories(${STLPORT_INCLUDE_DIR})
	IF(MSVC)
		SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_STLP_DEBUG=1")
	ELSE()
		SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_STLP_DEBUG=1")
	ENDIF()
    set(LINK_WITH_LIBRARIES ${LINK_WITH_LIBRARIES} ${STLPORT_LIBRARIES})
endif()

find_package(BoostSTLPort 1.40 REQUIRED COMPONENTS filesystem system)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(LINK_WITH_LIBRARIES ${LINK_WITH_LIBRARIES} ${Boost_LIBRARIES})
endif()

#find_package(PCRE REQUIRED)
#if (PCRE_FOUND)
#    include_directories(${PCRE_INCLUDE_DIR})
#    set(LINK_WITH_LIBRARIES ${LINK_WITH_LIBRARIES} ${PCRE_LIBRARIES})
#endif()

find_package(COLLADA14 REQUIRED)
if(COLLADA14_FOUND)
	include_directories(${COLLADA14_INCLUDE_DIR} ${COLLADA14_INCLUDE_DIR}/1.4)
	set(LINK_WITH_LIBRARIES ${LINK_WITH_LIBRARIES} ${COLLADA14_LIBRARIES})
endif()

#Don't forget 'bout Freya public includes. There is no actual sence in searching freya3d, as it's location is fixed

include_directories(${CMAKE_SOURCE_DIR}/../../../Freya/Framework/include/)

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

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


message ( STATUS " Generating build dependencies for FreyaCore" )

set( FREYA_CORE_INCLUDES 
	Include/FreyaCoreInternal.h
)

source_group("Include" FILES Include/FreyaCoreInternal.h )

set( FREYA_CORE_SOURCES
)

if( FREYA_BUILD_SHARED )
#	add_definitions( -D_FREYA_CORE_SHARED_BUILD )
#	add_library( FreyaCore SHARED ${FREYA_CORE_INCLUDES} ${FREYA_CORE_SOURCES} )
#	target_link_libraries( FreyaCore FreyaSupport )
else()
#	add_library( FreyaCore STATIC ${FREYA_CORE_INCLUDES} ${FREYA_CORE_SOURCES} )
endif()

set_target_properties( FreyaCore PROPERTIES FOLDER "Core Libraries" )

#SET_PROPERTY( GLOBAL PROPERTY RUNTIME_LINK_LIBRARIES_GLOBAL ${RUNTIME_LINK_LIBRARIES} FreyaCore)

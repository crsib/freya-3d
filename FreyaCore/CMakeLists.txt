message ( STATUS " Generating build dependencies for FreyaCore" )

set( FREYA_CORE_INCLUDES 
	# core/multithreading
	Include/core/multithreading/thread.h
	Include/core/multithreading/ThreadManager.h
	Include/core/multithreading/details/autodetect.h
	Include/core/multithreading/details/thread-details.h
)

source_group("multithreading" FILES
												./Include/core/multithreading/thread.h
												./Include/core/multithreading/ThreadManager.h
)
			
source_group("multithreading\\details" FILES
												./Include/core/multithreading/details/autodetect.h
												./Include/core/multithreading/details/thread-details.h
)			

# Platform specific includes
if( WIN32 )
	set ( FREYA_CORE_INCLUDES ${FREYA_CORE_INCLUDES}
	# core/multithreading
		Include/core/multithreading/details/plat-win-thread.h
		Include/core/multithreading/details/plat-win-thread-data.h
	)

	source_group("multithreading\\details" FILES
												./Include/core/multithreading/details/plat-win-thread.h
												./Include/core/multithreading/details/plat-win-thread-data.h
	)

elseif( UNIX )

endif()

set( FREYA_CORE_SOURCES
# core/multithreading
	Source/core/multithreading/ThreadManager.cpp
)

source_group("multithreading" FILES
												./Source/core/multithreading/ThreadManager.cpp
)

if( WIN32 )
	set ( FREYA_CORE_SOURCES ${FREYA_CORE_SOURCES}
		# core/multithreading
		Source/core/multithreading/details/plat-win-thread.cpp
	)
	
	source_group("multithreading\\details" FILES
												./Source/core/multithreading/details/plat-win-thread.cpp
	)
elseif( UNIX )

endif()

if( FREYA_BUILD_SHARED )
	add_definitions( -D_FREYA_CORE_SHARED_BUILD )
	add_library( FreyaCore SHARED ${FREYA_CORE_INCLUDES} ${FREYA_CORE_SOURCES} )
	target_link_libraries( FreyaCore FreyaSupport )
else()
	add_library( FreyaCore STATIC ${FREYA_CORE_INCLUDES} ${FREYA_CORE_SOURCES} )
endif()

#SET_PROPERTY( GLOBAL PROPERTY RUNTIME_LINK_LIBRARIES_GLOBAL ${RUNTIME_LINK_LIBRARIES} FreyaCore)

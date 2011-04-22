message ( STATUS " Generating build dependencies for FreyaCore" )

set( FREYA_CORE_INCLUDES 
	Include/FreyaCoreInternal.h
	# core/multithreading
	Include/core/multithreading/thread.h
	Include/core/multithreading/thread-interface.h
	Include/core/multithreading/details/thread-data.h
	Include/core/multithreading/details/thread-details.h
)

source_group("Include" FILES Include/FreyaCoreInternal.h )

source_group("Include\\multithreading" FILES
												./Include/core/multithreading/thread.h
												./Include/core/multithreading/thread-interface.h
)
			
source_group("Include\\multithreading\\details" FILES
												./Include/core/multithreading/details/thread-data.h
												./Include/core/multithreading/details/thread-details.h
)			

# Platform specific includes
if( WIN32 )
	if( MSVC OR MINGW )
		add_definitions(-DPLATFORM_WIN_THREADS)
	endif()
	set ( FREYA_CORE_INCLUDES ${FREYA_CORE_INCLUDES}
	# core/multithreading
		Include/core/multithreading/details/plat-win-thread.h
		Include/core/multithreading/details/plat-win-thread-data.h
	)

	source_group("Include\\multithreading\\details" FILES
												./Include/core/multithreading/details/plat-win-thread.h
												./Include/core/multithreading/details/plat-win-thread-data.h
	)

elseif( UNIX OR APPLE )
	add_definitions(-DPLATFORM_POSIX_THREADS)
endif()

set( FREYA_CORE_SOURCES
# core/multithreading
	Source/core/multithreading/thread.cpp
)

source_group("multithreading" FILES
												./Source/core/multithreading/thread.cpp
)

#if( WIN32 AND ( MSVC OR MINGW ) )
#	set ( FREYA_CORE_SOURCES ${FREYA_CORE_SOURCES}
#		# core/multithreading
#	)
#	
#	source_group("multithreading\\details" FILES
#	)
#elseif( UNIX OR APPLE )
#
#endif()

if( FREYA_BUILD_SHARED )
	add_definitions( -D_FREYA_CORE_SHARED_BUILD )
	add_library( FreyaCore SHARED ${FREYA_CORE_INCLUDES} ${FREYA_CORE_SOURCES} )
	target_link_libraries( FreyaCore FreyaSupport )
else()
	add_library( FreyaCore STATIC ${FREYA_CORE_INCLUDES} ${FREYA_CORE_SOURCES} )
endif()

set_target_properties( FreyaCore PROPERTIES FOLDER "Core Libraries" )

#SET_PROPERTY( GLOBAL PROPERTY RUNTIME_LINK_LIBRARIES_GLOBAL ${RUNTIME_LINK_LIBRARIES} FreyaCore)

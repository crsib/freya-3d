message ( STATUS " Generating build dependencies for FreyaSupport" )

# includes
set( FREYA_SUPPORT_INCLUDES 
	Include/FreyaSupportInternal.h
	Include/integer.h
# atomic
	Include/atomic/atomic.h
	Include/atomic/atomic-interface.h
	Include/atomic/memory_order.h
# core
	Include/core/string.h
	Include/core/Log.h
	Include/core/Object.h
#date_time
	Include/date_time/system_clock.h
	Include/date_time/TimeUnit.h
	Include/date_time/details/system_clock.h
	Include/date_time/details/platform.h
# core/memory
	Include/core/memory/MemoryAllocator.h
	Include/core/memory/MemoryArena.h
	Include/core/memory/MemoryPools.h
# core/multithreading
	Include/core/multithreading/multithreading.h
	Include/core/multithreading/thread.h
	Include/core/multithreading/thread_local.h
	Include/core/multithreading/mutex.h
	Include/core/multithreading/condition_variable.h
	Include/core/multithreading/thread_self.h
	Include/core/multithreading/spinlock.h
	Include/core/multithreading/synchronize.h
	
	Include/core/multithreading/details/platform.h
	Include/core/multithreading/details/thread.h
	Include/core/multithreading/details/thread_local.h
	Include/core/multithreading/details/mutex.h
	Include/core/multithreading/details/condition_variable.h
	Include/core/multithreading/details/thread_self.h
)

# include source groups
source_group("Include" FILES ./Include/FreyaSupportInternal.h ./Include/integer.h)
source_group("Include\\core" FILES 
								./Include/core/string.h
								./Include/core/Log.h
								./Include/core/Object.h
)

source_group("Include\\core\\memory" FILES 
								./Include/core/memory/MemoryAllocator.h
								./Include/core/memory/MemoryArena.h
								./Include/core/memory/MemoryException.h
								./Include/core/memory/MemoryPools.h 
)

source_group("Include\\atomic" FILES 
								./Include/atomic/atomic.h
								./Include/atomic/atomic-interface.h
								./Include/atomic/memory_order.h
)

source_group("Include\\date_time" FILES
								./Include/date_time/TimeUnit.h
								./Include/date_time/system_clock.h
)

source_group("Include\\date_time\\details" FILES
								./Include/date_time/details/platform.h
								./Include/date_time/details/system_clock.h
)

source_group("Include\\core\\multithreading" FILES
								./Include/core/multithreading/multithreading.h
								./Include/core/multithreading/thread.h
								./Include/core/multithreading/thread_local.h
								./Include/core/multithreading/mutex.h
								./Include/core/multithreading/condition_variable.h
								./Include/core/multithreading/thread_self.h
								./Include/core/multithreading/synchronize.h
								./Include/core/multithreading/spinlock.h
)
source_group("Include\\core\\multithreading\\details" FILES
								./Include/core/multithreading/details/platform.h
								./Include/core/multithreading/details/thread.h
								./Include/core/multithreading/details/thread_local.h
								./Include/core/multithreading/details/mutex.h
								./Include/core/multithreading/details/condition_variable.h
								./Include/core/multithreading/details/thread_self.h
								./Include/core/multithreading/details/spinlock.h
)

if( MSVC )
	set( FREYA_SUPPORT_INCLUDES ${FREYA_SUPPORT_INCLUDES} 
									Include/atomic/details/atomic-msvc.h 
	)
	source_group("Include\\atomic\\details" FILES
									Include/atomic/details/atomic-msvc.h
	)
endif()

if( WIN32 )
	if( MSVC OR MINGW )
		# multithreading implementation
		add_definitions(-DPLATFORM_WIN_THREADS)
		set( FREYA_SUPPORT_INCLUDES ${FREYA_SUPPORT_INCLUDES}
									Include/core/multithreading/win32/thread.h
									Include/core/multithreading/win32/thread_local.h
									Include/core/multithreading/win32/mutex.h
									Include/core/multithreading/win32/condition_variable.h
									Include/core/multithreading/win32/thread_self.h
		)
		source_group("Include\\core\\multithreading\\win32" FILES
						Include/core/multithreading/win32/thread.h
						Include/core/multithreading/win32/thread_local.h
						Include/core/multithreading/win32/mutex.h
						Include/core/multithreading/win32/condition_variable.h
						Include/core/multithreading/win32/thread_self.h
		)
		#date_time implmenetation
		set( FREYA_SUPPORT_INCLUDES ${FREYA_SUPPORT_INCLUDES}
									Include/date_time/win32/system_clock.h
		)
		source_group("Include\\date_time\\win32" FILES
						Include/date_time/win32/system_clock.h
		)
		#
		set( FREYA_USE_WINMM 1 )
		set( WINMM_LIBRARY winmm.lib )
		
	endif( MSVC OR MINGW )
elseif( UNIX OR APPLE )
endif()

# sources
set( FREYA_SUPPORT_SOURCES
# core
	Source/core/string.cpp
	Source/core/Log.cpp
# core/memory
	Source/core/memory/MemoryImpl.cpp
# core/multithreading
	Source/core/multithreading/thread.cpp
)
# sources source groups			
source_group("core" FILES 
								./Source/core/string.cpp
								./Source/core/Log.cpp
)

source_group("core\\memory" FILES
								./Source/core/memory/MemoryImpl.cpp
)

source_group("core\\multithreading" FILES
								./Source/core/multithreading/thread.cpp
)

include ( Include/containers/VectorInc.cmake )
include ( Include/containers/Unordered.cmake )
include ( Include/containers/PoliciesInc.cmake )

set( FREYA_SUPPORT_INCLUDES ${FREYA_SUPPORT_INCLUDES} 
Include/containers/type_utils.h 
Include/containers/utils.h
Include/containers/iterator.h
)
source_group( "Include\\containers" FILES Include/containers/type_utils.h Include/containers/utils.h Include/containers/iterator.h)

# Add UTF8CPP library 
include_directories( ../3party/utf8cpp )

if( FREYA_BUILD_SHARED )
	add_definitions( -D_FREYA_SUPPORT_SHARED_BUILD )
	add_library( FreyaSupport SHARED ${FREYA_SUPPORT_INCLUDES} ${FREYA_SUPPORT_SOURCES} )
	if(FREYA_USE_ICU)
		target_link_libraries( FreyaSupport ${ICU_LIBRARIES})
	endif()
	if(FREYA_USE_WINMM)
		target_link_libraries( FreyaSupport ${WINMM_LIBRARY})
	endif()
else()
	add_library( FreyaSupport STATIC ${FREYA_SUPPORT_INCLUDES} ${FREYA_SUPPORT_SOURCES} )
endif()

set_target_properties ( FreyaSupport PROPERTIES FOLDER "Core Libraries" )

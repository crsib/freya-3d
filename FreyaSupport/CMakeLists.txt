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
# core/memory
	Include/core/memory/MemoryAllocator.h
	Include/core/memory/MemoryArena.h
	Include/core/memory/MemoryPools.h
# core/multithreading
	Include/core/multithreading/thread.h
	Include/core/multithreading/thread_local.h
	Include/core/multithreading/mutex.h
	
	Include/core/multithreading/details/platform.h
	Include/core/multithreading/details/thread.h
	Include/core/multithreading/details/thread_local.h
	Include/core/multithreading/details/mutex.h
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
								Include/atomic/atomic.h
								Include/atomic/atomic-interface.h
								Include/atomic/memory_order.h
)

source_group("Include\\core\\multithreading" FILES
								./Include/core/multithreading/thread.h
								./Include/core/multithreading/thread_local.h
								./Include/core/multithreading/mutex.h
)
source_group("Include\\core\\multithreading\\details" FILES
								./Include/core/multithreading/details/platform.h
								./Include/core/multithreading/details/thread.h
								./Include/core/multithreading/details/thread_local.h
								./Include/core/multithreading/details/mutex.h
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
		add_definitions(-DPLATFORM_WIN_THREADS)
		set( FREYA_SUPPORT_INCLUDES ${FREYA_SUPPORT_INCLUDES}
									Include/core/multithreading/win32/thread.h
									Include/core/multithreading/win32/thread_local.h
									Include/core/multithreading/win32/mutex.h
		)
		source_group("Include\\core\\multithreading\\win32" FILES
						Include/core/multithreading/win32/thread.h
						Include/core/multithreading/win32/thread_local.h
						Include/core/multithreading/win32/mutex.h
		)
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
include ( Include/containers/PoliciesInc.cmake )

set( FREYA_SUPPORT_INCLUDES ${FREYA_SUPPORT_INCLUDES} Include/containers/type_utils.h )
source_group( "Include\\containers" FILES Include/containers/type_utils.h )

# Add UTF8CPP library 
include_directories( ../3party/utf8cpp )

if( FREYA_BUILD_SHARED )
	add_definitions( -D_FREYA_SUPPORT_SHARED_BUILD )
	add_library( FreyaSupport SHARED ${FREYA_SUPPORT_INCLUDES} ${FREYA_SUPPORT_SOURCES} )
	if(FREYA_USE_ICU)
		target_link_libraries( FreyaSupport ${ICU_LIBRARIES} )
	endif()
else()
	add_library( FreyaSupport STATIC ${FREYA_SUPPORT_INCLUDES} ${FREYA_SUPPORT_SOURCES} )
endif()
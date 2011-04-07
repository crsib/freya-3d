message ( STATUS " Generating build dependencies for FreyaSupport" )

# includes
set( FREYA_SUPPORT_INCLUDES 
	Include/FreyaSupportInternal.h
	Include/integer.h
# core
	Include/core/string.h
	Include/core/Log.h
	Include/core/Object.h
# core/memory
	Include/core/memory/MemoryAllocator.h
	Include/core/memory/MemoryArena.h
	Include/core/memory/MemoryPools.h
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

# sources
set( FREYA_SUPPORT_SOURCES
# core
	Source/core/string.cpp
	Source/core/Log.cpp
# core/memory
	Source/core/memory/MemoryImpl.cpp
)
# sources source groups			
source_group("core" FILES 
								./Source/core/string.cpp
								./Source/core/Log.cpp
)

source_group("core\\memory" FILES
								./Source/core/memory/MemoryImpl.cpp
)

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
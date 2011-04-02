message ( STATUS " Generating build dependencies for FreyaSupport" )

# includes
set( FREYA_SUPPORT_INCLUDES 
	Include/FreyaSupportInternal.h
# core/memory
	Include/core/memory/MemoryAllocator.h
	Include/core/memory/MemoryArena.h
	Include/core/memory/MemoryPools.h
)

# include source groups
source_group("" FILES ./Include/FreyaSupportInternal.h )

source_group("memory" FILES 
								./Include/core/memory/MemoryAllocator.h
								./Include/core/memory/MemoryArena.h
								./Include/core/memory/MemoryException.h
								./Include/core/memory/MemoryPools.h 
)

# sources
set( FREYA_SUPPORT_SOURCES
	Source/core/memory/MemoryImpl.cpp
)
# sources source groups			
source_group("memory" FILES
								./Source/core/memory/MemoryImpl.cpp
)

if( FREYA_BUILD_SHARED )
	add_definitions( -D_FREYA_SUPPORT_SHARED_BUILD )
	add_library( FreyaSupport SHARED ${FREYA_SUPPORT_INCLUDES} ${FREYA_SUPPORT_SOURCES} )
else()
	add_library( FreyaSupport STATIC ${FREYA_SUPPORT_INCLUDES} ${FREYA_SUPPORT_SOURCES} )
endif()
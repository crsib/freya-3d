set( FREYA_SUPPORT_INCLUDES ${FREYA_SUPPORT_INCLUDES}
Include/containers/details/hashtable.h
Include/containers/hash_map.h
Include/containers/hash_set.h
)

source_group( "Include\\containers" FILES 
				Include/containers/hash_map.h
				Include/containers/hash_set.h
			)
			
source_group( "Include\\containers\\details" FILES Include/containers/details/hashtable.h )

#set( FREYA_SUPPORT_SOURCES ${FREYA_SUPPORT_SOURCES}
#Source/containers/hashtable.cpp
#)

#source_group( "containers" FILES Source/containers/hashtable.cpp )
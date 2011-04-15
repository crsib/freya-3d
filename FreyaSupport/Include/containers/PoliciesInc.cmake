set( FREYA_SUPPORT_INCLUDES ${FREYA_SUPPORT_INCLUDES}
Include/containers/policies/memory/FreyaAllocator.h
Include/containers/policies/memory/Malloc.h
Include/containers/policies/memory/New.h

Include/containers/policies/multithreading/AtomicLock.h
Include/containers/policies/multithreading/NoLock.h

Include/containers/policies/storage/Exponential.h
Include/containers/policies/storage/FixedSize.h
Include/containers/policies/storage/Greedy.h

Include/containers/policies/Policies.h
)

source_group( "Include\\containers\\policies" FILES Include/containers/policies/Policies.h )

source_group( "Include\\containers\\policies\\memory" FILES 
				Include/containers/policies/memory/FreyaAllocator.h
				Include/containers/policies/memory/Malloc.h
				Include/containers/policies/memory/New.h 
			)
			
source_group( "Include\\containers\\policies\\multithreading" FILES
				Include/containers/policies/multithreading/AtomicLock.h
				Include/containers/policies/multithreading/NoLock.h
			)
			
source_group( "Include\\containers\\policies\\storage" FILES
				Include/containers/policies/storage/Exponential.h
				Include/containers/policies/storage/FixedSize.h
				Include/containers/policies/storage/Greedy.h
			)
set( FREYA_SUPPORT_INCLUDES ${FREYA_SUPPORT_INCLUDES}
	Include/core/policies/SmartPtrPolicies.h
	Include/core/policies/checking/Assert.h
	Include/core/policies/ownership/Intrusive.h
	Include/core/policies/ownership/RefCounted.h
	Include/core/policies/ownership/Scoped.h
	Include/core/policies/storage/Default.h
	Include/core/policies/storage/Array.h
)

source_group( "Include\\core\\policies" FILES Include/core/policies/SmartPtrPolicies.h )
source_group( "Include\\core\\policies\\checking" FILES Include/core/policies/checking/Assert.h )
source_group( "Include\\core\\policies\\ownership" FILES 
				Include/core/policies/ownership/Intrusive.h
				Include/core/policies/ownership/RefCounted.h
				Include/core/policies/ownership/Scoped.h	
			)
source_group( "Include\\core\\policies\\storage" FILES
				Include/core/policies/storage/Default.h
				Include/core/policies/storage/Array.h
			)
			
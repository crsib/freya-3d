message ( STATUS " Generating build dependencies for FreyaReflect" )

set( FREYA_REFLECT_INCLUDES 
	Include/FreyaReflectInternal.h
	Include/reflect/Class.h
	Include/reflect/Method.h
	Include/reflect/Namespace.h
	Include/reflect/Property.h
	Include/reflect/ReflectionDatabase.h
	Include/reflect/ReflectionModule.h
	Include/reflect/ReflectionObject.h
	Include/reflect/ReflectionConsumer.h
	Include/reflect/reflect_cast.h
	Include/reflect/Scope.h
)

set( FREYA_REFLECT_SOURCES
	Source/Class.cpp
	Source/Method.cpp
	Source/Namespace.cpp
	Source/Property.cpp
	Source/ReflectionDatabase.cpp
	Source/ReflectionModule.cpp
	Source/ReflectionObject.cpp
	Source/Scope.cpp
)

if( FREYA_BUILD_SHARED )
	add_definitions( -D_FREYA_REFLECT_SHARED_BUILD )
	add_library( FreyaReflect SHARED ${FREYA_REFLECT_INCLUDES} ${FREYA_REFLECT_SOURCES} )
	target_link_libraries( FreyaReflect FreyaSupport )
else()
	add_library( FreyaReflect STATIC ${FREYA_REFLECT_INCLUDES} ${FREYA_REFLECT_SOURCES} )
endif()

set_target_properties ( FreyaReflect PROPERTIES FOLDER "Core Libraries" )

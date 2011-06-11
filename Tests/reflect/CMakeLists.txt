message( STATUS "  Reflection tests" )

include_directories( ./ )

add_library( reflection_test_lib SHARED reflection_test.h reflection_test_dll.cpp )
target_link_libraries( reflection_test_lib FreyaSupport FreyaReflect )

add_library( reflection_test_static_lib STATIC reflection_test.h reflection_test_static.cpp )

add_executable( reflection_test reflection_test.h reflection_test.cpp )
target_link_libraries( reflection_test FreyaSupport FreyaReflect reflection_test_static_lib )

set_target_properties( 
					reflection_test_lib reflection_test_static_lib reflection_test 
					PROPERTIES FOLDER "Tests/FreyaReflect"
					 )


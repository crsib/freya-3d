message( STATUS "  Containers tests" )

add_executable( vector_tests vector.cpp )
target_link_libraries( vector_tests FreyaSupport )

add_executable( hashtable_tests hashtable_test.cpp )
target_link_libraries( hashtable_tests FreyaSupport )
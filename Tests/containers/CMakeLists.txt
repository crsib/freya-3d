message( STATUS "  Containers tests" )

add_executable( vector_tests vector.cpp )
target_link_libraries( vector_tests FreyaSupport )
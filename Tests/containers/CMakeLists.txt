message( STATUS "  Containers tests" )

add_executable( vector_test vector.cpp )
target_link_libraries( vector_test FreyaSupport )

add_executable( hashtable_test hashtable_test.cpp )
target_link_libraries( hashtable_test FreyaSupport )

add_executable( hashmap_perf hashmap_perf.cpp )
target_link_libraries( hashmap_perf FreyaSupport )

add_executable( hashmap_test hashmap_test.cpp )
target_link_libraries( hashmap_test FreyaSupport )

add_executable( hashset_test hashset_test.cpp )
target_link_libraries( hashset_test FreyaSupport )

set_target_properties( vector_test hashtable_test hashmap_perf hashmap_test hashset_test
						PROPERTIES
						FOLDER "Tests/FreyaSupport"
					)
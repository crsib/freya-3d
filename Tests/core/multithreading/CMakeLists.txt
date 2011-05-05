
add_executable( thread_test thread_test.cpp )
target_link_libraries( thread_test FreyaSupport )
set_target_properties( thread_test
						PROPERTIES
						FOLDER "Tests/FreyaSupport"
					)

add_executable( cond_sync_test cond_sync_test.cpp )
target_link_libraries( cond_sync_test FreyaSupport )
set_target_properties( cond_sync_test
						PROPERTIES
						FOLDER "Tests/FreyaSupport"
					)

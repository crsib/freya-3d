
add_executable( log_test log_test.cpp )
target_link_libraries( log_test FreyaSupport )

set_target_properties( log_test
						PROPERTIES
						FOLDER "Tests/FreyaSupport"
					)
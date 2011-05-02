
add_executable( smart_ptr_test smart_ptr.cpp )
target_link_libraries( smart_ptr_test FreyaSupport )

set_target_properties( smart_ptr_test
						PROPERTIES
						FOLDER "Tests/FreyaSupport"
					)
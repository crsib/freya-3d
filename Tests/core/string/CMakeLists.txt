
add_executable( string_test main.cpp )
target_link_libraries( string_test FreyaSupport )

set_target_properties( string_test
						PROPERTIES
						FOLDER "Tests/FreyaSupport"
					)
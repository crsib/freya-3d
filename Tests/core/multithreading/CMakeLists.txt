
add_executable( Multithreading_Test test.cpp )
target_link_libraries( Multithreading_Test FreyaSupport)

set_target_properties( Multithreading_Test
						PROPERTIES
						FOLDER "Tests/FreyaSupport"
					)
if( WIN32 )
	add_definitions(-DPLATFORM_WIN_THREADS)
elseif( UNIX OR APPLE)
	add_definitions(-DPLATFORM_POSIX_THREADS)
endif()

add_executable( Multithreading_Test test.cpp )
target_link_libraries( Multithreading_Test FreyaSupport)

set_target_properties( Multithreading_Test
						PROPERTIES
						FOLDER "Tests/FreyaSupport"
					)
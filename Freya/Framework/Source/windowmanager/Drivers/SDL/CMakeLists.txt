# plugins

IF(BUILD_SDL_WINDOWMANAGER_DRIVER) 
	
	#Retrieve SDL 1.3 Library
	
	FIND_PACKAGE ( SDL13 REQUIRED )
	MESSAGE ("SDL 1.3 found: ${SDL_FOUND}\n\tinclude: ${SDL_INCLUDE_DIR}\n\tlibs: ${SDL_LIBRARY}" )


	FIND_PACKAGE ( OpenGL REQUIRED )
	MESSAGE ("OpenGL for use with windowmanager:\n\tinclude: ${OPENGL_INCLUDE_DIR}\n\tlibs: ${OPENGL_LIBRARY}" )

	INCLUDE_DIRECTORIES (${SDL_INCLUDE_DIR} ../../..)
	
	SET(SDL_WINDOWMANAGER_DRIVER_SOURCE
		InputDeviceFactory.h
		InputDevices/ids/SDLKeyboardID.h
		InputDevices/ids/SDLMouseButtonsID.h
		InputDevices/ids/SDLMouseID.h
		InputDevices/SDLKeyboard.h
		InputDevices/SDLMouse.h
		InputDevices/SDLMouseButtons.h
		OpenGLSDLAPIInit.h
		SDLDriverID.h
		SDLManagerDriver.h
		InputDeviceFactory.cpp
		InputDevices/SDLKeyboard.cpp
		InputDevices/SDLKeyboardLookup.cpp
		InputDevices/SDLMouse.cpp
		InputDevices/SDLMouseButtons.cpp
		OpenGLSDLAPIInit.cpp
		SDLManagerDriver.cpp
	)
	
	
	IF(BUILD_SHARED_SDL_WINDOWMANAGER_DRIVER)
		MESSAGE("Building shared ")
		ADD_DEFINITIONS(-D_FREYA_SHARED_PLUGIN)
		ADD_LIBRARY( SDLWindowmanagerDriver MODULE ${SDL_WINDOWMANAGER_DRIVER_SOURCE} SDLWindowmanagerDriverSharedBuild.cpp ../../WMException.cpp)
		TARGET_LINK_LIBRARIES( SDLWindowmanagerDriver ${GLOBAL_LINK_LIBRARIES} ${SDL_LIBRARY} ${OPENGL_LIBRARY})
		SET_TARGET_PROPERTIES ( SDLWindowmanagerDriver PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Plugins)
		AddPlugin( SDLWindowmanagerDriver )
	ELSE(BUILD_SHARED_SDL_WINDOWMANAGER_DRIVER)
		ADD_LIBRARY( SDLWindowmanagerDriver STATIC ${SDL_WINDOWMANAGER_DRIVER_SOURCE} SDLWindowmanagerDriverStaticBuild.cpp)
		SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} SDLWindowmanagerDriver ${SDL_LIBRARY} ${OPENGL_LIBRARY})
		SET_PROPERTY( GLOBAL PROPERTY FREYA_CORE_LINK_LIBRARIES_GLOBAL ${FREYA_CORE_LINK_LIBRARIES})
		AddWindowManagerPlugin( SDLDriver )
	ENDIF(BUILD_SHARED_SDL_WINDOWMANAGER_DRIVER)
ENDIF(BUILD_SDL_WINDOWMANAGER_DRIVER)

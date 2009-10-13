# plugins

IF(BUILD_OPENGL_RENDERER_DRIVER) 
	
	INCLUDE_DIRECTORIES( ../../.. )
	
	FIND_PACKAGE ( OpenGL REQUIRED )
	MESSAGE ( "OpenGL for use with renderer:\n\tinclude: ${OPENGL_INCLUDE_DIR}\n\tlibs: ${OPENGL_LIBRARY}" )
	
	MESSAGE( "Configuring GLEW" )
	
	SET( GLEW_SOURCES 
		GLEW/glew.c
		GLEW/glew.h
		GLEW/glxew.h
		GLEW/wglew.h	
	)
	
	ADD_LIBRARY( GLEW ${GLEW_SOURCES} )
	
	SET(OPENGL_SM3_SIMPLE_RENDERER_DRIVER_SOURCE
		OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_Simple.h
		OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Shader_SM3_Simple.h
		OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Texture_SM3_Simple.h
		OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_Simple.h
		OpenGL15Driver/OpenGL_GLSL_Driver_SM3_Simple.h
		OpenGL15Driver/OpenGL_GLSL_SM3_Simple.h
		OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_Simple.cpp
		OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Shader_SM3_Simple.cpp
		OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Texture_SM3_Simple.cpp
		OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_Simple.cpp
		OpenGL15Driver/OpenGL_GLSL_Driver_SM3_Simple.cpp

	)
	
	SET(OPENGL_CROSS_SOURCES
		OpenGL_GLSL_ConstantsTables.h
		OpenGL_GLSL_ConstantsTables.cpp
		../../../math/MathSubsystem.cpp
		../../../math/operations.cpp
	)
	
	IF(BUILD_SHARED_OPENGL_RENDERER_DRIVER)
		MESSAGE("Building shared ")
		ADD_DEFINITIONS(-D_FREYA_SHARED_PLUGIN)
		#SM3 simple
		ADD_LIBRARY( OpenGL15Driver MODULE ${OPENGL_SM3_SIMPLE_RENDERER_DRIVER_SOURCE} SM3SimpleDriverSharedBuild.cpp ${OPENGL_CROSS_SOURCES})
		TARGET_LINK_LIBRARIES( OpenGL15Driver ${GLOBAL_LINK_LIBRARIES} GLEW ${OPENGL_LIBRARY} )
		SET_TARGET_PROPERTIES ( OpenGL15Driver PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Plugins)
		AddPlugin( OpenGL15Driver )
	ELSE(BUILD_SHARED_OPENGL_RENDERER_DRIVER)
		ADD_LIBRARY( OpenGLDriver STATIC ${OPENGL_SM3_SIMPLE_RENDERER_DRIVER_SOURCE}  OpenGL_GLSL_ConstantsTables.h	OpenGL_GLSL_ConstantsTables.cpp OpenGLDriverStaticBuild.cpp)
		SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} OpenGLDriver GLEW ${OPENGL_LIBRARY} )
		SET_PROPERTY( GLOBAL PROPERTY FREYA_CORE_LINK_LIBRARIES_GLOBAL ${FREYA_CORE_LINK_LIBRARIES})
		AddRendererPlugin( OpenGLDriver )
	ENDIF(BUILD_SHARED_OPENGL_RENDERER_DRIVER)
ENDIF(BUILD_OPENGL_RENDERER_DRIVER)

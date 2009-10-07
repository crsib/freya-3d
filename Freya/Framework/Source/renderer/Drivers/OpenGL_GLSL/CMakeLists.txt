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
	
	SET(OPENGL_SM4_RENDERER_DRIVER_SOURCE
		SM4_Full/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM4_Full.h
		SM4_Full/DriverSubsystems/OpenGL_GLSL_Shader_SM4_Full.h
		SM4_Full/DriverSubsystems/OpenGL_GLSL_Texture_SM4_Full.h
		SM4_Full/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM4_Full.h
		SM4_Full/OpenGL_GLSL_Driver_SM4_Full.h
		SM4_Full/OpenGL_GLSL_SM4_Full.h
		SM4_NoDS/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM4_NoDS.h
		SM4_NoDS/DriverSubsystems/OpenGL_GLSL_Shader_SM4_NoDS.h
		SM4_NoDS/DriverSubsystems/OpenGL_GLSL_Texture_SM4_NoDS.h
		SM4_NoDS/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM4_NoDS.h
		SM4_NoDS/OpenGL_GLSL_Driver_SM4_NoDS.h
		SM4_NoDS/OpenGL_GLSL_SM4_NoDS.h
		SM4_NoMRT/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM4_NoMRT.h
		SM4_NoMRT/DriverSubsystems/OpenGL_GLSL_Shader_SM4_NoMRT.h
		SM4_NoMRT/DriverSubsystems/OpenGL_GLSL_Texture_SM4_NoMRT.h
		SM4_NoMRT/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM4_NoMRT.h
		SM4_NoMRT/OpenGL_GLSL_Driver_SM4_NoMRT.h
		SM4_NoMRT/OpenGL_GLSL_SM4_NoMRT.h
		SM4_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM4_NoMRTDS.h
		SM4_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Shader_SM4_NoMRTDS.h
		SM4_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Texture_SM4_NoMRTDS.h
		SM4_NoMRTDS/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM4_NoMRTDS.h
		SM4_NoMRTDS/OpenGL_GLSL_Driver_SM4_NoMRTDS.h
		SM4_NoMRTDS/OpenGL_GLSL_SM4_NoMRTDS.h
		SM4_Full/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM4_Full.cpp
		SM4_Full/DriverSubsystems/OpenGL_GLSL_Shader_SM4_Full.cpp
		SM4_Full/DriverSubsystems/OpenGL_GLSL_Texture_SM4_Full.cpp
		SM4_Full/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM4_Full.cpp
		SM4_Full/OpenGL_GLSL_Driver_SM4_Full.cpp
		SM4_NoDS/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM4_NoDS.cpp
		SM4_NoDS/DriverSubsystems/OpenGL_GLSL_Shader_SM4_NoDS.cpp
		SM4_NoDS/DriverSubsystems/OpenGL_GLSL_Texture_SM4_NoDS.cpp
		SM4_NoDS/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM4_NoDS.cpp
		SM4_NoDS/OpenGL_GLSL_Driver_SM4_NoDS.cpp
		SM4_NoMRT/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM4_NoMRT.cpp
		SM4_NoMRT/DriverSubsystems/OpenGL_GLSL_Shader_SM4_NoMRT.cpp
		SM4_NoMRT/DriverSubsystems/OpenGL_GLSL_Texture_SM4_NoMRT.cpp
		SM4_NoMRT/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM4_NoMRT.cpp
		SM4_NoMRT/OpenGL_GLSL_Driver_SM4_NoMRT.cpp
		SM4_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM4_NoMRTDS.cpp
		SM4_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Shader_SM4_NoMRTDS.cpp
		SM4_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Texture_SM4_NoMRTDS.cpp
		SM4_NoMRTDS/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM4_NoMRTDS.cpp
		SM4_NoMRTDS/OpenGL_GLSL_Driver_SM4_NoMRTDS.cpp
	)
	
	SET(OPENGL_SM3_RENDERER_DRIVER_SOURCE
		SM3_Full/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_Full.h
		SM3_Full/DriverSubsystems/OpenGL_GLSL_Shader_SM3_Full.h
		SM3_Full/DriverSubsystems/OpenGL_GLSL_Texture_SM3_Full.h
		SM3_Full/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_Full.h
		SM3_Full/OpenGL_GLSL_Driver_SM3_Full.h
		SM3_Full/OpenGL_GLSL_SM3_Full.h
		SM3_NoDS/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_NoDS.h
		SM3_NoDS/DriverSubsystems/OpenGL_GLSL_Shader_SM3_NoDS.h
		SM3_NoDS/DriverSubsystems/OpenGL_GLSL_Texture_SM3_NoDS.h
		SM3_NoDS/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_NoDS.h
		SM3_NoDS/OpenGL_GLSL_Driver_SM3_NoDS.h
		SM3_NoDS/OpenGL_GLSL_SM3_NoDS.h
		SM3_NoMRT/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_NoMRT.h
		SM3_NoMRT/DriverSubsystems/OpenGL_GLSL_Shader_SM3_NoMRT.h
		SM3_NoMRT/DriverSubsystems/OpenGL_GLSL_Texture_SM3_NoMRT.h
		SM3_NoMRT/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_NoMRT.h
		SM3_NoMRT/OpenGL_GLSL_Driver_SM3_NoMRT.h
		SM3_NoMRT/OpenGL_GLSL_SM3_NoMRT.h
		SM3_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_NoMRTDS.h
		SM3_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Shader_SM3_NoMRTDS.h
		SM3_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Texture_SM3_NoMRTDS.h
		SM3_NoMRTDS/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_NoMRTDS.h
		SM3_NoMRTDS/OpenGL_GLSL_Driver_SM3_NoMRTDS.h
		SM3_NoMRTDS/OpenGL_GLSL_SM3_NoMRTDS.h
		SM3_Full/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_Full.cpp
		SM3_Full/DriverSubsystems/OpenGL_GLSL_Shader_SM3_Full.cpp
		SM3_Full/DriverSubsystems/OpenGL_GLSL_Texture_SM3_Full.cpp
		SM3_Full/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_Full.cpp
		SM3_Full/OpenGL_GLSL_Driver_SM3_Full.cpp
		SM3_NoDS/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_NoDS.cpp
		SM3_NoDS/DriverSubsystems/OpenGL_GLSL_Shader_SM3_NoDS.cpp
		SM3_NoDS/DriverSubsystems/OpenGL_GLSL_Texture_SM3_NoDS.cpp
		SM3_NoDS/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_NoDS.cpp
		SM3_NoDS/OpenGL_GLSL_Driver_SM3_NoDS.cpp
		SM3_NoMRT/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_NoMRT.cpp
		SM3_NoMRT/DriverSubsystems/OpenGL_GLSL_Shader_SM3_NoMRT.cpp
		SM3_NoMRT/DriverSubsystems/OpenGL_GLSL_Texture_SM3_NoMRT.cpp
		SM3_NoMRT/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_NoMRT.cpp
		SM3_NoMRT/OpenGL_GLSL_Driver_SM3_NoMRT.cpp
		SM3_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_NoMRTDS.cpp
		SM3_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Shader_SM3_NoMRTDS.cpp
		SM3_NoMRTDS/DriverSubsystems/OpenGL_GLSL_Texture_SM3_NoMRTDS.cpp
		SM3_NoMRTDS/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_NoMRTDS.cpp
		SM3_NoMRTDS/OpenGL_GLSL_Driver_SM3_NoMRTDS.cpp

	)
	
	SET(OPENGL_SM3_SIMPLE_RENDERER_DRIVER_SOURCE
		SM3_Simple/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_Simple.h
		SM3_Simple/DriverSubsystems/OpenGL_GLSL_Shader_SM3_Simple.h
		SM3_Simple/DriverSubsystems/OpenGL_GLSL_Texture_SM3_Simple.h
		SM3_Simple/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_Simple.h
		SM3_Simple/OpenGL_GLSL_Driver_SM3_Simple.h
		SM3_Simple/OpenGL_GLSL_SM3_Simple.h
		SM3_Simple/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_Simple.cpp
		SM3_Simple/DriverSubsystems/OpenGL_GLSL_Shader_SM3_Simple.cpp
		SM3_Simple/DriverSubsystems/OpenGL_GLSL_Texture_SM3_Simple.cpp
		SM3_Simple/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_Simple.cpp
		SM3_Simple/OpenGL_GLSL_Driver_SM3_Simple.cpp

	)
	
	SET(OPENGL_CROSS_SOURCES
		OpenGL_GLSL_ConstantsTables.h
		OpenGL_GLSL_ConstantsTables.cpp
		../../../math/MathSubsystem.cpp
		../../../math/Operations.cpp
	)
	
	IF(BUILD_SHARED_OPENGL_RENDERER_DRIVER)
		MESSAGE("Building shared ")
		ADD_DEFINITIONS(-D_FREYA_SHARED_PLUGIN)
		#SM3
		ADD_LIBRARY( OpenGLSM3Driver MODULE ${OPENGL_SM3_RENDERER_DRIVER_SOURCE} SM3DriverSharedBuild.cpp ${OPENGL_CROSS_SOURCES})
		TARGET_LINK_LIBRARIES( OpenGLSM3Driver ${GLOBAL_LINK_LIBRARIES} GLEW ${OPENGL_LIBRARY} )
		SET_TARGET_PROPERTIES ( OpenGLSM3Driver PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Plugins)
		#SM3 simple
		ADD_LIBRARY( OpenGLSimpleDriver MODULE ${OPENGL_SM3_SIMPLE_RENDERER_DRIVER_SOURCE} SM3SimpleDriverSharedBuild.cpp ${OPENGL_CROSS_SOURCES})
		TARGET_LINK_LIBRARIES( OpenGLSimpleDriver ${GLOBAL_LINK_LIBRARIES} GLEW ${OPENGL_LIBRARY} )
		SET_TARGET_PROPERTIES ( OpenGLSimpleDriver PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Plugins)
		#SM4
		ADD_LIBRARY( OpenGLSM4Driver MODULE ${OPENGL_SM4_RENDERER_DRIVER_SOURCE} SM4DriverSharedBuild.cpp ${OPENGL_CROSS_SOURCES})
		TARGET_LINK_LIBRARIES( OpenGLSM4Driver ${GLOBAL_LINK_LIBRARIES} GLEW ${OPENGL_LIBRARY} )
		SET_TARGET_PROPERTIES ( OpenGLSM4Driver PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Plugins)
		AddPlugin( OpenGLSM3Driver )
		AddPlugin( OpenGLSimpleDriver )
		AddPlugin( OpenGLSM4Driver )
	ELSE(BUILD_SHARED_OPENGL_RENDERER_DRIVER)
		ADD_LIBRARY( OpenGLDriver STATIC ${OPENGL_SM3_RENDERER_DRIVER_SOURCE} ${OPENGL_SM3_SIMPLE_RENDERER_DRIVER_SOURCE} 
						${OPENGL_SM4_RENDERER_DRIVER_SOURCE} OpenGL_GLSL_ConstantsTables.h	OpenGL_GLSL_ConstantsTables.cpp OpenGLDriverStaticBuild.cpp)
		SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} OpenGLDriver GLEW ${OPENGL_LIBRARY} )
		SET_PROPERTY( GLOBAL PROPERTY FREYA_CORE_LINK_LIBRARIES_GLOBAL ${FREYA_CORE_LINK_LIBRARIES})
		AddRendererPlugin( OpenGLDriver )
	ENDIF(BUILD_SHARED_OPENGL_RENDERER_DRIVER)
ENDIF(BUILD_OPENGL_RENDERER_DRIVER)

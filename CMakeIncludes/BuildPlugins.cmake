INCLUDE( AddPlugin )

#Standart filesystem plugins

#Defaults are Local & LZMA filesystems. Both build dynamicaly
MESSAGE( "Configuring filesystem plugins" )
SET(BUILD_LOCAL_FILESYSTEM_DRIVER YES)
SET(BUILD_SHARED_LOCAL_FILESYSTEM_DRIVER YES)

SET(BUILD_LZMA_FILESYSTEM_DRIVER  YES)
SET(BUILD_SHARED_LZMA_FILESYSTEM_DRIVER  YES)
GET_PROPERTY ( FREYA_CORE_LINK_LIBRARIES GLOBAL PROPERTY FREYA_CORE_LINK_LIBRARIES_GLOBAL )
ADD_SUBDIRECTORY( Framework/Source/core/filesystem/drivers )

#Window manager plugins

GET_PROPERTY ( FREYA_CORE_LINK_LIBRARIES GLOBAL PROPERTY FREYA_CORE_LINK_LIBRARIES_GLOBAL )

#Default is SDL driver.
MESSAGE( "Configuring windowmanager plugins. This will be changed with with input plugins in future releases" )

SET( BUILD_SDL_WINDOWMANAGER_DRIVER YES )
SET( BUILD_SHARED_SDL_WINDOWMANAGER_DRIVER YES )

ADD_SUBDIRECTORY ( Framework/Source/windowmanager/Drivers/SDL )

#Renderer plugins

#Default is various version of OpenGL plugins.

MESSAGE( "Configuring renderer plugins. This will highly changed in the future" )

GET_PROPERTY ( FREYA_CORE_LINK_LIBRARIES GLOBAL PROPERTY FREYA_CORE_LINK_LIBRARIES_GLOBAL )

SET( BUILD_OPENGL_RENDERER_DRIVER YES )
SET( BUILD_SHARED_OPENGL_RENDERER_DRIVER YES )

ADD_SUBDIRECTORY( Framework/Source/renderer/Drivers/OpenGL_GLSL )

#Resource drivers

#TGA + DDS (not ready yet) for now.

GET_PROPERTY ( FREYA_CORE_LINK_LIBRARIES GLOBAL PROPERTY FREYA_CORE_LINK_LIBRARIES_GLOBAL )

MESSAGE ( "Configuring resource subsystem plugins" )

SET( BUILD_TGA_DRIVER YES )
SET( BUILD_SHARED_TGA_DRIVER YES )

SET( BUILD_DDS_DRIVER YES )
SET( BUILD_SHARED_DDS_DRIVER YES )

ADD_SUBDIRECTORY ( Framework/Source/resources/drivers )


MESSAGE("Generating build dependencies for FreyaCore")
MESSAGE(STATUS "Building Framework using: ${CMAKE_BUILD_TYPE}")
SET(FREYA_CORE_SOURCES 
#Application settings global include  
Include/application-settings.h
Include/camera/BasicCamera.h
Include/camera/FlyCamera.h
Include/camera/RotateCamera.h
Include/config.h
Include/core/PluginCore.h
Include/core/drivermodel/Driver.h
Include/core/drivermodel/DriverException.h
Include/core/drivermodel/DriverFactory.h
Include/core/drivermodel/DriverID.h
Include/core/EngineCore.h
Include/core/EngineException.h
Include/core/EngineSubsystem.h
Include/core/EString.h
Include/core/EStringList.h
Include/core/filesystem/Filesystem.h
Include/core/filesystem/FilesystemDriver.h
Include/core/filesystem/FilesystemException.h
Include/core/memory/MemoryAllocator.h
Include/core/memory/MemoryArena.h
Include/core/memory/MemoryException.h
Include/core/multithreading/Condition.h
Include/core/multithreading/ImplementationFactory.h
Include/core/multithreading/Lock.h
Include/core/multithreading/Mutex.h
Include/core/multithreading/RingBuffer.h
Include/core/multithreading/Runnable.h
Include/core/multithreading/Thread.h
Include/core/multithreading/ThreadBlocks.h
Include/core/multithreading/ThreadID.h
Include/core/taskmanager/Shutdown.h
Include/core/taskmanager/Task.h
Include/core/taskmanager/TaskManager.h
Include/core/Utils/StringUtils.h
Include/core/Variable.h
Include/core.h
Include/doxygen.h
Include/freya.h
Include/internal.h
Include/primitives/Cube.h
Include/primitives/Sphere.h
Include/renderer/3DConstants.h
Include/renderer/DriverException.h
Include/renderer/DriverSubsystems/Framebuffer.h
Include/renderer/DriverSubsystems/Shader.h
Include/renderer/DriverSubsystems/ShaderException.h
Include/renderer/DriverSubsystems/Texture.h
Include/renderer/DriverSubsystems/VertexBufferObject.h
Include/renderer/RenderingAPIDriver.h
Include/renderer.h
Include/resources/Resource.h
Include/resources/ResourceException.h
Include/resources/ResourceManager.h
Include/resources/ResourceManagerDriver.h
Include/resources.h
Include/windowmanager/Callback.h
Include/windowmanager/DriverSubsystems/InputDevices/KeyboardKeys.h
Include/windowmanager/DriverSubsystems/InputDevices/KeyDrivenDevice.h
Include/windowmanager/DriverSubsystems/InputDevices/MouseButtons.h
Include/windowmanager/DriverSubsystems/InputDevices/MovementDrivenDevice.h
Include/windowmanager/WindowManagerDriver.h
Include/windowmanager/WMException.h
Include/windowmanager.h
#Sources and private includes
Source/core/filesystem/FilesystemDriverFactory.h
#Source/core/memory/MemoryBuffer.h
#Source/core/memory/MemoryHeader.h
#Source/core/memory/MemoryHeaderList.h
#Source/core/memory/MemoryPool.h
Source/core/multithreading/implementations/boost_thread/BoostCondition.h
Source/core/multithreading/implementations/boost_thread/BoostMutex.h
Source/core/multithreading/implementations/boost_thread/BoostThread.h
Source/core/multithreading/implementations/boost_thread/BoostThreadID.h
Source/core/multithreading/implementations/boost_thread/ImplementationFactory.h
Source/core/taskmanager/TaskThread.h
Source/renderer/RenderingAPIFactory.h
Source/resources/ResourceFactory.h
Source/resources/ResourceLibrary.h
Source/windowmanager/WindowManagerFactory.h

Source/application-settings.cpp
Source/camera/FlyCamera.cpp
Source/camera/RotateCamera.cpp
Source/core/EngineCore.cpp
Source/core/filesystem/boost_stlport_fix.cpp
Source/core/filesystem/Filesystem.cpp
Source/core/filesystem/FilesystemDriverFactory.cpp
#Source/core/memory/MemoryArena.cpp
#Source/core/memory/MemoryBuffer.cpp
#Source/core/memory/MemoryHeaderList.cpp
#Source/core/memory/MemoryPool.cpp
Source/core/memory/MemoryImpl.cpp
Source/core/multithreading/implementations/boost_thread/BoostThread.cpp
Source/core/multithreading/implementations/boost_thread/BoostThreadBlocks.cpp
Source/core/taskmanager/Shutdown.cpp
Source/core/taskmanager/Task.cpp
Source/core/taskmanager/TaskManager.cpp
Source/core/taskmanager/TaskThread.cpp
Source/core/Utils/StringUtils.cpp
Source/core/Variable.cpp
Source/primitives/Cube.cpp
Source/renderer/RenderingAPIFactory.cpp
Source/resources/Resource.cpp
Source/resources/ResourceLibrary.cpp
Source/resources/ResourceManager.cpp
Source/resources/ResourceFactory.cpp
Source/windowmanager/KeyboardKeysNames.cpp
Source/windowmanager/MouseButtonsNames.cpp
Source/windowmanager/WindowManagerFactory.cpp
Source/windowmanager/WMException.cpp
Source/core/PluginCore.cpp
#Plugin subsystem
Include/core/PluginLoader.h
Source/core/PluginLoader.cpp
#Log buffer
Source/core/freya_buf.hpp
#Lua headers
Include/core/lua/FunctionException.h
Include/core/lua/LuaCore.h
Include/core/lua/LuaException.h
Include/core/lua/LuaFunction.h
Include/core/lua/tolua++/tolua++.h
Include/core/lua/VariableException.h
#Lua dependencies
Source/core/lua/lua_libraries/init_math.h
Source/core/lua/lua_libraries/jit_code.h
Source/core/lua/lua_libraries/lua_alloc.h
Source/core/lua/lua_libraries/lua_libs.h
Source/core/lua/lua_libraries/wrap_math.h
Source/core/lua/tolua++/tolua_event.h

Source/core/lua/lua_libraries/init_math.cpp
Source/core/lua/lua_libraries/jit_code.cpp
Source/core/lua/lua_libraries/lua_alloc.cpp
Source/core/lua/lua_libraries/lua_libs.cpp
Source/core/lua/lua_libraries/wrap_math.cpp
Source/core/lua/LuaCore.cpp
Source/core/lua/LuaFunction.cpp

#tolua++
Source/core/lua/tolua++/tolua_event.c
Source/core/lua/tolua++/tolua_is.c
Source/core/lua/tolua++/tolua_map.c
Source/core/lua/tolua++/tolua_push.c
Source/core/lua/tolua++/tolua_to.c

Source/core/lua/lua_libraries/3party/bit.c

Source/resources/drivers/std/ShaderLoaderDriver.cpp

#Scene graph
Include/scenegraph/Structures.h
Source/scenegraph/SceneGraphImpl.cpp
Include/scenegraph/World.h
Source/scenegraph/World.cpp
Include/scenegraph/AABB.h
Include/scenegraph/SceneNode.h
Source/scenegraph/SceneNode.cpp

Include/scenegraph/StaticGeometryNode.h
Source/scenegraph/StaticGeometryNode.cpp

#Scene graph loaders
Source/resources/drivers/std/VDataLoader.h
Source/resources/drivers/std/VDataLoader.cpp

#Generated sources
"${INTERMIDIATE_DIRECTORY}/StaticPluginsLoader.cpp"
"${INTERMIDIATE_DIRECTORY}/freya_lua_bind.cpp"
)

SET( FREYA_CEGUI_SRC 
./3party/cegui/src/freya/FreyaResourceProvider.cpp
./3party/cegui/src/freya/FreyaGeometryBuffer.cpp
./3party/cegui/src/freya/FreyaRenderer.cpp
./3party/cegui/src/freya/FreyaRenderTarget.cpp
./3party/cegui/src/freya/FreyaTexture.cpp
./3party/cegui/src/freya/FreyaTextureTarget.cpp
./3party/cegui/src/freya/FreyaWindowTarget.cpp
)

SET(TOLUA_PACKAGES
./Source/core/lua/lua_packages/core/EngineCore.lpkg
./Source/core/lua/lua_packages/core/Filesystem.lpkg
./Source/core/lua/lua_packages/core/MemoryArena.lpkg
./Source/core/lua/lua_packages/core/MemoryPools.lpkg
./Source/core/lua/lua_packages/core/Task.lpkg
./Source/core/lua/lua_packages/core/TaskManager.lpkg
./Source/core/lua/lua_packages/luabind.lpkg
./Source/core/lua/lua_packages/math/frustum.lpkg
./Source/core/lua/lua_packages/math/matrix3x3.lpkg
./Source/core/lua/lua_packages/math/matrix4x4.lpkg
./Source/core/lua/lua_packages/math/plane.lpkg
./Source/core/lua/lua_packages/math/quaternion.lpkg
./Source/core/lua/lua_packages/math/vector3d.lpkg
./Source/core/lua/lua_packages/math/wrap_math.lpkg
./Source/core/lua/lua_packages/renderer/Framebuffer.lpkg
./Source/core/lua/lua_packages/renderer/RenderingAPIDriver.lpkg
./Source/core/lua/lua_packages/renderer/Shader.lpkg
./Source/core/lua/lua_packages/renderer/Texture.lpkg
./Source/core/lua/lua_packages/renderer/VertexBufferObject.lpkg
./Source/core/lua/lua_packages/resource/Resource.lpkg
./Source/core/lua/lua_packages/resource/ResourceManager.lpkg
./Source/core/lua/lua_packages/windowmanager/Callback.lpkg
./Source/core/lua/lua_packages/windowmanager/KeyboardKeys.lpkg
./Source/core/lua/lua_packages/windowmanager/KeyDrivenDevice.lpkg
./Source/core/lua/lua_packages/windowmanager/MouseButtons.lpkg
./Source/core/lua/lua_packages/windowmanager/MovementDrivenDevice.lpkg
./Source/core/lua/lua_packages/windowmanager/WindowManagerDriver.lpkg
./Source/core/lua/lua_packages/lua_debug.lua
./Source/core/lua/lua_packages/virtual_method_hooks.lua
)

INCLUDE_DIRECTORIES( 3party/cegui/include
    3party/cegui/include/elements 
    3party/cegui/include/falagard 
    3party/cegui/include
    3party/cegui/include/ScriptingModules/LuaScriptModule 
    3party/cegui/include/WindowRendererSets/Falagard 
    3party/cegui/include/XMLParserModules/XercesParser
    3party/cegui/src/ScriptingModules/LuaScriptModule AFTER)

SET_SOURCE_FILES_PROPERTIES("${INTERMIDIATE_DIRECTORY}/StaticPluginsLoader.cpp" PROPERTIES GENERATED YES)
SET_SOURCE_FILES_PROPERTIES("${INTERMIDIATE_DIRECTORY}/freya_lua_bind.cpp" PROPERTIES GENERATED YES)
#EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/Framework/Include/core/lua/tolua++/tolua++.h" "${INTERMIDIATE_DIRECTORY}/tolua++.h")

MESSAGE(STATUS "Searching tolua") 
FIND_PROGRAM( TOLUA_APP NAMES tolua tolua++ tolua++5 tolua++5.1 PATH ${TOLUA_APP_PATH} )
IF( NOT TOLUA_APP )
    MESSAGE(FATAL_ERROR "Failed to find tolua++ application. Please,set TOLUA_APP_PATH to path, where one of tolua, tolua++, tolua++5, tolua++5.1 is located" )
ENDIF( NOT TOLUA_APP )

MESSAGE(STATUS "Generating bind file using ${TOLUA_APP}..." )



ADD_CUSTOM_COMMAND(OUTPUT "${INTERMIDIATE_DIRECTORY}/freya_lua_bind.cpp"
                    COMMAND ${TOLUA_APP} -n freya -L virtual_method_hooks.lua -L "${CMAKE_SOURCE_DIR}/Framework/3party/cegui/src/ScriptingModules/LuaScriptModule/package/exceptions.lua" -o "${INTERMIDIATE_DIRECTORY}/freya_lua_bind.cpp" luabind.lpkg
                    DEPENDS  ${TOLUA_PACKAGES}
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Framework/Source/core/lua/lua_packages
                    VERBATIM)

#EXECUTE_PROCESS(COMMAND ${TOLUA_APP} -n freya -L virtual_method_hooks.lua -L lua_debug.lua -L "${CMAKE_SOURCE_DIR}/Framework/3party/cegui/src/ScriptingModules/LuaScriptModule/package/exceptions.lua" -o "${INTERMIDIATE_DIRECTORY}/freya_lua_bind.cpp" luabind.lpkg 
 #                           WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Framework/Source/core/lua/lua_packages 
  #                          OUTPUT_VARIABLE TOLUA_OUT ERROR_VARIABLE TOLUA_ERROR)
MESSAGE(STATUS "Done\n\tOutput: ${TOLUA_OUT}\n\tErrors: ${TOLUA_ERROR}" )

#MESSAGE(STATUS "Searching lua")
#FIND_PROGRAM( LUA_APP NAMES lua lua51 lua5 lua5.1 PATH ${LUA_APP_PATH} )
#IF( NOT LUA_APP )
#    MESSAGE(FATAL_ERROR "Failed to find lua application. Please,set LUA_APP_PATH to path, where one of lua lua51 lua5 lua5.1 is located" )
#ENDIF( NOT LUA_APP )
#
#EXECUTE_PROCESS(COMMAND ${LUA_APP} ${GENERATORS_DIRECTORY}/XMLStrings.lua 
#                            WORKING_DIRECTORY ${INTERMIDIATE_DIRECTORY} 
#                            OUTPUT_VARIABLE LUA_OUT ERROR_VARIABLE LUA_ERROR)
#MESSAGE(STATUS "Done generating static xml strings\n\tOutput: ${LUA_OUT}\n\tErrors: ${LUA_ERROR}" )

#Search for boost.thread and boost.date_time 
IF( FREYA_CORE_USE_BOOST )
	SET(Boost_USE_STATIC_LIBS   NO)
	SET(Boost_USE_MULTITHREADED YES)
	FIND_PACKAGE ( BoostSTLPort 1.40 REQUIRED COMPONENTS filesystem system thread date_time )
	MESSAGE ("Boost flags for FreyaCore \n\tinclude: ${Boost_INCLUDE_DIRS} \n\tlibs: ${Boost_LIBRARIES}" )
	INCLUDE_DIRECTORIES ( ${Boost_INCLUDE_DIRS} )
	SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} ${Boost_LIBRARIES} )
ENDIF( FREYA_CORE_USE_BOOST )
INCLUDE_DIRECTORIES ( Source )
#Find lua

FIND_PACKAGE( Lua51 REQUIRED )
IF ( LUA51_FOUND )
    INCLUDE_DIRECTORIES( ${LUA_INCLUDE_DIR} )
    SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} ${LUA_LIBRARIES} )
    FILE(WRITE "${INTERMIDIATE_DIRECTORY}/Tests/LuaJIT/jit_available.c" "#include <lua.h>\nLUA_API int (luaopen_jit) (lua_State *L);\n\nint main(int argc,char** argv)\n{\n\tluaopen_jit(0);\n\treturn 0;\n}\n")

    TRY_COMPILE(LUA_JIT_FOUND "${INTERMIDIATE_DIRECTORY}/Tests/LuaJIT" "${INTERMIDIATE_DIRECTORY}/Tests/LuaJIT/jit_available.c" CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${LUA_INCLUDE_DIR}" "-DLINK_LIBRARIES:STRING=${LUA_LIBRARIES}" OUTPUT_VARIABLE LUA_JIT_OUTPUT )
    MESSAGE("LuaJIT trycompile: \n\toutput: ${LUA_JIT_OUTPUT}")
    IF( LUA_JIT_FOUND )
        MESSAGE(STATUS "LuaJIT found!" )
        ADD_DEFINITIONS( -DLUA_JIT_AVAILABLE )
    ENDIF( LUA_JIT_FOUND )
    IF( UNIX AND NOT APPLE )
		SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} dl )
    ENDIF( UNIX AND NOT APPLE )
ENDIF ( LUA51_FOUND )

#Find Freetype
FIND_PACKAGE(Freetype REQUIRED)

IF( FREETYPE_FOUND )
    INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
    SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} ${FREETYPE_LIBRARIES} )
ENDIF()

#Find PCRE
FIND_PACKAGE(PCRE REQUIRED)

IF ( PCRE_FOUND )
    INCLUDE_DIRECTORIES(${PCRE_INCLUDE_DIRS})
    SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} ${PCRE_LIBRARIES} )
ENDIF()
#Link to 
MESSAGE( "Preparing 3party libs configuration" )
add_subdirectory( ./3party )  

SET(FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} cegui-freya ${BULLET_LIBRARIES} FreyaMath_core )

#Generate library target depending on FREYA_CORE_SHARED

ADD_DEFINITIONS( -DTOLUA_RELEASE )
ADD_DEFINITIONS( -DCEGUITGAIMAGECODEC_EXPORTS -DCEGUIBASE_EXPORTS -DCEGUILUA_EXPORTS -DCEGUITINYXMLPARSER_EXPORTS -DCEGUI_WITH_TINYXML -DFALAGARDWRBASE_EXPORTS -DCEGUI_FALAGARD_RENDERER -DCEGUI_CODEC_TGA -DCEGUI_HAS_FREETYPE)

IF(FREYA_CORE_SHARED)   #Dynamic linkage
	ADD_DEFINITIONS( -D_SHARED_BUILD )
	MESSAGE("Building shared version of FreyaCore")
	ADD_LIBRARY( FreyaCore SHARED ${FREYA_CORE_SOURCES} ${FREYA_CEGUI_SRC})
	IF( UNIX AND NOT APPLE)
		#SET_PROPERTY( TARGET FreyaCore PROPERTY LINK_FLAGS "-rpath ." )
	ENDIF( UNIX AND NOT APPLE)
	INSTALL(TARGETS FreyaCore DESTINATION ${CMAKE_INSTALL_PREFIX}/Shared)
	MESSAGE("Linking with ${FREYA_CORE_LINK_LIBRARIES}")
	TARGET_LINK_LIBRARIES( FreyaCore ${FREYA_CORE_LINK_LIBRARIES} ${GLOBAL_LINK_LIBRARIES} )
ELSE( FREYA_CORE_SHARED ) #Static linkage
	MESSAGE("Building shared version of FreyaCore")
	ADD_LIBRARY( FreyaCore STATIC ${FREYA_CORE_SOURCES} ${FREYA_CEGUI_SRC})
	#Setup correct link flags
	SET( RUNTIME_LINK_LIBRARIES ${RUNTIME_LINK_LIBRARIES} ${FREYA_CORE_LINK_LIBRARIES})
ENDIF( FREYA_CORE_SHARED )

SET_PROPERTY( GLOBAL PROPERTY RUNTIME_LINK_LIBRARIES_GLOBAL ${RUNTIME_LINK_LIBRARIES} FreyaCore)

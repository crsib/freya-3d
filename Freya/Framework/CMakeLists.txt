MESSAGE("Generating build dependencies for FreyaCore")
SET(FREYA_CORE_SOURCES 
#Application settings global include
Include/application-settings.h
Include/camera/BasicCamera.h
Include/camera/FlyCamera.h
Include/camera/Frustum.h
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
Include/framework/AIObject.h
Include/framework/EmissionObject.h
Include/framework/OcclusionObject.h
Include/framework/RenderObject.h
Include/framework/SimulationObject.h
Include/freya.h
Include/internal.h
Include/math/MathSubsystem.h
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
Include/windowmanager/DriverSubsystems/RenderingAPIInitialization/RenderingAPIInitialization.h
Include/windowmanager/WindowManagerDriver.h
Include/windowmanager/WMException.h
Include/windowmanager.h
#Sources and private includes
Source/core/filesystem/FilesystemDriverFactory.h
Source/core/memory/MemoryBuffer.h
Source/core/memory/MemoryHeader.h
Source/core/memory/MemoryHeaderList.h
Source/core/memory/MemoryPool.h
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
Source/core/memory/MemoryArena.cpp
Source/core/memory/MemoryBuffer.cpp
Source/core/memory/MemoryHeaderList.cpp
Source/core/memory/MemoryPool.cpp
Source/core/multithreading/implementations/boost_thread/BoostThread.cpp
Source/core/multithreading/implementations/boost_thread/BoostThreadBlocks.cpp
Source/core/taskmanager/Shutdown.cpp
Source/core/taskmanager/Task.cpp
Source/core/taskmanager/TaskManager.cpp
Source/core/taskmanager/TaskThread.cpp
Source/core/Utils/StringUtils.cpp
Source/core/Variable.cpp
Source/math/MathSubsystem.cpp
Source/math/operations.cpp
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


"${INTERMIDIATE_DIRECTORY}/StaticPluginsLoader.cpp"
"${INTERMIDIATE_DIRECTORY}/freya_lua_bind.cpp"
)

SET_SOURCE_FILES_PROPERTIES("${INTERMIDIATE_DIRECTORY}/StaticPluginsLoader.cpp" PROPERTIES GENERATED YES)
SET_SOURCE_FILES_PROPERTIES("${INTERMIDIATE_DIRECTORY}/freya_lua_bind.cpp" PROPERTIES GENERATED YES)

MESSAGE(STATUS "Searching tolua")
FIND_PROGRAM( TOLUA_APP NAMES tolua tolua++ tolua++5 tolua++5.1 PATH ${TOLUA_APP_PATH} )
IF( NOT TOLUA_APP )
    MESSAGE(FATAL_ERROR "Failed to find tolua++ application. Please,set TOLUA_APP_PATH to path, where one of tolua, tolua++, tolua++5, tolua++5.1 is located" )
ENDIF( NOT TOLUA_APP )

MESSAGE(STATUS "Generating bind file using ${TOLUA_APP}..." )
EXECUTE_PROCESS(COMMAND ${TOLUA_APP} -n freya -L virtual_method_hooks.lua -o "${INTERMIDIATE_DIRECTORY}/freya_lua_bind.cpp" luabind.lpkg 
                            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Framework/Source/core/lua/lua_packages 
                            OUTPUT_VARIABLE TOLUA_OUT ERROR_VARIABLE TOLUA_ERROR)
MESSAGE(STATUS "Done\n\tOutput: ${TOLUA_OUT}\n\tErrors: ${TOLUA_ERROR}" )

#Search for boost.thread and boost.date_time
IF( FREYA_CORE_USE_BOOST )
	SET(Boost_USE_STATIC_LIBS   NO)
	SET(Boost_USE_MULTITHREADED YES)
	FIND_PACKAGE ( BoostSTLPort 1.40 REQUIRED COMPONENTS filesystem system thread date_time )
	MESSAGE ("Boost flags for FreyaCore \n\tinclude: ${Boost_INCLUDE_DIRS} \n\tlibs: ${Boost_LIBRARIES}" )
	INCLUDE_DIRECTORIES ( ${Boost_INCLUDE_DIRS} Source)
	SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} ${Boost_LIBRARIES} )
ENDIF( FREYA_CORE_USE_BOOST )

#Find lua

FIND_PACKAGE( Lua51 REQUIRED )
IF ( LUA51_FOUND )
    INCLUDE_DIRECTORIES( ${LUA_INCLUDE_DIR} )
    SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} ${LUA_LIBRARIES} )
ENDIF ( LUA51_FOUND )
#Generate library target depending on FREYA_CORE_DYNAMIC
	
IF(FREYA_CORE_SHARED)   #Dynamic linkage
	MESSAGE("Building shared version of FreyaCore")
	ADD_LIBRARY( FreyaCore SHARED ${FREYA_CORE_SOURCES} )
	IF( APPLE)
		#SET_PROPERTY( TARGET FreyaCore PROPERTY FRAMEWORK YES )
		INSTALL(TARGETS FreyaCore LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/Shared)
	ENDIF( APPLE)
	MESSAGE("Linking with ${FREYA_CORE_LINK_LIBRARIES}")
	TARGET_LINK_LIBRARIES( FreyaCore ${FREYA_CORE_LINK_LIBRARIES} ${GLOBAL_LINK_LIBRARIES} )
ELSE( FREYA_CORE_SHARED ) #Static linkage
	MESSAGE("Building shared version of FreyaCore")
	ADD_LIBRARY( FreyaCore STATIC ${FREYA_CORE_SOURCES} )
	#Setup correct link flags
	SET( RUNTIME_LINK_LIBRARIES ${RUNTIME_LINK_LIBRARIES} ${FREYA_CORE_LINK_LIBRARIES})
ENDIF( FREYA_CORE_SHARED )

SET_PROPERTY( GLOBAL PROPERTY RUNTIME_LINK_LIBRARIES_GLOBAL ${RUNTIME_LINK_LIBRARIES} FreyaCore)

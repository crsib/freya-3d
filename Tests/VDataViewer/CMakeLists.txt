#RESOURCE VIEWER
IF( APPLE )

SET ( RESOURCES "${SHARED_PLUGINS}" ${APP_STD_DATA}/StdGUI.7z ${APP_STD_DATA}/StdShaders.7z Scripts/Startup.lua GUI/layouts/VDataViewer.layout ${APP_DATA}/VertexData/cube.vdata ../BumpMapping/Textures.7z
        Shaders/GLSL_1_10/vertex/bump.vert Shaders/GLSL_1_10/vertex/nobump.vert Shaders/GLSL_1_10/fragment/bump.frag Shaders/GLSL_1_10/fragment/nobump.frag)
SET_SOURCE_FILES_PROPERTIES( Scripts/Startup.lua PROPERTIES MACOSX_PACKAGE_LOCATION Resources/Scripts/VDataViewer )
SET_SOURCE_FILES_PROPERTIES( ../BumpMapping/Textures.7z ${APP_STD_DATA}/StdGUI.7z ${APP_STD_DATA}/StdShaders.7z PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
SET_SOURCE_FILES_PROPERTIES( GUI/layouts/VDataViewer.layout PROPERTIES MACOSX_PACKAGE_LOCATION Resources/GUI/layouts )
SET_SOURCE_FILES_PROPERTIES( ${SHARED_PLUGINS} PROPERTIES GENERATED YES MACOSX_PACKAGE_LOCATION Plugins )
SET_SOURCE_FILES_PROPERTIES( ${APP_DATA}/VertexData/cube.vdata PROPERTIES MACOSX_PACKAGE_LOCATION Resources/VertexData )
SET_SOURCE_FILES_PROPERTIES(Shaders/GLSL_1_10/vertex/bump.vert Shaders/GLSL_1_10/vertex/nobump.vert PROPERTIES MACOSX_PACKAGE_LOCATION Resources/Shaders/GLSL_1_10/vertex )
SET_SOURCE_FILES_PROPERTIES(Shaders/GLSL_1_10/fragment/bump.frag Shaders/GLSL_1_10/fragment/nobump.frag PROPERTIES MACOSX_PACKAGE_LOCATION Resources/Shaders/GLSL_1_10/fragment )
ADD_EXECUTABLE( VDataViewer MACOSX_BUNDLE main.cpp ${RESOURCES})
#installation routines
INSTALL(TARGETS VDataViewer DESTINATION ${CMAKE_INSTALL_PREFIX})
INSTALL(CODE "INCLUDE ( ${CMAKE_SOURCE_DIR}/CMakeIncludes/CompleteBundle.cmake )\nMakeCompleteBundle( VDataViewer )")
ELSE()

ENDIF()

TARGET_LINK_LIBRARIES( VDataViewer ${RUNTIME_LINK_LIBRARIES} ${GLOBAL_LINK_LIBRARIES} )
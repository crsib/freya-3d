#TODO: 
SET ( RESOURCES Base.7z "${SHARED_PLUGINS}")
IF( APPLE )
	SET_SOURCE_FILES_PROPERTIES( Base.7z PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
	SET_SOURCE_FILES_PROPERTIES( ${SHARED_PLUGINS} PROPERTIES GENERATED YES MACOSX_PACKAGE_LOCATION Plugins )
	ADD_EXECUTABLE( ResourcesTest MACOSX_BUNDLE main.cpp ${RESOURCES})
	#installation routines
	INSTALL(TARGETS ResourcesTest DESTINATION ${CMAKE_INSTALL_PREFIX})
	INSTALL(CODE "INCLUDE ( ${CMAKE_SOURCE_DIR}/CMakeIncludes/CompleteBundle.cmake )\nMakeCompleteBundle( ResourcesTest )")
ELSE( APPLE )
#Non apple platforms 
	IF( WIN32 )
		ADD_EXECUTABLE( ResourcesTest main.cpp )
		INSTALL(TARGETS ResourcesTest DESTINATION ${CMAKE_INSTALL_PREFIX}/ResourcesTest)
		INSTALL(FILES Base.7z DESTINATION ${CMAKE_INSTALL_PREFIX}/ResourcesTest)
		INSTALL(FILES ${SHARED_PLUGINS} DESTINATION ${CMAKE_INSTALL_PREFIX}/ResourcesTest/Plugins )
		INSTALL(CODE "INCLUDE ( ${CMAKE_SOURCE_DIR}/CMakeIncludes/CompleteBundle.cmake )\nMakeCompleteBundle( ResourcesTest )")
	ELSE( WIN32 )
		ADD_EXECUTABLE( ResourcesTest main.cpp )
		INSTALL(TARGETS ResourcesTest DESTINATION ${CMAKE_INSTALL_PREFIX}/ResourcesTest)
		INSTALL(FILES Base.7z DESTINATION ${CMAKE_INSTALL_PREFIX}/ResourcesTest)
		INSTALL(FILES ${SHARED_PLUGINS} DESTINATION ${CMAKE_INSTALL_PREFIX}/ResourcesTest/Plugins )
		INSTALL(CODE "INCLUDE ( ${CMAKE_SOURCE_DIR}/CMakeIncludes/CompleteBundle.cmake )\nMakeCompleteBundle( ResourcesTest )")
	ENDIF( WIN32 )

ENDIF( APPLE )
TARGET_LINK_LIBRARIES( ResourcesTest ${RUNTIME_LINK_LIBRARIES} ${GLOBAL_LINK_LIBRARIES} )

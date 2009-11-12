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
#XML integration
#Global includes
Include/core/xml/XMLParser.h
Include/core/xml/XMLParserException.h
Include/core/xml/XMLStringWrap.h
#Private includes and sources
Source/core/xml/XMLParser.cpp

Source/core/xml/xerces/FreyaDomErrorHandler.h
Source/core/xml/xerces/FreyaFile.h
Source/core/xml/xerces/FreyaFileManager.h
Source/core/xml/xerces/FreyaMemoryManager.h
Source/core/xml/xerces/FreyaPanicHandler.h

Source/core/xml/xerces/FreyaDomErrorHandler.cpp
Source/core/xml/xerces/FreyaFile.cpp
Source/core/xml/xerces/FreyaFileManager.cpp
Source/core/xml/xerces/FreyaMemoryManager.cpp
Source/core/xml/xerces/FreyaPanicHandler.cpp

Source/resources/drivers/std/ShaderLoaderDriver.cpp

#Generated sources
"${INTERMIDIATE_DIRECTORY}/StaticPluginsLoader.cpp"
"${INTERMIDIATE_DIRECTORY}/freya_lua_bind.cpp"
"${INTERMIDIATE_DIRECTORY}/XMLStaticStrings.h"
"${INTERMIDIATE_DIRECTORY}/XMLStaticStrings.cpp"

#World
#public includes
Include/framework/World.h
Include/framework/SceneNode.h
Include/framework/SceneNodeController.h
Include/framework/Structures.h

#Sources & private includes
Source/framework/World.cpp
Source/framework/SceneNode.cpp
Source/framework/SceneNodeController.cpp
Source/framework/FrameworkImpl.cpp

Source/resources/drivers/std/VDataLoader.h
Source/resources/drivers/std/VDataLoader.cpp
)

SET( CEGUI_SOURCE 
./3party/cegui/include/CEGUI.h
./3party/cegui/include/CEGUIBase.h
./3party/cegui/include/CEGUIBasicRenderedStringParser.h
./3party/cegui/include/CEGUIBiDiVisualMapping.h
./3party/cegui/include/CEGUIBoundSlot.h
./3party/cegui/include/CEGUICentredRenderedString.h
./3party/cegui/include/CEGUIcolour.h
./3party/cegui/include/CEGUIColourRect.h
./3party/cegui/include/CEGUIConfig.h
./3party/cegui/include/CEGUIConfig_xmlHandler.h
./3party/cegui/include/CEGUICoordConverter.h
./3party/cegui/include/CEGUIDataContainer.h
./3party/cegui/include/CEGUIDefaultLogger.h
./3party/cegui/include/CEGUIDefaultRenderedStringParser.h
./3party/cegui/include/CEGUIDefaultResourceProvider.h
./3party/cegui/include/CEGUIDynamicModule.h
./3party/cegui/include/CEGUIEvent.h
./3party/cegui/include/CEGUIEventArgs.h
./3party/cegui/include/CEGUIEventSet.h
./3party/cegui/include/CEGUIExceptions.h
./3party/cegui/include/CEGUIFactoryModule.h
./3party/cegui/include/CEGUIFont.h
./3party/cegui/include/CEGUIFont_xmlHandler.h
./3party/cegui/include/CEGUIFontGlyph.h
./3party/cegui/include/CEGUIFontManager.h
./3party/cegui/include/CEGUIFormattedRenderedString.h
./3party/cegui/include/CEGUIForwardRefs.h
./3party/cegui/include/CEGUIFreeFunctionSlot.h
./3party/cegui/include/CEGUIFreeTypeFont.h
./3party/cegui/include/CEGUIFribidiVisualMapping.h
./3party/cegui/include/CEGUIFunctorCopySlot.h
./3party/cegui/include/CEGUIFunctorPointerSlot.h
./3party/cegui/include/CEGUIFunctorReferenceBinder.h
./3party/cegui/include/CEGUIFunctorReferenceSlot.h
./3party/cegui/include/CEGUIGeometryBuffer.h
./3party/cegui/include/CEGUIGlobalEventSet.h
./3party/cegui/include/CEGUIGUILayout_xmlHandler.h
./3party/cegui/include/CEGUIImage.h
./3party/cegui/include/CEGUIImageCodec.h
./3party/cegui/include/CEGUIImageset.h
./3party/cegui/include/CEGUIImageset_xmlHandler.h
./3party/cegui/include/CEGUIImagesetManager.h
./3party/cegui/include/CEGUIInputEvent.h
./3party/cegui/include/CEGUIIteratorBase.h
./3party/cegui/include/CEGUIJustifiedRenderedString.h
./3party/cegui/include/CEGUILeftAlignedRenderedString.h
./3party/cegui/include/CEGUILogger.h   
./3party/cegui/include/CEGUIMemberFunctionSlot.h
./3party/cegui/include/CEGUIMinibidiVisualMapping.h
./3party/cegui/include/CEGUIMouseCursor.h 
./3party/cegui/include/CEGUINamedXMLResourceManager.h
./3party/cegui/include/CEGUIPCRERegexMatcher.h
./3party/cegui/include/CEGUIPixmapFont.h 
./3party/cegui/include/CEGUIProperty.h
./3party/cegui/include/CEGUIPropertyHelper.h
./3party/cegui/include/CEGUIPropertySet.h
./3party/cegui/include/CEGUIRect.h
./3party/cegui/include/CEGUIRefCounted.h
./3party/cegui/include/CEGUIRegexMatcher.h
./3party/cegui/include/CEGUIRenderedString.h
./3party/cegui/include/CEGUIRenderedStringComponent.h
./3party/cegui/include/CEGUIRenderedStringImageComponent.h
./3party/cegui/include/CEGUIRenderedStringParser.h   
./3party/cegui/include/CEGUIRenderedStringTextComponent.h
./3party/cegui/include/CEGUIRenderedStringWidgetComponent.h
./3party/cegui/include/CEGUIRenderedStringWordWrapper.h
./3party/cegui/include/CEGUIRenderEffect.h
./3party/cegui/include/CEGUIRenderer.h
./3party/cegui/include/CEGUIRenderingContext.h
./3party/cegui/include/CEGUIRenderingRoot.h
./3party/cegui/include/CEGUIRenderingSurface.h
./3party/cegui/include/CEGUIRenderingWindow.h
./3party/cegui/include/CEGUIRenderQueue.h
./3party/cegui/include/CEGUIRenderTarget.h
./3party/cegui/include/CEGUIResourceProvider.h
./3party/cegui/include/CEGUIRightAlignedRenderedString.h
./3party/cegui/include/CEGUIScheme.h
./3party/cegui/include/CEGUIScheme_xmlHandler.h
./3party/cegui/include/CEGUISchemeManager.h
./3party/cegui/include/CEGUIScriptModule.h
./3party/cegui/include/CEGUISingleton.h
./3party/cegui/include/CEGUISize.h
./3party/cegui/include/CEGUISlotFunctorBase.h
./3party/cegui/include/CEGUIString.h
./3party/cegui/include/CEGUISubscriberSlot.h
./3party/cegui/include/CEGUISystem.h
./3party/cegui/include/CEGUITexture.h
./3party/cegui/include/CEGUITextureTarget.h
./3party/cegui/include/CEGUITextUtils.h
./3party/cegui/include/CEGUITplWindowFactory.h
./3party/cegui/include/CEGUITplWindowRendererFactory.h
./3party/cegui/include/CEGUITplWRFactoryRegisterer.h
./3party/cegui/include/CEGUIUDim.h
./3party/cegui/include/CEGUIVector.h
./3party/cegui/include/CEGUIVersion.h
./3party/cegui/include/CEGUIVertex.h
./3party/cegui/include/CEGUIWidgetModule.h
./3party/cegui/include/CEGUIWindow.h
./3party/cegui/include/CEGUIWindowFactory.h
./3party/cegui/include/CEGUIWindowFactoryManager.h
./3party/cegui/include/CEGUIWindowManager.h
./3party/cegui/include/CEGUIWindowProperties.h
./3party/cegui/include/CEGUIWindowRenderer.h
./3party/cegui/include/CEGUIWindowRendererManager.h
./3party/cegui/include/CEGUIWindowRendererModule.h
./3party/cegui/include/CEGUIWRFactoryRegisterer.h
./3party/cegui/include/CEGUIXMLAttributes.h
./3party/cegui/include/CEGUIXMLHandler.h
./3party/cegui/include/CEGUIXMLParser.h
./3party/cegui/include/CEGUIXMLSerializer.h
./3party/cegui/include/elements/CEGUIAll.h
./3party/cegui/include/elements/CEGUIButtonBase.h
./3party/cegui/include/elements/CEGUICheckbox.h
./3party/cegui/include/elements/CEGUICheckboxProperties.h
./3party/cegui/include/elements/CEGUIClippedContainer.h
./3party/cegui/include/elements/CEGUICombobox.h
./3party/cegui/include/elements/CEGUIComboboxProperties.h
./3party/cegui/include/elements/CEGUIComboDropList.h
./3party/cegui/include/elements/CEGUIDragContainer.h
./3party/cegui/include/elements/CEGUIDragContainerProperties.h
./3party/cegui/include/elements/CEGUIEditbox.h
./3party/cegui/include/elements/CEGUIEditboxProperties.h
./3party/cegui/include/elements/CEGUIFrameWindow.h
./3party/cegui/include/elements/CEGUIFrameWindowProperties.h
./3party/cegui/include/elements/CEGUIGroupBox.h
./3party/cegui/include/elements/CEGUIGUISheet.h
./3party/cegui/include/elements/CEGUIItemEntry.h
./3party/cegui/include/elements/CEGUIItemEntryProperties.h
./3party/cegui/include/elements/CEGUIItemListBase.h
./3party/cegui/include/elements/CEGUIItemListBaseProperties.h
./3party/cegui/include/elements/CEGUIItemListbox.h
./3party/cegui/include/elements/CEGUIItemListboxProperties.h
./3party/cegui/include/elements/CEGUIListbox.h
./3party/cegui/include/elements/CEGUIListboxItem.h
./3party/cegui/include/elements/CEGUIListboxProperties.h
./3party/cegui/include/elements/CEGUIListboxTextItem.h
./3party/cegui/include/elements/CEGUIListHeader.h
./3party/cegui/include/elements/CEGUIListHeaderProperties.h
./3party/cegui/include/elements/CEGUIListHeaderSegment.h
./3party/cegui/include/elements/CEGUIListHeaderSegmentProperties.h
./3party/cegui/include/elements/CEGUIMenubar.h
./3party/cegui/include/elements/CEGUIMenuBase.h
./3party/cegui/include/elements/CEGUIMenuBaseProperties.h
./3party/cegui/include/elements/CEGUIMenuItem.h
./3party/cegui/include/elements/CEGUIMultiColumnList.h
./3party/cegui/include/elements/CEGUIMultiColumnListProperties.h
./3party/cegui/include/elements/CEGUIMultiLineEditbox.h
./3party/cegui/include/elements/CEGUIMultiLineEditboxProperties.h
./3party/cegui/include/elements/CEGUIPopupMenu.h
./3party/cegui/include/elements/CEGUIPopupMenuProperties.h
./3party/cegui/include/elements/CEGUIProgressBar.h
./3party/cegui/include/elements/CEGUIProgressBarProperties.h
./3party/cegui/include/elements/CEGUIPushButton.h
./3party/cegui/include/elements/CEGUIRadioButton.h
./3party/cegui/include/elements/CEGUIRadioButtonProperties.h
./3party/cegui/include/elements/CEGUIScrollablePane.h
./3party/cegui/include/elements/CEGUIScrollablePaneProperties.h
./3party/cegui/include/elements/CEGUIScrollbar.h
./3party/cegui/include/elements/CEGUIScrollbarProperties.h
./3party/cegui/include/elements/CEGUIScrolledContainer.h
./3party/cegui/include/elements/CEGUIScrolledContainerProperties.h
./3party/cegui/include/elements/CEGUIScrolledItemListBase.h
./3party/cegui/include/elements/CEGUIScrolledItemListBaseProperties.h
./3party/cegui/include/elements/CEGUISlider.h
./3party/cegui/include/elements/CEGUISliderProperties.h
./3party/cegui/include/elements/CEGUISpinner.h
./3party/cegui/include/elements/CEGUISpinnerProperties.h
./3party/cegui/include/elements/CEGUITabButton.h
./3party/cegui/include/elements/CEGUITabControl.h
./3party/cegui/include/elements/CEGUITabControlProperties.h
./3party/cegui/include/elements/CEGUIThumb.h
./3party/cegui/include/elements/CEGUIThumbProperties.h
./3party/cegui/include/elements/CEGUITitlebar.h
./3party/cegui/include/elements/CEGUITitlebarProperties.h
./3party/cegui/include/elements/CEGUITooltip.h
./3party/cegui/include/elements/CEGUITooltipProperties.h
./3party/cegui/include/elements/CEGUITree.h
./3party/cegui/include/elements/CEGUITreeItem.h
./3party/cegui/include/elements/CEGUITreeProperties.h
./3party/cegui/include/falagard/CEGUIFalagard_xmlHandler.h
./3party/cegui/include/falagard/CEGUIFalComponentBase.h
./3party/cegui/include/falagard/CEGUIFalDimensions.h
./3party/cegui/include/falagard/CEGUIFalEnums.h
./3party/cegui/include/falagard/CEGUIFalFrameComponent.h
./3party/cegui/include/falagard/CEGUIFalImageryComponent.h
./3party/cegui/include/falagard/CEGUIFalImagerySection.h
./3party/cegui/include/falagard/CEGUIFalLayerSpecification.h
./3party/cegui/include/falagard/CEGUIFalNamedArea.h
./3party/cegui/include/falagard/CEGUIFalPropertyDefinition.h
./3party/cegui/include/falagard/CEGUIFalPropertyDefinitionBase.h
./3party/cegui/include/falagard/CEGUIFalPropertyInitialiser.h
./3party/cegui/include/falagard/CEGUIFalPropertyLinkDefinition.h
./3party/cegui/include/falagard/CEGUIFalSectionSpecification.h
./3party/cegui/include/falagard/CEGUIFalStateImagery.h
./3party/cegui/include/falagard/CEGUIFalTextComponent.h
./3party/cegui/include/falagard/CEGUIFalWidgetComponent.h
./3party/cegui/include/falagard/CEGUIFalWidgetLookFeel.h
./3party/cegui/include/falagard/CEGUIFalWidgetLookManager.h
./3party/cegui/include/falagard/CEGUIFalXMLEnumHelper.h
./3party/cegui/include/ScriptingModules/LuaScriptModule/CEGUILua.h
./3party/cegui/include/ScriptingModules/LuaScriptModule/CEGUILuaFunctor.h
./3party/cegui/include/WindowRendererSets/Falagard/FalButton.h
./3party/cegui/include/WindowRendererSets/Falagard/FalDefault.h
./3party/cegui/include/WindowRendererSets/Falagard/FalEditbox.h
./3party/cegui/include/WindowRendererSets/Falagard/FalEditboxProperties.h
./3party/cegui/include/WindowRendererSets/Falagard/FalFrameWindow.h
./3party/cegui/include/WindowRendererSets/Falagard/FalItemEntry.h
./3party/cegui/include/WindowRendererSets/Falagard/FalItemListbox.h
./3party/cegui/include/WindowRendererSets/Falagard/FalListbox.h
./3party/cegui/include/WindowRendererSets/Falagard/FalListHeader.h
./3party/cegui/include/WindowRendererSets/Falagard/FalListHeaderProperties.h
./3party/cegui/include/WindowRendererSets/Falagard/FalListHeaderSegment.h
./3party/cegui/include/WindowRendererSets/Falagard/FalMenubar.h
./3party/cegui/include/WindowRendererSets/Falagard/FalMenuItem.h
./3party/cegui/include/WindowRendererSets/Falagard/FalModule.h
./3party/cegui/include/WindowRendererSets/Falagard/FalMultiColumnList.h
./3party/cegui/include/WindowRendererSets/Falagard/FalMultiLineEditbox.h
./3party/cegui/include/WindowRendererSets/Falagard/FalMultiLineEditboxProperties.h
./3party/cegui/include/WindowRendererSets/Falagard/FalPopupMenu.h
./3party/cegui/include/WindowRendererSets/Falagard/FalProgressBar.h
./3party/cegui/include/WindowRendererSets/Falagard/FalProgressBarProperties.h
./3party/cegui/include/WindowRendererSets/Falagard/FalScrollablePane.h
./3party/cegui/include/WindowRendererSets/Falagard/FalScrollbar.h
./3party/cegui/include/WindowRendererSets/Falagard/FalScrollbarProperties.h
./3party/cegui/include/WindowRendererSets/Falagard/FalSlider.h
./3party/cegui/include/WindowRendererSets/Falagard/FalSliderProperties.h
./3party/cegui/include/WindowRendererSets/Falagard/FalStatic.h
./3party/cegui/include/WindowRendererSets/Falagard/FalStaticImage.h
./3party/cegui/include/WindowRendererSets/Falagard/FalStaticImageProperties.h
./3party/cegui/include/WindowRendererSets/Falagard/FalStaticProperties.h
./3party/cegui/include/WindowRendererSets/Falagard/FalStaticText.h
./3party/cegui/include/WindowRendererSets/Falagard/FalStaticTextProperties.h
./3party/cegui/include/WindowRendererSets/Falagard/FalSystemButton.h
./3party/cegui/include/WindowRendererSets/Falagard/FalTabButton.h
./3party/cegui/include/WindowRendererSets/Falagard/FalTabControl.h
./3party/cegui/include/WindowRendererSets/Falagard/FalTabControlProperties.h
./3party/cegui/include/WindowRendererSets/Falagard/FalTitlebar.h
./3party/cegui/include/WindowRendererSets/Falagard/FalToggleButton.h
./3party/cegui/include/WindowRendererSets/Falagard/FalTooltip.h
./3party/cegui/include/WindowRendererSets/Falagard/FalTree.h
./3party/cegui/include/XMLParserModules/XercesParser/CEGUIXercesParser.h
./3party/cegui/include/XMLParserModules/XercesParser/CEGUIXercesParserModule.h
./3party/cegui/include/XMLParserModules/XercesParser/CEGUIXercesParserProperties.h
#
./3party/cegui/src/ScriptingModules/LuaScriptModule/required.h

./3party/cegui/src/CEGUIBase.cpp
./3party/cegui/src/CEGUIBasicRenderedStringParser.cpp
./3party/cegui/src/CEGUIBiDiVisualMapping.cpp
./3party/cegui/src/CEGUIBoundSlot.cpp
./3party/cegui/src/CEGUICentredRenderedString.cpp
./3party/cegui/src/CEGUIcolour.cpp
./3party/cegui/src/CEGUIColourRect.cpp
./3party/cegui/src/CEGUIConfig_xmlHandler.cpp
./3party/cegui/src/CEGUICoordConverter.cpp
./3party/cegui/src/CEGUIDataContainer.cpp
./3party/cegui/src/CEGUIDefaultLogger.cpp
./3party/cegui/src/CEGUIDefaultRenderedStringParser.cpp
./3party/cegui/src/CEGUIDefaultResourceProvider.cpp
./3party/cegui/src/CEGUIDynamicModule.cpp
./3party/cegui/src/CEGUIEvent.cpp
./3party/cegui/src/CEGUIEventArgs.cpp
./3party/cegui/src/CEGUIEventSet.cpp
./3party/cegui/src/CEGUIEventSignal.cpp
./3party/cegui/src/CEGUIEventSignalSet.cpp
./3party/cegui/src/CEGUIExceptions.cpp
./3party/cegui/src/CEGUIFactoryModule.cpp
./3party/cegui/src/CEGUIFont.cpp
./3party/cegui/src/CEGUIFont_xmlHandler.cpp
./3party/cegui/src/CEGUIFontManager.cpp
./3party/cegui/src/CEGUIFontProperties.cpp
./3party/cegui/src/CEGUIFormattedRenderedString.cpp
./3party/cegui/src/CEGUIFreeTypeFont.cpp
./3party/cegui/src/CEGUIFribidiVisualMapping.cpp
./3party/cegui/src/CEGUIGlobalEventSet.cpp
./3party/cegui/src/CEGUIGUILayout_xmlHandler.cpp
./3party/cegui/src/CEGUIImage.cpp
./3party/cegui/src/CEGUIImageCodec.cpp
./3party/cegui/src/CEGUIImageset.cpp
./3party/cegui/src/CEGUIImageset_xmlHandler.cpp
./3party/cegui/src/CEGUIImagesetManager.cpp
./3party/cegui/src/CEGUIJustifiedRenderedString.cpp
./3party/cegui/src/CEGUIJustifiedRenderedStringWordWrapper.cpp
./3party/cegui/src/CEGUILeftAlignedRenderedString.cpp
./3party/cegui/src/CEGUILogger.cpp
./3party/cegui/src/CEGUIMinibidiVisualMapping.cpp
./3party/cegui/src/CEGUIMouseCursor.cpp
./3party/cegui/src/CEGUINamedXMLResourceManager.cpp
./3party/cegui/src/CEGUIPCRERegexMatcher.cpp
./3party/cegui/src/CEGUIPixmapFont.cpp
./3party/cegui/src/CEGUIProperty.cpp
./3party/cegui/src/CEGUIPropertyHelper.cpp
./3party/cegui/src/CEGUIPropertySet.cpp
./3party/cegui/src/CEGUIRect.cpp
./3party/cegui/src/CEGUIRenderedString.cpp
./3party/cegui/src/CEGUIRenderedStringComponent.cpp
./3party/cegui/src/CEGUIRenderedStringImageComponent.cpp
./3party/cegui/src/CEGUIRenderedStringTextComponent.cpp
./3party/cegui/src/CEGUIRenderedStringWidgetComponent.cpp
./3party/cegui/src/CEGUIRenderingRoot.cpp
./3party/cegui/src/CEGUIRenderingSurface.cpp
./3party/cegui/src/CEGUIRenderingWindow.cpp
./3party/cegui/src/CEGUIRenderQueue.cpp
./3party/cegui/src/CEGUIRightAlignedRenderedString.cpp
./3party/cegui/src/CEGUIScheme.cpp
./3party/cegui/src/CEGUIScheme_xmlHandler.cpp
./3party/cegui/src/CEGUISchemeManager.cpp
./3party/cegui/src/CEGUIScriptModule.cpp
./3party/cegui/src/CEGUISize.cpp
./3party/cegui/src/CEGUIString.cpp
./3party/cegui/src/CEGUISubscriberSlot.cpp
./3party/cegui/src/CEGUISystem.cpp
./3party/cegui/src/CEGUITextUtils.cpp
./3party/cegui/src/CEGUIWindow.cpp
./3party/cegui/src/CEGUIWindowFactory.cpp
./3party/cegui/src/CEGUIWindowFactoryManager.cpp
./3party/cegui/src/CEGUIWindowManager.cpp
./3party/cegui/src/CEGUIWindowProperties.cpp
./3party/cegui/src/CEGUIWindowRenderer.cpp
./3party/cegui/src/CEGUIWindowRendererManager.cpp
./3party/cegui/src/CEGUIWindowRendererModule.cpp
./3party/cegui/src/CEGUIWRFactoryRegisterer.cpp
./3party/cegui/src/CEGUIXMLAttributes.cpp
./3party/cegui/src/CEGUIXMLHandler.cpp
./3party/cegui/src/CEGUIXMLParser.cpp
./3party/cegui/src/CEGUIXMLSerializer.cpp
./3party/cegui/src/elements/CEGUIButtonBase.cpp
./3party/cegui/src/elements/CEGUICheckbox.cpp
./3party/cegui/src/elements/CEGUICheckboxProperties.cpp
./3party/cegui/src/elements/CEGUIClippedContainer.cpp
./3party/cegui/src/elements/CEGUICombobox.cpp
./3party/cegui/src/elements/CEGUIComboboxProperties.cpp
./3party/cegui/src/elements/CEGUIComboDropList.cpp
./3party/cegui/src/elements/CEGUIDragContainer.cpp
./3party/cegui/src/elements/CEGUIDragContainerProperties.cpp
./3party/cegui/src/elements/CEGUIEditbox.cpp
./3party/cegui/src/elements/CEGUIEditboxProperties.cpp
./3party/cegui/src/elements/CEGUIFrameWindow.cpp
./3party/cegui/src/elements/CEGUIFrameWindowProperties.cpp
./3party/cegui/src/elements/CEGUIGroupBox.cpp
./3party/cegui/src/elements/CEGUIGUISheet.cpp
./3party/cegui/src/elements/CEGUIItemEntry.cpp
./3party/cegui/src/elements/CEGUIItemEntryProperties.cpp
./3party/cegui/src/elements/CEGUIItemListBase.cpp
./3party/cegui/src/elements/CEGUIItemListBaseProperties.cpp
./3party/cegui/src/elements/CEGUIItemListbox.cpp
./3party/cegui/src/elements/CEGUIItemListboxProperties.cpp
./3party/cegui/src/elements/CEGUIListbox.cpp
./3party/cegui/src/elements/CEGUIListboxItem.cpp
./3party/cegui/src/elements/CEGUIListboxProperties.cpp
./3party/cegui/src/elements/CEGUIListboxTextItem.cpp
./3party/cegui/src/elements/CEGUIListHeader.cpp
./3party/cegui/src/elements/CEGUIListHeaderProperties.cpp
./3party/cegui/src/elements/CEGUIListHeaderSegment.cpp
./3party/cegui/src/elements/CEGUIListHeaderSegmentProperties.cpp
./3party/cegui/src/elements/CEGUIMenubar.cpp
./3party/cegui/src/elements/CEGUIMenuBase.cpp
./3party/cegui/src/elements/CEGUIMenuBaseProperties.cpp
./3party/cegui/src/elements/CEGUIMenuItem.cpp
./3party/cegui/src/elements/CEGUIMultiColumnList.cpp
./3party/cegui/src/elements/CEGUIMultiColumnListProperties.cpp
./3party/cegui/src/elements/CEGUIMultiLineEditbox.cpp
./3party/cegui/src/elements/CEGUIMultiLineEditboxProperties.cpp
./3party/cegui/src/elements/CEGUIPopupMenu.cpp
./3party/cegui/src/elements/CEGUIPopupMenuProperties.cpp
./3party/cegui/src/elements/CEGUIProgressBar.cpp
./3party/cegui/src/elements/CEGUIProgressBarProperties.cpp
./3party/cegui/src/elements/CEGUIPushButton.cpp
./3party/cegui/src/elements/CEGUIRadioButton.cpp
./3party/cegui/src/elements/CEGUIRadioButtonProperties.cpp
./3party/cegui/src/elements/CEGUIScrollablePane.cpp
./3party/cegui/src/elements/CEGUIScrollablePaneProperties.cpp
./3party/cegui/src/elements/CEGUIScrollbar.cpp
./3party/cegui/src/elements/CEGUIScrollbarProperties.cpp
./3party/cegui/src/elements/CEGUIScrolledContainer.cpp
./3party/cegui/src/elements/CEGUIScrolledContainerProperties.cpp
./3party/cegui/src/elements/CEGUIScrolledItemListBase.cpp
./3party/cegui/src/elements/CEGUIScrolledItemListBaseProperties.cpp
./3party/cegui/src/elements/CEGUISlider.cpp
./3party/cegui/src/elements/CEGUISliderProperties.cpp
./3party/cegui/src/elements/CEGUISpinner.cpp
./3party/cegui/src/elements/CEGUISpinnerProperties.cpp
./3party/cegui/src/elements/CEGUITabButton.cpp
./3party/cegui/src/elements/CEGUITabControl.cpp
./3party/cegui/src/elements/CEGUITabControlProperties.cpp
./3party/cegui/src/elements/CEGUIThumb.cpp
./3party/cegui/src/elements/CEGUIThumbProperties.cpp
./3party/cegui/src/elements/CEGUITitlebar.cpp
./3party/cegui/src/elements/CEGUITitlebarProperties.cpp
./3party/cegui/src/elements/CEGUITooltip.cpp
./3party/cegui/src/elements/CEGUITooltipProperties.cpp
./3party/cegui/src/elements/CEGUITree.cpp
./3party/cegui/src/elements/CEGUITreeItem.cpp
./3party/cegui/src/elements/CEGUITreeProperties.cpp
./3party/cegui/src/falagard/CEGUIFalagard_xmlHandler.cpp
./3party/cegui/src/falagard/CEGUIFalComponentBase.cpp
./3party/cegui/src/falagard/CEGUIFalDimensions.cpp
./3party/cegui/src/falagard/CEGUIFalFrameComponent.cpp
./3party/cegui/src/falagard/CEGUIFalImageryComponent.cpp
./3party/cegui/src/falagard/CEGUIFalImagerySection.cpp
./3party/cegui/src/falagard/CEGUIFalLayerSpecification.cpp
./3party/cegui/src/falagard/CEGUIFalNamedArea.cpp
./3party/cegui/src/falagard/CEGUIFalPropertyDefinition.cpp
./3party/cegui/src/falagard/CEGUIFalPropertyDefinitionBase.cpp
./3party/cegui/src/falagard/CEGUIFalPropertyInitialiser.cpp
./3party/cegui/src/falagard/CEGUIFalPropertyLinkDefinition.cpp
./3party/cegui/src/falagard/CEGUIFalSectionSpecification.cpp
./3party/cegui/src/falagard/CEGUIFalStateImagery.cpp
./3party/cegui/src/falagard/CEGUIFalTextComponent.cpp
./3party/cegui/src/falagard/CEGUIFalWidgetComponent.cpp
./3party/cegui/src/falagard/CEGUIFalWidgetLookFeel.cpp
./3party/cegui/src/falagard/CEGUIFalWidgetLookManager.cpp
./3party/cegui/src/falagard/CEGUIFalXMLEnumHelper.cpp
#
./3party/cegui/src/minibidi.cpp
./3party/cegui/src/ScriptingModules/LuaScriptModule/CEGUILua.cpp
./3party/cegui/src/ScriptingModules/LuaScriptModule/CEGUILuaFunctor.cpp  
./3party/cegui/src/ScriptingModules/LuaScriptModule/required.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalButton.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalDefault.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalEditbox.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalEditboxProperties.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalFrameWindow.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalItemEntry.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalItemListbox.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalListbox.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalListHeader.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalListHeaderProperties.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalListHeaderSegment.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalMenubar.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalMenuItem.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalModule.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalMultiColumnList.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalMultiLineEditbox.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalMultiLineEditboxProperties.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalPopupMenu.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalProgressBar.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalProgressBarProperties.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalScrollablePane.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalScrollbar.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalScrollbarProperties.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalSlider.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalSliderProperties.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalStatic.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalStaticImage.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalStaticImageProperties.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalStaticProperties.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalStaticText.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalStaticTextProperties.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalSystemButton.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalTabButton.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalTabControl.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalTabControlProperties.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalTitlebar.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalToggleButton.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalTooltip.cpp
./3party/cegui/src/WindowRendererSets/Falagard/FalTree.cpp
./3party/cegui/src/XMLParserModules/XercesParser/CEGUIXercesParser.cpp
./3party/cegui/src/XMLParserModules/XercesParser/CEGUIXercesParserModule.cpp
./3party/cegui/src/XMLParserModules/XercesParser/CEGUIXercesParserProperties.cpp

./3party/cegui/src/ImageCodecModules/TGAImageCodec/CEGUITGAImageCodec.cpp
./3party/cegui/src/ImageCodecModules/TGAImageCodec/CEGUITGAImageCodecModule.cpp
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


IF ( APPLE )
    SET(CEGUI_SOURCE ${CEGUI_SOURCE} ./3party/cegui/src/implementations/mac/macPlugins.cpp ./3party/cegui/src/implementations/mac/macPlugins.h )
    INCLUDE_DIRECTORIES( ./3party/cegui/src/implementations/mac )
ENDIF()

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
SET_SOURCE_FILES_PROPERTIES("${INTERMIDIATE_DIRECTORY}/XMLStaticStrings.h" PROPERTIES GENERATED YES)
SET_SOURCE_FILES_PROPERTIES("${INTERMIDIATE_DIRECTORY}/XMLStaticStrings.cpp" PROPERTIES GENERATED YES)
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/Framework/Include/core/lua/tolua++/tolua++.h" "${INTERMIDIATE_DIRECTORY}/tolua++.h")

MESSAGE(STATUS "Searching tolua") 
FIND_PROGRAM( TOLUA_APP NAMES tolua tolua++ tolua++5 tolua++5.1 PATH ${TOLUA_APP_PATH} )
IF( NOT TOLUA_APP )
    MESSAGE(FATAL_ERROR "Failed to find tolua++ application. Please,set TOLUA_APP_PATH to path, where one of tolua, tolua++, tolua++5, tolua++5.1 is located" )
ENDIF( NOT TOLUA_APP )

MESSAGE(STATUS "Generating bind file using ${TOLUA_APP}..." )
EXECUTE_PROCESS(COMMAND ${TOLUA_APP} -n freya -L virtual_method_hooks.lua -L "${CMAKE_SOURCE_DIR}/Framework/3party/cegui/src/ScriptingModules/LuaScriptModule/package/exceptions.lua" -o "${INTERMIDIATE_DIRECTORY}/freya_lua_bind.cpp" luabind.lpkg 
                            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Framework/Source/core/lua/lua_packages 
                            OUTPUT_VARIABLE TOLUA_OUT ERROR_VARIABLE TOLUA_ERROR)
MESSAGE(STATUS "Done\n\tOutput: ${TOLUA_OUT}\n\tErrors: ${TOLUA_ERROR}" )

MESSAGE(STATUS "Searching lua")
FIND_PROGRAM( LUA_APP NAMES lua lua51 lua5 lua5.1 PATH ${LUA_APP_PATH} )
IF( NOT LUA_APP )
    MESSAGE(FATAL_ERROR "Failed to find lua application. Please,set LUA_APP_PATH to path, where one of lua lua51 lua5 lua5.1 is located" )
ENDIF( NOT LUA_APP )

EXECUTE_PROCESS(COMMAND ${LUA_APP} ${GENERATORS_DIRECTORY}/XMLStrings.lua 
                            WORKING_DIRECTORY ${INTERMIDIATE_DIRECTORY} 
                            OUTPUT_VARIABLE LUA_OUT ERROR_VARIABLE LUA_ERROR)
MESSAGE(STATUS "Done generating static xml strings\n\tOutput: ${LUA_OUT}\n\tErrors: ${LUA_ERROR}" )

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

#Find Xerces-C++
FIND_PACKAGE( XercesC REQUIRED )

IF ( XERCESC_FOUND )
	INCLUDE_DIRECTORIES(${XERCESC_INCLUDE})
	SET( FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} ${XERCESC_LIBRARY} )
ENDIF( XERCESC_FOUND )

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
#Build cegui
ADD_DEFINITIONS( -DCEGUITGAIMAGECODEC_EXPORTS -DCEGUIBASE_EXPORTS -DCEGUILUA_EXPORTS -DCEGUIXERCESPARSER_EXPORTS -DCEGUI_WITH_XERCES -DFALAGARDWRBASE_EXPORTS -DCEGUI_FALAGARD_RENDERER -DCEGUI_CODEC_TGA -DCEGUI_HAS_FREETYPE)

ADD_LIBRARY(cegui-freya STATIC ${CEGUI_SOURCE} )

SET(FREYA_CORE_LINK_LIBRARIES ${FREYA_CORE_LINK_LIBRARIES} cegui-freya ${BULLET_LIBRARIES} FreyaMath_core )

#Generate library target depending on FREYA_CORE_SHARED

IF(APPLE)
    ADD_DEFINITIONS( -DTOLUA_RELEASE )
ENDIF()	

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

---------------------Startup script----------------------------
print("Starting up engine")

local EngineCore = core.EngineCore.getInstance()

--Filesystem
print("Mounting default filesystems")

local fs		 = EngineCore:getFilesystem()
fs:mount("lzma","StdGUI.7z");
fs:mount("lzma","StdShaders.7z");

--Rendering window
EngineCore:createWindowManager("SDL")
local wm		= EngineCore:getWindowManager()
wm:setWindowedModeWindowSize(640,640)
wm:showCursor(true)
wm:grabInput(false)
wm:setCaption("World concept test")

--Startup renderer
local futures = bit.bor(renderer.futures.MULTITEXTURE,renderer.futures.FRAMEBUFFER,renderer.futures.VERTEX_SHADER,renderer.futures.FRAGMENT_SHADER)

EngineCore:createRenderingDriver(futures)
local rapi = EngineCore:getRenderingDriver()

local rm = EngineCore:getResourceManager()
local tm = EngineCore:getTaskManager()

--create keyboard
local kbd 		= 	wm:createKeyDrivenDevice("keyboard")
local mouse 	= 	wm:createMovementDrivenDevice("mouse")
local mouse_btn = 	wm:createKeyDrivenDevice("mouse_buttons")
-------------- CEGUI --------------
local system    
local fontman   
local schememan 
local root

local mx_v,my_v,fps_v,memory_v
local memory_s

function quitbtn_clicked()
	EngineCore:shutdown()
end
-------------- Time ---------------
local oldTime = wm:getTickCount()
-------------- Mouse hack -----------------
local left 	= false
local right = false

--------- FPS -----------------------------
local fps = 0
local frames = 0
local foTime = wm:getTickCount()

function get_fps()
	local fnTime = wm:getTickCount()
	if (fnTime - foTime) > 1000.0 then
		fps = frames / ((fnTime - foTime)*0.001)
		frames = 0
		foTime = fnTime 
		local memUsage = 		memoryUsage(TOTAL_ALLOCATED)
		local memTotalUsage = 	memoryUsage(ALLOCATED_FOR_BUFFERS)
		if memUsage > 1024.0*1024.0 then
			memory_s = ""..string.format("%4.3f",(memUsage / (1024.0*1024.0))) .." MB"
		elseif memUsage > 1024.0 then
			memory_s = ""..string.format("%4.3f",(memUsage / (1024.0))) .." KB"
		else
			memory_s = ""..string.format("%4.3f",(memUsage)) .." B"
		end
		memory_s = memory_s.." / "..string.format("%4.3f",(memTotalUsage / (1024.0*1024.0))).." Mb"
	end
	return core.taskmanager.Task.SECONDARY_THREAD
end

------------------------------	Event update task ---------------------------------------------------------------------------------------
function update_events()
	local newTime = wm:getTickCount()
	wm:updateEvents()
	
	if kbd:getKeyState(windowmanager.input.KeyboardKeys.KEY_ESCAPE) then
		EngineCore:shutdown()
	end
	
	system:injectTimePulse((newTime - oldTime)*0.001)
	-- Inject mouse
	local x = 0
	local y = 0
	x,y = mouse:absoluteState(x,y)
	system:injectMousePosition(x,y)
	mx_v:setText(""..x)
	my_v:setText(""..y)
	
	if mouse_btn:getKeyState(windowmanager.input.BUTTON_LEFT) then
		if not left then
			system:injectMouseButtonDown(CEGUI.LeftButton);
			left = true;

		end
	elseif left then
		system:injectMouseButtonUp(CEGUI.LeftButton);
		left = false;
	end

	
	oldTime = newTime
	return core.taskmanager.Task.MAIN_THREAD
end
------------------------------ Rendering task -------------------------------------------------------------------------------------------
function render()
	rapi:clearColorValue(0.3,0.4,0.5,1.0)
	rapi:clearColor()
	rapi:clearDepth()
	rapi:beginScene()
	
	fps_v:setText(string.format("%4.2f",fps))
	memory_v:setText(memory_s)
	--print(fps)
	system:renderGUI()
	rapi:endScene()
	wm:swapBuffers()
	frames = frames + 1
	return core.taskmanager.Task.MAIN_THREAD
end
------------------------------ Entry point ----------------------------------------------------------------------------------------------
function finish_init()
	rapi:enableDepthTest()
	EngineCore:startCEGUI()
	
	system    = CEGUI.System:getSingleton()
	fontman   = CEGUI.FontManager:getSingleton()
	schememan = CEGUI.SchemeManager:getSingleton()

	schememan:create( "TaharezLook.scheme" )
	fontman:create( "Commonwealth-10.font" )
	fontman:create( "DejaVuSans-10.font" )
	system:setDefaultMouseCursor( "TaharezLook","MouseArrow" )
	
	local ceWm = CEGUI.WindowManager:getSingleton()
	root = ceWm:loadWindowLayout( "WorldTest.layout" )
	system:setGUISheet(root)
	
	mx_v 		= root:getChildRecursive(1000)
	my_v 		= root:getChildRecursive(1001)
	fps_v 		= root:getChildRecursive(3)
	memory_v 	= root:getChildRecursive(1002)
	
	local rend	= root:getChildRecursive(4)
	rend:setText(rapi:getAPIName().." "..rapi:getShaderAPIName())
	rend		= root:getChildRecursive(5)
	rend:setText(rapi:getRendererName()) 
	
	local upTask = core.taskmanager.LuaTask:new("update_events")
	tm:addTask(upTask)
	local rTask = core.taskmanager.LuaTask:new("render")
	tm:addTask(rTask)
	local fpsTask = core.taskmanager.LuaTask:new("get_fps")
	tm:addAsynchronousTask(fpsTask)
	return core.taskmanager.Task.DONE
end

----------------------------- Inject script into app loop
local finTask = core.taskmanager.LuaTask:new("finish_init")
tm:addTask(finTask)

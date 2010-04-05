-----------------	Vertex data viewer entry point -------------------------------------
------ Acquire engine ------------------------------------------------------------------

local EngineCore = core.EngineCore.getInstance()

----------------------------------------------------------------------------------------

print("Mounting default filesystems...")

local fs		 = EngineCore:getFilesystem()
fs:mount("lzma","StdGUI.7z");
fs:mount("lzma","StdShaders.7z");
fs:mount("lzma","Textures.7z");

----------------------------------------------------------------------------------------

EngineCore:createWindowManager("SDL")
local wm		= EngineCore:getWindowManager()
wm:setWindowedModeWindowSize(640,640)
wm:showCursor(true)
wm:grabInput(false)
wm:setCaption("Vertex data viewer")

----------------------------------------------------------------------------------------

local futures = bit.bor(renderer.futures.MULTITEXTURE,renderer.futures.FRAMEBUFFER,renderer.futures.VERTEX_SHADER,renderer.futures.FRAGMENT_SHADER)

EngineCore:createRenderingDriver(futures)
local rapi = EngineCore:getRenderingDriver()

-----------------------------------------------------------------------------------------

local rm = EngineCore:getResourceManager()
local tm = EngineCore:getTaskManager()

-----------------------------------------------------------------------------------------

local kbd 		= 	wm:createKeyDrivenDevice("keyboard")
local mouse 	= 	wm:createMovementDrivenDevice("mouse")
local mouse_btn = 	wm:createKeyDrivenDevice("mouse_buttons")

-----------------------------------------------------------------------------------------

local vdata_renderer = nil
local memory_s
------------------------------------------------------------------------------------------

local system    
local fontman   
local schememan 
local root
local left = false

local fsTable = {}

local oldTime = wm:getTickCount()
------------------------------------------------------------------------------------------

function quitCallback()
	EngineCore:shutdown()
end

setQuitCallback("quitCallback")

function wheelCallback(x,y)
	print ("Wheel scrolled ( "..x..", "..y.." )")
end

setWheelCallback("wheelCallback")

------------------------------------------------------------------------------------------

local	light_pos = math.vector3d.create {x = 1.0, y = 1.0, z = 1.0}
light_pos = light_pos:normalize()
local   light_dist = 5
local   eye_pos    = math.vector3d.create {z = 1,y = 0,x = 0}
local   eye_dist   = 10	
local   camera_selected = true

local zero = math.vector3d.create {}
local up   = math.vector3d.create {y = 1}

function controller_changed(event)
	camera_selected = tolua.cast(root:getChildRecursive(310),"CEGUI::RadioButton"):isSelected()
	if camera_selected then
		print("Camera controller")
	else
		print("Light controller")
	end
 end


function update_events()
	local newTime = wm:getTickCount()
	wm:updateEvents()
	
	if kbd:getKeyState(windowmanager.input.KeyboardKeys.KEY_ESCAPE) then
		EngineCore:shutdown()
	end
	
	local dt = (newTime - oldTime)*0.001;
	
	if kbd:getKeyState(windowmanager.input.KeyboardKeys.KEY_UP) then
		local quat = math.createRotationQuat(dt,math.vector3d.i)
		if camera_selected then
			local new_pos = quat:rotate(eye_pos)
			eye_pos:delete()
			eye_pos = new_pos
			
			local new_up = quat:rotate(up)
			up:delete()
			up = new_up
		else
			local new_pos = quat:rotate(light_pos)
			light_pos:delete()
			light_pos = new_pos
		end
		quat:delete();
	end
	
	if kbd:getKeyState(windowmanager.input.KeyboardKeys.KEY_DOWN) then
		local quat = math.createRotationQuat(-dt,math.vector3d.i)
		if camera_selected then
			local new_pos = quat:rotate(eye_pos)
			eye_pos:delete()
			eye_pos = new_pos
			
			local new_up = quat:rotate(up)
			up:delete()
			up = new_up
		else
			local new_pos = quat:rotate(light_pos)
			light_pos:delete()
			light_pos = new_pos
		end
		quat:delete();
	end
	
	if kbd:getKeyState(windowmanager.input.KeyboardKeys.KEY_LEFT) then
		local quat = math.createRotationQuat(dt,math.vector3d.j)
		if camera_selected then
			local new_pos = quat:rotate(eye_pos)
			eye_pos:delete()
			eye_pos = new_pos
		else
			local new_pos = quat:rotate(light_pos)
			light_pos:delete()
			light_pos = new_pos
		end
		quat:delete();
	end
	
	if kbd:getKeyState(windowmanager.input.KeyboardKeys.KEY_RIGHT) then
		local quat = math.createRotationQuat(-dt,math.vector3d.j)
		if camera_selected then
			local new_pos = quat:rotate(eye_pos)
			eye_pos:delete()
			eye_pos = new_pos
		else
			local new_pos = quat:rotate(light_pos)
			light_pos:delete()
			light_pos = new_pos
		end
		quat:delete();
	end
	
	if kbd:getKeyState(windowmanager.input.KeyboardKeys.KEY_W) then
		if camera_selected then
			eye_dist = eye_dist - dt*10;
		else
			light_dist = light_dist - dt*10;
		end
	end
	
	if kbd:getKeyState(windowmanager.input.KeyboardKeys.KEY_S) then
		if camera_selected then
			eye_dist = eye_dist + dt*10;
		else
			light_dist = light_dist + dt*10;
		end
	end
	
	
	system:injectTimePulse((newTime - oldTime)*0.001)
	-- Inject mouse
	local x = 0
	local y = 0
	x,y = mouse:absoluteState(x,y)
	system:injectMousePosition(x,y)
	
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

----------------------------------------------------------------------------------------------

local fps = 0
local fps_v
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
			memory_s = string.format("%4.3f",(memUsage / (1024.0*1024.0))) .." MB"
		elseif memUsage > 1024.0 then
			memory_s = string.format("%4.3f",(memUsage / (1024.0))) .." KB"
		else
			memory_s = string.format("%4.3f",(memUsage)) .." B"
		end
		memory_s = memory_s.." / "..string.format("%4.3f",(memTotalUsage / (1024.0*1024.0))).." Mb"
	end
	return core.taskmanager.Task.SECONDARY_THREAD
end



local memory_v
------------------------------ Rendering task -------------------------------------------------------------------------------------------
function render()
	rapi:clearColorValue(0.3,0.4,0.5,1.0)
	rapi:clearColor()
	rapi:clearDepth()
	rapi:beginScene()
	
	--setup matricies
	--setup projection
	local projection = math.createPerspectiveProjectionMatrix4x4(1.04,1,1,1000);
	rapi:setMatrix(renderer.Matrix.PROJECTION,projection)
	projection:delete()
	
	local real_eye = eye_pos * eye_dist
	
	local lookat     = math.createLookatMatrix4x4(real_eye, zero, up)
	rapi:setMatrix(renderer.Matrix.VIEW, lookat)
	lookat:delete()
	
	if vdata_renderer then
		local light_pos_ = light_pos*light_dist
		vdata_renderer:render(light_pos_,real_eye)
		light_pos_:delete()
	end
	
	real_eye:delete()
	fps_v:setText(string.format("%3.2f",fps))
	memory_v:setText(memory_s)
	print(fps)
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
	system:setDefaultMouseCursorWithName( "TaharezLook", "MouseArrow" )
	
	local cursor = CEGUI.MouseCursor:getSingleton()
	cursor:show()
	local pos	=	CEGUI.Vector2:new(320,320)
	cursor:setPosition(pos)
	
	if cursor:isVisible() then
		print("Mouse cursor is visible")
	else
		print("Mouse cursor is hidden")
	end
	
	local rect = cursor:getConstraintArea()
	print(string.format("Cursor constraint area is ( %.2f, %.2f, %.2f, %.2f )",rect.left,rect.top,rect.right,rect.bottom))
	
	local ceWm = CEGUI.WindowManager:getSingleton()
	root = ceWm:loadWindowLayout( "VDataViewer.layout" )
	system:setGUISheet(root)
	
	
	local rend	= root:getChildRecursive(103)
	rend:setText(rapi:getShaderAPIName())
 
 	fps_v = root:getChildRecursive(102)
 	
 	
 	local fs_list = fs:list()
 	
 	print ("Retrieved fs list of size "..fs_list:size())
 	
 	local list_size = fs_list:size()
 	
 	local listbox = tolua.cast(root:getChildRecursive(201),"CEGUI::Listbox")
 	local cols = CEGUI.colour:new_local(0.2,0.2,1.0,1.0)
 	
 	for i=0,(list_size - 1),1 do
 		local n = fs_list[i]
 		if string.match(n,"(.vdata)$") then
 			print("Adding item "..n)
 			local item = CEGUI.createListboxTextItem(n, 0, nil, false, true)
 			item:setSelectionBrush("TaharezLook", "MultiListSelectionBrush")
  			item:setSelectionColour(cols)
  			listbox:addItem(item)
 		end
 	end
	memory_v = root:getChildRecursive(1002)
	vdata_renderer = VDataRenderer:new()
	
	local upTask = core.taskmanager.LuaTask:new("update_events")
	tm:addTask(upTask)
	local rTask = core.taskmanager.LuaTask:new("render")
	tm:addTask(rTask)
	local fpsTask = core.taskmanager.LuaTask:new("get_fps")
	tm:addAsynchronousTask(fpsTask)
	return core.taskmanager.Task.DONE
end

local selection_path = nil

function reload_data(event)
	vdata_renderer:reload(selection_path)
	if vdata_renderer:hasTangentSpace() then
		local checkbox = tolua.cast(root:getChildRecursive(110),"CEGUI::Checkbox")
		checkbox:setSelected(true)
		checkbox:setProperty("Disabled","False")
	else
		checkbox:setProperty("Disabled","True")
	end
end

function bump_enabler_clicked(event)
	--print("Changing bump state")
	local checkbox = tolua.cast(root:getChildRecursive(110),"CEGUI::Checkbox")
	vdata_renderer:enableBumpMapping(checkbox:isSelected())
end

function selection_changed(event)
	local load_btn = root:getChildRecursive(202)
	local listbox = tolua.cast(root:getChildRecursive(201),"CEGUI::Listbox")

	local item = listbox:getFirstSelectedItem()
	if item then
		load_btn:setProperty("Disabled","False")
		selection_path = item:getText()
	else
		load_btn:setProperty("Disabled","True")
	end
end

----------------------------- Inject script into app loop ------------------------------------------------
local finTask = core.taskmanager.LuaTask:new("finish_init")
tm:addTask(finTask)

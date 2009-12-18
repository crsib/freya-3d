string.split = function(str, pattern)
  pattern = pattern or "[^%s]+"
  if pattern:len() == 0 then pattern = "[^%s]+" end
  local parts = {__index = table.insert}
  setmetatable(parts, parts)
  str:gsub(pattern, parts)
  setmetatable(parts, nil)
  parts.__index = nil
  return parts
end

world = {}

shader = {}

bind_type = framework
--------------------------- World creation -------------------------------------------------------------------------------------

function world.size(list)
	print "Creating world..."
	world.controller = world_builder:new(list.cell_width or 1024,list.cell_height or 1024,list.width or 1,list.height or 1)
	world.instance = framework.World.getSingleton()
	return world.instance
end

function world.data(list)
	world.controller:delete()
	return world.instance
end

function world.shader_library(list)
	world.controller:createShaderLibrary(#list, list.api)
	for i,v in ipairs(list) do
		print(table.show(v, "shader"))
		world.load_shader(v)
	end
end

function world.load_shader(list)
	local resid = ":shader"
	if list.shader_name then
		resid = ":shader:"..list.shader_name
	else
		if list.vertex_shader then
			resid=resid..":vertex:"..list.vertex_shader
		end
		
		if list.fragment_shader then
			resid=resid..":fragment:"..list.fragment_shader
		end
		
		if list.geometry_shader then
			resid=resid..":geometry:"..list.geometry_shader
		end
		
		if list.vertex_shaders then
			local shaders = list.vertex_shaders:split( "[^,%s]+" )
			for i,val in ipairs(shaders) do
				resid = resid..":vertex:"..val
			end
		end
		
		if list.fragment_shaders then
			local shaders = list.fragment_shaders:split( "[^,%s]+" )
			for i,val in ipairs(shaders) do
				resid = resid..":fragment:"..val
			end
		end
		
		if list.geometry_shaders then
			local shaders = list.geometry_shaders:split( "[^,%s]+" )
			for i,val in ipairs(shaders) do
				resid = resid..":geometry:"..val
			end
		end
	end
	print ("ResId for ID "..(list.id or "shader").." is "..resid) 
	
	local uniformCount = 0
	local attributeCount = 0
	
	if list.uniforms then
		uniformCount = #list.uniforms
	end
	
	if list.attributes then
		attributeCount = #list.attributes
	end 
	world.controller:addShaderToLibrary((list.id or "shader"),resid, uniformCount ,attributeCount)
	print( "Uniform count " .. uniformCount )
	print( "Attribute count " .. attributeCount )
	----------------- Now, create bindings ----------------------------------------------------------
	if uniformCount > 0 then
		for i,val in ipairs(list.uniforms) do
			local tp = val.type
			print ("Uniform "..i.." type "..val.type)
			if tp == framework.INT then
				world.controller:addUniformBind1i(val.id or 1,val.loc or "unknown", val.value)
			elseif tp == framework.FLOAT then
				world.controller:addUniformBind1f(val.id or 1,val.loc or "unknown", val.value)
			elseif tp == framework.FLOAT2 then 
				world.controller:addUniformBind2f(val.id or 1,val.loc or "unknown", val.value[1] or 0,val.value[2] or 0)
			elseif tp == framework.FLOAT3 then 
				world.controller:addUniformBind3f(val.id or 1,val.loc or "unknown", val.value[1] or 0,val.value[2] or 0,val.value[3] or 0)
			elseif tp == framework.FLOAT4 then
				world.controller:addUniformBind4f(val.id or 1,val.loc or "unknown", val.value[1] or 0,val.value[2] or 0,val.value[3] or 0, 
																					val.value[4] or 0)
			elseif tp == framework.MAT3x3 then
				world.controller:addUniformBind4f(val.id or 1,val.loc or "unknown", 
														val.value[1] or 0,val.value[2] or 0,val.value[3] or 0,
														val.value[4] or 0,val.value[5] or 0,val.value[6] or 0,
														val.value[7] or 0,val.value[8] or 0,val.value[9] or 0
														)
			elseif tp == framework.MAT4x4 then 
				world.controller:addUniformBind4f(val.id or 1,val.loc or "unknown", 
														val.value[1] or 0,val.value[2] or 0,val.value[3] or 0,val.value[4] or 0,
														val.value[5] or 0,val.value[6] or 0,val.value[7] or 0,val.value[8] or 0,
														val.value[9] or 0,val.value[10] or 0,val.value[11] or 0,val.value[12] or 0,
														val.value[13] or 0,val.value[14] or 0,val.value[15] or 0,val.value[16] or 0
														)
			elseif tp == framework.SAMPLER then
				world.controller:addUniformBindSampler(val.id or 1,val.loc or "unknown", val.value)
			elseif tp == framework.VIEW then
				world.controller:addViewMatrixBind(val.id or 1,val.loc or "unknown")
			elseif tp == framework.WORLD then 
				world.controller:addViewMatrixBind(val.id or 1,val.loc or "unknown")
			elseif tp == framework.PROJECTION then
				world.controller:addViewMatrixBind(val.id or 1,val.loc or "unknown")
			end--if--
		end--for--
	end--if--
	
	if attributeCount > 0 then
		for i,val in ipairs(list.attributes) do
			local tp = val.type
			print ("Uniform "..i.." type "..val.type)
			if tp == framework.INT then
				world.controller:addAttributeBind1i(val.id or 1,val.loc or "unknown", val.value)
			elseif tp == framework.FLOAT then
				world.controller:addAttributeBind1f(val.id or 1,val.loc or "unknown", val.value)
			elseif tp == framework.FLOAT2 then 
				world.controller:addAttributeBind2f(val.id or 1,val.loc or "unknown", val.value[1] or 0,val.value[2] or 0)
			elseif tp == framework.FLOAT3 then 
				world.controller:addAttributeBind3f(val.id or 1,val.loc or "unknown", val.value[1] or 0,val.value[2] or 0,val.value[3] or 0)
			elseif tp == framework.FLOAT4 then
				world.controller:addAttributeBind4f(val.id or 1,val.loc or "unknown", val.value[1] or 0,val.value[2] or 0,val.value[3] or 0, 
																					val.value[4] or 0)
			elseif tp == framework.MAT3x3 then
				world.controller:addAttributeBind4f(val.id or 1,val.loc or "unknown", 
														val.value[1] or 0,val.value[2] or 0,val.value[3] or 0,
														val.value[4] or 0,val.value[5] or 0,val.value[6] or 0,
														val.value[7] or 0,val.value[8] or 0,val.value[9] or 0
														)
			elseif tp == framework.MAT4x4 then 
				world.controller:addAttributeBind4f(val.id or 1,val.loc or "unknown", 
														val.value[1] or 0,val.value[2] or 0,val.value[3] or 0,val.value[4] or 0,
														val.value[5] or 0,val.value[6] or 0,val.value[7] or 0,val.value[8] or 0,
														val.value[9] or 0,val.value[10] or 0,val.value[11] or 0,val.value[12] or 0,
														val.value[13] or 0,val.value[14] or 0,val.value[15] or 0,val.value[16] or 0
														)
			end--if--
		end--for--
	end--if--
	
end--function--

function shader.uniforms(list)
	return list;
end;
function shader.attributes(list)
	return list;
end;

function world.shader(list)
	return list;
end;

function shader.bind(list)
	return list
end;
----------------------------- Generates static XML strings -------------------------------------------------------------
local strings_db = {	
--scene node
	"camera", "type","value",
	"rect",	"left",	"right",
	"top",	"bottom",	"fov",
	"clip_distance",	"near","far",
	"position",	"up",	"light",
	"type",	"position",	"radius",
	"is_shadow_caster",	"attentuation",	"constant",	"linear",
	"quadratic",	"light_map",	"scene_node",	"path",
	"loader",	"rendering",	"is_skinned",	"animation_file",
	"geometry_path",	"shader",	"id",	"texture",	"mipmaps_needed",
	"true",	"false",	"min_filter",	"NEAREST",	"LINEAR",	"NEAREST_MIPMAP_NEAREST",
	"NEAREST_MIPMAP_LINEAR",	"LINEAR_MIPMAP_NEAREST",	"LINEAR_MIPMAP_LINEAR",
	"PROJECTIVE",	"ORTHO",	"POINT",
	"SPOT",	"DIRECTIONAL",	"vertex_data",
	"use_batch",	"lod_level",	"pass",
	"physics_simulation",	"internal_id",
--world
	"world", "shader_library", "shader_api",
	"cell_size","width","height",
	"world_size", "horizontal", "vertical",
	"include","path","horizontal_range","vertical_range",
	"cell",
	"height_map", "path",
	"water_map", "nodes_map",
	"landscape_shader", "id",
	"node",
	"scene_node",
	"position","value","orientation",
	"world_part",
--shader library
	"shader_library","shader_api",
	"shader","id","shader_name",
	"bind", "uniform", "type", "value","id",
	"attribute", "vertex", "geometry", "fragment",
	"INT","FLOAT","FLOAT2","FLOAT3","FLOAT4","MAT3x3","MAT4x4",
	"SAMPLER","VIEW","WORLD","PROJECTION","scale",
	
	"node_id","x","y"
}

function removedups (t)
    local result = {}
    local count = 0
    local found
    for i,v in ipairs(t) do
        found = false
        if count > 0 then
            for j = 1,count do
                    if v == result[j] then found = true; break end
                end
        end
        if not found then 
            count = count + 1
            result[count] = v 
        end
    end
    return result, count
end

local strings,count = removedups (strings_db)

local h_file 	= io.open("XMLStaticStrings.h","w")
local cpp_file 	= io.open("XMLStaticStrings.cpp","w")
---------------------- Writing headers --------------------------------------------------------------------------------
h_file:write([[
/*
 * This file was auto generated using XMLString.lua.
 * Please, do not modify contents of this file.
 */
 
#ifndef _XMLSTATICSTRINGS_H_
#define _XMLSTATICSTRINGS_H_

#include "core/xml/XMLParser.h"

#define XMLS(x) framework::xmls::XMLStr_##x

namespace framework
{
	
namespace xmls
{
	
]])

cpp_file:write([[
/*
 * This file was auto generated using XMLString.lua.
 * Please, do not modify contents of this file.
 */
 
#include "XMLStaticStrings.h"

namespace framework
{
	
namespace xmls
{

using namespace core::xml;

]])
-----------------------Writing data------------------------------------------------------------------------------------
for i,v in ipairs(strings) do
    local str 	= string.gsub(v," ","_");
    str 		= string.gsub(v,"\t","__");
	h_file:write("//String representing \""..str.."\"\nextern const\tXMLCh\tXMLStr_"..str.."[];\n\n")
	--More interesting part
	cpp_file:write("//String representing \""..str.."\"\nconst\tXMLCh\tXMLStr_"..str.."[] = {\n\t")
	
	for j = 1,string.len(str) do
		local it = string.sub(str,j,j)
		if it ~= "_" then
			cpp_file:write("chLatin_"..it..", ");
		else
			cpp_file:write("chUnderscore, ");
		end
	end
	
	cpp_file:write("chNull\n};\n\n");
end
-----------------------Finalizing--------------------------------------------------------------------------------------
h_file:write([[

} //namespace xml_s
} //namespace framework

#endif //_XMLSTATICSTRINGS_H_
]])

cpp_file:write([[

} //namespace xml_s
} //namespace framework

]])
h_file:close()
cpp_file:close()
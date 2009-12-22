/*
 * DeclarativeMethods.hpp
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Dec 15, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef DECLARATIVEMETHODS_HPP_
#define DECLARATIVEMETHODS_HPP_
#include "framework/World.h"
#include "framework/Structures.h"

#include <iostream>
#include <cassert>

class world_builder
{
public:
	world_builder(unsigned cellWidth, unsigned cellHeight, unsigned worldWidth, unsigned worldHeight);

	framework::ShaderLibrary* 	createShaderLibrary(unsigned num_shader, const EString& api);

	framework::ShaderWrapper*  	addShaderToLibrary(const EString& id,const EString& resid, unsigned num_uniform_b,unsigned num_attr_b);

	void					  	addUniformBind1i(unsigned id,const EString& loc, int _1);
	void					  	addUniformBindSampler(unsigned id,const EString& loc, int _1);
	void						addUniformBind1f(unsigned id,const EString& loc, float _1);
	void						addUniformBind2f(unsigned id,const EString& loc, float _1, float _2);
	void						addUniformBind3f(unsigned id,const EString& loc, float _1, float _2, float _3);
	void						addUniformBind4f(unsigned id,const EString& loc, float _1, float _2, float _3, float _4);
	void						addUniformBind3x3f(unsigned id,const EString& loc,
			float _11, float _12, float _13,
			float _21, float _22, float _23,
			float _31, float _32, float _33);
	void						addUniformBind4x4f(unsigned id,const EString& loc,
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44);

	void					  	addAttributeBind1i(unsigned id,const EString& loc, int _1);
	void						addAttributeBind1f(unsigned id,const EString& loc, float _1);
	void						addAttributeBind2f(unsigned id,const EString& loc, float _1, float _2);
	void						addAttributeBind3f(unsigned id,const EString& loc, float _1, float _2, float _3);
	void						addAttributeBind4f(unsigned id,const EString& loc, float _1, float _2, float _3, float _4);
	void						addAttributeBind3x3f(unsigned id,const EString& loc,
			float _11, float _12, float _13,
			float _21, float _22, float _23,
			float _31, float _32, float _33);
	void						addAttributeBind4x4f(unsigned id,const EString& loc,
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44);

	void						addViewMatrxiBind(unsigned id,const EString& loc);
	void						addProjMatrixBind(unsigned id,const EString& loc);
	void						addWorldMatrixBind(unsigned id,const EString& loc);

private:
	framework::World*				m_WorldInstance;
	framework::ShaderLibraryPtr		m_CurrentLibraryPtr;
	unsigned						m_CurrentLibraryShaderIdx;
	unsigned						m_CurrentUniformBind;
	unsigned						m_CurrentAttributeBind;
};


//======================================= Implementation =====================================
inline
world_builder::world_builder(unsigned cellWidth, unsigned cellHeight, unsigned worldWidth, unsigned worldHeight)
{
	m_WorldInstance = framework::World::create(cellWidth,cellHeight,worldWidth, worldHeight);
}

inline framework::ShaderLibrary *world_builder::createShaderLibrary(unsigned  num_shaders, const EString & api)
{
	std::clog << "Adding shader library for " << api << std::endl;

	framework::ShaderLibraryPtr lib = new framework::ShaderLibrary;
	lib->apiName = api;
	lib->num_shaders = num_shaders;
	lib->shaders	= new framework::ShaderWrapper[num_shaders];
	m_CurrentLibraryPtr = lib;
	m_CurrentLibraryShaderIdx = 0;
	return lib;
}

inline void world_builder::addUniformBind3f(unsigned id,const EString & loc, float _1, float _2, float _3)
{
	std::clog << "Adding shader uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind ++;
	bind->FLOAT3[0] = _1;
	bind->FLOAT3[1] = _2;
	bind->FLOAT3[2] = _3;

	bind->type = framework::FLOAT3;

	bind->id 		= id;
	bind->name 		= loc;

}



inline void world_builder::addUniformBind1f(unsigned id,const EString & loc, float _1)
{
	std::clog << "Adding shader uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind ++;
	bind->FLOAT = _1;

	bind->type = framework::FLOAT;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addAttributeBind3f(unsigned id,const EString & loc, float _1, float _2, float _3)
{
	std::clog << "Adding shader attribute bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->attribute_bindings + m_CurrentAttributeBind;
	m_CurrentAttributeBind ++;
	bind->FLOAT3[0] = _1;
	bind->FLOAT3[1] = _2;
	bind->FLOAT3[2] = _3;

	bind->type = framework::FLOAT3;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addUniformBind3x3f(unsigned id,const EString & loc, float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33)
{
	std::clog << "Adding shader uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind ++;

	bind->MAT3x3[0][0] = _11; bind->MAT3x3[0][1] = _12; bind->MAT3x3[0][2] = _13;
	bind->MAT3x3[1][0] = _21; bind->MAT3x3[1][1] = _22; bind->MAT3x3[1][2] = _23;
	bind->MAT3x3[2][0] = _31; bind->MAT3x3[2][1] = _32; bind->MAT3x3[2][2] = _33;


	bind->type = framework::MAT3x3;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addProjMatrixBind(unsigned id,const EString & loc)
{
	std::clog << "Adding shader uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind ++;

	bind->type = framework::PROJECTION;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addViewMatrxiBind(unsigned id,const EString & loc)
{
	std::clog << "Adding shader uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind ++;

	bind->type = framework::VIEW;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addUniformBind4x4f(unsigned id,const EString & loc, float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24, float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44)
{
	std::clog << "Adding shader uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind ++;

	bind->MAT4x4[0][0] = _11; bind->MAT4x4[0][1] = _12; bind->MAT4x4[0][2] = _13; bind->MAT4x4[0][3] = _14;
	bind->MAT4x4[1][0] = _21; bind->MAT4x4[1][1] = _22; bind->MAT4x4[1][2] = _23; bind->MAT4x4[1][3] = _24;
	bind->MAT4x4[2][0] = _31; bind->MAT4x4[2][1] = _32; bind->MAT4x4[2][2] = _33; bind->MAT4x4[2][3] = _34;
	bind->MAT4x4[3][0] = _41; bind->MAT4x4[3][1] = _42; bind->MAT4x4[3][2] = _43; bind->MAT4x4[3][3] = _44;

	bind->type = framework::MAT4x4;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addAttributeBind2f(unsigned id,const EString & loc, float _1, float _2)
{
	std::clog << "Adding shader attribute bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->attribute_bindings + m_CurrentAttributeBind;
	m_CurrentAttributeBind ++;
	bind->FLOAT2[0] = _1;
	bind->FLOAT2[1] = _2;

	bind->type = framework::FLOAT2;

	bind->id 		= id;
	bind->name 		= loc;

}



inline void world_builder::addUniformBind1i(unsigned id,const EString & loc, int _1)
{
	std::clog << "Adding shader uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind++;
	bind->INT = _1;

	bind->type = framework::INT;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addAttributeBind1i(unsigned id,const EString & loc, int _1)
{
	std::clog << "Adding shader attribute bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->attribute_bindings + m_CurrentAttributeBind;
	m_CurrentAttributeBind++;
	bind->INT = _1;

	bind->type = framework::INT;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addUniformBind2f(unsigned id,const EString & loc, float _1, float _2)
{
	std::clog << "Adding shader uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind ++;
	bind->FLOAT2[0] = _1;
	bind->FLOAT2[1] = _2;

	bind->type = framework::FLOAT2;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addUniformBindSampler(unsigned id,const EString & loc, int _1)
{
	std::clog << "Adding shader uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind++;
	bind->SAMPLER = _1;

	bind->type = framework::SAMPLER;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addAttributeBind4f(unsigned id,const EString & loc, float _1, float _2, float _3, float _4)
{
	std::clog << "Adding attribute bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->attribute_bindings + m_CurrentAttributeBind;
	m_CurrentAttributeBind ++;
	bind->FLOAT4[0] = _1;
	bind->FLOAT4[1] = _2;
	bind->FLOAT4[2] = _3;
	bind->FLOAT4[3] = _4;

	bind->type = framework::FLOAT4;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addAttributeBind1f(unsigned id,const EString & loc, float _1)
{
	std::clog << "Adding attribute bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->attribute_bindings + m_CurrentAttributeBind;
	m_CurrentAttributeBind ++;
	bind->FLOAT = _1;

	bind->type = framework::FLOAT;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addWorldMatrixBind(unsigned id,const EString & loc)
{
	std::clog << "Adding uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind ++;

	bind->type = framework::WORLD;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addUniformBind4f(unsigned id,const EString & loc, float _1, float _2, float _3, float _4)
{
	std::clog << "Adding uniform bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->uniform_bindings + m_CurrentUniformBind;
	m_CurrentUniformBind ++;
	bind->FLOAT4[0] = _1;
	bind->FLOAT4[1] = _2;
	bind->FLOAT4[2] = _3;
	bind->FLOAT4[3] = _4;

	bind->type = framework::FLOAT4;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addAttributeBind4x4f(unsigned id,const EString & loc, float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24, float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44)
{
	std::clog << "Adding attribute bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->attribute_bindings + m_CurrentAttributeBind;
	m_CurrentAttributeBind ++;

	bind->MAT4x4[0][0] = _11; bind->MAT4x4[0][1] = _12; bind->MAT4x4[0][2] = _13; bind->MAT4x4[0][3] = _14;
	bind->MAT4x4[1][0] = _21; bind->MAT4x4[1][1] = _22; bind->MAT4x4[1][2] = _23; bind->MAT4x4[1][3] = _24;
	bind->MAT4x4[2][0] = _31; bind->MAT4x4[2][1] = _32; bind->MAT4x4[2][2] = _33; bind->MAT4x4[2][3] = _34;
	bind->MAT4x4[3][0] = _41; bind->MAT4x4[3][1] = _42; bind->MAT4x4[3][2] = _43; bind->MAT4x4[3][3] = _44;

	bind->type = framework::MAT4x4;

	bind->id 		= id;
	bind->name 		= loc;
}



inline void world_builder::addAttributeBind3x3f(unsigned id,const EString & loc, float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33)
{
	std::clog << "Adding attribute bind \"" << loc << "\" to " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx - 1;
	framework::ShaderBindingPtr bind = shader->attribute_bindings + m_CurrentAttributeBind;
	m_CurrentAttributeBind ++;

	bind->MAT3x3[0][0] = _11; bind->MAT3x3[0][1] = _12; bind->MAT3x3[0][2] = _13;
	bind->MAT3x3[1][0] = _21; bind->MAT3x3[1][1] = _22; bind->MAT3x3[1][2] = _23;
	bind->MAT3x3[2][0] = _31; bind->MAT3x3[2][1] = _32; bind->MAT3x3[2][2] = _33;


	bind->type = framework::MAT3x3;

	bind->id 		= id;
	bind->name 		= loc;
}



inline framework::ShaderWrapper* world_builder::addShaderToLibrary(const EString & id,const EString& resid, unsigned  num_uniform_b, unsigned  num_attr_b)
{
	std::clog << "Adding shader " << id << std::endl;
	framework::ShaderWrapperPtr shader = m_CurrentLibraryPtr->shaders + m_CurrentLibraryShaderIdx;
	m_CurrentLibraryShaderIdx++;
	assert(m_CurrentLibraryShaderIdx <= m_CurrentLibraryPtr->num_shaders);
	m_CurrentUniformBind = 0;
	m_CurrentAttributeBind = 0;

	shader->shaderID = id;
	shader->shaderResId = resid;
	shader->num_uniform_bindings = num_uniform_b;
	shader->uniform_bindings = new framework::ShaderBinding[num_uniform_b];
	shader->num_attribute_bindings = num_attr_b;
	shader->attribute_bindings = new framework::ShaderBinding[num_attr_b];
	return shader;
}





#endif /* DECLARATIVEMETHODS_HPP_ */

/*
 * lua_helpers.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 5, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef LUA_HELPERS_H_
#define LUA_HELPERS_H_

#ifndef _cstring
#define _cstring char*
#endif

#include "core/EngineCore.h"
#include "core/filesystem/Filesystem.h"
#include "core/lua/LuaCore.h"
#include "core/lua/LuaFunction.h"
#include "windowmanager/DriverSubsystems/InputDevices/KeyboardKeys.h"
#include "windowmanager/DriverSubsystems/InputDevices/MouseButtons.h"
#include "core/taskmanager/Task.h"
#include "windowmanager/WindowManagerDriver.h"
#include "windowmanager/Callback.h"
#include "scenegraph/VBOData.h"
#include "resources/Resource.h"
#include "resources/ResourceManager.h"
#include "primitives/Cube.h"

inline
void include(const EString& modName, const EString& path)
{
	size_t ssz;
	void* s_src = core::EngineCore::getFilesystem()->read(path,&ssz);
	EString scr(reinterpret_cast<char*>(s_src),ssz);
	core::EngineCore::getLuaCore()->includeModule(modName,scr);
	core::memory::Free(s_src,core::memory::GENERIC_POOL);
}

enum	MemControl
{
	TOTAL_ALLOCATED,
	ALLOCATION_COUNT,
	DEALLOCATION_COUNT,
	ALLOCATED_FOR_BUFFERS
};

namespace core
{
namespace memory
{
extern EXPORT unsigned memory_allocated;
extern EXPORT unsigned allocation_count;
extern EXPORT unsigned deallocation_count;
extern EXPORT unsigned alloc_dealloc_dif;
extern EXPORT unsigned allocated_for_buffers;
}
}

unsigned memoryUsage(MemControl ctrl)
{

	switch(ctrl)
	{
		case TOTAL_ALLOCATED:
			return core::memory::memory_allocated;
		case ALLOCATION_COUNT:
			return core::memory::allocation_count;
		case DEALLOCATION_COUNT:
			return core::memory::deallocation_count;
		case ALLOCATED_FOR_BUFFERS:
			return core::memory::allocated_for_buffers;
	}
	return 0;
}

const char*
keyboardKeyName(size_t i)
{
	return windowmanager::input::KeyboardKeyNames[i];
}

const char*
mouseButtonName(size_t i)
{
	return windowmanager::input::MouseButtonsNames[i];
}

namespace core
{
namespace taskmanager
{

class LuaTask : public core::taskmanager::Task
{
public:
	explicit LuaTask(const EString& metName) : m_Fn(metName,0,1)
	{
	}

	virtual
	int operator () ()
	{
		return (int)m_Fn();
	}
private:
	core::lua::LuaFunction		m_Fn;
};

}
}
namespace core
{
namespace lua
{
namespace __internal
{
extern core::lua::LuaFunction*		quit_callback;
extern core::lua::LuaFunction*		wheel_callback;

inline
void		quitCallback()
{
	if(quit_callback)
	{
		quit_callback->call();
	}
}

inline
void		wheelCallback(int hor,int vert)
{
	if(wheel_callback)
	{
		wheel_callback->setParameter(0,core::Variable((int)hor));
		wheel_callback->setParameter(1,core::Variable((int)vert));
		wheel_callback->call();
	}
}

}
}
}


inline
void	setQuitCallback(const EString& luaFn)
{
	if(core::lua::__internal::quit_callback)
		delete core::lua::__internal::quit_callback;
	core::lua::__internal::quit_callback = new core::lua::LuaFunction(luaFn,0,0);
	core::EngineCore::getWindowManager()->setQuitCallback(windowmanager::Callback(core::lua::__internal::quitCallback));
}

inline
void	setWheelCallback(const EString& luaFn)
{
	if(core::lua::__internal::wheel_callback)
		delete core::lua::__internal::wheel_callback;
	core::lua::__internal::wheel_callback = new core::lua::LuaFunction(luaFn,2,0);
	core::EngineCore::getWindowManager()->setMouseWheelCallback(windowmanager::Callback(core::lua::__internal::wheelCallback));
}

class		VDataRenderer : public EngineSubsystem
{
public:
	VDataRenderer()
	{
		m_VBODataResource = m_DiffuseResource =
				m_NormalMapResource = m_SpecularResource =
						m_BumpedShaderResource = m_NoBumpShaderResource =
								NULL;
		m_RM = core::EngineCore::getResourceManager();
		m_Rapi = core::EngineCore::getRenderingDriver();

		m_HasTangentSpace = false;

		m_DiffuseResource = m_RM->load(":tga:/Textures/diffuse.tga:mipmaps",resources::ResourceManager::IMMEDIATELY);
		m_SpecularResource = m_RM->load(":tga:/Textures/specular.tga:mipmaps",resources::ResourceManager::IMMEDIATELY);
		m_NormalMapResource = m_RM->load(":tga:/Textures/normal.tga:mipmaps",resources::ResourceManager::IMMEDIATELY);

		m_Diffuse = m_DiffuseResource->get<renderer::Texture*>();
		m_Specular = m_SpecularResource->get<renderer::Texture*>();
		m_NormalMap = m_NormalMapResource->get<renderer::Texture*>();

		m_BumpedShaderResource = m_RM->load(":shader:bump",resources::ResourceManager::IMMEDIATELY);
		m_NoBumpShaderResource = m_RM->load(":shader:nobump",resources::ResourceManager::IMMEDIATELY);

		m_LightSource = new primitives::Cube;
		m_LightSource->setDiffuse(m_Diffuse);
		m_LightSource->setSpecular(m_Specular);
		m_LightSource->setBump(m_NormalMap);
		m_LightSource->setShader(m_BumpedShaderResource->get<renderer::Shader*>());

		renderer::Shader* s = m_NoBumpShaderResource->get<renderer::Shader*>();
		s->setTexture("diffuse",renderer::TextureUnit::TEXTURE0);
		s->setTexture("specular",renderer::TextureUnit::TEXTURE1);

	}
	virtual ~VDataRenderer()
	{
		m_RM->free(m_DiffuseResource);
		m_RM->free(m_NormalMapResource);
		m_RM->free(m_SpecularResource);
		if(m_VBODataResource)
			m_RM->free(m_VBODataResource);
		m_RM->free(m_BumpedShaderResource);
		m_RM->free(m_NoBumpShaderResource);
		delete m_LightSource;
	}

	bool	hasTangentSpace() const
	{
		return m_HasTangentSpace;
	}

	void	reload(const EString& path)
	{
		resources::Resource* res = m_VBODataResource;

		m_VBODataResource = m_RM->load(":vbo:"+path,resources::ResourceManager::IMMEDIATELY);

		if(res)
			m_RM->free(res);

		m_VBOData = m_VBODataResource->get<scenegraph::VBOData*>();

		//Search for tangent
		m_HasTangentSpace = false;
		for(size_t i = 0; i < m_VBOData->num_batches; i++)
		{
			scenegraph::VBOData::VBOBatchHeader*	batch = m_VBOData->batches + i;
			renderer::VertexElement* elem = batch->layout;
			while(elem->usage != renderer::VertexFormat::UNUSED)
			{
				if(elem->usage == renderer::VertexFormat::TANGENT)
				{
					m_HasTangentSpace = true;
					break;
				}
				elem++;
			}
			if(m_HasTangentSpace)
				break;
		}

		m_Shader = m_HasTangentSpace ? m_BumpedShaderResource->get<renderer::Shader*>() : m_NoBumpShaderResource->get<renderer::Shader*>();
	}

	void	enableBumpMapping(bool val)
	{
		//std::cout << "Switching bump " << (val ? "on" : "off") << std::endl;
		if(m_HasTangentSpace)
			m_Shader = val ? m_BumpedShaderResource->get<renderer::Shader*>() : m_NoBumpShaderResource->get<renderer::Shader*>();
	}

	void	render(const math::vector3d& light_pos, const math::vector3d& eye_pos)
	{
		if(m_VBODataResource)
		{
			m_Rapi->setTexture(renderer::TextureUnit::TEXTURE0,m_Diffuse);
			m_Rapi->setTexture(renderer::TextureUnit::TEXTURE1,m_Specular);
			m_Rapi->setTexture(renderer::TextureUnit::TEXTURE2,m_NormalMap);

			m_Shader->setUniform("lightPos",light_pos);
			m_Shader->setUniform("eyePos",eye_pos);

			m_Rapi->setMatrix(renderer::Matrix::MODEL,math::matrix4x4::identity);
			//Render VBO here
			m_Shader->bind();

			for(size_t i = 0; i < m_VBOData->num_batches; i++)
			{
				scenegraph::VBOData::VBOBatchHeader*	batch = m_VBOData->batches + i;
				m_Rapi->setStreamSource(0,m_VBOData->vertex_data,batch->buffer_offset,batch->stride);
				m_Rapi->setVertexFormat(batch->layout);

				if(m_VBOData->number_of_indicies)
				{
					m_Rapi->drawIndexedPrimitive((renderer::Primitive::type)batch->assembly_type,batch->index_count,renderer::DataType::UNSIGNED_SHORT,m_VBOData->indicies);
				}
				else
				{
					m_Rapi->drawPrimitive((renderer::Primitive::type)batch->assembly_type,0,batch->index_count);
				}
			}
			m_Shader->unbind();
			//Translate to light position
			math::matrix4x4 transf = math::matrix4x4::translationMatrix(light_pos)*math::matrix4x4::scaleMatrix(0.05,0.05,0.05);
			m_Rapi->setMatrix(renderer::Matrix::MODEL,transf);
			m_LightSource->render();
		}
	}

private:
	bool						m_HasTangentSpace;

	resources::Resource* 		m_VBODataResource;
	scenegraph::VBOData*		m_VBOData;

	resources::Resource*		m_DiffuseResource;
	resources::Resource*		m_NormalMapResource;
	resources::Resource*		m_SpecularResource;

	renderer::Texture*			m_Diffuse;
	renderer::Texture*			m_NormalMap;
	renderer::Texture*			m_Specular;

	resources::Resource*		m_BumpedShaderResource;
	resources::Resource*		m_NoBumpShaderResource;

	renderer::Shader*			m_Shader;

	resources::ResourceManager* m_RM;
	renderer::RenderingAPIDriver* m_Rapi;

	primitives::Cube*			m_LightSource;
};
#endif /* LUA_HELPERS_H_ */

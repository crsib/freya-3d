/*
 * ShaderLibrary.cpp
 *
 *  Created on: Jan 7, 2010
 *      Author: crsib
 */

#include "scenegraph/ShaderLibrary.h"

#include "core/EngineCore.h"
#include "resources/ResourceManager.h"
#include "renderer/RenderingAPIDriver.h"

#include "core/EngineException.h"

namespace scenegraph
{

namespace __internal
{
class EXPORT TypeMismatchException : public ::EngineException
{
public:
	TypeMismatchException(const char* func)
	{
		msg = "[SHADER_LIBRARY]: type mismatch in ";
		msg += func;
	}

	virtual ~TypeMismatchException()throw(){}

	virtual
	EString message() const
	{
		return msg;
	}

	virtual
	const char* what  	() const throw ()
	{
		return msg.c_str();
	}

private:
	EString 	msg;
};
}

ShaderLibrary::ShaderLibrary( const EString&  shader_api ) throw()
																		: m_APIName( shader_api )
{

}

ShaderLibrary::~ShaderLibrary( )
{

}

const EString&
ShaderLibrary::apiName() const
{
	return m_APIName;
}

ShaderLibrary::Shader*			ShaderLibrary::addShader(unsigned id, const EString& name, const EString res_id)
{
	Shader*			shader = new Shader(id,name,res_id);
	m_ShadersById[id] = shader;
	m_ShadersByName[name] = shader;
	return shader;
}

ShaderLibrary::Shader*			ShaderLibrary::getShader(unsigned id)
{
	return m_ShadersById[id];
}

ShaderLibrary::Shader*			ShaderLibrary::getShader(const EString& name)
{
	return m_ShadersByName[name];
}

void			ShaderLibrary::preloadShader(unsigned id)
{
	m_ShadersById[id]->load();
}

void			ShaderLibrary::preloadShader(const EString& name)
{
	m_ShadersByName[name]->load();
}

bool			ShaderLibrary::checkShader(unsigned id)
{
	return m_ShadersById[id]->isOk();
}

bool			ShaderLibrary::checkShader(const EString& name)
{
	return m_ShadersByName[name]->isOk();
}

//========= ShaderLibrary::Shader ==================================
ShaderLibrary::Shader::Shader( unsigned id, const EString& name, const EString& resource_id)
:m_ShaderName(name), m_ShaderId(id), m_ResourceId(resource_id),
 m_Shader(NULL),m_Resource(0),
 m_IsLoaded(false), m_IsOk(false), m_RefCount(0)
 {

 }

ShaderLibrary::Shader::~Shader()
{
	if(m_IsLoaded)
		core::EngineCore::getResourceManager()->free(m_Resource);
	m_IsLoaded = false;
	m_RefCount = 0;
	m_Shader = NULL;
	ShaderBindingsById::iterator it = m_ShaderBindingsById.begin();
	for( ; it != m_ShaderBindingsById.end(); ++it)
		delete it->second;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, int value)
{
	Shader::IntShaderBinding*	bind = new Shader::IntShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;
	bind->Data = value;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, float value)
{
	Shader::FloatShaderBinding*	bind = new Shader::FloatShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;
	bind->Data = value;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, const math::vector2d& value)
{
	Shader::Float2ShaderBinding*	bind = new Shader::Float2ShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;
	bind->Data = value;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, const math::vector3d& value)
{
	Shader::Float3ShaderBinding*	bind = new Shader::Float3ShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;
	bind->Data = value;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, const math::vector4d& value)
{
	Shader::Float4ShaderBinding*	bind = new Shader::Float4ShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;
	bind->Data = value;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, const math::matrix3x3& value)
{
	Shader::Mat3x3ShaderBinding*	bind = new Shader::Mat3x3ShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;
	bind->Data = value;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, const math::matrix4x4& value)
{
	Shader::Mat4x4ShaderBinding*	bind = new Shader::Mat4x4ShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;
	bind->Data = value;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, renderer::TextureUnit::type value)
{
	Shader::SamplerShaderBinding*	bind = new Shader::SamplerShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;
	bind->Data = value;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, const IntToType<SHADER_BIND_TYPE_PROJECTION>& type)
{
	(void) type;
	Shader::ProjectionShaderBinding*	bind = new Shader::ProjectionShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, const IntToType<SHADER_BIND_TYPE_WORLD>& type)
{
	(void) type;
	Shader::WorldShaderBinding*	bind = new Shader::WorldShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::addBinding(unsigned id, const EString& name, const EString& shader_id, const IntToType<SHADER_BIND_TYPE_VIEW>& type)
{
	(void) type;
	Shader::ViewShaderBinding*	bind = new Shader::ViewShaderBinding;

	bind->ID = id;
	bind->Name = name;
	bind->InShaderName = shader_id;

	m_ShaderBindingsById[id] = bind;
	m_ShaderBindingsByName[name] = bind;
}

void	ShaderLibrary::Shader::updateBinding(unsigned id, int value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsById[id];
	if(bind->BindType == SHADER_BIND_TYPE_INT)
	{
		static_cast<Shader::IntShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(unsigned id, float value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsById[id];
	if(bind->BindType == SHADER_BIND_TYPE_FLOAT)
	{
		static_cast<Shader::FloatShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(unsigned id, const math::vector2d& value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsById[id];
	if(bind->BindType == SHADER_BIND_TYPE_FLOAT2)
	{
		static_cast<Shader::Float2ShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(unsigned id, const math::vector3d& value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsById[id];
	if(bind->BindType == SHADER_BIND_TYPE_FLOAT3)
	{
		static_cast<Shader::Float3ShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(unsigned id, const math::vector4d& value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsById[id];
	if(bind->BindType == SHADER_BIND_TYPE_FLOAT4)
	{
		static_cast<Shader::Float4ShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(unsigned id, const math::matrix3x3& value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsById[id];
	if(bind->BindType == SHADER_BIND_TYPE_MAT3x3)
	{
		static_cast<Shader::Mat3x3ShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(unsigned id, const math::matrix4x4& value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsById[id];
	if(bind->BindType == SHADER_BIND_TYPE_MAT4x4)
	{
		static_cast<Shader::Mat4x4ShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void  	ShaderLibrary::Shader::updateBinding(unsigned id, renderer::TextureUnit::type value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsById[id];
	if(bind->BindType == SHADER_BIND_TYPE_SAMPLER)
	{
		static_cast<Shader::SamplerShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(const EString& name, int value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsByName[name];
	if(bind->BindType == SHADER_BIND_TYPE_INT)
	{
		static_cast<Shader::IntShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(const EString& name, float value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsByName[name];
	if(bind->BindType == SHADER_BIND_TYPE_FLOAT)
	{
		static_cast<Shader::FloatShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(const EString& name, const math::vector2d& value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsByName[name];
	if(bind->BindType == SHADER_BIND_TYPE_FLOAT2)
	{
		static_cast<Shader::Float2ShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(const EString& name, const math::vector3d& value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsByName[name];
	if(bind->BindType == SHADER_BIND_TYPE_FLOAT3)
	{
		static_cast<Shader::Float3ShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(const EString& name, const math::vector4d& value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsByName[name];
	if(bind->BindType == SHADER_BIND_TYPE_FLOAT4)
	{
		static_cast<Shader::Float4ShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(const EString& name, const math::matrix3x3& value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsByName[name];
	if(bind->BindType == SHADER_BIND_TYPE_MAT3x3)
	{
		static_cast<Shader::Mat3x3ShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::updateBinding(const EString& name, const math::matrix4x4& value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsByName[name];
	if(bind->BindType == SHADER_BIND_TYPE_MAT4x4)
	{
		static_cast<Shader::Mat4x4ShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void  	ShaderLibrary::Shader::updateBinding(const EString& name, renderer::TextureUnit::type value)
{
	Shader::ShaderBinding*	bind = m_ShaderBindingsByName[name];
	if(bind->BindType == SHADER_BIND_TYPE_SAMPLER)
	{
		static_cast<Shader::SamplerShaderBinding*>(bind)->Data = value;
		bind->NeedsUpdate = true;
	}
	else
		throw __internal::TypeMismatchException(__FUNCTION__);
}

void	ShaderLibrary::Shader::bind()
{
	if(m_Shader)
	{
		m_Shader->bind();
		for(ShaderBindingsById::iterator it = m_ShaderBindingsById.begin(); it != m_ShaderBindingsById.end(); ++it)
		{
			Shader::ShaderBinding* _bind = it->second;
			if(_bind->NeedsUpdate)
			{
				_bind->bind(m_Shader);
				if(_bind->BindType < SHADER_BIND_TYPE_ALWAYS_UPDATE)
					_bind->NeedsUpdate = false;
			}
		}
	}
	else
	{
		if(m_Resource)
		{
			if(m_Resource->ready())
			{
				m_IsLoaded = true;
				m_Shader = m_Resource->get<renderer::Shader*>();
				m_IsOk = m_Shader->isOk();
			}
		}
		else
			load();
	}
}

void	ShaderLibrary::Shader::unbind()
{
	if(m_Shader)
		m_Shader->unbind();
}

bool	ShaderLibrary::Shader::isLoaded()
{
	if(!m_IsLoaded && m_Resource && m_Resource->ready())
	{
		m_IsLoaded = true;
		m_Shader = m_Resource->get<renderer::Shader*>();
		m_IsOk = m_Shader->isOk();
	}

	return m_IsLoaded;
}

bool	ShaderLibrary::Shader::isOk()
{
	return isLoaded() && m_IsOk;
}

void	ShaderLibrary::Shader::load()
{
	if(m_RefCount == 0)
	{
		m_Resource = core::EngineCore::getResourceManager()->load(m_ResourceId);
	}
}

void	ShaderLibrary::Shader::free()
{
	if(m_RefCount > 1)
	{
		m_RefCount--;
	}
	else
	{
		core::EngineCore::getResourceManager()->free(m_Resource);
		m_Resource = NULL;
		m_RefCount = 0;
		m_IsLoaded = m_IsOk = false;
		m_Shader = NULL;
	}
}

void	ShaderLibrary::Shader::retain()
{
	m_RefCount++;
}

unsigned short ShaderLibrary::Shader::retainCount()
{
	return m_RefCount;
}

// ShaderBindings

void
ShaderLibrary::Shader::IntShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, Data);
}

void
ShaderLibrary::Shader::FloatShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, Data);
}

void
ShaderLibrary::Shader::Float2ShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, Data);
}

void
ShaderLibrary::Shader::Float3ShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, Data);
}

void
ShaderLibrary::Shader::Float4ShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, Data);
}

void
ShaderLibrary::Shader::Mat3x3ShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, Data);
}

void
ShaderLibrary::Shader::Mat4x4ShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, Data);
}

void
ShaderLibrary::Shader::SamplerShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, Data);
}

void
ShaderLibrary::Shader::ViewShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, core::EngineCore::getRenderingDriver()->getMatrix(renderer::Matrix::VIEW));
}

void
ShaderLibrary::Shader::WorldShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, core::EngineCore::getRenderingDriver()->getMatrix(renderer::Matrix::WORLD));
}

void
ShaderLibrary::Shader::ProjectionShaderBinding::bind(renderer::Shader* shader) const
{
	shader->setUniform(InShaderName, core::EngineCore::getRenderingDriver()->getMatrix(renderer::Matrix::PROJECTION));
}

}

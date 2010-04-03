/*
 * ShaderLibrary.h
 *
 *  Created on: Jan 7, 2010
 *      Author: crsib
 */

#ifndef SHADERLIBRARY_H_
#define SHADERLIBRARY_H_

#include "core/EngineSubsystem.h"
#include "core/EString.h"

#include "math/math.hpp"

#include "internal.h"

#include "renderer/DriverSubsystems/Shader.h"
#include "renderer/3DConstants.h"
#include "resources/Resource.h"

#include <map>
#include "core/memory/MemoryAllocator.h"

namespace scenegraph
{
//! This class provides a shader library
/*!
* This class provides generic shader library for creating more generic abstraction of Shader from renderer.
* It provides functionality of loading, compiling and linking shaders on per api basis, binding shader uniforms,
* setting attribute streams (if needed) and providing fast and robust interface for accessing shaders from rendering pipe.
*/
class EXPORT ShaderLibrary : virtual public EngineSubsystem
{
public:
	//! Generic constructor
	/*!
	* This constructor creates a library for a specific shader API.
	* @param shader_api is shader API string.
	* @return
	*/
	ShaderLibrary( const EString&  shader_api ) throw();

	//! Generic destructor
	virtual ~ShaderLibrary( );

	//!Get the name of the shader api
	/*!
	* Retrieves the name of shader api used by this library.
	* @return Shader API name.
	*/
	const EString&	apiName() const;
	//====================== Internal classes ======================================
	//! Abstraction of a library shader
	class EXPORT Shader : virtual public EngineSubsystem
	{
		friend class ShaderLibrary;
	private:
		Shader( unsigned id, const EString& name, const EString& resource_id);
		virtual ~Shader();
	public:
		//! Type of shader binding
		enum	SHADER_BIND_TYPE
		{
			//! The type is int
			SHADER_BIND_TYPE_INT,
			//! The type is float
			SHADER_BIND_TYPE_FLOAT,
			//! The type is 2D vector of floats
			SHADER_BIND_TYPE_FLOAT2,
			//! The type is 3D vector of floats
			SHADER_BIND_TYPE_FLOAT3,
			//! The type is 4D vector of floats
			SHADER_BIND_TYPE_FLOAT4,
			//! The type is 3x3 matrix of floats
			SHADER_BIND_TYPE_MAT3x3,
			//! The type is 4x4 matrix of floats
			SHADER_BIND_TYPE_MAT4x4,
			//! Texture sampler
			SHADER_BIND_TYPE_SAMPLER,

			SHADER_BIND_TYPE_ALWAYS_UPDATE,
			//! Uniform for passing view matrix, if not otherwise defined by the API
			SHADER_BIND_TYPE_VIEW,
			//! Uniform for passing world matrix, if not otherwise specified by API
			SHADER_BIND_TYPE_WORLD,
			//! Uniform for passing projection matrix, if not otherwise specified by API
			SHADER_BIND_TYPE_PROJECTION
		};
		void	addBinding(unsigned id, const EString& name, const EString& shader_id, int value);
		void	addBinding(unsigned id, const EString& name, const EString& shader_id, float value);

		void	addBinding(unsigned id, const EString& name, const EString& shader_id, const math::vector2d& value);
		void	addBinding(unsigned id, const EString& name, const EString& shader_id, const math::vector3d& value);
		void	addBinding(unsigned id, const EString& name, const EString& shader_id, const math::vector4d& value);

		void	addBinding(unsigned id, const EString& name, const EString& shader_id, const math::matrix3x3& value);
		void	addBinding(unsigned id, const EString& name, const EString& shader_id, const math::matrix4x4& value);

		void	addBinding(unsigned id, const EString& name, const EString& shader_id, renderer::TextureUnit::type value);

		void	addBinding(unsigned id, const EString& name, const EString& shader_id, const IntToType<SHADER_BIND_TYPE_PROJECTION>& type);
		void	addBinding(unsigned id, const EString& name, const EString& shader_id, const IntToType<SHADER_BIND_TYPE_WORLD>& type);
		void	addBinding(unsigned id, const EString& name, const EString& shader_id, const IntToType<SHADER_BIND_TYPE_VIEW>& type);

		void	updateBinding(unsigned id, int value);
		void	updateBinding(unsigned id, float value);

		void	updateBinding(unsigned id, const math::vector2d& value);
		void	updateBinding(unsigned id, const math::vector3d& value);
		void	updateBinding(unsigned id, const math::vector4d& value);

		void	updateBinding(unsigned id, const math::matrix3x3& value);
		void	updateBinding(unsigned id, const math::matrix4x4& value);

		void  	updateBinding(unsigned id, renderer::TextureUnit::type value);

		void	updateBinding(const EString& name, int value);
		void	updateBinding(const EString& name, float value);

		void	updateBinding(const EString& name, const math::vector2d& value);
		void	updateBinding(const EString& name, const math::vector3d& value);
		void	updateBinding(const EString& name, const math::vector4d& value);

		void	updateBinding(const EString& name, const math::matrix3x3& value);
		void	updateBinding(const EString& name, const math::matrix4x4& value);

		void  	updateBinding(const EString& name, renderer::TextureUnit::type value);

		void	bind();
		void	unbind();

		bool	isLoaded();
		bool	isOk();

		void	load();
		void	free();
		void	retain();
		unsigned short retainCount();

	private:
		EString					m_ShaderName;
		unsigned				m_ShaderId;
		EString					m_ResourceId;
		renderer::Shader*		m_Shader;
		resources::Resource*	m_Resource;
		bool					m_IsLoaded;
		bool					m_IsOk;
		unsigned short			m_RefCount;
		//Binding classes
		class ShaderBinding : virtual public ::EngineSubsystem
		{
		public:
			ShaderBinding(SHADER_BIND_TYPE type) : BindType(type),NeedsUpdate(true){}
			virtual ~ShaderBinding(){}
			virtual void	bind(renderer::Shader* shader) const = 0;

			SHADER_BIND_TYPE		BindType;
			unsigned 				ID;
			EString					InShaderName;
			EString					Name;
			bool					NeedsUpdate;
		};
		//Inherited classes
		class IntShaderBinding : public ShaderBinding
		{
		public:
			IntShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_INT){}
			void			bind(renderer::Shader* shader) const;
			int 			Data;
		};

		class FloatShaderBinding : public ShaderBinding
		{
		public:
			FloatShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_FLOAT){}
			void			bind(renderer::Shader* shader) const;
			float			Data;
		};

		class Float2ShaderBinding : public ShaderBinding
		{
		public:
			Float2ShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_FLOAT2){}
			void			bind(renderer::Shader* shader) const;
			math::vector2d	Data;
		};

		class Float3ShaderBinding : public ShaderBinding
		{
		public:
			Float3ShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_FLOAT3){}
			void			bind(renderer::Shader* shader) const;
			math::vector3d	Data;
		};

		class Float4ShaderBinding : public ShaderBinding
		{
		public:
			Float4ShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_FLOAT4){}
			void			bind(renderer::Shader* shader) const;
			math::vector4d	Data;
		};

		class Mat3x3ShaderBinding : public ShaderBinding
		{
		public:
			Mat3x3ShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_MAT3x3){}
			void			bind(renderer::Shader* shader) const;
			math::matrix3x3	Data;
		};

		class Mat4x4ShaderBinding : public ShaderBinding
		{
		public:
			Mat4x4ShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_MAT4x4){}
			void			bind(renderer::Shader* shader) const;
			math::matrix4x4	Data;
		};

		class SamplerShaderBinding : public ShaderBinding
		{
		public:
			SamplerShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_SAMPLER){}
			void			bind(renderer::Shader* shader) const;
			renderer::TextureUnit::type		Data;
		};

		class ViewShaderBinding : public ShaderBinding
		{
		public:
			ViewShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_VIEW){}
			void			bind(renderer::Shader* shader) const;
		};

		class WorldShaderBinding : public ShaderBinding
		{
		public:
			WorldShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_WORLD){}
			void			bind(renderer::Shader* shader) const;
		};

		class ProjectionShaderBinding : public ShaderBinding
		{
		public:
			ProjectionShaderBinding() : ShaderBinding(SHADER_BIND_TYPE_PROJECTION){}
			void			bind(renderer::Shader* shader) const;
		};
		//End of helper class hierarchy
		typedef  std::map<unsigned, ShaderBinding*, std::less<unsigned>, core::memory::MemoryAllocator<std::pair<const unsigned, ShaderBinding*> > > ShaderBindingsById;
		typedef  std::map<EString, ShaderBinding*, std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString, ShaderBinding*> > > ShaderBindingsByName;
		ShaderBindingsById				m_ShaderBindingsById;
		ShaderBindingsByName			m_ShaderBindingsByName;
	};

	Shader*			addShader(unsigned id, const EString& name, const EString res_id);

	Shader*			getShader(unsigned id);
	Shader*			getShader(const EString& name);

	void			preloadShader(unsigned id);
	void			preloadShader(const EString& name);

	bool			checkShader(unsigned id);
	bool			checkShader(const EString& name);

	private:
	EString			m_APIName;

	typedef std::map<unsigned, Shader*, std::less<unsigned>, core::memory::MemoryAllocator<std::pair<const unsigned, Shader*> > > ShadersById;
	typedef std::map<EString, Shader*, std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString, Shader*> > > ShadersByName;

	ShadersById 	m_ShadersById;
	ShadersByName  	m_ShadersByName;
};

}

#endif /* SHADERLIBRARY_H_ */

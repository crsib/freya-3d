#ifndef _CUBE_H_
#define _CUBE_H_

#include "core/EngineSubsystem.h"
#include "internal.h"
#include "renderer.h"
namespace primitives
{

class EXPORT Cube : virtual public ::EngineSubsystem
{
public:
	Cube();
	virtual ~Cube();

	void render();

	void addInstance(const renderer::InstanceData& i);

	renderer::InstanceData&  getInstance(unsigned i);

	unsigned getInstancesCount();
	renderer::Shader *getShader() const
	{
		return m_Shader;
	}

	void setShader(renderer::Shader *m_Shader)
	{
		this->m_Shader = m_Shader;
	}

	renderer::Texture *getDiffuse() const
	{
		return m_Diffuse;
	}

	void setDiffuse(renderer::Texture *m_Diffuse)
	{
		this->m_Diffuse = m_Diffuse;
	}

	renderer::Texture *getSpecular() const
	{
		return m_Specular;
	}

	void setSpecular(renderer::Texture *m_Specular)
	{
		this->m_Specular = m_Specular;
	}

	renderer::Texture *getBump() const
	{
		return m_Bump;
	}

	void setBump(renderer::Texture *m_Bump)
	{
		this->m_Bump = m_Bump;
	}

private:
	renderer::InstanceArray					m_Arr;
	static renderer::VertexBufferObject*			m_Verticies;
	static renderer::VertexBufferObject*			m_Normals;
	static renderer::VertexBufferObject*			m_Indicies;
	static renderer::VertexBufferObject*			m_Tangents;
	static renderer::VertexBufferObject*			m_Binormals;
	static renderer::VertexBufferObject*			m_UV;

	renderer::Shader*						m_Shader;

	renderer::Texture*						m_Diffuse;
	renderer::Texture*						m_Specular;
	renderer::Texture*						m_Bump;

	renderer::RenderingAPIDriver*			rapi;

}; //End of Cube class

} //End of unit_tests namespace
#endif //End of _CUBE_H_

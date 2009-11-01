/*
 * Sphere.h
 *
 *  Created on: 22.04.2009
 *      Author: vedenko
 */

#ifndef SPHERE_H_
#define SPHERE_H_
#include "core/EngineSubsystem.h"
#include <iostream>
#include <vector>
/*
 *
 */
namespace primitives
{
template <unsigned x_div,unsigned y_div>
class Sphere : virtual public ::EngineSubsystem
{
public:
	Sphere();
	virtual ~Sphere()
	{

	}
	void render();

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
	renderer::Shader*						m_Shader;

	renderer::Texture*						m_Diffuse;
	renderer::Texture*						m_Specular;
	renderer::Texture*						m_Bump;

	static renderer::VertexBufferObject* m_VBO;
	static renderer::VertexBufferObject* m_Ind;
	renderer::RenderingAPIDriver*		m_Rapi;
	struct VertexData
	{
		math::vector3d vert; //normal is equal to vertex, as we construct the unit sphere
		math::vector3d t;
		math::vector3d b;
		float u;
		float v;
		void* operator new(size_t sz)
		{
			return core::memory::Allocate(sz,core::memory::GENERIC_POOL);
		}
		void* operator new[](size_t sz)
		{
			return core::memory::Allocate(sz,core::memory::GENERIC_POOL);
		}
		void	operator delete(void * p)
		{
			core::memory::Free(p,core::memory::GENERIC_POOL);
		}
		void	operator delete[](void * p)
		{
			core::memory::Free(p,core::memory::GENERIC_POOL);
		}
	};
	struct IndexData
	{
		unsigned short t1;
		unsigned short t2;
		unsigned short t3;
		void* operator new(size_t sz)
		{
			return core::memory::Allocate(sz,core::memory::GENERIC_POOL);
		}
		void* operator new[](size_t sz)
		{
			return core::memory::Allocate(sz,core::memory::GENERIC_POOL);
		}
		void	operator delete(void * p)
		{
			core::memory::Free(p,core::memory::GENERIC_POOL);
		}
		void	operator delete[](void * p)
		{
			core::memory::Free(p,core::memory::GENERIC_POOL);
		}
	};
};

template <unsigned x_div,unsigned y_div>
renderer::VertexBufferObject* Sphere<x_div,y_div>::m_VBO = NULL;
template <unsigned x_div,unsigned y_div>
renderer::VertexBufferObject* Sphere<x_div,y_div>::m_Ind = NULL;

//Constructor
template <unsigned x_div,unsigned y_div>
Sphere<x_div,y_div>::Sphere()
{
	m_Rapi = core::EngineCore::getRenderingDriver();
	if(m_VBO == NULL)
	{
		//We need to construct our sphere according the x and y subdivisons
		VertexData* arr = new VertexData[(x_div + 2) * y_div + 1];
		float alpha_ofs = 2.0*math::pi / x_div;
		float phi_ofs = math::pi / y_div;
		int i = 0;
		for(float phi = -math::pi * 0.5f; phi <= math::pi *0.5f; phi += phi_ofs)
		{
			for(float alpha = 0.0f; alpha < 2*math::pi; alpha += alpha_ofs,++i)
			{
				//Calculate vertex
				arr[i].vert.x = cos(alpha)*cos(phi);
				arr[i].vert.z = sin(alpha)*cos(phi);
				arr[i].vert.y = sin(phi);
				//Calculate mapping
				//arr[i].u = static_cast<float>(i % x_div) / x_div;
				//arr[i].v = static_cast<float>(i / x_div) / y_div;
				arr[i].u = alpha / (2 * math::pi);
				arr[i].v = (phi + math::pi*0.5) / math::pi;
				//Calculate t
				//y = 0;
				//a*vx + b*vy = 0;
				//a = -sin(alpha);
				//b = cos(alpha);
				arr[i].t.x = -sin(alpha);
				arr[i].t.y = 0;
				arr[i].t.z = cos(alpha);
				//Calculate b
				arr[i].b = arr[i].t * arr[i].vert;
				arr[i].b.normalize();
			}
		}
		//Now, let us build index array.
		//We have got the following number of indicies
		IndexData*	ind = new IndexData[2*(x_div + 1)*y_div];
		int index = 0;
		for(unsigned i = 0; i <= y_div; i++)
			for(unsigned j = 0;j < x_div;j++,index+=2)
			{
				unsigned k = j + 1;//((j + 1) == x_div) ? 0 : j + 1;
				unsigned l = ((i + 1) == y_div) ? i + 1 : i+1;
				ind [index].t1 = i*(x_div) + j;
				ind [index].t2 = (l)*(x_div) + j;
				ind [index].t3 = (l)*(x_div) + k;

				ind [index+1].t1 = i*(x_div) + j;
				ind [index+1].t2 = (l)*(x_div) + k;
				ind [index+1].t3 = i*(x_div) + k;
			}
		m_VBO = m_Rapi->createVertexBufferObject();
		m_VBO->setTarget(renderer::VBOTarget::VERTEX);
		m_VBO->setData(renderer::VBOUsage::STATIC_DRAW,((x_div + 2) * y_div + 1) * sizeof(VertexData),arr);

		m_Ind = m_Rapi->createVertexBufferObject();
		m_Ind->setTarget(renderer::VBOTarget::INDEX);
		m_Ind->setData(renderer::VBOUsage::STATIC_DRAW,(x_div + 1) * y_div * 2 * sizeof(IndexData),ind);

		delete [] ind;
		delete [] arr;
	}
}
template <unsigned x_div,unsigned y_div>
void Sphere<x_div,y_div>::render()
{
	m_Rapi->setStreamSource(0,m_VBO,0,sizeof(VertexData));

	static renderer::VertexElement  fmt[] =
	{
			FREYA_DECLARATION(0,renderer::VertexFormat::POSITION,renderer::VertexFormat::FLOAT3,0),
			FREYA_DECLARATION(0,renderer::VertexFormat::NORMAL,renderer::VertexFormat::FLOAT3,0),
			FREYA_DECLARATION(0,renderer::VertexFormat::TEXT_COORD0,renderer::VertexFormat::FLOAT2,3*sizeof(math::vector3d)),
			FREYA_DECLARATION(0,renderer::VertexFormat::TEXT_COORD1,renderer::VertexFormat::FLOAT3,sizeof(math::vector3d)),
			FREYA_DECLARATION(0,renderer::VertexFormat::TEXT_COORD2,renderer::VertexFormat::FLOAT3,2*sizeof(math::vector3d)),
			FREYA_LAST_DECLARATION(),
	};

	m_Rapi->setVertexFormat(fmt);
	if(m_Shader)
	{
		if(m_Diffuse)
			m_Shader->setTexture("diffuse",renderer::TextureUnit::TEXTURE0);
		if(m_Specular)
			m_Shader->setTexture("specular",renderer::TextureUnit::TEXTURE1);
		if(m_Bump)
			m_Shader->setTexture("bump",renderer::TextureUnit::TEXTURE2);
		m_Shader->bind();
	}

	if(m_Diffuse)
		m_Rapi->setTexture(renderer::TextureUnit::TEXTURE0,m_Diffuse);
	if(m_Specular)
		m_Rapi->setTexture(renderer::TextureUnit::TEXTURE1,m_Specular);
	if(m_Bump)
		m_Rapi->setTexture(renderer::TextureUnit::TEXTURE2,m_Bump);

	m_Rapi->drawIndexedPrimitive(renderer::Primitive::TRIANGLES,(x_div) * (y_div + 1) * 2 * 3,renderer::DataType::UNSIGNED_SHORT,m_Ind);

	if(m_Shader)
		m_Shader->unbind();
}


}
#endif /* SPHERE_H_ */

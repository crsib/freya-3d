#ifndef CFRUSTRUM_H_
#define CFRUSTRUM_H_

#include "math/vector3d.hpp"
#include "math/quaternion.hpp"
#include "math/plane.hpp"
#include "renderer/DriverSubsystems/VertexBufferObject.h"
#include "renderer/RenderingAPIDriver.h"
#include "core/EngineCore.h"
#include "core/EngineSubsystem.h"
#define IN_FRUSTUM	1
#define OUTSIDE_FRUSTUM 0

#include "internal.h"

namespace camera
{
inline bool AreCollinear(const math::vector3d& a,const math::vector3d& b,const math::vector3d& c)
{
	return abs_sq((b - a) * (c - a)) < math::eps * math::eps;
}
class EXPORT Frustum : virtual public ::EngineSubsystem
{
public:
	Frustum()
	{
		rapi = core::EngineCore::getRenderingDriver();

		m_VertexBuffer = rapi->createVertexBufferObject();
		m_VertexBuffer->setTarget(renderer::VBOTarget::VERTEX);
		m_VertexBuffer->setData(renderer::VBOUsage::DYNAMIC_DRAW,sizeof(math::vector3d)*8,&m_Verts[0]);

		m_IndexBuffer = rapi->createVertexBufferObject();
		m_IndexBuffer->setTarget(renderer::VBOTarget::INDEX);
		m_IndexBuffer->setData(renderer::VBOUsage::DYNAMIC_DRAW,sizeof(unsigned short int)*22,m_Indicies);
	}
	Frustum(const math::vector3d& orig, const math::plane& near,const math::plane& far) : Origin(orig), NearPlane(near),FarPlane(far)
	{
		rapi = core::EngineCore::getRenderingDriver();

		m_VertexBuffer = rapi->createVertexBufferObject();
		m_VertexBuffer->setTarget(renderer::VBOTarget::VERTEX);
		m_VertexBuffer->setData(renderer::VBOUsage::DYNAMIC_DRAW,sizeof(math::vector3d)*8,&m_Verts[0]);

		m_IndexBuffer = rapi->createVertexBufferObject();
		m_IndexBuffer->setTarget(renderer::VBOTarget::INDEX);
		m_IndexBuffer->setData(renderer::VBOUsage::DYNAMIC_DRAW,sizeof(unsigned short int)*22,m_Indicies);
	}
	Frustum(const Frustum& fr) : Origin(fr.Origin), NearPlane(fr.NearPlane),FarPlane(fr.FarPlane)
	{
		rapi = core::EngineCore::getRenderingDriver();
		m_Verticies[0] = fr.m_Verticies[0];
		m_Verticies[1] = fr.m_Verticies[1];
		m_Verticies[2] = fr.m_Verticies[2];
		m_Verticies[3] = fr.m_Verticies[3];

		m_Planes[0]    = fr.m_Planes[0];
		m_Planes[1]    = fr.m_Planes[1];
		m_Planes[2]    = fr.m_Planes[2];
		m_Planes[3]    = fr.m_Planes[3];

		m_VertexBuffer = rapi->createVertexBufferObject();
		m_VertexBuffer->setTarget(renderer::VBOTarget::VERTEX);
		m_VertexBuffer->setData(renderer::VBOUsage::DYNAMIC_DRAW,sizeof(math::vector3d)*8,&m_Verts[0]);

		m_IndexBuffer = rapi->createVertexBufferObject();
		m_IndexBuffer->setTarget(renderer::VBOTarget::INDEX);
		m_IndexBuffer->setData(renderer::VBOUsage::DYNAMIC_DRAW,sizeof(unsigned short int)*22,m_Indicies);
	}
	~Frustum()
	{
	}

	void 	setVertex(const math::vector3d& vert,unsigned pos)
	{
		m_Verticies[pos] = vert;
	}

	void    setVerticies(const math::vector3d* vert)
	{
		m_Verticies[0] = vert[0];
		m_Verticies[1] = vert[1];
		m_Verticies[2] = vert[2];
		m_Verticies[3] = vert[3];
	}
	void    reset() //Build planes
	{
		if(!AreCollinear(Origin,m_Verticies[0],m_Verticies[3]))
			m_Planes[0] = math::plane(Origin,m_Verticies[0],m_Verticies[3]);
		if(!AreCollinear(Origin,m_Verticies[1],m_Verticies[0]))
			m_Planes[1] = math::plane(Origin,m_Verticies[1],m_Verticies[0]);
		if(!AreCollinear(Origin,m_Verticies[2],m_Verticies[1]))
			m_Planes[2] = math::plane(Origin,m_Verticies[2],m_Verticies[1]);
		if(!AreCollinear(Origin,m_Verticies[3],m_Verticies[2]))
			m_Planes[3] = math::plane(Origin,m_Verticies[3],m_Verticies[2]);
		//Check for getNormal() correctness
		math::vector3d v = (m_Verticies[0] + m_Verticies[1] + m_Verticies[2] + m_Verticies[3])*0.25f;
		if(m_Planes[0].classify(v) == math::plane::IN_BACK)
			m_Planes[0].flip();
		if(m_Planes[1].classify(v) == math::plane::IN_BACK)
			m_Planes[1].flip();
		if(m_Planes[2].classify(v) == math::plane::IN_BACK)
			m_Planes[2].flip();
		if(m_Planes[3].classify(v) == math::plane::IN_BACK)
			m_Planes[3].flip();
	}
	void updateIndexBuffer()
	{
		m_Indicies[0] =  0;m_Indicies[1] =  1;
		m_Indicies[2] =  2;m_Indicies[3] =  3;
		m_Indicies[4] =  4;m_Indicies[5] =  5;
		m_Indicies[6] =  6;m_Indicies[7] =  7;

		m_Indicies[8] =  0;
		m_Indicies[9] =  1;
		m_Indicies[10] = 1;
		m_Indicies[11] = 0;
		m_Indicies[12] = 0;
		m_Indicies[13] = 2;
		m_Indicies[14] = 6;
		m_Indicies[15] = 4;
		m_Indicies[16] = 4;
		m_Indicies[17] = 5;
		m_Indicies[18] = 5;
		m_Indicies[19] = 7;
		m_Indicies[20] = 3;
		m_Indicies[21] = 1;
		m_IndexBuffer->setSubData(0,sizeof(unsigned short int)*22,m_Indicies);
	}
	void updateVertexBuffer()
	{
		m_Verts[0] = m_Verticies[0]*NearPlane.getDistance()/((m_Verticies[0],NearPlane.getNormal()));
		m_Verts[1] = m_Verticies[0]*FarPlane.getDistance()/((m_Verticies[0],NearPlane.getNormal()));
		m_Verts[2] = m_Verticies[1]*NearPlane.getDistance()/((m_Verticies[1],NearPlane.getNormal()));
		m_Verts[3] = m_Verticies[1]*FarPlane.getDistance()/((m_Verticies[1],NearPlane.getNormal()));
		m_Verts[4] = m_Verticies[2]*NearPlane.getDistance()/((m_Verticies[2],NearPlane.getNormal()));
		m_Verts[5] = m_Verticies[2]*FarPlane.getDistance()/((m_Verticies[2],NearPlane.getNormal()));
		m_Verts[6] = m_Verticies[3]*NearPlane.getDistance()/((m_Verticies[3],NearPlane.getNormal()));
		m_Verts[7] = m_Verticies[3]*FarPlane.getDistance()/((m_Verticies[3],NearPlane.getNormal()));
		m_VertexBuffer->setSubData(0,sizeof(math::vector3d)*8,&m_Verts[0]);
	}
	void   move(const math::vector3d& d)
	{
		Origin	+= d;
		NearPlane.move(d);
		FarPlane.move(d);
		m_Planes[0].move(d);
		m_Planes[1].move(d);
		m_Planes[2].move(d);
		m_Planes[3].move(d);
	}

	void setPosition(const math::vector3d& p)
	{
		Origin = p;
	}

	void   rotate(math::quaternion& d)
	{
		m_Rotation	*= d;
		NearPlane.rotate(d);
		FarPlane.rotate(d);
		m_Planes[0].rotate(d);
		m_Planes[1].rotate(d);
		m_Planes[2].rotate(d);
		m_Planes[3].rotate(d);
		m_RotMtx = m_Rotation;
	}

	void setOrientation(const math::quaternion& q)
	{
		m_Rotation = q;
		m_RotMtx   = q;
	}

	int    operator ()(const math::vector3d& point)//check point
	{
		if(NearPlane.classify(point) == math::plane::IN_BACK)
			return false;
		if(FarPlane.classify(point) == math::plane::IN_BACK)
			return false;
		if(m_Planes[0].classify(point) == math::plane::IN_BACK)
			return false;
		if(m_Planes[1].classify(point) == math::plane::IN_BACK)
			return false;
		if(m_Planes[2].classify(point) == math::plane::IN_BACK)
			return false;
		if(m_Planes[3].classify(point) == math::plane::IN_BACK)
			return false;
	}
	void   render()	//Renders frustum
	{
		//TODO: Add moving to position code here
		/*rapi->enableClientState(renderer::ClientState::VERTEX_ARRAY);
		m_VertexBuffer->bind();
		rapi->vertexPointer(renderer::DataType::FLOAT,3,0,m_VertexBuffer);
		m_VertexBuffer->unbind();
		m_IndexBuffer->bind();
		rapi->pushMatrix();
		rapi->translate(Origin);
		rapi->multMatrix(m_RotMtx);
		rapi->drawIndexedPrimitive(renderer::Primitive::TRIANGLE_STRIP,22,renderer::DataType::UNSIGNED_SHORT,m_IndexBuffer);
		rapi->popMatrix();
		m_IndexBuffer->unbind();
		rapi->disableClientState(renderer::ClientState::VERTEX_ARRAY);*/
	}
	//As in camera, everything is public,as speed is in favour
	math::vector3d  	Origin;
	//Set at the begining
	math::plane	   			NearPlane;
	math::plane     			FarPlane;
protected:
	renderer::RenderingAPIDriver* rapi;
	math::quaternion 			m_Rotation;
	math::matrix4x4			m_RotMtx;
	//Can be added by the way
	math::vector3d 		m_Verticies[4];
	math::plane			m_Planes[4];

	math::vector3d 		m_Verts[8];
	unsigned short int 	m_Indicies[22];
	renderer::VertexBufferObject*		m_VertexBuffer;
	renderer::VertexBufferObject*  	m_IndexBuffer;
};
}
#endif /*CFRUSTRUM_H_*/

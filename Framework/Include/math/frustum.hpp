#ifndef CFRUSTRUM_H_
#define CFRUSTRUM_H_

#include "math/vector3d.hpp"
#include "math/quaternion.hpp"
#include "math/plane.hpp"
#include "renderer/DriverSubsystems/VertexBufferObject.h"

#include "core/PluginCore.h"
#include "renderer/RenderingAPIDriver.h"
#define IN_FRUSTUM	1
#define OUTSIDE_FRUSTUM 0

#include "math_internal.h"

namespace core
{
extern core::PluginCore*	CoreInstance;
}
namespace math
{
inline bool AreCollinear(const math::vector3d& a,const math::vector3d& b,const math::vector3d& c)
{
	return abs_sq((b - a) * (c - a)) < math::eps * math::eps;
}


class frustum
{
public:
	MATH_MEMORY_FUNCTIONS
	frustum();
	frustum(const math::vector3d& orig, const math::plane& near,const math::plane& far)
	: Origin(orig), NearPlane(near),FarPlane(far)
	  {
	  }
	frustum(const frustum& fr)
	: Origin(fr.Origin), NearPlane(fr.NearPlane),FarPlane(fr.FarPlane)
	  {
	  }
	~frustum()
	{
	}

	void 	setVertex(const math::vector3d& vert,unsigned pos)
	{
		m_Verticies[pos] = vert;
	}

	void    setVerticies(const math::vector3d vert[4])
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

	int
	operator ()(const math::vector3d& point) const
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
	//As in camera, everything is public,as speed is in favour
	math::vector3d  	Origin;
	//Set at the begining
	math::plane	   			NearPlane;
	math::plane     			FarPlane;
protected:
	math::quaternion 			m_Rotation;
	math::matrix4x4			m_RotMtx;
	//Can be added by the way
	math::vector3d 		m_Verticies[4];
	math::plane			m_Planes[4];

};

//====================Implementation====================================================================

inline
frustum::frustum()
{
}

}
#endif /*CFRUSTRUM_H_*/

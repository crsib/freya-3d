#ifndef CPLANE_H_
#define CPLANE_H_

#include "math/vector3d.hpp"
#include "math/quaternion.hpp"

namespace math
{
class plane : public MathSubsystem
{
public:
	enum
	{
		IN_FRONT =  1,
		IN_BACK =  2,
		IN_PLANE = 0
	};
	plane()
	{

	}
	plane(const vector3d& normal,float dist)
	{
		m_Normal = normal;
		m_Normal.normalize();
		m_Distance = dist;
	}
	plane(const vector3d& normal,const vector3d& p)
	{
		m_Normal = normal;
		m_Normal.normalize();
		m_Distance =  (p , m_Normal);
	}
	plane(float nx,float ny,float nz,float dist)
	{
		m_Normal = vector3d(nx,ny,nz);
		m_Normal.normalize();
		m_Distance = dist;
	}
	plane(const vector3d& p1,const vector3d& p2, const vector3d& p3)
	{
		m_Normal = (p2-p1)*(p3-p1);
		m_Normal.normalize();
		m_Distance = - (p1 , m_Normal);
	}

	plane(const plane& p)
	{
		m_Normal 	= p.m_Normal;
		m_Distance 	= p.m_Distance;
	}

	plane& operator= (const plane& p)
	{
		m_Normal 	= p.m_Normal;
		m_Distance 	= p.m_Distance;
		return *this;
	}
	~plane(){}

	int   classify(const vector3d& point)
	{
		float   v = signedDistance (point);
		if (v > math::eps)
			return IN_FRONT;
		else
			if (v < -math::eps)
				return IN_BACK;
		return IN_PLANE;
	}

	float signedDistance(const vector3d& point)
	{
		return (m_Normal , point) + m_Distance;
	}
	float distance(vector3d& point)
	{
		return (float)((fabs((m_Normal, point) + m_Distance)));
	}

	void rotate(const vector3d & Dir, float angle)
	{
		vector3d p(-m_Distance * m_Normal);
		quaternion quat(Dir, angle);
		m_Normal = quat.rotate(m_Normal);
		m_Distance = -(p, m_Normal);
	}

	void rotate(quaternion & q)
	{
		vector3d p(-m_Distance * m_Normal);
		m_Normal = (vector3d)((q.rotate(m_Normal)));
		m_Distance = -(p, m_Normal);
	}

	void move(const vector3d & mv)
	{
		m_Normal += mv;
	}

	void flip()
	{
		m_Normal = -m_Normal;
		m_Distance = -m_Distance;
	}

	math::vector3d getNormal() const
	{
		return m_Normal;
	}

	void setNormal(math::vector3d& Normal)
	{
		this->m_Normal = Normal;
	}

	float getDistance() const
	{
		return m_Distance;
	}

	void setDistance(float Distance)
	{
		this->m_Distance = Distance;
	}
private:
	math::vector3d m_Normal;
	float m_Distance;

};
}

#endif /*CPLANE_H_*/

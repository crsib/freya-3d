#ifndef CBASICCAMERA_H_
#define CBASICCAMERA_H_


#include "math/vector3d.hpp"
#include "math/quaternion.hpp"
#include "math/frustum.hpp"
#include "math/plane.hpp"
#include "renderer/RenderingAPIDriver.h"
#include "core/EngineCore.h"
#include "core/EngineSubsystem.h"

#include "internal.h"

#include <iostream>

#ifdef _WIN32
#undef near
#undef far
#endif

namespace camera
{
inline  void qcheck(math::vector3d& v)
{
	if(math::abs(abs_sq(v) - 1) > math::eps) v.normalize();
}

class EXPORT BasicCamera : virtual public ::EngineSubsystem
{
public:
	BasicCamera(const math::vector3d& pos,const math::vector3d& dir,const math::vector3d& up) :  m_Position(pos),m_Direction(dir),m_Up(up),m_Frustum (NULL)
	{
		rapi = core::EngineCore::getRenderingDriver();
		m_Right = m_Up*m_Direction;
		m_Right.normalize();
	}
	BasicCamera(const math::vector3d& pos,const math::vector3d& dir,const math::vector3d& up,float FOW,float Aspect,float zNear,float zFar) :m_Frustum (NULL)
			{
		rapi = core::EngineCore::getRenderingDriver();
		m_Position = pos;
		m_Direction = dir;
		m_Up  = up;
		m_FieldOfView = FOW;
		m_Aspect = Aspect;
		m_Near = zNear;
		m_Far  = zFar;
		m_Right = (m_Up*m_Direction);
		m_Right.normalize();

		generateFrustum();
			}
	~BasicCamera()
	{
		delete m_Frustum;
	}

	void applyRenderingSettings()
	{
		rapi->setMatrixMode(renderer::MatrixMode::PROJECTION);
		rapi->loadIdentityMatrix();
		rapi->setPerspective(m_FieldOfView,m_Aspect,m_Near,m_Far);
		rapi->setMatrixMode(renderer::MatrixMode::WORLD);
		rapi->loadIdentityMatrix();
	}
	void applyRenderingSettings(float FOW,float Aspect,float Near,float Far)
	{
		m_Near = Near;
		m_Far  = Far;
		m_FieldOfView = FOW;
		m_Aspect = Aspect;

		rapi->setMatrixMode(renderer::MatrixMode::PROJECTION);
		rapi->loadIdentityMatrix();
		rapi->setPerspective(m_FieldOfView,m_Aspect,m_Near,m_Far);
		rapi->setMatrixMode(renderer::MatrixMode::WORLD);
		rapi->loadIdentityMatrix();
	}

	virtual void apply()
	{
		//Please, do it in a more optimal way. And actually, there is some mis understand of ModelView matrix here
		//We multiply our matrix with a projection (for OpenGL compatibility with only matrices for general transformation)
		//Actually, the following happens P*Cam*Modelview*Vertex
		//This greatly helps in developement
		rapi->setMatrixMode(renderer::MatrixMode::PROJECTION);
		//rapi->loadIdentityMatrix();
		//rapi->setPerspective(m_FieldOfView,m_Aspect,m_Near,m_Far);

		rapi->loadMatrix(math::matrix4x4::perspectiveProjection(m_FieldOfView,m_Aspect,m_Near, m_Far)*math::matrix4x4::lookat(m_Position,m_Position+m_Direction,m_Up));
		rapi->setMatrixMode(renderer::MatrixMode::WORLD);
		rapi->loadIdentityMatrix();
		//rapi->multMatrix(math::matrix4x4(m));
	}

	float *getModelViewInverse()
	{
		float *m = m_ViewInverse;
		m[0] = m_Right.x;
		m[4] = m_Right.y;
		m[8] = m_Right.z;
		m[12] = 0.0;
		m[1] = m_Up.x;
		m[5] = m_Up.y;
		m[9] = m_Up.z;
		m[13] = 0.0;
		m[2] = -m_Direction.x;
		m[6] = -m_Direction.y;
		m[10] = -m_Direction.z;
		m[14] = 0.0;
		float vx = (m_Right, m_Position);
		float vy = (m_Up, m_Position);
		float vz = (-m_Direction, m_Position);
		m[3] = vx * m[0] + vy * m[1] + vz * m[2];
		m[7] = vx * m[4] + vy * m[5] + vz * m[6];
		m[11] = vx * m[8] + vy * m[9] + vz * m[10];
		m[15] = 1.0f;
		return m;
	}

	void enter2D(int width, int height)
	{
		rapi->setMatrixMode(renderer::MatrixMode::PROJECTION);
		rapi->loadIdentityMatrix();
		rapi->setOrtho(width, height);
		rapi->setMatrixMode(renderer::MatrixMode::MODELVIEW);
		rapi->loadIdentityMatrix();
		rapi->disableDepthTest();
	}

	void leave2D()
	{
		rapi->setMatrixMode(renderer::MatrixMode::PROJECTION);
		rapi->loadIdentityMatrix();
		rapi->setPerspective(m_FieldOfView, m_Aspect, m_Near, m_Far);
		rapi->setMatrixMode(renderer::MatrixMode::MODELVIEW);
		rapi->loadIdentityMatrix();
		rapi->enableDepthTest();
	}

	void generateFrustum()
	{
		qcheck(m_Direction);
		float halfAngle = 0.5f * m_FieldOfView * math::pi / 180.0;
		float fovValueY = 1 / (float)(tan(halfAngle));
		float fovValueX = fovValueY / m_Aspect;
		math::vector3d v(m_Direction * m_Far);
		math::vector3d hr(m_Right * (m_Far / fovValueX));
		math::vector3d hu(m_Up * (m_Far / fovValueY));
		math::vector3d vv[4];
		vv[0] = v + hr + hu;
		vv[1] = v - hr + hu;
		vv[2] = v - hr - hu;
		vv[3] = v + hr - hu;
		math::plane near(m_Direction, m_Near * m_Direction);
		math::plane far(m_Direction, m_Far * m_Direction);
		delete m_Frustum;

		m_Frustum = new math::frustum(m_Position, near, far);
		m_Frustum->setVerticies(&vv[0]);
		m_Frustum->reset();
		//m_Frustum->updateIndexBuffer();
		//m_Frustum->updateVertexBuffer();
	}

	math::frustum & getFrustum()
	{
		return *m_Frustum;
	}

	float *getModelviewMatrix()
	{
		//glGetFloatv(GL_MODELVIEW_MATRIX,mMVMat);
		return mMVMat;
	}

	float *getProjectionMatrix()
	{
		//glGetFloatv(GL_PROJECTION_MATRIX,mPrMat);
		return mPrMat;
	}

	float *getMatrAddress()
	{
		return m_Address;
	}

	virtual void moveForward(float Step) =0;
	virtual void moveBackward(float Step) =0;
	virtual void moveLeft(float Step) =0;
	virtual void moveRight(float St45ep) =0;
	virtual void moveUp(float Step) =0;
	virtual void moveDown(float Step) =0;
	virtual void changePitch(float AngleStep) =0;
	virtual void changeYaw(float AngleStep) =0;
	virtual void changeRoll(float AngleStep) =0;
	math::vector3d getPos() const
			{
		return m_Position;
			}

	void setPos(math::vector3d mPos)
	{
		this->m_Position = mPos;
	}

	math::vector3d getDir() const
			{
		return m_Direction;
			}

	void setDir(math::vector3d mDir)
	{
		this->m_Direction = mDir;
	}

	math::vector3d getUp() const
			{
		return m_Up;
			}

	void setUp(math::vector3d mUp)
	{
		this->m_Up = mUp;
	}

	math::vector3d getRight() const
			{
		return m_Right;
			}

	void setRight(math::vector3d mRight)
	{
		this->m_Right = mRight;
	}

protected:
	math::vector3d m_Position;
	math::vector3d m_Direction;
	math::vector3d m_Up;
	math::vector3d m_Right;
	math::frustum  *m_Frustum;
	float m_Near;
	float m_Far;
	float m_FieldOfView;
	float m_Aspect;
	float					m_ViewInverse[16];
	union
	{
		float*			m_Address;
		struct
		{
			float			mMVMat[16];
			float			mPrMat[16];
		};
	};
	renderer::RenderingAPIDriver* rapi;
};
}
#endif /*CBASICCAMERA_H_*/

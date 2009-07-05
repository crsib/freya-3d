#ifndef CBASICCAMERA_H_
#define CBASICCAMERA_H_


#include "math/vector3d.hpp"
#include "math/quaternion.hpp"
#include "camera/Frustum.h"
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
	BasicCamera(const math::vector3d& pos,const math::vector3d& dir,const math::vector3d& up) :  mPos(pos),mDir(dir),mUp(up),mFrust (NULL)
	{
		rapi = core::EngineCore::getRenderingDriver();
		mRight = mUp*mDir;
		mRight.normalize();
	}
	BasicCamera(const math::vector3d& pos,const math::vector3d& dir,const math::vector3d& up,float FOW,float Aspect,float zNear,float zFar) :mFrust (NULL)
	{
		rapi = core::EngineCore::getRenderingDriver();
		mPos = pos;
		mDir = dir;
		mUp  = up;
		mFOW = FOW;
		mAspect = Aspect;
		mNear = zNear;
		mFar  = zFar;
		mRight = (mUp*mDir);
		mRight.normalize();

		generateFrustum();
	}
	~BasicCamera()
	{
		delete mFrust;
	}

	void applyRenderingSettings()
	{
		rapi->setMatrixMode(renderer::MatrixMode::PROJECTION);
		rapi->loadIdentityMatrix();
		rapi->setPerspective(mFOW,mAspect,mNear,mFar);
		rapi->setMatrixMode(renderer::MatrixMode::MODELVIEW);
		rapi->loadIdentityMatrix();
	}
	void applyRenderingSettings(float FOW,float Aspect,float Near,float Far)
	{
		mNear = Near;
		mFar  = Far;
		mFOW = FOW;
		mAspect = Aspect;

		rapi->setMatrixMode(renderer::MatrixMode::PROJECTION);
		rapi->loadIdentityMatrix();
		rapi->setPerspective(mFOW,mAspect,mNear,mFar);
		rapi->setMatrixMode(renderer::MatrixMode::MODELVIEW);
		rapi->loadIdentityMatrix();
	}

	virtual void apply()
	{
		float m[16];
		qcheck(mRight);
		qcheck(mDir);
		qcheck(mUp);
		m[0] = mRight.x;
		m[1] = mRight.y;
		m[2] = mRight.z;
		m[4] = mUp.x;
		m[5] = mUp.y;
		m[6] = mUp.z;
		m[8] = -mDir.x;
		m[9] = -mDir.y;
		m[10] = -mDir.z;
		m[3] = (-mRight, mPos);
		m[7] = (-mUp, mPos);
		m[11] = (mDir, mPos);
		m[12] = 0.0f;
		m[13] = 0.0f;
		m[14] = 0.0f;
		m[15] = 1.0f;

		//Please, do it in a more optimal way. And actually, there is some mis understand of ModelView matrix here
		//We multiply our matrix with a projection (for OpenGL compatibility with only matrices for general transformation)
		//Actually, the following happens P*Cam*Modelview*Vertex
		//This greatly helps in developement
		rapi->setMatrixMode(renderer::MatrixMode::PROJECTION);
		rapi->loadIdentityMatrix();
		rapi->setPerspective(mFOW,mAspect,mNear,mFar);

		rapi->multMatrix(math::matrix4x4(m));
		rapi->setMatrixMode(renderer::MatrixMode::MODELVIEW);
		rapi->loadIdentityMatrix();
		//rapi->multMatrix(math::matrix4x4(m));
	}

	float *getModelViewInverse()
	{
		float *m = mModelviewInverse;
		m[0] = mRight.x;
		m[4] = mRight.y;
		m[8] = mRight.z;
		m[12] = 0.0;
		m[1] = mUp.x;
		m[5] = mUp.y;
		m[9] = mUp.z;
		m[13] = 0.0;
		m[2] = -mDir.x;
		m[6] = -mDir.y;
		m[10] = -mDir.z;
		m[14] = 0.0;
		float vx = (mRight, mPos);
		float vy = (mUp, mPos);
		float vz = (-mDir, mPos);
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
		rapi->setPerspective(mFOW, mAspect, mNear, mFar);
		rapi->setMatrixMode(renderer::MatrixMode::MODELVIEW);
		rapi->loadIdentityMatrix();
		rapi->enableDepthTest();
	}

	void generateFrustum()
	{
		qcheck(mDir);
		float halfAngle = 0.5f * mFOW * math::pi / 180.0;
		float fovValueY = 1 / (float)(tan(halfAngle));
		float fovValueX = fovValueY / mAspect;
		math::vector3d v(mDir * mFar);
		math::vector3d hr(mRight * (mFar / fovValueX));
		math::vector3d hu(mUp * (mFar / fovValueY));
		math::vector3d vv[4];
		vv[0] = v + hr + hu;
		vv[1] = v - hr + hu;
		vv[2] = v - hr - hu;
		vv[3] = v + hr - hu;
		math::plane near(mDir, mNear * mDir);
		math::plane far(mDir, mFar * mDir);
		delete mFrust;

		mFrust = new camera::Frustum(mPos, near, far);
		mFrust->setVerticies(&vv[0]);
		mFrust->reset();
		mFrust->updateIndexBuffer();
		mFrust->updateVertexBuffer();
	}

	camera::Frustum & getFrustum()
	{
		return *mFrust;
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
		return mAddress;
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
		return mPos;
	}

	void setPos(math::vector3d mPos)
	{
		this->mPos = mPos;
	}

	math::vector3d getDir() const
	{
		return mDir;
	}

	void setDir(math::vector3d mDir)
	{
		this->mDir = mDir;
	}

	math::vector3d getUp() const
	{
		return mUp;
	}

	void setUp(math::vector3d mUp)
	{
		this->mUp = mUp;
	}

	math::vector3d getRight() const
	{
		return mRight;
	}

	void setRight(math::vector3d mRight)
	{
		this->mRight = mRight;
	}

protected:
	math::vector3d mPos;
	math::vector3d mDir;
	math::vector3d mUp;
	math::vector3d mRight;
	camera::Frustum *mFrust;
	float mNear;
	float mFar;
	float mFOW;
	float mAspect;
	float					mModelviewInverse[16];
	union
	{
		float*			mAddress;
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

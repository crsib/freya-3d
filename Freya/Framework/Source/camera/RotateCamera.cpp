#include "camera/RotateCamera.h"

namespace camera
{
void RotateCamera::moveForward(float Step)
{

}
void RotateCamera::moveBackward(float Step)
{

}

void RotateCamera::moveLeft(float Step)
{

}
void RotateCamera::moveRight(float Step)
{

}

void RotateCamera::moveUp(float Step)
{

}
void RotateCamera::moveDown(float Step)
{

}

void RotateCamera::changePitch(float AngleStep)
{
	math::quaternion Pitch(math::vector3d(1.0f,0.0f,0.0f),AngleStep);
	mUp = Pitch(mUp);
	mRight = Pitch(mRight);
	mDir = Pitch(mDir);
	mPos = Pitch(mPos-LP)+LP;
	qcheck(mUp);qcheck(mDir);qcheck(mRight);
	Pitch.w = -Pitch.w;
	mFrust->rotate(Pitch);
	mFrust->setPosition(mPos);
}
void RotateCamera::changeYaw(float AngleStep)
{
	math::quaternion Yaw(math::vector3d(0.0f,1.0f,0.0f),AngleStep);
	mUp = Yaw(mUp);
	mRight = Yaw(mRight);
	mDir = Yaw(mDir);
	mPos = Yaw(mPos-LP)+LP;
	qcheck(mRight);qcheck(mDir);qcheck(mUp);
	Yaw.w = -Yaw.w;
	mFrust->rotate(Yaw);
	mFrust->setPosition(mPos);
}
void RotateCamera::changeRoll(float AngleStep)
{

}
}


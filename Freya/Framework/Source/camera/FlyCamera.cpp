#include "camera/FlyCamera.h"
#include <iostream>
namespace camera
{
void FlyCamera::moveForward(float Step)
{
	mPos += Step*mDir;
	mFrust->setPosition(mPos);
}
void FlyCamera::moveBackward(float Step)
{
	mPos -= Step*mDir;
	mFrust->setPosition(mPos);
}

void FlyCamera::moveLeft(float Step)
{
	mPos -= Step*mRight;
	mFrust->setPosition(mPos);
}
void FlyCamera::moveRight(float Step)
{
	mPos   += Step*mRight;
	mFrust->setPosition(mPos);
}

void FlyCamera::moveUp(float Step)
{
	mPos += Step*mUp;
	mFrust->setPosition(mPos);
}
void FlyCamera::moveDown(float Step)
{
	mPos -= Step*mUp;
	mFrust->setPosition(mPos);
}

void FlyCamera::changePitch(float AngleStep)
{
	math::quaternion Pitch(mRight,AngleStep);
	mUp = Pitch.rotate(mUp);
	//mRight = Pitch.rotate(mRight);
	mDir = Pitch.rotate(mDir);
	Pitch.w = -Pitch.w;
	mFrust->rotate(Pitch);
	qcheck(mUp);qcheck(mDir);
}
void FlyCamera::changeYaw(float AngleStep)
{
	math::quaternion Yaw(mUp,AngleStep);
	//mUp = Yaw.rotate(mUp);
	mRight = Yaw.rotate(mRight);
	mDir = Yaw.rotate(mDir);
	Yaw.w = -Yaw.w;
	mFrust->rotate(Yaw);
	qcheck(mRight);qcheck(mDir);
}
void FlyCamera::changeRoll(float AngleStep)
{
	math::quaternion Roll(mDir,AngleStep);
	mUp = Roll.rotate(mUp);
	mRight = Roll.rotate(mRight);
	qcheck(mUp);qcheck(mRight);
	Roll.w = -Roll.w;
	mFrust->rotate(Roll);
	//mDir = Roll.rotate(mDir);
}
}

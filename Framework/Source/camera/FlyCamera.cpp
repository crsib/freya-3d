#include "camera/FlyCamera.h"
#include <iostream>
namespace camera
{
void FlyCamera::moveForward(float Step)
{
	m_Position += Step*m_Direction;
	m_Frustum->setPosition(m_Position);
}
void FlyCamera::moveBackward(float Step)
{
	m_Position -= Step*m_Direction;
	m_Frustum->setPosition(m_Position);
}

void FlyCamera::moveLeft(float Step)
{
	m_Position -= Step*m_Right;
	m_Frustum->setPosition(m_Position);
}
void FlyCamera::moveRight(float Step)
{
	m_Position   += Step*m_Right;
	m_Frustum->setPosition(m_Position);
}

void FlyCamera::moveUp(float Step)
{
	m_Position += Step*m_Up;
	m_Frustum->setPosition(m_Position);
}
void FlyCamera::moveDown(float Step)
{
	m_Position -= Step*m_Up;
	m_Frustum->setPosition(m_Position);
}

void FlyCamera::changePitch(float AngleStep)
{
	math::quaternion Pitch(m_Right,AngleStep);
	m_Up = Pitch.rotate(m_Up);
	//mRight = Pitch.rotate(mRight);
	m_Direction = Pitch.rotate(m_Direction);
	Pitch.w = -Pitch.w;
	m_Frustum->rotate(Pitch);
	qcheck(m_Up);qcheck(m_Direction);
}
void FlyCamera::changeYaw(float AngleStep)
{
	math::quaternion Yaw(m_Up,AngleStep);
	//mUp = Yaw.rotate(mUp);
	m_Right = Yaw.rotate(m_Right);
	m_Direction = Yaw.rotate(m_Direction);
	Yaw.w = -Yaw.w;
	m_Frustum->rotate(Yaw);
	qcheck(m_Right);qcheck(m_Direction);
}
void FlyCamera::changeRoll(float AngleStep)
{
	math::quaternion Roll(m_Direction,AngleStep);
	m_Up = Roll.rotate(m_Up);
	m_Right = Roll.rotate(m_Right);
	qcheck(m_Up);qcheck(m_Right);
	Roll.w = -Roll.w;
	m_Frustum->rotate(Roll);
	//mDir = Roll.rotate(mDir);
}
}

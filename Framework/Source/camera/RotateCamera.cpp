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
	m_Up = Pitch(m_Up);
	m_Right = Pitch(m_Right);
	m_Direction = Pitch(m_Direction);
	m_Position = Pitch(m_Position-LP)+LP;
	qcheck(m_Up);qcheck(m_Direction);qcheck(m_Right);
	Pitch.w = -Pitch.w;
	m_Frustum->rotate(Pitch);
	m_Frustum->setPosition(m_Position);
}
void RotateCamera::changeYaw(float AngleStep)
{
	math::quaternion Yaw(math::vector3d(0.0f,1.0f,0.0f),AngleStep);
	m_Up = Yaw(m_Up);
	m_Right = Yaw(m_Right);
	m_Direction = Yaw(m_Direction);
	m_Position = Yaw(m_Position-LP)+LP;
	qcheck(m_Right);qcheck(m_Direction);qcheck(m_Up);
	Yaw.w = -Yaw.w;
	m_Frustum->rotate(Yaw);
	m_Frustum->setPosition(m_Position);
}
void RotateCamera::changeRoll(float AngleStep)
{

}
}


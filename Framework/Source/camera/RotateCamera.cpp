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
	math::quaternion Pitch = math::quaternion::rotationQuat(AngleStep,math::vector3d(1.0f,0.0f,0.0f));
	m_Up = Pitch.rotate(m_Up);
	m_Right = Pitch.rotate(m_Right);
	m_Direction = Pitch.rotate(m_Direction);
	m_Position = Pitch.rotate(m_Position-LP)+LP;
	qcheck(m_Up);qcheck(m_Direction);qcheck(m_Right);
	Pitch.w = -Pitch.w;
	m_Frustum->rotate(Pitch);
	m_Frustum->setPosition(m_Position);
}
void RotateCamera::changeYaw(float AngleStep)
{
	math::quaternion Yaw = math::quaternion::rotationQuat(AngleStep,math::vector3d(0.0f,1.0f,0.0f));
	m_Up = Yaw.rotate(m_Up);
	m_Right = Yaw.rotate(m_Right);
	m_Direction = Yaw.rotate(m_Direction);
	m_Position = Yaw.rotate(m_Position-LP)+LP;
	qcheck(m_Right);qcheck(m_Direction);qcheck(m_Up);
	Yaw.w = -Yaw.w;
	m_Frustum->rotate(Yaw);
	m_Frustum->setPosition(m_Position);
}
void RotateCamera::changeRoll(float AngleStep)
{

}
}


/*
 * wrap_math.cpp
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#include "core/lua/lua_libraries/wrap_math.h"
#include <iostream>
namespace math
{
float dot(const vector3d& _1,const vector3d& _2)
{
	return (_1,_2);
}

matrix3x3 createYRotationMatrix3x3(const float angle)
{
	return math::matrix3x3::yRotationMatrix(angle);
}



matrix4x4 createLookatMatrix4x4(const vector3d & from, const vector3d & to, const vector3d & up)
{
//	std::cout << from << " " << to << " " << " " << up << std::endl;
	return matrix4x4::lookat(from,to,up);
}



matrix4x4 createYRotationMatrix4x4(const float angle)
{
	return matrix4x4::yRotationMatrix(angle);
}



quaternion quaternionFromMatrix4x4(const matrix4x4 & mtx)
{
	return static_cast<quaternion>(mtx);
}



matrix3x3 createRotationMatrix3x3(const float angle, const vector3d & v3d)
{
	return matrix3x3::rotationMatrix(angle,v3d);
}



matrix3x3 createScaleMatrix3x3(const float sx, const float sy, const float sz)
{
	return matrix3x3::scaleMatrix(sx,sy,sz);
}



matrix4x4 createPerspectiveProjectionMatrix4x4(float fovy, float aspect, float nearPlane, float farPlane)
{
	return matrix4x4::perspectiveProjection(fovy,aspect,nearPlane,farPlane);
}



matrix4x4 createZRotationMatrix4x4(const float angle)
{
	return matrix4x4::zRotationMatrix(angle);
}



matrix4x4 createTranslationMatrix4x4(const vector3d & v3d)
{
	return matrix4x4::translationMatrix(v3d);
}



matrix4x4 createFrustumMatrix4x4(float top, float left, float bottom, float right, float nearPlane, float farPlane)
{
	return matrix4x4::frustumMatrix(top,left,bottom,right,nearPlane,farPlane);
}



matrix4x4 createBillboardMatrix4x4(const vector3d & from, const vector3d & to, const vector3d & up)
{
	return matrix4x4::billboard(from,to,up);
}



matrix3x3 createZRotationMatrix3x3(const float angle)
{
	return matrix3x3::zRotationMatrix(angle);
}



matrix3x3 matrix3x3FromQuaternion(const quaternion & q)
{
	return matrix3x3(q);
}



matrix4x4 createOrthoProjectionMatrix4x4(float left,float top,float right,float bottom, float nearPlane, float farPlane)
{
	return matrix4x4::orthoProjection(left,top,right,bottom,nearPlane,farPlane);
}



quaternion quaternionFromMatrix3x3(const matrix3x3 & mtx)
{
	return static_cast<quaternion>(mtx);
}



matrix4x4 createScaleMatrix4x4(const float sx, const float sy, const float sz)
{
	return matrix4x4::scaleMatrix(sx,sy,sz);
}



matrix4x4 createXRotationMatrix4x4(const float angle)
{
	return matrix4x4::xRotationMatrix(angle);
}



matrix4x4 createRotationMatrix4x4(const float angle, const vector3d & v3d)
{
	return matrix4x4::rotationMatrix(angle,v3d);
}



quaternion createRotationQuat(const float angle, const vector3d & axis)
{
	return quaternion::rotationQuat(angle,axis);
}



matrix3x3 createXRotationMatrix3x3(const float angle)
{
	return matrix3x3::xRotationMatrix(angle);
}

matrix4x4 matrix4x4FromQuaternion(const quaternion & q)
{
	return matrix4x4(q);
}

bool				pointInFrustum(const frustum& f, const vector3d& p)
{
	return f(p);
}
}



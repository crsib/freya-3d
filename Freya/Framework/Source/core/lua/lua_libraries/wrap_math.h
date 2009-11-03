/*
 * wrap_math.h
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#ifndef WRAP_MATH_H_
#define WRAP_MATH_H_
#include "math/vector3d.hpp"
#include "math/quaternion.hpp"
#include "math/matrix3x3.hpp"
#include "math/matrix4x4.hpp"
#include "math/frustum.hpp"
namespace math
{
//Vector 3d
float dot(const vector3d& _1,const vector3d& _2);
//Quaternion
quaternion	createRotationQuat(const float angle, const vector3d& axis);
quaternion	quaternionFromMatrix3x3(const matrix3x3& mtx);
quaternion	quaternionFromMatrix4x4(const matrix4x4& mtx);
//Matrix 3x3
matrix3x3			matrix3x3FromQuaternion(const quaternion& q);
matrix3x3  			createXRotationMatrix3x3(const float angle);
matrix3x3  			createYRotationMatrix3x3(const float angle);
matrix3x3  			createZRotationMatrix3x3(const float angle);
matrix3x3			createRotationMatrix3x3(const float  angle,const vector3d& v3d);
matrix3x3			createScaleMatrix3x3(const float sx,const float sy, const float sz);
//Matrix 4x4
matrix4x4			matrix4x4FromQuaternion(const quaternion& q);
matrix4x4  			createXRotationMatrix4x4(const float angle);
matrix4x4  			createYRotationMatrix4x4(const float angle);
matrix4x4  			createZRotationMatrix4x4(const float angle);
matrix4x4			createRotationMatrix4x4(const float  angle,const vector3d& v3d);
matrix4x4			createScaleMatrix4x4(const float sx,const float sy, const float sz);
matrix4x4  			createTranslationMatrix4x4(const vector3d& v3d);
matrix4x4   		createOrthoProjectionMatrix4x4(float left,float top,float right,float bottom,float nearPlane,float farPlane);
matrix4x4			createPerspectiveProjectionMatrix4x4(float fovy,float aspect, float nearPlane, float farPlane);
matrix4x4			createFrustumMatrix4x4 (float top,float left,float bootom,float right,float nearPlane,float farPlane);
matrix4x4 			createLookatMatrix4x4(const vector3d& from, const vector3d& to, const vector3d& up);
matrix4x4 			createBillboardMatrix4x4(const vector3d& from, const vector3d& to, const vector3d& up);

bool				pointInFrustum(const frustum& f, const vector3d& p);

}

#endif /* WRAP_MATH_H_ */

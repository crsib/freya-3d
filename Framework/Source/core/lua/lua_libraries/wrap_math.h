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

namespace math
{
vector3d __vec3dADD(const vector3d& v1, const vector3d& v2);
vector3d __vec3dSUB(const vector3d& v1, const vector3d& v2);
vector3d __vec3dMUL(const vector3d& v1, const vector3d& v2);
vector3d __vec3dMUL(const vector3d& v, const float scalar);
vector3d __vec3dMUL(const float scalar,const vector3d& v);
vector3d __vec3dDIV(const vector3d& v, const float scalar);
float	 __innerProduct3(const vector3d& v, const vector3d& v2);

quaternion __quatADD(const quaternion& q1, const quaternion& q2);
quaternion __quatADD(const float q1, const quaternion& q2);
quaternion __quatADD(const quaternion& q1, const float q2);
quaternion __vec3dADD(const vector3d& q1, const quaternion& q2);
quaternion __quatADD(const quaternion& q1, const vector3d& q2);

quaternion __quatSUB(const quaternion& q1, const quaternion& q2);
quaternion __quatSUB(const quaternion& q1, const float q2);
quaternion __vec3dSUB(const vector3d& q1, const quaternion& q2);
quaternion __quatSUB(const quaternion& q1, const vector3d& q2);

quaternion __quatMUL(const quaternion& q1, const quaternion& q2);
quaternion __quatMUL(const float q1, const quaternion& q2);
quaternion __quatMUL(const quaternion& q1, const float q2);
quaternion __vec3dMUL(const vector3d& q1, const quaternion& q2);
quaternion __quatMUL(const quaternion& q1, const vector3d& q2);

float __innerProductQuat(const quaternion& q1, const quaternion& q2);
quaternion __quatDIV(const quaternion& q1, const float q2);
}

#endif /* WRAP_MATH_H_ */

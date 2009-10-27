/*
 * wrap_math.cpp
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#include "core/lua/lua_libraries/wrap_math.h"

namespace math
{

float __innerProduct3(const vector3d& v1, const vector3d& v2)
{
	return (v1,v2);
}
//Internals
vector3d __vec3dADD(const vector3d& v1, const vector3d& v2)
{
	return v1+v2;
}


vector3d __vec3dSUB(const vector3d& v1, const vector3d& v2)
{
	return v1-v2;
}


vector3d __vec3dMUL(const vector3d& v1, const vector3d& v2)
{
	return v1 * v2;
}


vector3d __vec3dMUL(const vector3d& v, const float scalar)
{
	return v*scalar;
}


vector3d __vec3dMUL(const float scalar,const vector3d& v)
{
	return scalar*v;
}


vector3d __vec3dDIV(const vector3d& v, const float scalar)
{
	return v/scalar;
}

//quats

quaternion __quatADD(const quaternion& q1, const quaternion& q2)
{
	return q1 + q2;
}


quaternion __vec3dADD(const vector3d& q1, const quaternion& q2)
{
	return q1 + q2;
}


quaternion __quatADD(const quaternion& q1, const vector3d& q2)
{
	return q1 + q2;
}


//sub


quaternion __quatSUB(const quaternion& q1, const quaternion& q2)
{
	return q1 - q2;
}


quaternion __vec3dSUB(const vector3d& q1, const quaternion& q2)
{
	return q1 - q2;
}


quaternion __quatSUB(const quaternion& q1, const vector3d& q2)
{
	return q1 - q2;
}

//mul


quaternion __quatMUL(const quaternion& q1, const quaternion& q2)
{
	return q1 * q2;
}


quaternion __quatMUL(const float q1, const quaternion& q2)
{
	return q1 * q2;
}


quaternion __quatMUL(const quaternion& q1, const float q2)
{
	return q1 * q2;
}


quaternion __vec3dMUL(const vector3d& q1, const quaternion& q2)
{
	return q1 * q2;
}


quaternion __quatMUL(const quaternion& q1, const vector3d& q2)
{
	return q1 * q2;
}


quaternion __quatDIV(const quaternion& q1, const float q2)
{
	return q1/q2;
}


//vec4d

}

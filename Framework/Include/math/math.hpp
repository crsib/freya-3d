#ifndef MATH_HPP_
#define MATH_HPP_

#include <cmath>
#include <iostream>
#include "math_internal.h"

//Vectors
#include "vector2d.hpp"
#include "vector3d.hpp"
#include "vector4d.hpp"

//Matricies
#include "matrix2x2.hpp"
#include "matrix3x3.hpp"
#include "matrix4x4.hpp"

//Quaternions
#include "quaternion.hpp"

//Misc
#include "plane.hpp"

#include "frustum.hpp"


#define MATH_DEBUG

#ifdef _MSC_VER
#	pragma warning(disable:4805)
#	pragma warning(disable:4244)
#endif

namespace math
{

float abs(const float scalar);

//SSE based functions


//============================ Output operator =======================================================================

inline std::ostream& operator << (std::ostream& s,const float4& _);
inline std::ostream& operator << (std::ostream& s,const int4& _);

float 		sqrt(float);
float4		sqrt(float4&);
float4		sqrt(float,float,float,float);

float 		floor(float);
float4		floor(float4&);
float4		floor(float,float,float,float);

float 		rcp(float);
float4		rcp(float4&);
float4		rcp(float,float,float,float);

float 		rcp_sqrt(float);
float4		rcp_sqrt(float4&);
float4		rcp_sqrt(float,float,float,float);

float4		rcp_mull(float4&,float4&);
float4		rcp_sqrt_mull(float4&,float4&);

float		sin	(float);
float		cos (float);
float		acos(float);
void		sincos(float,float* s,float* c);
float		tan (float);
float		cot (float);
float		atan(float);

float		log (float);
float		exp (float);
}//math


#endif /*MATH_HPP_*/

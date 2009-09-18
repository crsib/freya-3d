#ifndef MATH_HPP_
#define MATH_HPP_

#include <cmath>
#include "struct_def.hpp"
#include <iostream>
#include "internal.h"
#include "MathSubsystem.h"
#define MATH_DEBUG

namespace math
{
	
	class vector2d;
    class vector3d;
    class vector4d;
    class quaternion;
    class matrix3x3;
    class matrix4x4;

    class polar_vector;
    class spherical_vector;
    class cylindric_vector;
    class barycentric_vector;

    class line;
    class plane;

    class bezier;
    class bspline;
    class NURBS;

    const float unit 		= 1.0f;
    const float zero 		= 0.0f;
    const float pi   		= 3.1415926536f;
    const float e    		= 2.7182818285f;
    const float eps  	 	= 0.000001f;
    const float wu_coeff	= 0.34375;
    const float infinity	= 1e10;
    const float minfinity	= -1e10;


    inline
    float abs(const float scalar) {
    	return scalar > zero ? scalar : -scalar;
    }

    EXPORT float     abs   (const vector2d&);
    EXPORT float     abs   (const vector3d&);
    EXPORT float     abs_sq(const vector2d&);
    EXPORT float     abs_sq(const vector3d&);

    EXPORT float     distance   (const vector2d&, const vector2d&);
    EXPORT float     distance   (const vector3d&, const vector3d&);
    EXPORT float     distance_sq(const vector2d&, const vector2d&);
    EXPORT float     distance_sq(const vector3d&, const vector3d&);

    //float     sqrt(const float);
    //float     sqr (const float);
    EXPORT float     wu_hypotenuse(const float, const float);

    EXPORT float     max(float,     float);
    EXPORT vector2d& max(vector2d&, vector2d&);
    EXPORT vector3d& max(vector3d&, vector3d&);

    EXPORT float     min(float,     float);
    EXPORT vector2d& min(vector2d&, vector2d&);
    EXPORT vector3d& min(vector3d&, vector3d&);

    EXPORT vector2d  normalized(const vector2d&);
    EXPORT vector3d  normalized(const vector3d&);


    EXPORT float     det(const matrix3x3&);
    EXPORT float     det(const matrix4x4&);

    EXPORT matrix3x3 transposed(const matrix3x3&);
    EXPORT matrix4x4 transposed(const matrix4x4&);

    EXPORT float     dot(const matrix3x3&, const matrix3x3&);
    EXPORT float     dot(const matrix4x4&, const matrix4x4&);

    EXPORT float 	   norm		 (const quaternion&);
    EXPORT bool	   isNormed	 (const quaternion&);
    EXPORT float	   abs		 (const quaternion&);
    EXPORT quaternion conjugated(const quaternion&);
    EXPORT quaternion inversed  (const quaternion&);
    EXPORT quaternion normalized(const quaternion&);

    EXPORT matrix4x4  QuaternionToMatrix4x4(const quaternion& q);
    EXPORT quaternion Matrix4x4ToQuaternion(const matrix4x4& m);
    //void matrix3x3ToQuaternion(const matrix3x3&, const quaternion&);

    //r means radian, d means degree
    /*float     sin_r(const float);
    float     sin_d(const float);
    float     cos_r(const float);
    float     cos_d(const float);
    float     tg_r (const float);
    float     tg_d (const float);
    float     ctg_r(const float);
    float     ctg_d(const float);

    float     arcsin_r(const float);
    float     arcsin_d(const float);
    float     arccos_r(const float);
    float     arccos_d(const float);
    float     arctg_r (const float);
    float     arctg_d (const float);
    float     arcctg_r(const float);
    float     arcctg_d(const float);*/

    //dont use directly
    //const int max_buffer_size = 3;
}//math

#endif /*MATH_HPP_*/

/*
 * matrix4x4.hpp
 *	This file is part of Freya 3D engine. For licensing information
 *  from LICENCE file 
 *  Created on: Oct 22, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef MATRIX4X4_HPP_
#define MATRIX4X4_HPP_

#include "math_internal.h"
#include "matrix3x3.hpp"
#include "vector4d.hpp"
#include "vector3d.hpp"
#include "quaternion.hpp"

namespace math
{
namespace __internal
{
static const float4  mtx4d_first_row 	= {{1,0,0,0}};
static const float4  mtx4d_second_row 	= {{0,1,0,0}};
static const float4  mtx4d_third_row 	= {{0,0,1,0}};
static const float4  mtx4d_fourth_row 	= {{0,0,0,1}};
}

MATH_OBJECT_DECL class matrix4x4
{
public:
	__forceinline matrix4x4(const __m128& _1,const __m128& _2,const __m128& _3,const __m128& _4)
	{
		row[0] = _1;
		row[1] = _2;
		row[2] = _3;
		row[3] = _4;
	}
public:
	static const matrix4x4 identity;

	MATH_MEMORY_FUNCTIONS

	union
	{
		__m128	row [4];
		float	elem[4][4];
		struct
		{
			float _11,_12,_13,_14;
			float _21,_22,_23,_24;
			float _31,_32,_33,_34;
			float _41,_42,_43,_44;
		};
	};

	matrix4x4();

	matrix4x4(
			const float _11,const float _12,const float _13, const float _14,
			const float _21,const float _22,const float _23, const float _24,
			const float _31,const float _32,const float _33, const float _34,
			const float _41,const float _42,const float _43, const float _44);


	matrix4x4(const vector4d& _1, const vector4d& _2,const vector4d& _3,const vector4d& _4);

	matrix4x4(const matrix4x4& m);

	matrix4x4(const matrix3x3& m);

	matrix4x4& operator = (const matrix4x4&);

	matrix4x4(const quaternion& q);
	operator quaternion () const;

	static
	matrix4x4  	xRotationMatrix(const float angle);

	static
	matrix4x4  	yRotationMatrix(const float angle);

	static
	matrix4x4  	zRotationMatrix(const float angle);

	static
	matrix4x4	rotationMatrix(const float  angle,const vector3d& v3d);
	static
	matrix4x4	scaleMatrix(const float sx,const float sy, const float sz);

	static
	matrix4x4  	translationMatrix(const vector3d& v3d);

	//Projection
	static
	matrix4x4   orthoProjection(float left,float top,float right,float bottom,float nearPlane,float farPlane);

	static
	matrix4x4	perspectiveProjection(float fovy,float aspect, float nearPlane, float farPlane);

	static
	matrix4x4	frustumMatrix (float top,float left,float bootom,float right,float nearPlane,float farPlane);

	//view
	static
	matrix4x4 lookat(const vector3d& from, const vector3d& to, const vector3d& up);

	static
	matrix4x4 billboard(const vector3d& from, const vector3d& to, const vector3d& up);

	matrix4x4 	operator + () const;
	matrix4x4 	operator - () const;

	matrix4x4 	operator + (const matrix4x4& ) const;
	matrix4x4 	operator - (const matrix4x4& ) const;

	matrix4x4 	operator * (const matrix4x4& ) const;
	vector4d  	operator * (const vector4d& )  const;
	vector3d  	operator * (const vector3d& )  const;

	matrix4x4&	operator+= (const matrix4x4& );
	matrix4x4&  operator-= (const matrix4x4& );

	matrix4x4&	operator*= (const matrix4x4& );

	matrix4x4   operator * (const float ) const;
	matrix4x4&  operator*= (const float );

	matrix4x4	operator / (const float ) const;
	matrix4x4&  operator/= (const float );

	matrix4x4&	inverse();
	//!Inverse a transformation matrix, i.e. composition of rotations and translations (NOT SCALE)
	matrix4x4&  fast_inverse();
	matrix4x4&  transpose();

	operator    float*	();
	operator const float* () const;

	friend
	std::ostream& operator << (std::ostream& , const matrix4x4& );
	friend
	matrix4x4 operator * (const float, const matrix4x4&);

	//!Inverse a transformation matrix, i.e. composition of rotations and translations (NOT SCALE)
	friend
	matrix4x4	  fast_inversed(const matrix4x4&);

	friend
	matrix4x4	  inversed(const matrix4x4&);
	friend
	matrix4x4	  transposed(const matrix4x4&);
	friend
	float		  det(const matrix4x4&);


} MATH_OBJECT_END_DECL;

//============================Implemetation=========================================
inline
std::ostream& operator << (std::ostream& s, const matrix4x4& m)
{
	return s
	<< "(( "
	<< m._11 << ", " << m._12 << ", " << m._13 << ", " << m._14 << " ),( "
	<< m._21 << ", " << m._22 << ", " << m._23 << ", " << m._24 << " ),( "
	<< m._31 << ", " << m._32 << ", " << m._33 << ", " << m._34 << " ),( "
	<< m._41 << ", " << m._42 << ", " << m._43 << ", " << m._44 <<  " ))" ;
}

inline
matrix4x4::matrix4x4()
{
	row[0] = math::__internal::mtx4d_first_row.xmm;
	row[1] = math::__internal::mtx4d_second_row.xmm;
	row[2] = math::__internal::mtx4d_third_row.xmm;
	row[3] = math::__internal::mtx4d_fourth_row.xmm;
}

inline
matrix4x4::matrix4x4(
		const float __11,const float __12,const float __13, const float __14,
		const float __21,const float __22,const float __23, const float __24,
		const float __31,const float __32,const float __33, const float __34,
		const float __41,const float __42,const float __43, const float __44
)
{
	row[0] = _mm_setzero_ps();
	row[1] = _mm_setzero_ps();
	row[2] = _mm_setzero_ps();
	_11 = __11;
	_12 = __12;
	_13 = __13;
	_14 = __14;

	_21 = __21;
	_22 = __22;
	_23 = __23;
	_24 = __24;

	_31 = __31;
	_32 = __32;
	_33 = __33;
	_34 = __34;

	_41 = __41;
	_42 = __42;
	_43 = __43;
	_44 = __44;
}

inline
matrix4x4::matrix4x4(const vector4d& _1, const vector4d& _2,const vector4d& _3,const vector4d& _4)
{
	row[0] = _1.xmm;
	row[1] = _2.xmm;
	row[2] = _3.xmm;
	row[3] = _4.xmm;
}

inline
matrix4x4::matrix4x4(const matrix4x4& m)
{
	row[0] = m.row[0];
	row[1] = m.row[1];
	row[2] = m.row[2];
	row[3] = m.row[3];
}

inline
matrix4x4& matrix4x4::operator = (const matrix4x4& m)
{
	row[0] = m.row[0];
	row[1] = m.row[1];
	row[2] = m.row[2];
	row[3] = m.row[3];
	return *this;
}

inline
matrix4x4::matrix4x4(const matrix3x3 & m)
{
	row[0] = m.row[0];
	row[1] = m.row[1];
	row[2] = m.row[2];
	row[3] = math::__internal::mtx4d_fourth_row.xmm;
}

//Todo: optimize me
inline
matrix4x4  	matrix4x4::rotationMatrix(const float angle,const vector3d& v3d)
{
	return matrix4x4(matrix3x3::rotationMatrix(angle,v3d));
}

inline
matrix4x4  	matrix4x4::xRotationMatrix(const float angle)
{
	matrix4x4 o;
	math::sincos(angle,&o._23,&o._22);
	o._32 = - o._23;
	o._33 = o._22;
	return o;
}

inline
matrix4x4  	matrix4x4::yRotationMatrix(const float angle)
{
	matrix4x4 o;
	math::sincos(angle,&o._31,&o._11);
	o._13 = -o._31;
	o._33 = o._11;
	return o;
}

inline
matrix4x4  	matrix4x4::zRotationMatrix(const float angle)
{
	matrix4x4 o;
	math::sincos(angle,&o._12,&o._11);
	o._22 = o._11;
	o._21 = -o._12;
	return o;
}

inline
matrix4x4	matrix4x4::scaleMatrix(const float sx,const float sy, const float sz)
{
	matrix4x4 o;
	o._11 = sx;
	o._22 = sy;
	o._33 = sz;
	return o;
}

inline
matrix4x4  	matrix4x4::translationMatrix(const vector3d& v2d)
{
	matrix4x4 o;
	o._14 = v2d.x;
	o._24 = v2d.y;
	o._34 = v2d.z;
	return o;
}

inline
matrix4x4 	matrix4x4::operator + () const
{
	return matrix4x4(*this);
}
inline
matrix4x4 	matrix4x4::operator - () const
{
	matrix4x4 o(*this);
	o.row[0] = _mm_xor_ps(o.row[0],*reinterpret_cast<const __m128*>(_ps_sign_mask));
	o.row[1] = _mm_xor_ps(o.row[1],*reinterpret_cast<const __m128*>(_ps_sign_mask));
	o.row[2] = _mm_xor_ps(o.row[2],*reinterpret_cast<const __m128*>(_ps_sign_mask));
	o.row[3] = _mm_xor_ps(o.row[3],*reinterpret_cast<const __m128*>(_ps_sign_mask));
	return o;
}

inline
matrix4x4 	matrix4x4::operator + (const matrix4x4& m) const
{
	return matrix4x4(_mm_add_ps(row[0],m.row[0]),_mm_add_ps(row[1],m.row[1]),_mm_add_ps(row[2],m.row[2]),_mm_add_ps(row[3],m.row[3]));
}

inline
matrix4x4 	matrix4x4::operator - (const matrix4x4& m) const
{
	return matrix4x4(_mm_sub_ps(row[0],m.row[0]),_mm_sub_ps(row[1],m.row[1]),_mm_sub_ps(row[2],m.row[2]),_mm_sub_ps(row[3],m.row[3]));
}

inline
matrix4x4 	matrix4x4::operator * (const matrix4x4& mb) const
{
	return matrix4x4(
			_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(0,0,0,0)), mb.row[0]), _mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(1,1,1,1)), mb.row[1])), _mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(2,2,2,2)), mb.row[2])), _mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(3,3,3,3)), mb.row[3])),
			_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(0,0,0,0)), mb.row[0]), _mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(1,1,1,1)), mb.row[1])), _mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(2,2,2,2)), mb.row[2])), _mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(3,3,3,3)), mb.row[3])),
			_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(0,0,0,0)), mb.row[0]), _mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(1,1,1,1)), mb.row[1])), _mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(2,2,2,2)), mb.row[2])), _mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(3,3,3,3)), mb.row[3])),
			_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(row[3], row[3], _MM_SHUFFLE(0,0,0,0)), mb.row[0]), _mm_mul_ps(_mm_shuffle_ps(row[3], row[3], _MM_SHUFFLE(1,1,1,1)), mb.row[1])), _mm_mul_ps(_mm_shuffle_ps(row[3], row[3], _MM_SHUFFLE(2,2,2,2)), mb.row[2])), _mm_mul_ps(_mm_shuffle_ps(row[3], row[3], _MM_SHUFFLE(3,3,3,3)), mb.row[3]))
	);
}

inline
vector3d  	matrix4x4::operator * (const vector3d& v)  const
{
	vector4d o(v);
	return *this*o;
}

inline
vector4d  	matrix4x4::operator * (const vector4d& v)  const
{
	vector4d o;
	o.xmm =  _mm_add_ps(
			_mm_add_ps(
					_mm_add_ps(_mm_mul_ps(row[0], _mm_shuffle_ps(v.xmm, v.xmm, _MM_SHUFFLE(0,0,0,0))),
							_mm_mul_ps(row[1], _mm_shuffle_ps(v.xmm, v.xmm, _MM_SHUFFLE(1,1,1,1)))),
							_mm_mul_ps(row[2], _mm_shuffle_ps(v.xmm, v.xmm, _MM_SHUFFLE(2,2,2,2)))),
							_mm_mul_ps(row[3], _mm_shuffle_ps(v.xmm, v.xmm, _MM_SHUFFLE(3,3,3,3))));


	return o;
}

inline
matrix4x4&	matrix4x4::operator+= (const matrix4x4& m)
{
	row[0] = _mm_add_ps(row[0],m.row[0]);
	row[1] = _mm_add_ps(row[1],m.row[1]);
	row[2] = _mm_add_ps(row[2],m.row[2]);
	row[3] = _mm_add_ps(row[3],m.row[3]);
	return *this;
}

inline
matrix4x4&  matrix4x4::operator-= (const matrix4x4& m)
{
	row[0] = _mm_sub_ps(row[0],m.row[0]);
	row[1] = _mm_sub_ps(row[1],m.row[1]);
	row[2] = _mm_sub_ps(row[2],m.row[2]);
	row[3] = _mm_sub_ps(row[3],m.row[3]);
	return *this;
}

inline
matrix4x4&	matrix4x4::operator*= (const matrix4x4& mb)
{
	row[0] = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(0,0,0,0)), mb.row[0]), _mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(1,1,1,1)), mb.row[1])), _mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(2,2,2,2)), mb.row[2])), _mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(3,3,3,3)), mb.row[3]));
	row[1] = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(0,0,0,0)), mb.row[0]), _mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(1,1,1,1)), mb.row[1])), _mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(2,2,2,2)), mb.row[2])), _mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(3,3,3,3)), mb.row[3]));
	row[2] = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(0,0,0,0)), mb.row[0]), _mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(1,1,1,1)), mb.row[1])), _mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(2,2,2,2)), mb.row[2])), _mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(3,3,3,3)), mb.row[3]));
	row[3] = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(row[3], row[3], _MM_SHUFFLE(0,0,0,0)), mb.row[0]), _mm_mul_ps(_mm_shuffle_ps(row[3], row[3], _MM_SHUFFLE(1,1,1,1)), mb.row[1])), _mm_mul_ps(_mm_shuffle_ps(row[3], row[3], _MM_SHUFFLE(2,2,2,2)), mb.row[2])), _mm_mul_ps(_mm_shuffle_ps(row[3], row[3], _MM_SHUFFLE(3,3,3,3)), mb.row[3]));

	return *this;
}

inline
matrix4x4   matrix4x4::operator * (const float f) const
{
	__m128 tmp = _mm_set1_ps ( f );
	return matrix4x4(_mm_mul_ps( row[0],tmp),_mm_mul_ps( row[1], tmp),_mm_mul_ps(row[2],tmp),_mm_mul_ps(row[3],tmp));
}

inline
matrix4x4&  matrix4x4::operator*= (const float f)
{
	__m128 tmp = _mm_set1_ps ( f );
	row[0] = _mm_mul_ps( row[0], tmp);
	row[1] = _mm_mul_ps( row[1], tmp);
	row[2] = _mm_mul_ps( row[2], tmp);
	row[3] = _mm_mul_ps( row[3], tmp);
	return *this;
}

inline
matrix4x4	matrix4x4::operator / (const float f) const
{
	__m128 tmp = _mm_set1_ps ( f );
	tmp = __invert_ps(tmp);
	return matrix4x4(_mm_mul_ps( row[0],tmp),_mm_mul_ps( row[1], tmp),_mm_mul_ps(row[2],tmp),_mm_mul_ps(row[3],tmp));
}

inline
matrix4x4&  matrix4x4::operator/= (const float f)
{
	__m128 tmp = __invert_ps(_mm_set1_ps ( f ));
	row[0] = _mm_mul_ps( row[0], tmp);
	row[1] = _mm_mul_ps( row[1], tmp);
	row[2] = _mm_mul_ps( row[2], tmp);
	row[3] = _mm_mul_ps( row[3], tmp);
	return *this;
}
inline
matrix4x4 operator * (const float f, const matrix4x4& m)
{
	__m128 tmp = _mm_set1_ps ( f );
	return matrix4x4(_mm_mul_ps( m.row[0],tmp),_mm_mul_ps( m.row[1], tmp),_mm_mul_ps(m.row[2],tmp),_mm_mul_ps(m.row[3],tmp));
}

//Code taken from Intel pdf "Streaming SIMD Extension - Inverse of 4x4 Matrix"

inline
matrix4x4&	matrix4x4::inverse()
{
	const float* src = &(elem[0][0]);

	__m128 minor0, minor1, minor2, minor3;
	__m128 row0, row1, row2, row3;
	__m128 det, tmp1;

	tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src)), (__m64*)(src+ 4));
	row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(src+8)), (__m64*)(src+12));

	row0 = _mm_shuffle_ps(tmp1, row1, 0x88);
	row1 = _mm_shuffle_ps(row1, tmp1, 0xDD);

	tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src+ 2)), (__m64*)(src+ 6));
	row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(src+10)), (__m64*)(src+14));

	row2 = _mm_shuffle_ps(tmp1, row3, 0x88);
	row3 = _mm_shuffle_ps(row3, tmp1, 0xDD);

	tmp1 = _mm_mul_ps(row2, row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

	minor0 = _mm_mul_ps(row1, tmp1);
	minor1 = _mm_mul_ps(row0, tmp1);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
	minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
	minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);

	tmp1 = _mm_mul_ps(row1, row2);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

	minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
	minor3 = _mm_mul_ps(row0, tmp1);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
	minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
	minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

	tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	row2 = _mm_shuffle_ps(row2, row2, 0x4E);

	minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
	minor2 = _mm_mul_ps(row0, tmp1);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
	minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
	minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

	tmp1 = _mm_mul_ps(row0, row1);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

	minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
	minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));

	tmp1 = _mm_mul_ps(row0, row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
	minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
	minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));

	tmp1 = _mm_mul_ps(row0, row2);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

	minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
	minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);

	det = _mm_mul_ps(row0, minor0);
	det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
	det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
	tmp1 = __invert_ss(det);

	det = _mm_sub_ss(_mm_add_ss(tmp1, tmp1), _mm_mul_ss(det, _mm_mul_ss(tmp1, tmp1)));
	det = _mm_shuffle_ps(det, det, 0x00);

	minor0 = _mm_mul_ps(det, minor0);
	_mm_storel_pi((__m64*)(src), minor0);
	_mm_storeh_pi((__m64*)(src+2), minor0);

	minor1 = _mm_mul_ps(det, minor1);
	_mm_storel_pi((__m64*)(src+4), minor1);
	_mm_storeh_pi((__m64*)(src+6), minor1);

	minor2 = _mm_mul_ps(det, minor2);
	_mm_storel_pi((__m64*)(src+ 8), minor2);
	_mm_storeh_pi((__m64*)(src+10), minor2);

	minor3 = _mm_mul_ps(det, minor3);
	_mm_storel_pi((__m64*)(src+12), minor3);
	_mm_storeh_pi((__m64*)(src+14), minor3);

	return *this;
}

inline
matrix4x4::operator
float*	()
{
	return &elem[0][0];
}

inline
matrix4x4::operator
const float* () const
{
	return &elem[0][0];
}

inline
matrix4x4&  matrix4x4::transpose()
{
	_MM_TRANSPOSE4_PS(row[0], row[1], row[2], row[3]);
	return *this;
}

inline
matrix4x4	  inversed(const matrix4x4& m)
{
	matrix4x4 inv(m);
	return (inv.inverse());
}

inline
matrix4x4	  transposed(const matrix4x4& m)
{
	matrix4x4 o (m);
	_MM_TRANSPOSE4_PS(o.row[0], o.row[1], o.row[2], o.row[3]);
	return o;
}
//TODO: Intel's version of 4x4 determinant
inline
float		  det(const matrix4x4& m)
{
	const float* src = &(m.elem[0][0]);

	__m128 minor0, minor1, minor2, minor3;
	__m128 row0, row1, row2, row3;
	__m128 det, tmp1;

	tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src)), (__m64*)(src+ 4));
	row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(src+8)), (__m64*)(src+12));

	row0 = _mm_shuffle_ps(tmp1, row1, 0x88);
	row1 = _mm_shuffle_ps(row1, tmp1, 0xDD);

	tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src+ 2)), (__m64*)(src+ 6));
	row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(src+10)), (__m64*)(src+14));

	row2 = _mm_shuffle_ps(tmp1, row3, 0x88);
	row3 = _mm_shuffle_ps(row3, tmp1, 0xDD);

	tmp1 = _mm_mul_ps(row2, row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

	minor0 = _mm_mul_ps(row1, tmp1);
	minor1 = _mm_mul_ps(row0, tmp1);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
	minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
	minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);

	tmp1 = _mm_mul_ps(row1, row2);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

	minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
	minor3 = _mm_mul_ps(row0, tmp1);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
	minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
	minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

	tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	row2 = _mm_shuffle_ps(row2, row2, 0x4E);

	minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
	minor2 = _mm_mul_ps(row0, tmp1);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
	minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
	minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

	tmp1 = _mm_mul_ps(row0, row1);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

	minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
	minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));

	tmp1 = _mm_mul_ps(row0, row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
	minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
	minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));

	tmp1 = _mm_mul_ps(row0, row2);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

	minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));

	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
	minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);

	det = _mm_mul_ps(row0, minor0);
	det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
	det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);

	float _;
	_mm_store_ss(&_,det);
	return _;
}

//TODO: Optimize it
inline
matrix4x4& matrix4x4::fast_inverse()
{
	matrix3x3 mtx (row[0],row[1],row[2]);
	mtx._r1 = mtx._r2 = mtx._r3 = 0.0;
	mtx.transpose();
	vector3d  v3d (_14,_24,_34);
	v3d = - mtx*v3d;
	matrix4x4 r (mtx);
	r._14 = v3d.x;
	r._24 = v3d.y;
	r._34 = v3d.z;
	return (*this = r);
}

inline
matrix4x4 fast_inversed(const matrix4x4& m)
{
	matrix3x3 mtx (m.row[0],m.row[1],m.row[2]);
	mtx._r1 = mtx._r2 = mtx._r3 = 0.0;
	mtx.transpose();
	vector3d  v3d (m._14,m._24,m._34);
	v3d = - mtx*v3d;
	matrix4x4 r (mtx);
	r._14 = v3d.x;
	r._24 = v3d.y;
	r._34 = v3d.z;
	return r;
}

//Projection
inline
matrix4x4   matrix4x4::orthoProjection(float left,float top,float right,float bottom,float nearPlane,float farPlane)
{
	float _1_rl, _1_tb,_1_fn;

	_mm_store_ss(&_1_rl,__invert_ss(_mm_sub_ss(_mm_load_ss(&right),_mm_load_ss(&left))));
	_mm_store_ss(&_1_tb,__invert_ss(_mm_sub_ss(_mm_load_ss(&top),_mm_load_ss(&bottom))));
	_mm_store_ss(&_1_fn,__invert_ss(_mm_sub_ss(_mm_load_ss(&nearPlane),_mm_load_ss(&farPlane))));

	matrix4x4 m;
	m._11 = 2.0 * _1_rl;
	m._22 = 2.0 * _1_tb;
	m._33 = 2.0 * _1_fn;
	m._44 = -1.0;

	m._14 = - (right + left  ) * _1_rl;
	m._24 = - (top   + bottom) * _1_tb;
	m._34 =   ( farPlane  + nearPlane  ) * _1_fn;

	return m;

}

inline
matrix4x4	matrix4x4::perspectiveProjection(float fovy,float aspect, float nearPlane, float farPlane)
{
	float _1_fn;
	_mm_store_ss(&_1_fn,__invert_ss(_mm_sub_ss(_mm_load_ss(&nearPlane),_mm_load_ss(&farPlane))));
	float f = math::cot(fovy*0.5);

	matrix4x4 m;
	_mm_store_ss(&m._11,_mm_mul_ss(_mm_load_ss(&f),__invert_ss(_mm_load_ss(&aspect))));
	m._22 = f;
	m._33 = ( farPlane  + nearPlane  ) * _1_fn;
	m._44 = 0;
	m._43 = -1;
	m._34 = 2.0 * farPlane * nearPlane * _1_fn;
	return m;
}

inline
matrix4x4	matrix4x4::frustumMatrix (float top,float left,float bottom,float right,float nearPlane,float farPlane)
{
	float _1_rl, _1_tb,_1_fn;

	_mm_store_ss(&_1_rl,__invert_ss(_mm_sub_ss(_mm_load_ss(&right),_mm_load_ss(&left))));
	_mm_store_ss(&_1_tb,__invert_ss(_mm_sub_ss(_mm_load_ss(&top),_mm_load_ss(&bottom))));
	_mm_store_ss(&_1_fn,__invert_ss(_mm_sub_ss(_mm_load_ss(&nearPlane),_mm_load_ss(&farPlane))));

	matrix4x4 m;
	m._44 = 0;
	m._34 = -1;

	m._11 = 2.0 * nearPlane * _1_rl;
	m._22 = 2.0 * nearPlane * _1_tb;

	m._13 = - (right + left  ) * _1_rl;
	m._23 = - (top   + bottom) * _1_tb;
	m._33 =   ( farPlane  + nearPlane  ) * _1_fn;

	m._34 = 2 * nearPlane * farPlane * _1_fn;

	return m;

}

//view
inline
matrix4x4 matrix4x4::lookat(const vector3d& from, const vector3d& to, const vector3d& up)
{
	vector3d f = (to - from);
	vector3d s = f*up;
	vector3d u = s*f;
	f.normalize();
	s.normalize();
	u.normalize();

	matrix4x4 m;
	m.row[0] = s.xmm;
	m.row[1] = u.xmm;
	m.row[2] = (-f).xmm;

	m._14 = -(s,from);
	m._24 = -(u,from);
	m._34 =  (f,from);

	return m;
}

inline
matrix4x4 matrix4x4::billboard(const vector3d& from, const vector3d& to, const vector3d& up)
{
	vector3d f = (to - from);
	vector3d s = f*up;
	vector3d u = s*f;
	f = u*up;
	f.normalize();
	s.normalize();
	u.normalize();

	matrix4x4 m;
	m.row[0] = s.xmm;
	m.row[1] = u.xmm;
	m.row[2] = (-f).xmm;

	m._14 = -(s,from);
	m._24 = -(u,from);
	m._34 =  (f,from);

	return m;
}

inline
matrix4x4::matrix4x4(const quaternion& q)
{
	row[0] = _mm_setzero_ps();
	row[1] = _mm_setzero_ps();
	row[2] = _mm_setzero_ps();
	row[3] = __internal::mtx4d_fourth_row.xmm;

	float xx = q.x*q.x; float yy = q.y*q.y; float zz = q.z*q.z;
	float xy = q.x*q.y; float xz = q.x*q.z; float yz = q.y*q.z;
	float wx = q.w*q.x; float wy = q.w*q.y; float wz = q.w*q.z;

	elem[0][0] = 1.0f - 2.0f * (yy + zz);
	elem[1][0] =        2.0f * (xy - wz);
	elem[2][0] =        2.0f * (xz + wy);

	elem[0][1] =        2.0f * (xy + wz);
	elem[1][1] = 1.0f - 2.0f * (xx + zz);
	elem[2][1] =        2.0f * (yz - wx);

	elem[0][2] =        2.0f * (xz - wy);
	elem[1][2] =        2.0f * (yz + wx);
	elem[2][2] = 1.0f - 2.0f * (xx + yy);
}

inline
matrix4x4::operator
quaternion () const
{
	float qa[4];
	float tr = elem[0][0] + elem[1][1] + elem[2][2];
	if (tr > 0.0f)
	{
		float s = math::sqrt (tr + 1.0f);
		qa[3] = s * 0.5f;
		s = 0.5f / s;
		qa[0] = (elem[1][2] - elem[2][1]) * s;
		qa[1] = (elem[2][0] - elem[0][2]) * s;
		qa[2] = (elem[0][1] - elem[1][0]) * s;
	}
	else
	{
		int i, j, k, nxt[3] = {1,2,0};
		i = 0;
		if (elem[1][1] > elem[0][0]) i=1;
		if (elem[2][2] > elem[i][i]) i=2;
		j = nxt[i];
		k = nxt[j];
		float s = math::sqrt((elem[i][i] - (elem[j][j] + elem[k][k])) + 1.0f);
		qa[i] = s * 0.5f;
		s = 0.5f / s;
		qa[3] = (elem[j][k] - elem[k][j])* s;
		qa[j] = (elem[i][j] + elem[j][i]) * s;
		qa[k] = (elem[i][k] + elem[k][i]) * s;
	}
	quaternion q(qa[0],qa[1],qa[2],qa[3]);
	return q;

}

}

#endif /* MATRIX4X4_HPP_ */

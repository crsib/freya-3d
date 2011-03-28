/*
 * matrix3x3.hpp
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 22, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef MATRIX3X3_HPP_
#define MATRIX3X3_HPP_
#include "math_internal.h"
#include "vector2d.hpp"
#include "vector3d.hpp"
#include "quaternion.hpp"
#include "matrix2x2.hpp"

namespace math
{
namespace __internal
{
static const float4  mtx3d_first_row 	= {{1,0,0,0}};
static const float4  mtx3d_second_row 	= {{0,1,0,0}};
static const float4  mtx3d_third_row 	= {{0,0,1,0}};
}

MATH_OBJECT_DECL class matrix3x3
{
public:
	matrix3x3(__m128 _1,__m128 _2,__m128 _3)
	{
		row[0] = _1;
		row[1] = _2;
		row[2] = _3;
	}
public:
	static const matrix3x3 identity;

	MATH_MEMORY_FUNCTIONS

	union
	{
		__m128	row [3];
		float	elem[3][4];
		struct
		{
			float _11,_12,_13,_r1;
			float _21,_22,_23,_r2;
			float _31,_32,_33,_r3;
		};
	};

	matrix3x3();

	matrix3x3(
			const float _11,const float _12,const float _13,
			const float _21,const float _22,const float _23,
			const float _31,const float _32,const float _33);


	matrix3x3(const vector3d& _1, const vector3d& _2,const vector3d& _3);

	matrix3x3(const matrix3x3& m);

	matrix3x3(const matrix2x2& m);

	matrix3x3& operator = (const matrix3x3&);

	matrix3x3(const quaternion& q);

	operator quaternion () const;

	static
	matrix3x3  	xRotationMatrix(const float angle);

	static
	matrix3x3  	yRotationMatrix(const float angle);

	static
	matrix3x3  	zRotationMatrix(const float angle);

	static
	matrix3x3	rotationMatrix(const float  angle,const vector3d& v3d);
	static
	matrix3x3	scaleMatrix(const float sx,const float sy, const float sz);
	static
	matrix3x3  	rotationMatrix2D(const float angle);
	static
	matrix3x3  	translationMatrix2D(const vector2d& v2d);

	static
	matrix3x3	scaleMatrix2d(const float sx, const float sy);

	matrix3x3 	operator + () const;
	matrix3x3 	operator - () const;

	matrix3x3 	operator + (const matrix3x3& ) const;
	matrix3x3 	operator - (const matrix3x3& ) const;

	matrix3x3 	operator * (const matrix3x3& ) const;
	vector2d  	operator * (const vector2d& )  const;
	vector3d  	operator * (const vector3d& )  const;

	matrix3x3&	operator+= (const matrix3x3& );
	matrix3x3&  operator-= (const matrix3x3& );

	matrix3x3&	operator*= (const matrix3x3& );

	matrix3x3   operator * (const float ) const;
	matrix3x3&  operator*= (const float );

	matrix3x3	operator / (const float ) const;
	matrix3x3&  operator/= (const float );

	matrix3x3&	inverse();
	matrix3x3&  transpose();

	friend
	std::ostream& operator << (std::ostream& , const matrix3x3& );
	friend
	matrix3x3 operator * (const float, const matrix3x3&);
	friend
	matrix3x3	  inversed(const matrix3x3&);
	friend
	matrix3x3	  transposed(const matrix3x3&);
	friend
	float		  det(const matrix3x3&);


} MATH_OBJECT_END_DECL;

//============================Implemetation=========================================
inline
std::ostream& operator << (std::ostream& s, const matrix3x3& m)
{
	return s << "(( " << m._11 << ", " << m._12 << ", " << m._13 <<  " ),( " << m._21 << ", " << m._22 << ", " << m._23 << " ),( " << m._31 << ", " << m._32 << ", " << m._33 <<  " ))" ;
}

inline
matrix3x3::matrix3x3()
{
	row[0] = math::__internal::mtx3d_first_row.xmm;
	row[1] = math::__internal::mtx3d_second_row.xmm;
	row[2] = math::__internal::mtx3d_third_row.xmm;
}

inline
matrix3x3::matrix3x3(const float __11,const float __12,const float __13,
		const float __21,const float __22,const float __23,
		const float __31,const float __32,const float __33)
{
	row[0] = _mm_setzero_ps();
	row[1] = _mm_setzero_ps();
	row[2] = _mm_setzero_ps();
	_11 = __11;
	_12 = __12;
	_13 = __13;

	_21 = __21;
	_22 = __22;
	_23 = __23;

	_31 = __31;
	_32 = __32;
	_33 = __33;
}

inline
matrix3x3::matrix3x3(const vector3d& _1, const vector3d& _2, const vector3d& _3)
{
	row[0] = _1.xmm;
	row[1] = _2.xmm;
	row[2] = _3.xmm;
}

inline
matrix3x3::matrix3x3(const matrix3x3& m)
{
	row[0] = m.row[0];
	row[1] = m.row[1];
	row[2] = m.row[2];
}

inline
matrix3x3& matrix3x3::operator = (const matrix3x3& m)
{
	row[0] = m.row[0];
	row[1] = m.row[1];
	row[2] = m.row[2];
	return *this;
}

inline
matrix3x3::matrix3x3(const matrix2x2 & m)
{
	row[0] = m.row[0];
	row[1] = m.row[1];
	row[2] = math::__internal::mtx3d_third_row.xmm;
}

//Todo: optimize me
inline
matrix3x3  	matrix3x3::rotationMatrix(const float angle,const vector3d& v3d)
{
	float s,c;
	math::sincos(angle,&s,&c);
	vector3d axis = normalized(v3d);
	return matrix3x3(
			axis.x*axis.x + (1 - axis.x*axis.x)*c, axis.x*axis.y*(1-c) - axis.z*s, axis.x*axis.z*(1-c) + axis.y*s,
			axis.x*axis.y*(1-c) + axis.z*s, axis.y*axis.y + (1 - axis.y*axis.y)*c, axis.y*axis.z*(1-c) - axis.x*s,
			axis.x*axis.z*(1-c) - axis.y*s, axis.y*axis.z*(1-c) + axis.x*s, axis.z*axis.z + (1 - axis.z*axis.z)*c
	);
}

inline
matrix3x3  	matrix3x3::xRotationMatrix(const float angle)
{
	matrix3x3 o;
	math::sincos(angle,&o._23,&o._22);
	o._32 = - o._23;
	o._33 = o._22;
	return o;
}

inline
matrix3x3  	matrix3x3::yRotationMatrix(const float angle)
{
	matrix3x3 o;
	math::sincos(angle,&o._31,&o._11);
	o._13 = -o._31;
	o._33 = o._11;
	return o;
}

inline
matrix3x3  	matrix3x3::zRotationMatrix(const float angle)
{
	matrix3x3 o;
	math::sincos(angle,&o._12,&o._11);
	o._22 = o._11;
	o._21 = -o._12;
	return o;
}

inline
matrix3x3	matrix3x3::scaleMatrix(const float sx,const float sy, const float sz)
{
	matrix3x3 o;
	o._11 = sx;
	o._22 = sy;
	o._33 = sz;
	return o;
}

inline
matrix3x3  	matrix3x3::translationMatrix2D(const vector2d& v2d)
{
	matrix3x3 o;
	o._31 = v2d.x;
	o._32 = v2d.y;
	return o;
}

inline
matrix3x3	matrix3x3::scaleMatrix2d(const float sx, const float sy)
{
	matrix3x3 o;
	o._11 = sx;
	o._22 = sy;
	return o;
}

inline
matrix3x3  matrix3x3::rotationMatrix2D(const float angle)
{
	matrix3x3 o;
	math::sincos(angle,&o._12,&o._11);
	o._22 =  o._11;
	o._21 = -o._12;
	o.row[2] = math::__internal::mtx3d_third_row.xmm;
	return o;
}
inline
matrix3x3 	matrix3x3::operator + () const
{
	return matrix3x3(*this);
}
inline
matrix3x3 	matrix3x3::operator - () const
{
	matrix3x3 o(*this);
	o.row[0] = _mm_xor_ps(o.row[0],*reinterpret_cast<const __m128*>(_ps_sign_mask));
	o.row[1] = _mm_xor_ps(o.row[1],*reinterpret_cast<const __m128*>(_ps_sign_mask));
	o.row[2] = _mm_xor_ps(o.row[2],*reinterpret_cast<const __m128*>(_ps_sign_mask));
	return o;
}

inline
matrix3x3 	matrix3x3::operator + (const matrix3x3& m) const
{
	return matrix3x3(_mm_add_ps(row[0],m.row[0]),_mm_add_ps(row[1],m.row[1]),_mm_add_ps(row[2],m.row[2]));
}

inline
matrix3x3 	matrix3x3::operator - (const matrix3x3& m) const
{
	return matrix3x3(_mm_sub_ps(row[0],m.row[0]),_mm_sub_ps(row[1],m.row[1]),_mm_sub_ps(row[2],m.row[2]));
}

inline
matrix3x3 	matrix3x3::operator * (const matrix3x3& mb) const
{
	return matrix3x3(
			_mm_add_ps(
					_mm_add_ps(
							_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(0,0,0,0)), mb.row[0]),
							_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(1,1,1,1)), mb.row[1])),
							_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(2,2,2,2)), mb.row[2])),

							_mm_add_ps(
									_mm_add_ps(
											_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(0,0,0,0)), mb.row[0]),
											_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(1,1,1,1)), mb.row[1])),
											_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(2,2,2,2)), mb.row[2])),

											_mm_add_ps(
													_mm_add_ps(
															_mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(0,0,0,0)), mb.row[0]),
															_mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(1,1,1,1)), mb.row[1])),
															_mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(2,2,2,2)), mb.row[2])));
}

inline
vector2d  	matrix3x3::operator * (const vector2d& v)  const
{
	vector3d o(v);
	return *this*o;
}

inline
vector3d  	matrix3x3::operator * (const vector3d& v)  const
{
	vector3d o;
	o.xmm = _mm_add_ps(
			_mm_add_ps(
					_mm_mul_ps(_mm_shuffle_ps(v.xmm, v.xmm, _MM_SHUFFLE(0,0,0,0)), row[0]),
					_mm_mul_ps(_mm_shuffle_ps(v.xmm, v.xmm, _MM_SHUFFLE(1,1,1,1)), row[1])),
					_mm_mul_ps(_mm_shuffle_ps(v.xmm, v.xmm, _MM_SHUFFLE(2,2,2,2)), row[2]));

	return o;
}

inline
matrix3x3&	matrix3x3::operator+= (const matrix3x3& m)
{
	row[0] = _mm_add_ps(row[0],m.row[0]);
	row[1] = _mm_add_ps(row[1],m.row[1]);
	row[2] = _mm_add_ps(row[2],m.row[2]);
	return *this;
}

inline
matrix3x3&  matrix3x3::operator-= (const matrix3x3& m)
{
	row[0] = _mm_sub_ps(row[0],m.row[0]);
	row[1] = _mm_sub_ps(row[1],m.row[1]);
	row[2] = _mm_sub_ps(row[2],m.row[2]);
	return *this;
}

inline
matrix3x3&	matrix3x3::operator*= (const matrix3x3& mb)
{
	row[0]= _mm_add_ps(
			_mm_add_ps(
					_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(0,0,0,0)), mb.row[0]),
					_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(1,1,1,1)), mb.row[1])),
					_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(2,2,2,2)), mb.row[2]));

	row[1]= _mm_add_ps(
			_mm_add_ps(
					_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(0,0,0,0)), mb.row[0]),
					_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(1,1,1,1)), mb.row[1])),
					_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(2,2,2,2)), mb.row[2]));

	row[2]= _mm_add_ps(
			_mm_add_ps(
					_mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(0,0,0,0)), mb.row[0]),
					_mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(1,1,1,1)), mb.row[1])),
					_mm_mul_ps(_mm_shuffle_ps(row[2], row[2], _MM_SHUFFLE(2,2,2,2)), mb.row[2]));
	return *this;
}

inline
matrix3x3   matrix3x3::operator * (const float f) const
{
	__m128 tmp = _mm_set1_ps ( f );
	return matrix3x3(_mm_mul_ps( row[0],tmp),_mm_mul_ps( row[1], tmp),_mm_mul_ps(row[2],tmp));
}

inline
matrix3x3&  matrix3x3::operator*= (const float f)
{
	__m128 tmp = _mm_set1_ps ( f );
	row[0] = _mm_mul_ps( row[0], tmp);
	row[1] = _mm_mul_ps( row[1], tmp);
	row[2] = _mm_mul_ps( row[2], tmp);
	return *this;
}

inline
matrix3x3	matrix3x3::operator / (const float f) const
{
	__m128 tmp = _mm_set1_ps ( f );
	tmp = __invert_ps(tmp);
	return matrix3x3(_mm_mul_ps( row[0],tmp),_mm_mul_ps( row[1], tmp),_mm_mul_ps(row[2],tmp));
}

inline
matrix3x3&  matrix3x3::operator/= (const float f)
{
	__m128 tmp = __invert_ps(_mm_set1_ps ( f ));
	row[0] = _mm_mul_ps( row[0], tmp);
	row[1] = _mm_mul_ps( row[1], tmp);
	row[2] = _mm_mul_ps( row[2], tmp);
	return *this;
}
inline
matrix3x3 operator * (const float f, const matrix3x3& m)
{
	__m128 tmp = _mm_set1_ps ( f );
	return matrix3x3(_mm_mul_ps( m.row[0],tmp),_mm_mul_ps( m.row[1], tmp),_mm_mul_ps( m.row[2],tmp));
}

//TODO: Code idea is tacken from SONY vectormath library

inline
matrix3x3&	matrix3x3::inverse()
{
	__m128 tmp0, tmp1, tmp2, tmp3, tmp4, dot, invdet, inv0, inv1, inv2;
	tmp2 = (vector3d(row[0])*vector3d(row[1])).xmm;
	tmp0 = (vector3d(row[1])*vector3d(row[2])).xmm;
	tmp1 = (vector3d(row[2])*vector3d(row[0])).xmm;
	dot = _mm_set1_ps((vector3d(tmp2),vector3d(row[2])));
	invdet = __invert_ps( dot );
	tmp3 = _mm_unpacklo_ps( tmp0, tmp2 );
	tmp4 = _mm_unpackhi_ps( tmp0, tmp2 );
	inv0 = _mm_unpacklo_ps( tmp3, tmp1 );
	//inv1 = vec_perm( tmp3, tmp1, _VECTORMATH_PERM_ZBWX );
	MATH_OBJECT_DECL unsigned int select_y[4] MATH_OBJECT_END_DECL = {0, 0xffffffff, 0, 0};
	inv1 = _mm_shuffle_ps( tmp3, tmp3, _MM_SHUFFLE(0,3,2,2));

	inv1 = vec_sel(inv1, tmp1, _mm_load_ps(reinterpret_cast<float*>(select_y)));
	//inv2 = vec_perm( tmp4, tmp1, _VECTORMATH_PERM_XCYX );
	inv2 = _mm_shuffle_ps( tmp4, tmp4, _MM_SHUFFLE(0,1,1,0));
	inv2 = vec_sel(inv2, _mm_shuffle_ps(tmp1, tmp1,_MM_SHUFFLE(2,2,2,2)), _mm_load_ps(reinterpret_cast<float*>(select_y)));
	inv0 = _mm_mul_ps( inv0, invdet );
	inv1 = _mm_mul_ps( inv1, invdet );
	inv2 = _mm_mul_ps( inv2, invdet );
	return (*this = matrix3x3( inv0, inv1, inv2 ));

}

inline
matrix3x3&  matrix3x3::transpose()
{
#define mswap(x,y) {float t = x; x=y; y = t;}
	mswap(elem[0][1],elem[1][0]);
	mswap(elem[0][2],elem[2][0]);
	mswap(elem[1][2],elem[2][1]);
#undef  mswap
	return *this;
}

inline
matrix3x3	  inversed(const matrix3x3& m)
{
	matrix3x3 inv(m);
	return (inv.inverse());
}

inline
matrix3x3	  transposed(const matrix3x3& m)
{
	matrix3x3 o (m);
#define mswap(x,y) {float t = x; x=y; y = t;}
	mswap(o.elem[0][1],o.elem[1][0]);
	mswap(o.elem[0][2],o.elem[2][0]);
	mswap(o.elem[1][2],o.elem[2][1]);
#undef  mswap
	return o;
}
//TODO: create an SSE version here
inline
float		  det(const matrix3x3& m)
{
	return ((vector3d(m.row[0])*vector3d(m.row[1])),vector3d(m.row[2]));
}

inline
matrix3x3::matrix3x3(const quaternion& q)
{
	row[0] = _mm_setzero_ps();
	row[1] = _mm_setzero_ps();
	row[2] = _mm_setzero_ps();

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
matrix3x3::operator
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

#endif /* MATRIX3X3_HPP_ */

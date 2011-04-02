/*
 * matrix2x2.hpp
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 22, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef MATRIX2X2_HPP_
#define MATRIX2X2_HPP_

#include "math_internal.h"
#include "vector2d.hpp"
namespace math
{
namespace __internal
{
static const float4  mtx2d_first_row = {{1,0,0,0}};
static const float4  mtx2d_second_row = {{0,1,0,0}};
}

MATH_OBJECT_DECL class matrix2x2
{
public:
	matrix2x2(__m128 _1,__m128 _2)
	{
		row[0] = _1;
		row[1] = _2;
	}
public:
	static const matrix2x2 identity;

	MATH_MEMORY_FUNCTIONS

	union
	{
		__m128	row [2];
		float	elem[2][4];
		struct
		{
			float _11,_12,_r1[2];
			float _21,_22,_r2[2];
		};
	};

	matrix2x2();

	matrix2x2(const float _11,const float _12,const float _21,const float _22);

	matrix2x2(const vector2d& _1, const vector2d& _2);

	matrix2x2(const matrix2x2& m);

	matrix2x2& operator = (const matrix2x2&);

	static
	matrix2x2  rotationMatrix(const float angle);

	static
	matrix2x2  scaleMatrix(const float sx, const float sy);

	matrix2x2 	operator + () const;
	matrix2x2 	operator - () const;

	matrix2x2 	operator + (const matrix2x2& ) const;
	matrix2x2 	operator - (const matrix2x2& ) const;

	matrix2x2 	operator * (const matrix2x2& ) const;
	vector2d  	operator * (const vector2d& )  const;

	matrix2x2&	operator+= (const matrix2x2& );
	matrix2x2&  operator-= (const matrix2x2& );

	matrix2x2&	operator*= (const matrix2x2& );

	matrix2x2   operator * (const float ) const;
	matrix2x2&  operator*= (const float );

	matrix2x2	operator / (const float ) const;
	matrix2x2&  operator/= (const float );

	matrix2x2&	inverse();
	matrix2x2&  transpose();

	friend
	std::ostream& operator << (std::ostream& , const matrix2x2& );
	friend
	matrix2x2 operator * (const float, const matrix2x2&);
	friend
	matrix2x2	  inversed(const matrix2x2&);
	friend
	matrix2x2	  transposed(const matrix2x2&);
	friend
	float		  det(const matrix2x2&);


} MATH_OBJECT_END_DECL;

//============================Implemetation=========================================
inline
std::ostream& operator << (std::ostream& s, const matrix2x2& m)
{
	return s << "(( " << m._11 << ", " << m._12 << " ),( " << m._21 << ", " << m._22 << " ))" ;
}

inline
matrix2x2::matrix2x2()
{
	row[0] = math::__internal::mtx2d_first_row.xmm;
	row[1] = math::__internal::mtx2d_second_row.xmm;
}

inline
matrix2x2::matrix2x2(const float __11,const float __12,const float __21,const float __22)
{
	row[0] = _mm_setzero_ps();
	row[1] = _mm_setzero_ps();
	_11 = __11;
	_12 = __12;
	_21 = __21;
	_22 = __22;
}

inline
matrix2x2::matrix2x2(const vector2d& _1, const vector2d& _2)
{
	row[0] = _1.xmm;
	row[1] = _2.xmm;
}

inline
matrix2x2::matrix2x2(const matrix2x2& m)
{
	row[0] = m.row[0];
	row[1] = m.row[1];
}

inline
matrix2x2& matrix2x2::operator = (const matrix2x2& m)
{
	row[0] = m.row[0];
	row[1] = m.row[1];
	return *this;
}

inline
matrix2x2  matrix2x2::rotationMatrix(const float angle)
{
	matrix2x2 o;
	math::sincos(angle,&o._12,&o._11);
	o._22 =  o._11;
	o._21 = -o._12;
	return o;
}

inline
matrix2x2  matrix2x2::scaleMatrix(const float sx, const float sy)
{
	matrix2x2 o;
	o._11 *= sx;
	o._22 *= sx;
	return o;
}

inline
matrix2x2 	matrix2x2::operator + () const
{
	return matrix2x2(*this);
}
inline
matrix2x2 	matrix2x2::operator - () const
{
	matrix2x2 o(*this);
	o.row[0] = _mm_xor_ps(o.row[0],*reinterpret_cast<const __m128*>(_ps_sign_mask));
	o.row[1] = _mm_xor_ps(o.row[1],*reinterpret_cast<const __m128*>(_ps_sign_mask));
	return o;
}

inline
matrix2x2 	matrix2x2::operator + (const matrix2x2& m) const
{
	return matrix2x2(_mm_add_ps(row[0],m.row[0]),_mm_add_ps(row[1],m.row[1]));
}

inline
matrix2x2 	matrix2x2::operator - (const matrix2x2& m) const
{
	return matrix2x2(_mm_sub_ps(row[0],m.row[0]),_mm_sub_ps(row[1],m.row[1]));
}

inline
matrix2x2 	matrix2x2::operator * (const matrix2x2& mb) const
{
	return matrix2x2(
			//Row 0
			_mm_add_ps(
					_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(0,0,0,0)), mb.row[0]),
					_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(1,1,1,1)), mb.row[1])),
					//Row 1
					_mm_add_ps(
							_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(0,0,0,0)), mb.row[0]),
							_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(1,1,1,1)), mb.row[1])));

}

inline
vector2d  	matrix2x2::operator * (const vector2d& v)  const
{
	vector2d o;
	o.xmm = (_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v.xmm,v.xmm,_MM_SHUFFLE(0,0,0,0)),row[0]),
			_mm_mul_ps(_mm_shuffle_ps(v.xmm,v.xmm,_MM_SHUFFLE(1,1,1,1)),row[1])));
	return o;
}

inline
matrix2x2&	matrix2x2::operator+= (const matrix2x2& m)
{
	row[0] = _mm_add_ps(row[0],m.row[0]);
	row[1] = _mm_add_ps(row[1],m.row[1]);
	return *this;
}

inline
matrix2x2&  matrix2x2::operator-= (const matrix2x2& m)
{
	row[0] = _mm_sub_ps(row[0],m.row[0]);
	row[1] = _mm_sub_ps(row[1],m.row[1]);
	return *this;
}

inline
matrix2x2&	matrix2x2::operator*= (const matrix2x2& mb)
{
	row[0] = _mm_add_ps(
			_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(0,0,0,0)), mb.row[0]),
			_mm_mul_ps(_mm_shuffle_ps(row[0], row[0], _MM_SHUFFLE(1,1,1,1)), mb.row[1]));

	row[1] = _mm_add_ps(
			_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(0,0,0,0)), mb.row[0]),
			_mm_mul_ps(_mm_shuffle_ps(row[1], row[1], _MM_SHUFFLE(1,1,1,1)), mb.row[1]));
	return *this;
}

inline
matrix2x2   matrix2x2::operator * (const float f) const
{
	__m128 tmp = _mm_set1_ps ( f );
	return matrix2x2(_mm_mul_ps( row[0],tmp),_mm_mul_ps( row[1], tmp));
}

inline
matrix2x2&  matrix2x2::operator*= (const float f)
{
	__m128 tmp = _mm_set1_ps ( f );
	row[0] = _mm_mul_ps( row[0], tmp);
	row[1] = _mm_mul_ps( row[1], tmp);
	return *this;
}

inline
matrix2x2	matrix2x2::operator / (const float f) const
{
	__m128 tmp = _mm_set1_ps ( f );
	tmp = __invert_ps(tmp);
	return matrix2x2(_mm_mul_ps( row[0],tmp),_mm_mul_ps( row[1], tmp));
}

inline
matrix2x2&  matrix2x2::operator/= (const float f)
{
	__m128 tmp = __invert_ps(_mm_set1_ps ( f ));
	row[0] = _mm_mul_ps( row[0], tmp);
	row[1] = _mm_mul_ps( row[1], tmp);
	return *this;
}
inline
matrix2x2 operator * (const float f, const matrix2x2& m)
{
	__m128 tmp = _mm_set1_ps ( f );
	return matrix2x2(_mm_mul_ps( m.row[0],tmp),_mm_mul_ps( m.row[1], tmp));
}

//TODO: create an sse version
inline
matrix2x2&	matrix2x2::inverse()
{
	matrix2x2 inv(_22,-_12,-_21,_11);
	*this = inv/det(inv);
	return *this;
}

inline
matrix2x2&  matrix2x2::transpose()
{
	float t = _12;
	_12 = _21;
	_21 = t;
	return *this;
}

inline
matrix2x2	  inversed(const matrix2x2& m)
{
	matrix2x2 inv(m._22,-m._12,-m._21,m._11);
	return inv/det(inv);
}

inline
matrix2x2	  transposed(const matrix2x2& m)
{
	matrix2x2 op (m);
	op._12 	= op._21;
	op._21 	= m._12;
	return op;
}
//TODO: create an SSE version here
inline
float		  det(const matrix2x2& m)
{
	return m._11*m._22 - m._12*m._21;
}


}
#endif /* MATRIX2X2_HPP_ */

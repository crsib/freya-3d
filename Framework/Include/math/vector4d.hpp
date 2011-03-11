/*
 * vector4d.hpp
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 22, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef VECTOR4D_HPP_
#define VECTOR4D_HPP_

#include "math_internal.h"
#include "vector3d.hpp"

namespace math
{

//!vector4d provided for convenience only, as it is implemented almost the same as vector 3d
MATH_OBJECT_DECL class vector4d
{
public:
	union
	{
		__m128  xmm;
		struct
		{
			//! x coordinate
			float x;
			//! y coordinate
			float y;
			//! z coordinate
			float z;
			//! w coordinate
			float w;
		};
	};

	MATH_MEMORY_FUNCTIONS
	//!Default constructor
	/*!
	 * Sets x and y to zero
	 */
	vector4d()
	{
		xmm = _mm_setzero_ps();
		w = 1.0;
	}

	//!Copy constructor
	vector4d(const vector4d& v)
	{
		xmm = v.xmm;
	}

	//!Initialization costructor
	vector4d(const float x, const float y, const float z);
	vector4d(const float x, const float y, const float z, const float w);

	//! Making vector3d a homogeneous vector
	vector4d(const vector3d& v3d);
	//!Operator =
	vector4d& operator = (const vector4d& v);
	//!Unary + (does nothing)
	vector4d   operator + () const;

	//!Unary -
	vector4d	operator - () const;

	//!binary operator +
	vector4d	operator + (const vector4d& v) const;
	//! Binary -
	vector4d	operator - (const vector4d& v) const;
	//! Float multiply
	vector4d	operator * (const float f) const;
	//! Float division
	vector4d	operator / (const float f) const;
	//! dot product
	float       operator , (const vector4d& v) const;

	//! Some operators provided for convenience
	vector4d&	operator += (const vector4d& v);
	vector4d&   operator -= (const vector4d& v);
	vector4d&	operator *= (const float f);
	vector4d&   operator /= (const float f);

	//! Conversion operators
	operator float* ();
	operator const float* () const;

	// returns v3d(x/w,y/w,z/w) if w != 0 and vectors if infs otherwise (please note, that OpenGL behavior is a little different)
	operator vector3d	() const;
	//! Self-normalizing
	vector4d&	normalize ();

	//External operators and functions
	//! Magnitude (or absolute) value
	friend	float	abs(const vector4d& v);
	//! Square of magnitude
	friend  float	abs_sq(const vector4d& v);
	//! Normalized version of vector
	friend vector4d normalized(const vector4d& v);
	//! Output operator
	friend	std::ostream&	operator << (std::ostream& s,const math::vector4d& v);
	//! Float multiplication
	friend	vector4d		operator*   (const float f, const vector4d& v);

} MATH_OBJECT_END_DECL ;

}

//=========================Implementation======================================
namespace math
{
inline
vector4d::vector4d(const float _x, const float _y,const float _z)
{
	x = _x;
	y = _y;
	z = _z;
	w = 1.0;
}

inline
vector4d::vector4d(const float _x, const float _y,const float _z,const float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

inline
vector4d::vector4d(const vector3d& v)
{
	xmm = v.xmm;
	w = 1.0;
}

inline
vector4d::operator vector3d () const
{
	if( (*reinterpret_cast<const unsigned*>(&z)) & 0x7F7FFFFF) //Non-zero value (due to encoding of IEEE 874-2008 for binary32 floats) + denormal handling
	{
		__m128 tmp = _mm_shuffle_ps(xmm,xmm,_MM_SHUFFLE(3,3,3,3));
		tmp = __invert_ps ( tmp );
		vector3d o;
		o.xmm = _mm_mul_ps ( xmm,tmp );
		*(&o.x + 3) = 0.0;
		return o;
	}
	else
	{
		return vector2d(math::infinity,math::infinity);
	}
	return vector2d();
}

inline
vector4d& vector4d::operator = (const vector4d& v)
{
	xmm = v.xmm;
	return *this;
}

inline
vector4d
vector4d::operator + () const
{
	return vector4d(*this);
}

//!Unary -
inline
vector4d	vector4d::operator - () const
{
	vector4d o(*this);
	o.xmm = _mm_xor_ps(o.xmm,*reinterpret_cast<const __m128*>(_ps_sign_mask));
	return o;
}

inline vector4d normalized(const vector4d & v)
{
	math::vector4d o(v);
	__m128 tmp = _mm_mul_ps	( o.xmm,o.xmm );
	tmp  = _mm_hadd_ps_f 		( tmp,tmp );
	tmp  = _mm_hadd_ps_f 		( tmp,tmp );
	__m128 tmp1 = _mm_and_ps		( tmp,*reinterpret_cast<const __m128*>(_ps_norm_value_mask));
	int r = _mm_comineq_ss	( tmp1,*reinterpret_cast<const __m128*>(_ps_0));
	if(r)
	{
		tmp  = __rsqrt_ss		( tmp );
		tmp  = _mm_shuffle_ps	( tmp, tmp, _MM_SHUFFLE(0,0,0,0) );
		o.xmm	 = _mm_mul_ps 		( o.xmm, tmp );
	}
	return o;
}

inline
vector4d::operator float*()
{
	return &x;
}

inline vector4d & vector4d::normalize()
{
	__m128 tmp = _mm_mul_ps	( xmm,xmm );
	tmp  = _mm_hadd_ps_f 		( tmp,tmp );
	tmp  = _mm_hadd_ps_f 		( tmp,tmp );
	__m128 tmp1 = _mm_and_ps		( tmp,*reinterpret_cast<const __m128*>(_ps_norm_value_mask));
	int r = _mm_comineq_ss	( tmp1,*reinterpret_cast<const __m128*>(_ps_0));
	if(r)
	{
		tmp  = __rsqrt_ss		( tmp );
		tmp  = _mm_shuffle_ps	( tmp, tmp, _MM_SHUFFLE(0,0,0,0) );
		this->xmm	 = _mm_mul_ps 		( xmm, tmp );
	}
	return *this;
}

inline float abs_sq(const vector4d & v)
{
	float res;
	__m128 tmp = _mm_mul_ps(v.xmm,v.xmm);
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	_mm_store_ss (&res,tmp);
	return res;
}

inline float abs(const vector4d & v)
{
	float res;
	__m128 tmp = _mm_mul_ps(v.xmm,v.xmm);
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	tmp =  _mm_sqrt_ss( tmp);
	_mm_store_ss (&res,tmp);
	return res;
}

inline vector4d &
vector4d::operator *=(const float f)
{
	__m128 tmp = _mm_set1_ps ( f );
	xmm = _mm_mul_ps ( xmm, tmp );
	return *this;
}

inline vector4d &
vector4d::operator -=(const vector4d & v)
{
	xmm = _mm_sub_ps(xmm,v.xmm);
	return *this;
}

inline vector4d &
vector4d::operator /=(const float f)
{
	__m128 tmp = _mm_set1_ps ( f );
	tmp = __invert_ps ( tmp );
	xmm = _mm_mul_ps ( xmm, tmp );
	return *this;
}

inline vector4d
vector4d::operator /(const float f) const
{
	vector4d o;
	__m128 tmp = _mm_set1_ps ( f );
	tmp = __invert_ps ( tmp );
	o.xmm = _mm_mul_ps ( xmm, tmp );
	return o;
}

inline vector4d &
vector4d::operator +=(const vector4d & v)
{
	xmm = _mm_add_ps(xmm,v.xmm);
	return *this;
}

inline vector4d
vector4d::operator -(const vector4d & v) const
{
	vector4d o;
	o.xmm = _mm_sub_ps(xmm,v.xmm);
	return o;
}

inline vector4d
vector4d::operator +(const vector4d & v) const
{
	vector4d o;
	o.xmm = _mm_add_ps(xmm,v.xmm);
	return o;
}

inline vector4d
vector4d::operator *(const float f) const
{
	vector4d o;
	__m128 tmp = _mm_set1_ps ( f );
	o.xmm = _mm_mul_ps ( xmm, tmp );
	return o;
}

inline
vector4d::operator const float*() const
{
	return &x;
}

inline float
vector4d::operator ,(const vector4d & v) const
{
	float res;
	__m128 tmp = _mm_mul_ps(xmm,v.xmm);
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	_mm_store_ss (&res,tmp);
	return res;
}

inline
std::ostream&
operator << (std::ostream& s,const math::vector4d& v)
{
	return s << "( " << v.x << ", " << v.y << ", " << v.z << ", " << v.w << " )";
}

inline vector4d
operator *(const float f, const vector4d & v)
{
	vector4d o(v);
	__m128 tmp = _mm_set1_ps ( f );
	o.xmm = _mm_mul_ps ( o.xmm, tmp );
	return o;
}
}

#endif /* VECTOR4D_HPP_ */

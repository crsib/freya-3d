/*
 * vector3d.hpp
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 22, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

#include "math_internal.h"
#include "vector2d.hpp"

#include <LinearMath/btVector3.h>

namespace math
{

//!vector3d provided for convenience only, as it is implemented almost the same as vector 3d
MATH_OBJECT_DECL class vector3d
{
public:

	static const vector3d i;
	static const vector3d j;
	static const vector3d k;

	union
	{
		unsigned int _int[4]; //Needed for speeding up cross product
		__m128  xmm;
		struct
		{
			//! x coordinate
			float x;
			//! y coordinate
			float y;
			//! z coordinate
			float z;
		};
	};

	MATH_MEMORY_FUNCTIONS
	//!Default constructor
	/*!
	 * Sets x and y to zero
	 */
	vector3d()
	{
		xmm = _mm_setzero_ps();
	}

	vector3d(const btVector3& bvec)
	{
		xmm = bvec.mVec128;
	}

	vector3d(__m128 m)
	{
		xmm = m;
	}

	//!Copy constructor
	vector3d(const vector3d& v)
	{
		xmm = v.xmm;
	}

	//!Initialization costructor
	vector3d(const float x, const float y, const float z);
	//! Initialize as homogeneous vector from vector2d
	vector3d(const vector2d& v2d);
	//!Operator =
	vector3d& operator = (const vector3d& v);
	//!Unary + (does nothing)
	vector3d   operator + () const;

	//!Unary -
	vector3d	operator - () const;

	//!binary operator +
	vector3d	operator + (const vector3d& v) const;
	//! Binary -
	vector3d	operator - (const vector3d& v) const;
	//! Float multiply
	vector3d	operator * (const float f) const;
	//! Float division
	vector3d	operator / (const float f) const;
	//! Cross product (strictly defined only for 3D vectors. Defined as outer product for higher dimension, thus, defined only for vector3d)
	vector3d	operator * (const vector3d& v) const;
	//! dot product
	float       operator , (const vector3d& v) const;

	//! Some operators provided for convenience
	vector3d&	operator += (const vector3d& v);
	vector3d&   operator -= (const vector3d& v);
	vector3d&	operator *= (const float f);
	vector3d&   operator /= (const float f);

	//! Conversion operators
	operator float* ();
	operator const float* () const;
	operator btVector3() const;
	//! vector2d(x/z,y/z) if z ≠ 0, vector2d(math::inf,math::inf) otherwise
	operator vector2d	() const;
	//! Self-normalizing
	vector3d&	normalize ();

	//External operators and functions
	//! Magnitude (or absolute) value
	friend	float	abs(const vector3d& v);
	//! Square of magnitude
	friend  float	abs_sq(const vector3d& v);
	//! Normalized version of vector
	friend vector3d normalized(const vector3d& v);
	//! Output operator
	friend	std::ostream&	operator << (std::ostream& s,const math::vector3d& v);
	//! Float multiplication
	friend	vector3d		operator*   (const float f, const vector3d& v);

} MATH_OBJECT_END_DECL ;

}

//=========================Implementation======================================
namespace math
{
inline
vector3d::vector3d(const float _x, const float _y,const float _z)
{
	xmm = _mm_setzero_ps();
	x = _x;
	y = _y;
	z = _z;
}

inline
vector3d::vector3d(const math::vector2d& v)
{
	xmm = v.xmm;
	z   = math::unit;
}
inline
vector3d::operator vector2d () const
{
	if( (*reinterpret_cast<const unsigned*>(&z)) & 0x7F7FFFFF) //Non-zero value (due to encoding of IEEE 874-2008 for binary32 floats) + denormal handling
	{
		__m128 tmp = _mm_shuffle_ps(xmm,xmm,_MM_SHUFFLE(2,2,2,2));
		tmp = __invert_ps ( tmp );
		vector2d o;
		o.xmm = _mm_mul_ps ( xmm,tmp );
		memset(&o.x + 2, 0, 2*sizeof(float));
		return o;
	}
	else
	{
		return vector2d(math::infinity,math::infinity);
	}
	return vector2d();
}

inline
vector3d	vector3d::operator *(const math::vector3d& v) const
{
	vector3d o;
	__m128 t1 = _mm_shuffle_ps (v.xmm,xmm,_MM_SHUFFLE(3,0,2,2));
	__m128 t2 = _mm_shuffle_ps (xmm,v.xmm,_MM_SHUFFLE(3,1,0,1));
	__m128 t3 = _mm_mul_ps (t1,t2);
	t1 = _mm_shuffle_ps (xmm,v.xmm,_MM_SHUFFLE(3,0,2,2));
	t2 = _mm_shuffle_ps (v.xmm,xmm,_MM_SHUFFLE(3,1,0,1));
	t1 = _mm_mul_ps (t1,t2);
	o.xmm = _mm_sub_ps(t3,t1);
	o._int[1] = (o._int[1]  ^ 0x80000000);
	return o;
}

inline
vector3d& vector3d::operator = (const vector3d& v)
{
	xmm = v.xmm;
	return *this;
}

inline
vector3d
vector3d::operator + () const
{
	return vector3d(*this);
}

//!Unary -
inline
vector3d	vector3d::operator - () const
{
	vector3d o(*this);
	o.xmm = _mm_xor_ps(o.xmm,*reinterpret_cast<const __m128*>(_ps_sign_mask));
	return o;
}

inline vector3d normalized(const vector3d & v)
{
	math::vector3d o(v);
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
vector3d::operator float*()
{
	return &x;
}

inline
vector3d::operator btVector3 () const
{
	btVector3 vec;
	vec.mVec128 = xmm;
	return vec;
}

inline vector3d & vector3d::normalize()
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

inline float abs_sq(const vector3d & v)
{
	float res;
	__m128 tmp = _mm_mul_ps(v.xmm,v.xmm);
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	_mm_store_ss (&res,tmp);
	return res;
}

inline float abs(const vector3d & v)
{
	float res;
	__m128 tmp = _mm_mul_ps(v.xmm,v.xmm);
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	tmp =  _mm_sqrt_ss( tmp);
	_mm_store_ss (&res,tmp);
	return res;
}

inline vector3d &
vector3d::operator *=(const float f)
{
	__m128 tmp = _mm_set1_ps ( f );
	xmm = _mm_mul_ps ( xmm, tmp );
	return *this;
}

inline vector3d &
vector3d::operator -=(const vector3d & v)
{
	xmm = _mm_sub_ps(xmm,v.xmm);
	return *this;
}

inline vector3d &
vector3d::operator /=(const float f)
{
	__m128 tmp = _mm_set1_ps ( f );
	tmp = __invert_ps ( tmp );
	xmm = _mm_mul_ps ( xmm, tmp );
	return *this;
}

inline vector3d
vector3d::operator /(const float f) const
{
	vector3d o;
	__m128 tmp = _mm_set1_ps ( f );
	tmp = __invert_ps ( tmp );
	o.xmm = _mm_mul_ps ( xmm, tmp );
	return o;
}

inline vector3d &
vector3d::operator +=(const vector3d & v)
{
	xmm = _mm_add_ps(xmm,v.xmm);
	return *this;
}

inline vector3d
vector3d::operator -(const vector3d & v) const
{
	vector3d o;
	o.xmm = _mm_sub_ps(xmm,v.xmm);
	return o;
}

inline vector3d
vector3d::operator +(const vector3d & v) const
{
	vector3d o;
	o.xmm = _mm_add_ps(xmm,v.xmm);
	return o;
}

inline vector3d
vector3d::operator *(const float f) const
{
	vector3d o;
	__m128 tmp = _mm_set1_ps ( f );
	o.xmm = _mm_mul_ps ( xmm, tmp );
	return o;
}

inline
vector3d::operator const float*() const
{
	return &x;
}

inline float
vector3d::operator ,(const vector3d & v) const
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
operator << (std::ostream& s,const math::vector3d& v)
{
	return s << "( " << v.x << ", " << v.y << ", " << v.z << " )";
}

inline vector3d
operator *(const float f, const vector3d & v)
{
	vector3d o(v);
	__m128 tmp = _mm_set1_ps ( f );
	o.xmm = _mm_mul_ps ( o.xmm, tmp );
	return o;
}
}


#endif /* VECTOR3D_HPP_ */

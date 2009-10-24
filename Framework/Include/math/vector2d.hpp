/*
 * vector2d.h
 *
 *  Created on: Oct 21, 2009
 *      Author: crsib
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include "math_internal.h"


namespace math
{

//!vector2d provided for convenience only, as it is implemented almost the same as vector 3d
MATH_OBJECT_DECL class vector2d
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
		};
	};

	MATH_MEMORY_FUNCTIONS
	//!Default constructor
	/*!
	 * Sets x and y to zero
	 */
	vector2d()
	{
		xmm = _mm_setzero_ps();
	}

	//!Copy constructor
	vector2d(const vector2d& v)
	{
		xmm = v.xmm;
	}

	//!Initialization costructor
	vector2d(const float x, const float y);
	//!Operator =
	vector2d& operator = (const vector2d& v);
	//!Unary + (does nothing)
	vector2d   operator + () const;

	//!Unary -
	vector2d	operator - () const;

	//!binary operator +
	vector2d	operator + (const vector2d& v) const;
	//! Binary -
	vector2d	operator - (const vector2d& v) const;
	//! Float multiply
	vector2d	operator * (const float f) const;
	//! Float division
	vector2d	operator / (const float f) const;
	//! dot product
	float       operator , (const vector2d& v) const;

	//! Some operators provided for convenience
	vector2d&	operator += (const vector2d& v);
	vector2d&   operator -= (const vector2d& v);
	vector2d&	operator *= (const float f);
	vector2d&   operator /= (const float f);

	//! Conversion operators
	operator float* ();
	operator const float* () const;

	//! Self-normalizing
	vector2d&	normalize ();

	//External operators and functions
	//! Magnitude (or absolute) value
	friend	float	abs(const vector2d& v);
	//! Square of magnitude
	friend  float	abs_sq(const vector2d& v);
	//! Normalized version of vector
	friend vector2d normalized(const vector2d& v);
	//! Output operator
	friend	std::ostream&	operator << (std::ostream& s,const math::vector2d& v);
	//! Float multiplication
	friend	vector2d		operator*   (const float f, const vector2d& v);

} MATH_OBJECT_END_DECL ;

}

//=========================Implementation======================================
namespace math
{
inline
vector2d::vector2d(const float _x, const float _y)
{
	xmm = _mm_setzero_ps();
	x = _x;
	y = _y;
}
inline
vector2d& vector2d::operator = (const vector2d& v)
{
	xmm = v.xmm;
	return *this;
}

inline
vector2d
vector2d::operator + () const
{
	return vector2d(*this);
}

//!Unary -
inline
vector2d	vector2d::operator - () const
{
	vector2d o(*this);
	o.xmm = _mm_xor_ps(o.xmm,*reinterpret_cast<const __m128*>(_ps_sign_mask));
	return o;
}

inline vector2d normalized(const vector2d & v)
{
	math::vector2d o(v);
	__m128 tmp = _mm_mul_ps	( o.xmm,o.xmm );
	tmp  = _mm_hadd_ps 		( tmp,tmp );
	tmp  = _mm_hadd_ps 		( tmp,tmp );
	__m128 tmp1 = _mm_and_ps( tmp,*reinterpret_cast<const __m128*>(_ps_norm_value_mask));
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
vector2d::operator float*()
{
	return &x;
}

inline vector2d & vector2d::normalize()
{
	__m128 tmp = _mm_mul_ps	( xmm,xmm );
	tmp  = _mm_hadd_ps 		( tmp,tmp );
	tmp  = _mm_hadd_ps 		( tmp,tmp );
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

inline float abs_sq(const vector2d & v)
{
	float res;
	__m128 tmp = _mm_mul_ps(v.xmm,v.xmm);
	tmp  = _mm_hadd_ps ( tmp,tmp );
	tmp  = _mm_hadd_ps ( tmp,tmp );
	_mm_store_ss (&res,tmp);
	return res;
}

inline float abs(const vector2d & v)
{
	float res;
	__m128 tmp = _mm_mul_ps(v.xmm,v.xmm);
	tmp  = _mm_hadd_ps ( tmp,tmp );
	tmp  = _mm_hadd_ps ( tmp,tmp );
	tmp =  _mm_sqrt_ss( tmp);
	_mm_store_ss (&res,tmp);
	return res;
}

inline vector2d &
vector2d::operator *=(const float f)
{
	__m128 tmp = _mm_set1_ps ( f );
	xmm = _mm_mul_ps ( xmm, tmp );
	return *this;
}

inline vector2d &
vector2d::operator -=(const vector2d & v)
{
	xmm = _mm_sub_ps(xmm,v.xmm);
	return *this;
}

inline vector2d &
vector2d::operator /=(const float f)
{
	__m128 tmp = _mm_set1_ps ( f );
	tmp = __invert_ps ( tmp );
	xmm = _mm_mul_ps ( xmm, tmp );
	return *this;
}

inline vector2d
vector2d::operator /(const float f) const
{
	vector2d o;
	__m128 tmp = _mm_set1_ps ( f );
	tmp = __invert_ps ( tmp );
	o.xmm = _mm_mul_ps ( xmm, tmp );
	return o;
}

inline vector2d &
vector2d::operator +=(const vector2d & v)
{
	xmm = _mm_add_ps(xmm,v.xmm);
	return *this;
}

inline vector2d
vector2d::operator -(const vector2d & v) const
{
	vector2d o;
	o.xmm = _mm_sub_ps(xmm,v.xmm);
	return o;
}

inline vector2d
vector2d::operator +(const vector2d & v) const
{
	vector2d o;
	o.xmm = _mm_add_ps(xmm,v.xmm);
	return o;
}

inline vector2d
vector2d::operator *(const float f) const
{
	vector2d o;
	__m128 tmp = _mm_set1_ps ( f );
	o.xmm = _mm_mul_ps ( xmm, tmp );
	return o;
}

inline
vector2d::operator const float*() const
{
	return &x;
}

inline float
vector2d::operator ,(const vector2d & v) const
{
	float res;
	__m128 tmp = _mm_mul_ps(xmm,v.xmm);
	tmp  = _mm_hadd_ps ( tmp,tmp );
	tmp  = _mm_hadd_ps ( tmp,tmp );
	_mm_store_ss (&res,tmp);
	return res;
}

inline
std::ostream&
operator << (std::ostream& s,const math::vector2d& v)
{
	return s << "( " << v.x << ", " << v.y << " )";
}

inline vector2d
operator *(const float f, const vector2d & v)
{
	vector2d o(v);
	__m128 tmp = _mm_set1_ps ( f );
	o.xmm = _mm_mul_ps ( o.xmm, tmp );
	return o;
}
}
#endif /* VECTOR2D_H_ */

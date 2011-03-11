/*
 * quaternion.hpp
 *	This file is part of Freya 3D engine. For licensing information
 *  from LICENCE file 
 *  Created on: Oct 22, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef QUATERNION_HPP_
#define QUATERNION_HPP_

#include "math_internal.h"
#include "vector3d.hpp"

namespace math
{

MATH_OBJECT_DECL	class quaternion
{
public:
	MATH_MEMORY_FUNCTIONS

	union
	{
		struct
		{
			float x,y,z,w;
		};
		__m128		xmm;
	};

	quaternion();
	quaternion(__m128 m);
	quaternion(const float x,const float y,const float z,const float w);
	quaternion(const float w, const vector3d& vec);
	quaternion(const vector3d& v);

	quaternion(const quaternion& q);
	quaternion& operator = (const quaternion& q);

	static
	quaternion	rotationQuat(const float angle, const vector3d& axis);

	quaternion& normalize();
	quaternion&	inverse();
	quaternion& conjugate();

	vector3d	rotate(const vector3d& v) const;

	friend
	quaternion  inversed(const quaternion& q);

	friend
	quaternion  conjugated(const quaternion& q);

	friend
	float 		abs(const quaternion& q);

	friend
	float 		abs_sq(const quaternion& q);

	friend
	quaternion	normalized(const quaternion& q);

	quaternion	operator + () const;
	quaternion  operator - () const;

	quaternion  operator + (const quaternion& q) const;
	quaternion  operator - (const quaternion& q) const;

	quaternion  operator * (const quaternion& q) const;
	quaternion 	operator * (const vector3d& v) const;

	operator    vector3d() const;
	operator	float*();
	operator	const float* () const;

	quaternion&	operator+= (const quaternion& q);
	quaternion&	operator-= (const quaternion& q);

	quaternion&	operator*= (const quaternion& q);
	quaternion&	operator*= (const vector3d& v);

	quaternion  operator * (const float f) const;
	quaternion  operator / (const float f) const;

	quaternion&	operator*= (const float f);
	quaternion& operator/= (const float f);

	friend
	quaternion operator * (const float f, const quaternion& q);

	friend
	std::ostream& operator << (std::ostream& s,const quaternion& q);

} MATH_OBJECT_END_DECL;

} // namespace math
//========================Implementation=====================================================
namespace math
{
inline
quaternion::quaternion(__m128 m)
{
	xmm = m;
}

inline
quaternion::quaternion()
{
	xmm = _mm_setzero_ps();
}

inline
quaternion::quaternion(const float _x,const float _y,const float _z,const float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

inline
quaternion::quaternion(const float _w, const vector3d& vec)
{
	xmm = vec.xmm;
	w = _w;
}

inline
quaternion::quaternion(const vector3d& v)
{
	xmm = v.xmm;
}

inline
quaternion::quaternion(const quaternion& q)
{
	xmm = q.xmm;
}

inline
quaternion& quaternion::operator = (const quaternion& q)
{
	xmm = q.xmm;
	return *this;
}

inline
quaternion	quaternion::rotationQuat(const float angle, const vector3d& axis)
{
	quaternion q;
	float s,c;
	math::sincos(angle*0.5f,&s,&c);
	q.xmm = (normalized(axis)*s).xmm;
	q.w = c;
	return q;
}

inline
quaternion& quaternion::normalize()
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

inline
quaternion&	quaternion::inverse()
{
	xmm = _mm_xor_ps(xmm,*reinterpret_cast<const __m128*>(_ps_sign_mask));
	w *= -1.0;
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

inline
quaternion& quaternion::conjugate()
{
	xmm = _mm_xor_ps(xmm,*reinterpret_cast<const __m128*>(_ps_sign_mask));
	w *= -1.0;
	return *this;
}

inline
quaternion  inversed(const quaternion& q)
{
	return quaternion(q).inverse();
}

inline
quaternion  conjugated(const quaternion& q)
{
	return quaternion(q.w,-vector3d(q.xmm));
}

inline
float 		abs(const quaternion& q)
{
	float res;
	__m128 tmp = _mm_mul_ps(q.xmm,q.xmm);
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	tmp =  _mm_sqrt_ss( tmp);
	_mm_store_ss (&res,tmp);
	return res;
}

inline
float 		abs_sq(const quaternion& q)
{
	float res;
	__m128 tmp = _mm_mul_ps(q.xmm,q.xmm);
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	tmp  = _mm_hadd_ps_f ( tmp,tmp );
	_mm_store_ss (&res,tmp);
	return res;
}

inline
quaternion	normalized(const quaternion& _q)
{
	quaternion q(_q);
	__m128 tmp = _mm_mul_ps	( q.xmm,q.xmm );
	tmp  = _mm_hadd_ps_f 		( tmp,tmp );
	tmp  = _mm_hadd_ps_f 		( tmp,tmp );
	__m128 tmp1 = _mm_and_ps		( tmp,*reinterpret_cast<const __m128*>(_ps_norm_value_mask));
	int r = _mm_comineq_ss	( tmp1,*reinterpret_cast<const __m128*>(_ps_0));
	if(r)
	{
		tmp  = __rsqrt_ss		( tmp );
		tmp  = _mm_shuffle_ps	( tmp, tmp, _MM_SHUFFLE(0,0,0,0) );
		q.xmm	 = _mm_mul_ps 		( q.xmm, tmp );
	}
	return q;
}

inline
quaternion	quaternion::operator + () const
{
	return *this;
}

inline
quaternion  quaternion::operator - () const
{
	return quaternion (_mm_xor_ps(xmm,*reinterpret_cast<const __m128*>(_ps_sign_mask)));
}

inline
quaternion  quaternion::operator + (const quaternion& q) const
{
	return quaternion(_mm_add_ps(xmm,q.xmm));
}

inline
quaternion  quaternion::operator - (const quaternion& q) const
{
	return quaternion(_mm_sub_ps(xmm,q.xmm));
}

inline
quaternion  quaternion::operator * (const quaternion& q) const
{
	vector3d v1 = *this;
	vector3d v2 = q;
	return quaternion(w*q.w - (v1,v2), v1*v2 + w*v2 + q.w*v1);
}

inline
quaternion 	quaternion::operator * (const vector3d& v) const
{
	return *this * quaternion(v);
}

inline
quaternion::operator    vector3d() const
{
	vector3d v(xmm);
	v._int[3] = 0; //Correct due to iEEE754-2008
	return v;
}

inline
quaternion::operator	float*()
{
	return &x;
}

inline
quaternion::operator	const float* () const
{
	return &x;
}

inline
quaternion&	quaternion::operator+= (const quaternion& q)
{
	xmm = _mm_add_ps(xmm,q.xmm);
	return *this;
}

inline
quaternion&	quaternion::operator-= (const quaternion& q)
{
	xmm = _mm_sub_ps(xmm,q.xmm);
	return *this;
}

inline
quaternion&	quaternion::operator*= (const quaternion& q)
{
	vector3d v1 = *this;
	vector3d v2 = q;
	return (*this = quaternion(w*q.w - (v1,v2), v1*v2 + w*v2 + q.w*v1));
}

inline
quaternion&	quaternion::operator*= (const vector3d& v2)
{
	vector3d v1 = *this;
	return (*this = quaternion( - (v1,v2), v1*v2 + w*v2));
}

inline
quaternion  quaternion::operator * (const float f) const
{
	return quaternion(_mm_mul_ps(xmm,_mm_set1_ps(f)));
}

inline
quaternion  quaternion::operator / (const float f) const
{
	return quaternion(_mm_mul_ps(xmm,__invert_ps(_mm_set1_ps(f))));
}

inline
quaternion&	quaternion::operator*= (const float f)
{
	xmm = _mm_mul_ps(xmm,_mm_set1_ps(f));
	return *this;
}

inline
quaternion& quaternion::operator/= (const float f)
{
	xmm = _mm_mul_ps(xmm,__invert_ps(_mm_set1_ps(f)));
	return *this;
}

inline
quaternion operator * (const float f, const quaternion& q)
{
	return quaternion(_mm_mul_ps(q.xmm,_mm_set1_ps(f)));
}

inline
std::ostream& operator << (std::ostream& s,const quaternion& q)
{
	return s << "( " << q.w << ", ( " << q.x << ", " << q.y << ", " << q.z << " ))";
}

inline
vector3d	quaternion::rotate(const vector3d& v) const
{
	quaternion rt(xmm);
	rt.normalize();
	return rt*v*conjugated(rt);
}

}

#endif /* QUATERNION_HPP_ */

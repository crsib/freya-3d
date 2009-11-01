/*
 * math_internal.h
 *
 *  Created on: Oct 21, 2009
 *      Author: crsib
 */

#ifndef MATH_INTERNAL_H_
#define MATH_INTERNAL_H_

#include <ostream>

#include "core/memory/MemoryPools.h"
#include "internal.h"
#include "constants.h"
#include "math_lookup_tables.h"

#include <xmmintrin.h>
#include <emmintrin.h>

#ifdef _MSC_VER
#	pragma warning(disable:4305) 
#	pragma warning(disable:4244) 
#endif

#ifdef __SSE3__
#include <pmmintrin.h>
#endif

#ifdef _MSC_VER
#define MATH_OBJECT_DECL __declspec(align(16))
#define MATH_OBJECT_END_DECL
#elif defined(__GNUC__)
#define MATH_OBJECT_DECL
#define MATH_OBJECT_END_DECL __attribute__ ((aligned(16)))
#endif

#ifdef _USE_FASTER_MATH
#define __invert_ps(v) _mm_rcp_ps(v)
#define __rsqrt_ps(v)  _mm_rsqrt_ps(v)
#define __invert_ss(v) _mm_rcp_ss(v)
#define __rsqrt_ss(v)   _mm_rsqrt_ss(v)
#else
#define __invert_ps(v) _mm_div_ps(_mm_set1_ps(1.0),v)
#define __rsqrt_ps(v)  _mm_div_ps(_mm_set1_ps(1.0),_mm_sqrt_ss(v))
#define __invert_ss(v) _mm_div_ss(_mm_set1_ps(1.0),v)
#define __rsqrt_ss(v)  _mm_div_ss(_mm_set1_ps(1.0),_mm_sqrt_ss(v))
#endif



#ifdef _FREYA_SHARED_PLUGIN
namespace core
{
namespace memory
{
	extern void* (*Allocate)(size_t,unsigned);
	extern void  (*Free)(void*,unsigned);
}
}
#else
namespace core
{
namespace memory
{
	EXPORT void* Allocate(size_t,unsigned);
	EXPORT void  Free(void*,unsigned);
}
}
#endif

#define MATH_MEMORY_FUNCTIONS \
		static void* operator new(size_t sz)\
		{\
			return core::memory::Allocate(sz,core::memory::MATH_POOL);\
		}\
\
		static void  operator delete(void* p)\
		{\
			core::memory::Free(p,core::memory::MATH_POOL);\
		}\
\
		static void* operator new[](size_t sz)\
		{\
			return core::memory::Allocate(sz,core::memory::MATH_POOL);\
		}\
\
		static void  operator delete[](void* p)\
		{\
			core::memory::Free(p,core::memory::MATH_POOL);\
		}\


//==================================================Constants===========================================================================================
#ifdef _MSC_VER
#define _PS_CONST(Name, Val) \
		static const __declspec(align(16)) float _ps_##Name[4] = { Val, Val, Val, Val }

#define _PS_EXTERN_CONST(Name, Val) \
		static const __declspec(align(16)) float _ps_##Name[4] = { Val, Val, Val, Val }

#define _PS_CONST4(Name, Val0, Val1, Val2, Val3) \
		static const __declspec(align(16)) float _ps_##Name[4] = { Val0, Val1, Val2, Val3 }

#define _PS_CONST_TYPE(Name, Type, Val) \
		static const __declspec(align(16)) Type _ps_##Name[4] = { Val, Val, Val, Val }; \

#define _PS_EXTERN_CONST_TYPE(Name, Type, Val) \
		static const __declspec(align(16)) Type _ps_##Name[4] = { Val, Val, Val, Val }; \

#define _EPI32_CONST(Name, Val) \
		static const __declspec(align(16)) __int32 _epi32_##Name[4] = { Val, Val, Val, Val }

#elif defined(__GNUC__)

#define _PS_CONST(Name, Val) \
		static const float _ps_##Name[4] __attribute__ ((aligned(16))) = { Val, Val, Val, Val }

#define _PS_EXTERN_CONST(Name, Val) \
		static const  float _ps_##Name[4] = { Val, Val, Val, Val }

#define _PS_CONST4(Name, Val0, Val1, Val2, Val3) \
		static const  float _ps_##Name[4] __attribute__ ((aligned(16))) = { Val0, Val1, Val2, Val3 }

#define _PS_CONST_TYPE(Name, Type, Val) \
		static const  Type _ps_##Name[4]  __attribute__ ((aligned(16))) = { Val, Val, Val, Val }; \

#define _PS_EXTERN_CONST_TYPE(Name, Type, Val) \
		static const Type _ps_##Name[4] __attribute__ ((aligned(16))) = { Val, Val, Val, Val }; \

#define _EPI32_CONST(Name, Val) \
		static const  __int32 _epi32_##Name[4] __attribute__ ((aligned(16))) = { Val, Val, Val, Val }
#endif

namespace math
{

#ifdef _MSC_VER
__declspec(align(16))
		union float4
		{
	__m128 xmm;
	float  val[4];
		};
#elif defined(__GNUC__)
union float4
{
	__m128 xmm;
	float  val[4];
} __attribute__ ((aligned(16)));
#else
#	error "This compiler seems to be not supported"
#endif

#ifdef _MSC_VER
__declspec(align(16)) union int4
		{
	__m128 xmm;
	float  val[4];
		};
#elif defined(__GNUC__)
typedef int32_t __int32;
union int4
{
	__m128i 	xmm;
	__int32	 	val[4];
} __attribute__ ((aligned(16)));
#else
#	error "This compiler seems to be not supported"
#endif

_PS_EXTERN_CONST(0, 0.0f);
_PS_EXTERN_CONST(1, 1.0f);
_PS_EXTERN_CONST(m1, -1.0f);
_PS_EXTERN_CONST(0p5, 0.5f);
_PS_EXTERN_CONST(1p5, 1.5f);
_PS_EXTERN_CONST(pi, (float)pi);
_PS_EXTERN_CONST(pi_o_2, (float)(pi / 2.0));
_PS_EXTERN_CONST(2_o_pi, (float)(2.0 / pi));
_PS_EXTERN_CONST(pi_o_4, (float)(pi / 4.0));
_PS_EXTERN_CONST(4_o_pi, (float)(4.0 / pi));
_PS_EXTERN_CONST_TYPE(sign_mask, __int32, 0x80000000);
_PS_EXTERN_CONST_TYPE(inv_sign_mask, __int32, ~0x80000000);
_PS_EXTERN_CONST_TYPE(min_norm_pos, __int32, 0x00800000);
_PS_EXTERN_CONST_TYPE(mant_mask, __int32, 0x7f800000);
_PS_EXTERN_CONST_TYPE(inv_mant_mask, __int32, ~0x7f800000);
_PS_EXTERN_CONST_TYPE(norm_value_mask, __int32, 0x7F7FFFFF);

_EPI32_CONST(1, 1);
_EPI32_CONST(2, 2);
_EPI32_CONST(7, 7);
_EPI32_CONST(0x7f, 0x7f);
_EPI32_CONST(0xff, 0xff);
}

#ifndef __SSE3__

inline
__m128 _mm_hadd_ps( __m128& a, __m128& b)
{
   __m128 tempA = _mm_shuffle_ps(a,b, _MM_SHUFFLE(2,0,2,0));
   __m128 tempB = _mm_shuffle_ps(a,b, _MM_SHUFFLE(3,1,3,1));
   return _mm_add_ps( tempB, tempA);
}
#endif

//==================== Implementation =====================================================================
namespace math
{

union bin_float
{
	float f;
	unsigned i;
};

inline
float abs(const float scalar) {
	bin_float bf = {scalar};
	if(bf.i & 0x80000000)
		bf.i ^= 0x80000000;
	return bf.f;
}

inline float sqrt(float _)
{
	__m128 xmm0 = _mm_load_ss(&_);
	xmm0 = _mm_sqrt_ss(xmm0);
	_mm_store_ss(&_,xmm0);
	return _;
}

inline float4		  sqrt(float4& _)
{
	__m128 xmm0 = _mm_load_ps(_.val);
	xmm0 = _mm_sqrt_ps(xmm0);
	_mm_store_ps(_.val,xmm0);
	return _;
}

inline float4		  sqrt(float _1,float _2, float _3, float _4)
{
	float4 _ = {{_1,_2,_3,_4}};
	__m128 xmm0 = _mm_load_ps(_.val);
	xmm0 = _mm_sqrt_ps(xmm0);
	_mm_store_ps(_.val,xmm0);
	return _;
}
//============================ Output operator =======================================================================

inline std::ostream& operator << (std::ostream& s,const float4& _)
{
	return s << "( " <<_.val[0] << ", " << _.val[1] << ", " << _.val[2] << ", " << _.val[3] << " )";
}


inline std::ostream& operator << (std::ostream& s,const int4& _)
{
	return s << "( " <<_.val[0] << ", " << _.val[1] << ", " << _.val[2] << ", " << _.val[3] << " )";
}

//============================= floor functions ======================================================================
inline float floor(float _)
{
	__m128  xmm0	= _mm_load_ss			( &_ );
	int		val   	= _mm_cvttss_si32		( xmm0 );
	return (float)val;
}

inline float4 floor(float4& _)
{
	__m128	xmm0	= _mm_load_ps			( _.val );
	__m128i	xmm1 	= _mm_cvttps_epi32		( xmm0	);
	xmm0	= _mm_cvtepi32_ps		( xmm1	);
	_mm_store_ps			( _.val, xmm0 );
	return _;
}

inline float4 floor(float _1,float _2, float _3, float _4)
{
	float4	_		= {{_1,_2,_3,_4}};
	__m128	xmm0	= _mm_load_ps			( _.val );
	__m128i	xmm1 	= _mm_cvttps_epi32		( xmm0	);
	xmm0	= _mm_cvtepi32_ps		( xmm1	);
	_mm_store_ps			( _.val, xmm0 );
	return _;
}

//============================= rcp functions =========================================================================

inline float rcp(float _)
{
	__m128	xmm0	= _mm_load_ss			( &_ );
	xmm0	= __invert_ss			( xmm0 );
	_mm_store_ss			( &_, xmm0 );
	return _;
}

inline float4 rcp(float4& _)
{
	__m128	xmm0	= _mm_load_ps			( _.val );
	xmm0	= __invert_ps			( xmm0 );
	_mm_store_ps			( _.val, xmm0 );
	return _;
}

inline float4 rcp(float _1,float _2, float _3, float _4)
{
	float4	_		= {{_1,_2,_3,_4}};
	__m128	xmm0	= _mm_load_ps			( _.val );
	xmm0	= __invert_ps			( xmm0 );
	_mm_store_ps			( _.val, xmm0 );
	return _;
}

inline float rcp_sqrt(float _)
{
	__m128	xmm0	= _mm_load_ss			( &_ );
	xmm0	= __rsqrt_ss			( xmm0 );
	_mm_store_ss			( &_, xmm0 );
	return _;
}

inline float4 rcp_sqrt(float4& _)
{
	__m128	xmm0	= _mm_load_ps			( _.val );
	xmm0	= __rsqrt_ps			( xmm0 );
	_mm_store_ps			( _.val, xmm0 );
	return _;
}

inline float4 rcp_sqrt(float _1,float _2, float _3, float _4)
{
	float4	_		= {{_1,_2,_3,_4}};
	__m128	xmm0	= _mm_load_ps			( _.val );
	xmm0	= __rsqrt_ps			( xmm0 );
	_mm_store_ps			( _.val, xmm0 );
	return _;
}

//! __/_
inline float4 rcp_mull(float4& __,float4& _)
{
	__m128	xmm0	= _mm_load_ps			( _.val );
	xmm0	= __invert_ps			( xmm0 );
	__m128  xmm1	= _mm_load_ps			( __.val );
	xmm0	= _mm_mul_ps			( xmm0, xmm1 );
	_mm_store_ps			( _.val, xmm0 );
	return _;
}
//! __/(_)^0.5
inline float4 rcp_sqrt_mull(float4& __,float4& _)
{
	__m128	xmm0	= _mm_load_ps			( _.val );
	xmm0	= __rsqrt_ps			( xmm0 );
	__m128  xmm1	= _mm_load_ps			( __.val );
	xmm0	= _mm_mul_ps			( xmm0, xmm1 );
	_mm_store_ps			( _.val, xmm0 );
	return _;
}

static const float _2_pi = 6.283185307179586476925;
static const float _2_pi_m1 = 1.0 / _2_pi;
static const float pi_m1 	= 1.0 / pi;

//static const float4& szero = {0.0,0.0,0.0,0.0};
static const float  pi_s	= (float) math::__internal::sub_divisions / pi;
//static const float  m_pi	= -pi;
inline float sin(float _)
{
	//std::cout << "sin ( " << _ << " ) " << std::endl;
	//First of all, convert _ to 0,2*PI range
	__m128 xmm7  	= _mm_xor_ps (xmm7,xmm7);// 			( zero.val );
	__m128 xmm8  	= _mm_load_ss 			( &_2_pi );
	__m128  xmm1	= _mm_load_ss			( &_ );
	loop:

	__m128	xmm5	= _mm_load_ss			( &_2_pi_m1 );
	xmm5	= _mm_mul_ss			( xmm1,xmm5 );
	int		n		= _mm_cvttss_si32		( xmm5 );

	xmm5	= _mm_cvtsi32_ss		( xmm1, n );
	__m128  xmm6	= _mm_load_ss			( &_2_pi );
	xmm5	= _mm_mul_ss			( xmm5, xmm6 );

	xmm1	= _mm_sub_ss			( xmm1, xmm5 );

	int		r1		= _mm_comilt_ss			( xmm1, xmm7 );
	if(r1)
	{
		//float4&	mmm; mmm.xmm = xmm1;
		xmm6	= _mm_load_ss			( &_2_pi );
		//std::cout << "repeating - pass " << mmm << " n " << n << std::endl;
		xmm1 = _mm_add_ss					(xmm1,xmm6);
		r1		= _mm_comilt_ss			( xmm1, xmm7 );
		if(r1)
			goto loop;
	}
	r1		= _mm_comigt_ss			( xmm1, xmm8 );
	if(r1)
	{
		//float4&	mmm; mmm.xmm = xmm1;
		//std::cout << "repeating + pass " << mmm << " n " << n << std::endl;
		goto loop;
	}

	__m128	xmm0	= _mm_load_ss			( &pi_s ); //xmm0 -> (0,0,0,subdivisions / pi)
	xmm0	= _mm_mul_ss			( xmm0, xmm1 ); //so as this one (0,0,0,x * sd / pi )
	n   	= _mm_cvttss_si32		( xmm0 );

	//Now, calculate sine using table
	__m128	xmm2	= _mm_load_ss			( math::__internal::sin_table + n );
	__m128	xmm3	= _mm_load_ss			( math::__internal::sin_table + n + 1 );
	__m128  xmm4	= _mm_xor_ps (xmm4,xmm4);//_mm_load_ss			( zero.val );
	xmm4	= _mm_cvtsi32_ss		( xmm4, n );
	//Now, compute xmm0 - xmm4 -> xmm0
	xmm0	= _mm_sub_ss			( xmm0,xmm4 );
	// xmm3 = xmm3 - xmm2
	xmm3	= _mm_sub_ss			( xmm3,xmm2 );
	// xmm0 = xmm0*xmm3
	xmm0	= _mm_mul_ss			( xmm0,xmm3 );
	// xmm0 = xmm2 + xmm0
	xmm0	= _mm_add_ss			( xmm0,xmm2 );
	_mm_store_ss			( &_,  xmm0 );
	return _;
}

inline float cos(float _)
{
	//__m128 xmm7  	= _mm_load_ss 			( zero.val );
	__m128	 xmm7	= _mm_xor_ps			(xmm7,xmm7);
	__m128 xmm8  	= _mm_load_ss 			( &_2_pi );
	__m128  xmm1	= _mm_load_ss			( &_ );
	loop:

	__m128	xmm5	= _mm_load_ss			( &_2_pi_m1 );
	xmm5	= _mm_mul_ss			( xmm1,xmm5 );
	int		n		= _mm_cvttss_si32		( xmm5 );

	xmm5	= _mm_cvtsi32_ss		( xmm1, n );
	__m128  xmm6	= _mm_load_ss			( &_2_pi );
	xmm5	= _mm_mul_ss			( xmm5, xmm6 );

	xmm1	= _mm_sub_ss			( xmm1, xmm5 );

	int		r1		= _mm_comilt_ss			( xmm1, xmm7 );
	if(r1)
	{
		//float4&	mmm; mmm.xmm = xmm1;
		xmm6	= _mm_load_ss			( &_2_pi );
		//std::cout << "repeating - pass " << mmm << " n " << n << std::endl;
		xmm1 = _mm_add_ss					(xmm1,xmm6);
		goto loop;
	}
	r1		= _mm_comigt_ss			( xmm1, xmm8 );
	if(r1)
	{
		//float4&	mmm; mmm.xmm = xmm1;
		//std::cout << "repeating + pass " << mmm << " n " << n << std::endl;
		goto loop;
	}

	__m128	xmm0	= _mm_load_ss			( &pi_s ); //xmm0 -> (0,0,0,subdivisions / pi)
	xmm0	= _mm_mul_ss			( xmm0, xmm1 ); //so as this one (0,0,0,x * sd / pi )
	n   	= _mm_cvttss_si32		( xmm0 );

	//Now, calculate sine using table
	__m128	xmm2	= _mm_load_ss			( math::__internal::cos_table + n );
	__m128	xmm3	= _mm_load_ss			( math::__internal::cos_table + n + 1 );
	//__m128  xmm4	= _mm_load_ss			( zero.val );
	__m128  xmm4	= _mm_xor_ps			( xmm4,xmm4 );
	xmm4	= _mm_cvtsi32_ss		( xmm4, n );
	//Now, compute xmm0 - xmm4 -> xmm0
	xmm0	= _mm_sub_ss			( xmm0,xmm4 );
	// xmm3 = xmm3 - xmm2
	xmm3	= _mm_sub_ss			( xmm3,xmm2 );
	// xmm0 = xmm0*xmm3
	xmm0	= _mm_mul_ss			( xmm0,xmm3 );
	// xmm0 = xmm2 + xmm0
	xmm0	= _mm_add_ss			( xmm0,xmm2 );
	_mm_store_ss			( &_,  xmm0 );
	return _;
}
//! Correctness of value is not explicitely tested
inline float acos(float _)
{
	__m128  xmm1	= _mm_load_ss			( &_ );

	__m128	xmm0	= _mm_cvtsi32_ss		( xmm0, math::__internal::sub_divisions ); //xmm0 -> (0,0,0,subdivisions / pi)
	xmm0	= _mm_mul_ss			( xmm0, xmm1 ); //so as this one (0,0,0,x * sd )
	int		n   	= _mm_cvttss_si32		( xmm0 );

	//Now, calculate sine using table
	__m128	xmm2	= _mm_load_ss			( math::__internal::acos_table + n +  math::__internal::sub_divisions);
	__m128	xmm3	= _mm_load_ss			( math::__internal::acos_table + n + 1  + math::__internal::sub_divisions );
	//__m128  xmm4	= _mm_load_ss			( zero.val );
	__m128	  xmm4	= _mm_xor_ps			( xmm4,xmm4);
	xmm4	= _mm_cvtsi32_ss		( xmm4, n );
	//Now, compute xmm0 - xmm4 -> xmm0
	xmm0	= _mm_sub_ss			( xmm0,xmm4 );
	// xmm3 = xmm3 - xmm2
	xmm3	= _mm_sub_ss			( xmm3,xmm2 );
	// xmm0 = xmm0*xmm3
	xmm0	= _mm_mul_ss			( xmm0,xmm3 );
	// xmm0 = xmm2 + xmm0
	xmm0	= _mm_add_ss			( xmm0,xmm2 );
	_mm_store_ss			( &_,  xmm0 );
	return _;
}

inline void sincos(float _,float* sin,float* cos)
{
	__m128	  xmm7	= _mm_setzero_ps();

	__m128 xmm8  	= _mm_load_ss 			( &_2_pi );
	__m128  xmm1	= _mm_load_ss			( &_ );
	loop:

	__m128	xmm5	= _mm_load_ss			( &_2_pi_m1 );
	xmm5	= _mm_mul_ss			( xmm1,xmm5 );
	int		n		= _mm_cvttss_si32		( xmm5 );

	xmm5	= _mm_cvtsi32_ss		( xmm1, n );
	__m128  xmm6	= _mm_load_ss			( &_2_pi );
	xmm5	= _mm_mul_ss			( xmm5, xmm6 );

	xmm1	= _mm_sub_ss			( xmm1, xmm5 );

	int		r1		= _mm_comilt_ss			( xmm1, xmm7 );
	if(r1)
	{
		//float4&	mmm; mmm.xmm = xmm1;
		xmm6	= _mm_load_ss			( &_2_pi );
		//std::cout << "repeating - pass " << mmm << " n " << n << std::endl;
		xmm1 = _mm_add_ss					(xmm1,xmm6);
		goto loop;
	}
	r1		= _mm_comigt_ss			( xmm1, xmm8 );
	if(r1)
	{
		//float4&	mmm; mmm.xmm = xmm1;
		//std::cout << "repeating + pass " << mmm << " n " << n << std::endl;
		goto loop;
	}

	__m128	xmm0	= _mm_load_ss			( &pi_s ); //xmm0 -> (0,0,0,subdivisions / pi)
	xmm0	= _mm_mul_ss			( xmm0, xmm1 ); //so as this one (0,0,0,x * sd / pi )
	n   	= _mm_cvttss_si32		( xmm0 );

	//Now, calculate cos using table
	__m128	xmm2	= _mm_load_ss			( math::__internal::cos_table + n );
	__m128	xmm3	= _mm_load_ss			( math::__internal::cos_table + n + 1 );
	//__m128  xmm4	= _mm_load_ss			( zero.val );
	__m128	  xmm4	= _mm_setzero_ps			();
	xmm4	= _mm_cvtsi32_ss		( xmm4, n );
	//Now, compute xmm0 - xmm4 -> xmm0
	xmm5	= _mm_sub_ss			( xmm0,xmm4 );
	// xmm3 = xmm3 - xmm2
	xmm6	= _mm_sub_ss			( xmm3,xmm2 );
	// xmm0 = xmm0*xmm3
	xmm5	= _mm_mul_ss			( xmm5,xmm6 );
	// xmm0 = xmm2 + xmm0
	xmm5	= _mm_add_ss			( xmm5,xmm2 );
	_mm_store_ss			( cos,  xmm5 );
	//Now, calculate sine using table
	xmm2	= _mm_load_ss			( math::__internal::sin_table + n );
	xmm3	= _mm_load_ss			( math::__internal::sin_table + n + 1 );
	//xmm4	= _mm_load_ss			( zero.val );
	xmm4	= _mm_xor_ps			( xmm4,xmm4);
	xmm4	= _mm_cvtsi32_ss		( xmm4, n );
	//Now, compute xmm0 - xmm4 -> xmm0
	xmm5	= _mm_sub_ss			( xmm0,xmm4 );
	// xmm3 = xmm3 - xmm2
	xmm6	= _mm_sub_ss			( xmm3,xmm2 );
	// xmm0 = xmm0*xmm3
	xmm5	= _mm_mul_ss			( xmm5,xmm6 );
	// xmm0 = xmm2 + xmm0
	xmm5	= _mm_add_ss			( xmm5,xmm2 );
	_mm_store_ss			( sin,  xmm5 );
}

inline   float   tan(float _)
{
	//First of all, convert _ to -PI,PI range
	//__m128 xmm7  	= _mm_load_ss 			( zero.val );
	__m128	  xmm7	= _mm_xor_ps			( xmm7,xmm7);
	__m128 xmm8  	= _mm_load_ss 			( &_2_pi );
	__m128  xmm1	= _mm_load_ss			( &_ );
	loop:

	__m128	xmm5	= _mm_load_ss			( &_2_pi_m1 );
	xmm5	= _mm_mul_ss			( xmm1,xmm5 );
	int		n		= _mm_cvttss_si32		( xmm5 );

	xmm5	= _mm_cvtsi32_ss		( xmm1, n );
	__m128  xmm6	= _mm_load_ss			( &_2_pi );
	xmm5	= _mm_mul_ss			( xmm5, xmm6 );

	xmm1	= _mm_sub_ss			( xmm1, xmm5 );

	int		r1		= _mm_comilt_ss			( xmm1, xmm7 );
	if(r1)
	{
		//float4&	mmm; mmm.xmm = xmm1;
		xmm6	= _mm_load_ss			( &_2_pi );
		//std::cout << "repeating - pass " << mmm << " n " << n << std::endl;
		xmm1 = _mm_add_ss					(xmm1,xmm6);
		goto loop;
	}
	r1		= _mm_comigt_ss			( xmm1, xmm8 );
	if(r1)
	{
		//float4&	mmm; mmm.xmm = xmm1;
		//std::cout << "repeating + pass " << mmm << " n " << n << std::endl;
		goto loop;
	}


	__m128	xmm0	= _mm_load_ss			( &pi_s ); //xmm0 -> (0,0,0,subdivisions / pi)
	xmm0	= _mm_mul_ss			( xmm0, xmm1 ); //so as this one (0,0,0,x * sd / pi )
	n   	= _mm_cvttss_si32		( xmm0 );

	//Now, calculate cos using table
	__m128	xmm2	= _mm_load_ss			( math::__internal::cos_table + n );
	__m128	xmm3	= _mm_load_ss			( math::__internal::cos_table + n + 1 );
	//__m128  xmm4	= _mm_load_ss			( zero.val );
	__m128	  xmm4	= _mm_xor_ps			( xmm4,xmm4);
	xmm4	= _mm_cvtsi32_ss		( xmm4, n );
	//Now, compute xmm0 - xmm4 -> xmm0
	xmm5	= _mm_sub_ss			( xmm0,xmm4 );
	// xmm3 = xmm3 - xmm2
	xmm6	= _mm_sub_ss			( xmm3,xmm2 );
	// xmm0 = xmm0*xmm3
	xmm5	= _mm_mul_ss			( xmm5,xmm6 );
	// xmm0 = xmm2 + xmm0
	xmm5	= _mm_add_ss			( xmm5,xmm2 );
	//		  _mm_store_ss			( cos,  xmm5 );
	//Now, calculate sine using table
	xmm2	= _mm_load_ss			( math::__internal::sin_table + n );
	xmm3	= _mm_load_ss			( math::__internal::sin_table + n + 1 );
	//xmm4	= _mm_load_ss			( zero.val );
	xmm4	= _mm_xor_ps			( xmm4,xmm4);
	xmm4	= _mm_cvtsi32_ss		( xmm4, n );
	//Now, compute xmm0 - xmm4 -> xmm0
	xmm7	= _mm_sub_ss			( xmm0,xmm4 );
	// xmm3 = xmm3 - xmm2
	xmm6	= _mm_sub_ss			( xmm3,xmm2 );
	// xmm0 = xmm0*xmm3
	xmm7	= _mm_mul_ss			( xmm7,xmm6 );
	// xmm0 = xmm2 + xmm0
	xmm7	= _mm_add_ss			( xmm7,xmm2 );
	//		  _mm_store_ss			( sin,  xmm7 );
	xmm0 	= _mm_div_ss			( xmm7, xmm5 );
	_mm_store_ss			( &_ , xmm0  );
	return	_;
}

inline   float   cot(float _)
{
	//First of all, convert _ to -PI,PI range
	//__m128 xmm7  	= _mm_load_ss 			( zero.val );
	__m128	  xmm7	= _mm_setzero_ps			( );
	__m128 xmm8  	= _mm_load_ss 			( &_2_pi );
	__m128  xmm1	= _mm_load_ss			( &_ );
	loop:

	__m128	xmm5	= _mm_load_ss			( &_2_pi_m1 );
	xmm5	= _mm_mul_ss			( xmm1,xmm5 );
	int		n		= _mm_cvttss_si32		( xmm5 );

	xmm5	= _mm_cvtsi32_ss		( xmm1, n );
	__m128  xmm6	= _mm_load_ss			( &_2_pi );
	xmm5	= _mm_mul_ss			( xmm5, xmm6 );

	xmm1	= _mm_sub_ss			( xmm1, xmm5 );

	int		r1		= _mm_comilt_ss			( xmm1, xmm7 );
	if(r1)
	{
		//float4&	mmm; mmm.xmm = xmm1;
		xmm6	= _mm_load_ss			( &_2_pi );
		//std::cout << "repeating - pass " << mmm << " n " << n << std::endl;
		xmm1 = _mm_add_ss					(xmm1,xmm6);
		goto loop;
	}
	r1		= _mm_comigt_ss			( xmm1, xmm8 );
	if(r1)
	{
		//float4&	mmm; mmm.xmm = xmm1;
		//std::cout << "repeating + pass " << mmm << " n " << n << std::endl;
		goto loop;
	}

	__m128	xmm0	= _mm_load_ss			( &pi_s ); //xmm0 -> (0,0,0,subdivisions / pi)
	xmm0	= _mm_mul_ss			( xmm0, xmm1 ); //so as this one (0,0,0,x * sd / pi )
	n   	= _mm_cvttss_si32		( xmm0 );

	//Now, calculate cos using table
	__m128	xmm2	= _mm_load_ss			( math::__internal::cos_table + n );
	__m128	xmm3	= _mm_load_ss			( math::__internal::cos_table + n + 1 );
	//__m128  xmm4	= _mm_load_ss			( zero.val );
	__m128	  xmm4	= _mm_setzero_ps			();
	xmm4	= _mm_cvtsi32_ss		( xmm4, n );
	//Now, compute xmm0 - xmm4 -> xmm0
	xmm5	= _mm_sub_ss			( xmm0,xmm4 );
	// xmm3 = xmm3 - xmm2
	xmm6	= _mm_sub_ss			( xmm3,xmm2 );
	// xmm0 = xmm0*xmm3
	xmm5	= _mm_mul_ss			( xmm5,xmm6 );
	// xmm0 = xmm2 + xmm0
	xmm5	= _mm_add_ss			( xmm5,xmm2 );
	//		  _mm_store_ss			( cos,  xmm5 );
	//Now, calculate sine using table
	xmm2	= _mm_load_ss			( math::__internal::sin_table + n );
	xmm3	= _mm_load_ss			( math::__internal::sin_table + n + 1 );
	//xmm4	= _mm_load_ss			( zero.val );
	xmm4	= _mm_xor_ps			( xmm4,xmm4);
	xmm4	= _mm_cvtsi32_ss		( xmm4, n );
	//Now, compute xmm0 - xmm4 -> xmm0
	xmm7	= _mm_sub_ss			( xmm0,xmm4 );
	// xmm3 = xmm3 - xmm2
	xmm6	= _mm_sub_ss			( xmm3,xmm2 );
	// xmm0 = xmm0*xmm3
	xmm7	= _mm_mul_ss			( xmm7,xmm6 );
	// xmm0 = xmm2 + xmm0
	xmm7	= _mm_add_ss			( xmm7,xmm2 );
	//		  _mm_store_ss			( sin,  xmm7 );
	xmm0 	= _mm_div_ss			( xmm5, xmm7 );
	_mm_store_ss			( &_ , xmm0  );
	return	_;
}
//==================================================Some other functions inspred by intel's AMath, yet done in intrisincs


//======================================================Atan interpolation===============================================================================
_PS_CONST(atan_t0, -0.91646118527267623468e-1f);
_PS_CONST(atan_t1, -0.13956945682312098640e1f);
_PS_CONST(atan_t2, -0.94393926122725531747e2f);
_PS_CONST(atan_t3,  0.12888383034157279340e2f);

_PS_CONST(atan_s0,  0.12797564625607904396e1f);
_PS_CONST(atan_s1,  0.21972168858277355914e1f);
_PS_CONST(atan_s2,  0.68193064729268275701e1f);
_PS_CONST(atan_s3,  0.28205206687035841409e2f);

inline float	atan(float _)
{
	__m128  xmm0	= _mm_load_ss		( &_ ); //Load xmm0

	__m128	xmm1	= _mm_load_ss 		( reinterpret_cast<const float*>(_ps_sign_mask) ); // movss	xmm1, _ps_sign_mask
	__m128	xmm4	= __invert_ss		( xmm0 ); // rcpss	xmm4, xmm0
	xmm1	= _mm_or_ps			( xmm1, xmm0 );//	orps	xmm1, xmm0
	__m128	xmm6	= _mm_move_ss		( xmm6, xmm4 );//	movss	xmm6, xmm4
	__m128  tmp		= _mm_load_ss		( _ps_m1 );
	int n 		= _mm_comilt_ss		( xmm1,tmp);//comiss	xmm1, _ps_m1
	__m128	xmm3	= _mm_load_ss		( _ps_atan_t0 );	//movss	xmm3, _ps_atan_t0
	//jnc		l_small  // 'c' is 'lt' for comiss
	if(n)
	{
		//l_big:
		xmm6	= _mm_mul_ss 		(xmm6,xmm6); //mulss	xmm6, xmm6

		__m128	xmm5	= _mm_load_ss 		( _ps_atan_s0 ); 	 //movss	xmm5, _ps_atan_s0
		xmm5	= _mm_add_ss		( xmm5,xmm6 ); //addss	xmm5, xmm6

		__m128	xmm7	= _mm_load_ss		( _ps_atan_s1 ); //movss	xmm7, _ps_atan_s1
		xmm5	= __invert_ss		( xmm5 );	//rcpss	xmm5, xmm5
		xmm5	= _mm_mul_ss		( xmm5,xmm3 ); //mulss	xmm5, xmm3
		xmm3	= _mm_load_ss		( _ps_atan_t1 ); //movss	xmm3, _ps_atan_t1
		xmm7	= _mm_add_ss		( xmm7, xmm6 );//addss	xmm7, xmm6
		xmm5	= _mm_add_ss		( xmm5,xmm7 ); //addss	xmm5, xmm7

		xmm7	= _mm_load_ss		( _ps_atan_s2 ); //movss	xmm7, _ps_atan_s2
		xmm5	= __invert_ss		( xmm5 );		//rcpss	xmm5, xmm5
		xmm5	= _mm_mul_ss		( xmm5,xmm3 );  //mulss	xmm5, xmm3
		xmm3	= _mm_load_ss		( _ps_atan_t2 ); //movss	xmm3, _ps_atan_t2
		xmm7	= _mm_add_ss		( xmm7,xmm6 ); //addss	xmm7, xmm6
		xmm5	= _mm_add_ss		( xmm5,xmm7 );//	addss	xmm5, xmm7

		xmm7	= _mm_load_ss		( _ps_atan_s3 );//movss	xmm7, _ps_atan_s3
		xmm5	= __invert_ss		( xmm5 ); 		//rcpss	xmm5, xmm5
		xmm5	= _mm_mul_ss		( xmm5,xmm3 );  //mulss	xmm5, xmm3
		xmm3	= _mm_load_ss		( _ps_atan_t3 );//movss	xmm3, _ps_atan_t3
		xmm7	= _mm_add_ss		( xmm7,xmm6 );	//addss	xmm7, xmm6
		__m128	xmm2	= _mm_load_ss		( reinterpret_cast<const float*>(_ps_sign_mask)); //movss	xmm2, _ps_sign_mask
		xmm4	= _mm_mul_ss		( xmm4,xmm3 ); //mulss	xmm4, xmm3
		xmm5	= _mm_add_ss		( xmm5, xmm7 ); //addss	xmm5, xmm7

		xmm7	= _mm_load_ss		( _ps_pi_o_2 ); 	//movss	xmm7, _ps_pi_o_2
		xmm5	= __invert_ss		( xmm5 );		//rcpss	xmm5, xmm5
		xmm5	= _mm_mul_ss		( xmm5, xmm4 ); //mulss	xmm5, xmm4

		xmm0	= _mm_and_ps		( xmm0, xmm2 ); //andps	xmm0, xmm2
		xmm0	= _mm_or_ps			( xmm0, xmm7 ); //orps	xmm0, xmm7
		xmm0 	= _mm_sub_ss		( xmm0, xmm5 ); //subss	xmm0, xmm5

	}
	else
	{
		__m128	xmm2	=  xmm0;//movaps	xmm2, xmm0 ???
		xmm2	= _mm_mul_ss		( xmm2, xmm2 ); //mulss	xmm2, xmm2

		xmm1	= _mm_load_ss 		( _ps_atan_s0 );//movss	xmm1, _ps_atan_s0
		xmm1	= _mm_add_ss		( xmm1, xmm2 );// addss	xmm1, xmm2

		__m128 	xmm7	= _mm_load_ss		( _ps_atan_s1 );//movss	xmm7, _ps_atan_s1
		xmm1	= __invert_ss		( xmm1 );//rcpss	xmm1, xmm1
		xmm1	= _mm_mul_ss			( xmm1,xmm3 ); //mulss	xmm1, xmm3
		xmm3	= _mm_load_ss		( _ps_atan_t1 ); //movss	xmm3, _ps_atan_t1
		xmm7	= _mm_add_ss		( xmm7,xmm2 );//addss	xmm7, xmm2
		xmm1	= _mm_add_ss		( xmm1,xmm7 );//addss	xmm1, xmm7

		xmm7	= _mm_load_ss		( _ps_atan_s2 );//movss	xmm7, _ps_atan_s2
		xmm1	= __invert_ss		( xmm1 ); //rcpss	xmm1, xmm1
		xmm1	= _mm_mul_ss		( xmm1,xmm3 );//mulss	xmm1, xmm3
		xmm3	= _mm_load_ss		( _ps_atan_t2 );//movss	xmm3, _ps_atan_t2
		xmm7	= _mm_add_ss		( xmm7,xmm2 );	//addss	xmm7, xmm2
		xmm1	= _mm_add_ss		( xmm1,xmm7 );	//addss	xmm1, xmm7

		xmm7	= _mm_load_ss		( _ps_atan_s3 );//movss	xmm7, _ps_atan_s3
		xmm1	= __invert_ss		( xmm1 );//rcpss	xmm1, xmm1
		xmm1	= _mm_mul_ss		( xmm1,xmm3	);//mulss	xmm1, xmm3
		xmm3	= _mm_load_ss		( _ps_atan_t3 );//movss	xmm3, _ps_atan_t3
		xmm7	= _mm_add_ss		( xmm7,xmm2 );//addss	xmm7, xmm2
		xmm0	= _mm_mul_ss		( xmm0,xmm3 );//mulss	xmm0, xmm3
		xmm1	= _mm_add_ss		( xmm1, xmm7 );//addss	xmm1, xmm7

		xmm1    = __invert_ss		( xmm1 );//rcpss	xmm1, xmm1
		xmm0	= _mm_mul_ss		( xmm0,xmm1 );//mulss	xmm0, xmm1
	}
	_mm_store_ss( &_, xmm0 );
	return  _;
}
//=======================================================Natural logarithm================================================================================
// This code was ported from cephes math library and rewritten to suit freya needs
_PS_CONST(SQRTHF, 0.707106781186547524);
_PS_CONST(log_p0, 7.0376836292E-2);
_PS_CONST(log_p1, - 1.1514610310E-1);
_PS_CONST(log_p2, 1.1676998740E-1);
_PS_CONST(log_p3, - 1.2420140846E-1);
_PS_CONST(log_p4, + 1.4249322787E-1);
_PS_CONST(log_p5, - 1.6668057665E-1);
_PS_CONST(log_p6, + 2.0000714765E-1);
_PS_CONST(log_p7, - 2.4999993993E-1);
_PS_CONST(log_p8, + 3.3333331174E-1);
_PS_CONST(log_q1, -2.12194440e-4);
_PS_CONST(log_q2, 0.693359375);
inline float  log(float _) {
	__m128  x	= _mm_load_ss ( &_ );
	__m128i emm0;

	__m128 one = *(__m128*)_ps_1;

	__m128 invalid_mask = _mm_cmple_ss(x, _mm_setzero_ps());

	x = _mm_max_ss(x, *(__m128*)_ps_min_norm_pos);  /* cut off denormalized stuff */

	emm0 = _mm_srli_epi32(_mm_castps_si128(x), 23);
	/* keep only the fractional part */
	x = _mm_and_ps(x, *(__m128*)_ps_inv_mant_mask);
	x = _mm_or_ps(x, *(__m128*)_ps_0p5);

	emm0 = _mm_sub_epi32(emm0, *(__m128i*)_epi32_0x7f);
	__m128 e = _mm_cvtepi32_ps(emm0);

	e = _mm_add_ss(e, one);

	/* part2:
     if( x < SQRTHF ) {
       e -= 1;
       x = x + x - 1.0;
     } else { x = x - 1.0; }
	 */
	__m128 mask = _mm_cmplt_ss(x, *(__m128*)_ps_SQRTHF);
	__m128 tmp = _mm_and_ps(x, mask);
	x = _mm_sub_ss(x, one);
	e = _mm_sub_ss(e, _mm_and_ps(one, mask));
	x = _mm_add_ss(x, tmp);


	__m128 z = _mm_mul_ss(x,x);

	__m128 y = *(__m128*)_ps_log_p0;
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_log_p1);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_log_p2);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_log_p3);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_log_p4);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_log_p5);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_log_p6);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_log_p7);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_log_p8);
	y = _mm_mul_ss(y, x);

	y = _mm_mul_ss(y, z);


	tmp = _mm_mul_ss(e, *(__m128*)_ps_log_q1);
	y = _mm_add_ss(y, tmp);


	tmp = _mm_mul_ss(z, *(__m128*)_ps_0p5);
	y = _mm_sub_ss(y, tmp);

	tmp = _mm_mul_ss(e, *(__m128*)_ps_log_q2);
	x = _mm_add_ss(x, y);
	x = _mm_add_ss(x, tmp);
	x = _mm_or_ps(x, invalid_mask); // negative arg will be NAN
	_mm_store_ss ( &_,x );
	return _;
}
//========================================================Exp============================================================================================
// This code was ported from cephes math library and rewritten to suit freya needs
_PS_CONST(exp_hi,	88.3762626647949f);
_PS_CONST(exp_lo,	-88.3762626647949f);

_PS_CONST(LOG2EF, 1.44269504088896341);
_PS_CONST(exp_C1, 0.693359375);
_PS_CONST(exp_C2, -2.12194440e-4);

_PS_CONST(exp_p0, 1.9875691500E-4);
_PS_CONST(exp_p1, 1.3981999507E-3);
_PS_CONST(exp_p2, 8.3334519073E-3);
_PS_CONST(exp_p3, 4.1665795894E-2);
_PS_CONST(exp_p4, 1.6666665459E-1);
_PS_CONST(exp_p5, 5.0000001201E-1);

inline float exp(float _) {
	__m128 x = _mm_load_ss (&_);
	__m128 tmp = _mm_setzero_ps(), fx;
	__m128i emm0;

	__m128 one = *(__m128*)_ps_1;

	x = _mm_min_ss(x, *(__m128*)_ps_exp_hi);
	x = _mm_max_ss(x, *(__m128*)_ps_exp_lo);

	/* express exp(x) as exp(g + n*log(2)) */
	fx = _mm_mul_ss(x, *(__m128*)_ps_LOG2EF);
	fx = _mm_add_ss(fx, *(__m128*)_ps_0p5);

	emm0 = _mm_cvttps_epi32(fx);
	tmp  = _mm_cvtepi32_ps(emm0);

	/* if greater, substract 1 */
	__m128 mask = _mm_cmpgt_ps(tmp, fx);
	mask = _mm_and_ps(mask, one);
	fx = _mm_sub_ss(tmp, mask);

	tmp = _mm_mul_ss(fx, *(__m128*)_ps_exp_C1);
	__m128 z = _mm_mul_ss(fx, *(__m128*)_ps_exp_C2);
	x = _mm_sub_ss(x, tmp);
	x = _mm_sub_ss(x, z);

	z = _mm_mul_ss(x,x);

	__m128 y = *(__m128*)_ps_exp_p0;
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_exp_p1);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_exp_p2);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_exp_p3);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_exp_p4);
	y = _mm_mul_ss(y, x);
	y = _mm_add_ss(y, *(__m128*)_ps_exp_p5);
	y = _mm_mul_ss(y, z);
	y = _mm_add_ss(y, x);
	y = _mm_add_ss(y, one);

	/* build 2^n */

	emm0 = _mm_cvttps_epi32(fx);
	emm0 = _mm_add_epi32(emm0, *(__m128i*)_epi32_0x7f);
	emm0 = _mm_slli_epi32(emm0, 23);
	__m128 pow2n = _mm_castsi128_ps(emm0);

	y = _mm_mul_ss(y, pow2n);
	_mm_store_ss( &_, y );
	return _;
}

static inline
__m128 vec_sel(__m128 a, __m128 b, __m128 mask)
{
	return _mm_or_ps(_mm_and_ps(mask, b), _mm_andnot_ps(mask, a));
}

}


#endif /* MATH_INTERNAL_H_ */

#ifndef MATRIX4X4_HPP_
#define MATRIX4X4_HPP_

#include "math.hpp"
//#include "quaternion.hpp"
namespace math {

class matrix4x4 : public MATRIX4X4, public MathSubsystem
{
public:
	using MATRIX4X4::m_size;
	using MATRIX4X4::_11;
	using MATRIX4X4::_21;
	using MATRIX4X4::_31;
	using MATRIX4X4::_41;
	using MATRIX4X4::_12;
	using MATRIX4X4::_22;
	using MATRIX4X4::_32;
	using MATRIX4X4::_42;
	using MATRIX4X4::_13;
	using MATRIX4X4::_23;
	using MATRIX4X4::_33;
	using MATRIX4X4::_43;
	using MATRIX4X4::_14;
	using MATRIX4X4::_24;
	using MATRIX4X4::_34;
	using MATRIX4X4::_44;
	using MATRIX4X4::mat;
	using MATRIX4X4::mat_linear;

	inline explicit
	matrix4x4() {
		_11 = _22 = _33 = _44 = unit;
		_21 = _31 = _41 = _12 =
			_32 = _42 = _13 = _23 =
				_43 = _14 = _24 = _34 = zero;
	}

	inline explicit
	matrix4x4(const float diag) {
		_11 = _22 = _33 = _44 = diag;
		_21 = _31 = _41 = _12 =
			_32 = _42 = _13 = _23 =
				_43 = _14 = _24 = _34 = zero;
	}

	inline explicit
	matrix4x4(const float m[m_size]) {
		mat_linear[0] = m[0];
		mat_linear[1] = m[1];
		mat_linear[2] = m[2];
		mat_linear[3] = m[3];
		mat_linear[4] = m[4];
		mat_linear[5] = m[5];
		mat_linear[6] = m[6];
		mat_linear[7] = m[7];
		mat_linear[8] = m[8];
		mat_linear[9] = m[9];
		mat_linear[10] = m[10];
		mat_linear[11] = m[11];
		mat_linear[12] = m[12];
		mat_linear[13] = m[13];
		mat_linear[14] = m[14];
		mat_linear[15] = m[15];
	}

	matrix4x4(const matrix4x4& m) {
		_11 = m._11;
		_21 = m._21;
		_31 = m._31;
		_41 = m._41;

		_12 = m._12;
		_22 = m._22;
		_32 = m._32;
		_42 = m._42;

		_13 = m._13;
		_23 = m._23;
		_33 = m._33;
		_43 = m._43;

		_14 = m._14;
		_24 = m._24;
		_34 = m._34;
		_44 = m._44;
	}
	matrix4x4& operator = (const matrix4x4& m)
	{
		_11 = m._11;
		_21 = m._21;
		_31 = m._31;
		_41 = m._41;

		_12 = m._12;
		_22 = m._22;
		_32 = m._32;
		_41 = m._42;

		_13 = m._13;
		_23 = m._23;
		_33 = m._33;
		_43 = m._43;

		_14 = m._14;
		_24 = m._24;
		_34 = m._34;
		_44 = m._44;
		return *this;
	}
	matrix4x4& operator = (const quaternion& q)
	{
		return (*this = QuaternionToMatrix4x4(q));
	}

	operator float*()
	{
		return mat_linear;
	}

	operator const float*() const
	{
		return mat_linear;
	}
};

}


#endif /*MATRIX4X4_HPP_*/

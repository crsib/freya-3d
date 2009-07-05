#ifndef __MATRIX3X3_HPP_
#define __MATRIX3X3_HPP_
//#include "math.hpp"

namespace math {

class matrix3x3 : public MATRIX3X3, public MathSubsystem
{
public:
	using MATRIX3X3::m_size;
	using MATRIX3X3::_11;
	using MATRIX3X3::_21;
	using MATRIX3X3::_31;
	using MATRIX3X3::_12;
	using MATRIX3X3::_22;
	using MATRIX3X3::_32;
	using MATRIX3X3::_13;
	using MATRIX3X3::_23;
	using MATRIX3X3::_33;
	using MATRIX3X3::mat;
	using MATRIX3X3::mat_linear;

	explicit
	matrix3x3() {
		_11 = _22 = _33 = unit;
		_21 = _31 = _12 =
		_32 = _13 = _23 = zero;
	}

	explicit
	matrix3x3(const float diag) {
		_11 = _22 = _33 = diag;
		_21 = _31 = _12 =
		_32 = _13 = _23 = zero;
	}

	explicit
	matrix3x3(const float m[m_size]) {
		mat_linear[0] = m[0];
		mat_linear[1] = m[1];
		mat_linear[2] = m[2];
		mat_linear[3] = m[3];
		mat_linear[4] = m[4];
		mat_linear[5] = m[5];
		mat_linear[6] = m[6];
		mat_linear[7] = m[7];
		mat_linear[8] = m[8];
	}

	matrix3x3(const matrix3x3& m) {
		_11 = m._11;
		_21 = m._21;
		_31 = m._31;

		_12 = m._12;
		_22 = m._22;
		_32 = m._32;

		_13 = m._13;
		_23 = m._23;
		_33 = m._33;
	}
/*
    static const matrix3x3 zero_matrix3x3 = matrix3x3(zero);
    static const matrix3x3 unit_matrix3x3 = matrix3x3(unit);
//*/

	operator float* ()
	{
		return mat_linear;
	}

	operator const float*() const
	{
		return mat_linear;
	}
};

}

#endif /*MATRIX3X3_HPP_*/

#ifndef QUATERNION_HPP_
#define QUATERNION_HPP_

#include "math.hpp"
#include "vector3d.hpp"
#include "matrix4x4.hpp"

namespace math {

class quaternion : public MathSubsystem
{
public:
	inline
	quaternion() {
		w 	= unit;
		u.x = zero;
		u.y = zero;
		u.z = zero;
	}

	inline explicit
	quaternion(const float ww, const float xx,
			const float yy, const float zz) {
		float q_norm = (ww * ww)+(xx * xx)+(yy * yy)+(zz * zz);
		w 	= ww;
		u.x = xx;
		u.y = yy;
		u.z = zz;
		if(abs(q_norm - unit) > eps) {
			w /= q_norm;
			u /= q_norm;
		}
	}

	inline explicit
	quaternion(const float ww, const vector3d& uu) {
		float q_norm = (ww * ww)+abs_sq(uu);
		w = ww;
		u = uu;
		if(abs(q_norm - unit) > eps) {
			w /= q_norm;
			u /= q_norm;
		}
	}
	inline explicit
	quaternion(const vector3d& dir,const float angle)//This constructor is used to create rotate quaternion
	{
		float ha = angle*0.5f;
		w = cosf(ha);
		u = sinf(ha)*normalized(dir);
		this->normalize();
	}
	inline
	quaternion(const quaternion& q) {
		float q_norm = (q.w * q.w)+abs_sq(q.u);
		w = q.w;
		u = q.u;
		if(abs(q_norm - unit) > eps) {
			w /= q_norm;
			u /= q_norm;
		}
	}

	inline
	operator float*() {
		return &w;
	}
	inline
	operator const float*()  const{
		return &w;
	}
	inline
	operator vector3d()
	{
		return u;
	}
	inline
	float& operator[](const int index) {
		return *(&w + index);
	}

	inline
	quaternion operator+() {
		return *this;
	}

	inline
	quaternion operator-() {
		return quaternion(-w, -u);
	}

	inline
	quaternion& operator=(const quaternion& q) {
		w = q.w;
		u = q.u;
		normalize();
		return *this;
	}

	inline
	quaternion& operator+=(const quaternion& q) {
		w += q.w;
		u += q.u;
		normalize();
		return *this;
	}

	inline
	quaternion& operator+=(const float scalar) {
		w += scalar;
		normalize();
		return *this;
	}

	inline
	quaternion& operator+=(const vector3d& uu) {
		u += uu;
		normalize();
		return *this;
	}

	inline
	quaternion& operator-=(const quaternion& q) {
		w -= q.w;
		u -= q.u;
		normalize();
		return *this;
	}

	inline
	quaternion& operator-=(const float scalar) {
		w -= scalar;
		normalize();
		return *this;
	}

	inline
	quaternion& operator-=(const vector3d& uu) {
		u -= uu;
		normalize();
		return *this;
	}

	inline
	quaternion& operator*=(const quaternion& q) {
		*this = quaternion((w * q.w) - (u , q.u),
				(u * q.u) + (w * q.u) + (u * q.w));
		normalize();
		return *this;
	}

	inline
	quaternion& operator*=(const float scalar) {
		w *= scalar;
		u *= scalar;
		normalize();
		return *this;
	}

	inline
	quaternion& operator*=(const vector3d& uu) {
		u = (u * uu)+(w * uu);
		w = zero;
		normalize();
		return *this;
	}

	inline
	quaternion& operator/=(const float scalar) {
		w /= scalar;
		u /= scalar;
		normalize();
		return *this;
	}

	inline
	bool operator==(const quaternion& q) {
		return (w == q.w)&&(u == q.u);
	}

	inline
	bool operator!=(const quaternion& q) {
		return (w != q.w)||(u != q.u);
	}

	inline
	vector3d rotate(const vector3d& vec)
	{
		if(!isNormed(*this)) normalize();
		return (vector3d) ((*this) * vec *conjugated(*this));
	}

	inline friend
	quaternion operator+(const quaternion& q1, const quaternion& q2) {
		return quaternion(q1.w + q2.w, q1.u + q2.u);
	}

	inline friend
	quaternion operator+(const quaternion& q, const float scalar) {
		return quaternion(q.w + scalar, q.u);
	}

	inline friend
	quaternion operator+(const float scalar, const quaternion& q) {
		return quaternion(q.w + scalar, q.u);
	}

	inline friend
	quaternion operator+(const quaternion& q, const vector3d& uu) {
		return quaternion(q.w, q.u + uu);
	}

	inline friend
	quaternion operator+(const vector3d& uu, const quaternion& q) {
		return quaternion(q.w, q.u + uu);
	}

	inline friend
	quaternion operator-(const quaternion& q1, const quaternion& q2) {
		return quaternion(q1.w - q2.w, q1.u - q2.u);
	}

	inline friend
	quaternion operator-(const quaternion& q, const float scalar) {
		return quaternion(q.w - scalar, q.u);
	}

	inline friend
	quaternion operator-(const float scalar, quaternion& q) {
		return quaternion(scalar - q.w, -q.u);
	}

	inline friend
	quaternion operator-(const quaternion& q, const vector3d& uu) {
		return quaternion(q.w, q.u - uu);
	}

	inline friend
	quaternion operator-(const vector3d& uu, const quaternion& q) {
		return quaternion(-q.w, uu - q.u);
	}

	inline friend
	quaternion operator*(const quaternion& q1, const quaternion& q2) {
		return quaternion((q1.w * q2.w)-(q1.u , q2.u),
				(q1.u * q2.u)+(q1.w * q2.u)+(q1.u * q2.w));
	}

	inline friend
	quaternion operator*(const quaternion& q, const float scalar) {
		return quaternion(q.w * scalar, q.u * scalar);
	}

	inline friend
	quaternion operator*(const float scalar, const quaternion& q) {
		return quaternion(q.w * scalar, q.u * scalar);
	}

	inline friend
	quaternion operator*(const quaternion& q, const vector3d& uu) {
		return quaternion(-(q.u,uu), (q.w * uu)+(q.u * uu));
	}

	inline friend
	quaternion operator*(const vector3d& uu, const quaternion& q) {
		return quaternion(-(q.u,uu), (uu * q.w)+(uu * q.u));
	}

	inline friend
	quaternion operator/(const quaternion& q, const float scalar) {
		return quaternion(q.w / scalar,
				q.u / scalar);
	}

	inline friend
	float operator,(const quaternion& q1, const quaternion& q2) {
		return (q1.w * q2.w)+(q1.u , q2.u);
	}

	inline
	quaternion& conjugate() {
		u = -u;
		return *this;
	}

	inline
	quaternion& inverse() {
		u = -u;
		return *this;
	}

	inline friend
	float norm(const quaternion& q) {
		return (q.w * q.w)+abs_sq(q.u);
	}

	inline
	quaternion& normalize() {
		float q_norm = abs(*this);
		if(abs(q_norm - unit) > eps)
			*this /= q_norm;
		return *this;
	}

	inline friend
	bool isNormed(const quaternion& q) {
		float q_norm = norm(q);
		if(abs(q_norm - unit) < eps)
			return true;
		return false;
	}

	inline friend
	float abs(const quaternion& q) {
		float q_norm = norm(q);
		if(abs(q_norm - unit) < eps) return q_norm;
		return sqrt(q_norm);
	}

	inline friend
	quaternion conjugated(quaternion& q) {
		return quaternion(q.w, -q.u);
	}

	inline friend
	quaternion inversed(quaternion& q) {
		float n = norm(q);
		if(n == 0) return quaternion(zero,zero,zero,zero);
		n = 1.0f/n;
		return quaternion(q.w*n, -q.u*n);
	}

	inline friend
	quaternion normalized(const quaternion& q) {
		float q_norm = norm(q);
		if(abs(q_norm - unit) > eps)
			return quaternion(q / q_norm);
		return q;
	}

	inline
	vector3d operator()(const vector3d& v) {
		quaternion q = (*this)*( v)*conjugated(*this);
		return q.u;
	}

	quaternion& operator = (const matrix4x4& mtx)
	{
		return (*this = Matrix4x4ToQuaternion(mtx));
	}
	float 	 w;
	vector3d u;
};

}

#endif /*QUATERNION_HPP_*/

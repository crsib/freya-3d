#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

#include "math.hpp"
#include "vector2d.hpp"

namespace math {

class vector3d : public VECTOR3F, public MathSubsystem
{
public:
	using VECTOR3F::x;
	using VECTOR3F::y;
	using VECTOR3F::z;

	inline
	vector3d() {
		x=0.0f;
		y=0.0f;
		z=0.0f;
	}

	inline explicit
	vector3d(const float xx, const float yy, const float zz) {
		x = xx;
		y = yy;
		z = zz;
	}

	inline explicit
	vector3d(const vector2d& v, float zz) {
		x = v.x;
		y = v.y;
		z = zz;
	}

	inline explicit
	vector3d(const vector3d* v) {
		x = v->x;
		y = v->y;
		z = v->z;
	}

	inline
	vector3d(const vector3d& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	inline
	operator float*()
	{
		return &x;
	}

	inline
	operator const float*() const
	{
		return &x;
	}

	inline
	float& operator[](const int index) {
		return *(&x + index);
	}

	inline
	vector3d operator+() {
		return *this;
	}

	inline
	vector3d operator-() {
		return vector3d(-x, -y, -z);
	}

	inline
	vector3d& operator=(const vector3d& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	inline
	vector3d& operator+=(const vector3d& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	inline
	vector3d& operator-=(const vector3d& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	inline
	vector3d& operator*=(const vector3d& v) {
		return *this = vector3d((y * v.z)-(z * v.y),
				(z * v.x)-(x * v.z),
				(x * v.y)-(y * v.x));
	}

	inline
	vector3d& operator*=(const float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	inline
	vector3d& operator/=(const float scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	inline
	bool operator==(const vector3d& v) {
		return (x == v.x)&&(y == v.y)&&(z == v.z);
	}

	inline
	bool operator!=(const vector3d& v) {
		return (x != v.x)||(y != v.y)||(z != v.z);
	}

	inline
	bool operator||(const vector3d& v) {
		return ((x * v.y * v.z)==(v.x * y * v.z))==(v.x * v.y * z);
	}

	inline friend
	vector3d operator+(const vector3d& v1, const vector3d& v2) {
		return vector3d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	inline friend
	vector3d operator-(const vector3d& v1, const vector3d& v2) {
		return vector3d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	inline friend
	vector3d operator*(const vector3d& v1, const vector3d& v2) {
		return vector3d((v1.y * v2.z)-(v1.z * v2.y),
				(v1.z * v2.x)-(v1.x * v2.z),
				(v1.x * v2.y)-(v1.y * v2.x));
	}

	inline friend
	vector3d operator*(const vector3d& v, const float scalar) {
		return vector3d(v.x * scalar, v.y * scalar, v.z * scalar);
	}

	inline friend
	vector3d operator*(const float scalar,const vector3d& v) {
		return vector3d(v.x * scalar, v.y * scalar, v.z * scalar);
	}

	inline friend
	vector3d operator/(const vector3d& v, const float scalar) {
		return vector3d(v.x / scalar, v.y / scalar, v.z / scalar);
	}

	inline friend
	float operator,(const vector3d& v1, const vector3d& v2) {
		return (v1.x * v2.x)+(v1.y * v2.y)+(v1.z * v2.z);
	}

	inline friend
	float abs(const vector3d& v) {
		return sqrt((v.x * v.x)+(v.y * v.y)+(v.z * v.z));
	}

	inline friend
	float abs_sq(const vector3d& v) {
		return (v.x * v.x)+(v.y * v.y)+(v.z * v.z);
	}

	inline friend
	float distance(const vector3d& v1, const vector3d& v2) {
		return sqrt((v1.x - v2.x)*(v1.x - v2.x)
				+(v1.y - v2.y)*(v1.y - v2.y)
				+(v1.z - v2.z)*(v1.z - v2.z));
	}

	inline friend
	float distance_sq(const vector3d& v1, const vector3d& v2) {
		return (v1.x - v2.x)*(v1.x - v2.x)
		+(v1.y - v2.y)*(v1.y - v2.y)
		+(v1.z - v2.z)*(v1.z - v2.z);
	}

	inline friend
	vector3d& max(vector3d& v1, vector3d& v2) {
		return abs_sq(v1) > abs_sq(v2) ? v1 : v2;
	}

	inline friend
	vector3d& min(vector3d& v1, vector3d& v2) {
		return abs_sq(v1) < abs_sq(v2) ? v1 : v2;
	}

	inline friend
	vector3d normalized(const vector3d& v) {
		return vector3d(v/abs(v));
	}

	inline
	vector3d& normalize() {
		return *this/=abs(*this);
	}

#ifdef MATH_DEBUG
friend std::ostream& operator<<(std::ostream& os, vector3d& v) {
	return os<<"x: "<<v.x<<" y: "<<v.y<<" z: "<<v.z<<'\n';
}
#endif
};

}//math

#endif /*VECTOR3D_HPP_*/

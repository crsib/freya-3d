#ifndef VECTOR2D_HPP_
#define VECTOR2D_HPP_

#include "math.hpp"

namespace math {

class vector2d : public math::VECTOR2F, public MathSubsystem
{
public:

	inline
	vector2d(){
	}

    inline explicit
    vector2d(const float xx, const float yy) {
    	x = xx;
    	y = yy;
	}

	inline explicit
	vector2d(const vector2d* v) {
		x = v->x;
		y = v->y;
	}

	inline
	vector2d(const vector2d& v) {
		x = v.x;
		y = v.y;
	}

	inline
	operator float*() {
		return &x;
	}

    inline
    float& operator[](const int index) {
    	return *(&x+index);
	}

    inline
    vector2d operator+() {
    	return *this;
	}

    inline
    vector2d operator-() {
    	return vector2d(-x, -y);
	}

    inline
    vector2d& operator=(const vector2d& v) {
    	x = v.x;
    	y = v.y;
    	return *this;
	}

    inline
    vector2d& operator+=(const vector2d& v) {
    	x += v.x;
    	y += v.y;
    	return *this;
	}

    inline
    vector2d& operator-=(const vector2d& v) {
    	x -= v.x;
    	y -= v.y;
    	return *this;
	}

    inline
    vector2d& operator*=(const float scalar) {
    	x *= scalar;
    	y *= scalar;
    	return *this;
	}

    inline
    vector2d& operator/=(const float scalar) {
    	x /= scalar;
    	y /= scalar;
    	return *this;
	}

	inline
	bool operator==(const vector2d& v) {
		return (x == v.x)&&(y == v.y);
	}

    inline
    bool operator!=(const vector2d& v) {
    	return (x != v.x)||(y != v.y);
	}

	inline
	bool operator||(const vector2d& v) {
		return (x * v.y)==(y * v.x);
	}

	inline friend
	vector2d operator+(const vector2d& v1, const vector2d& v2) {
    	return vector2d(v1.x + v2.x, v1.y + v2.y);
	}

	inline friend
	vector2d operator-(const vector2d& v1, const vector2d& v2) {
		return vector2d(v1.x - v2.x, v1.y - v2.y);
	}

	inline friend
	vector2d operator*(const vector2d& v, const float scalar) {
		return vector2d(v.x * scalar, v.y * scalar);
	}

	inline friend
	vector2d operator*(const float scalar, const vector2d& v) {
		return vector2d(v.x * scalar, v.y * scalar);
	}

	inline friend
	vector2d operator/(const vector2d& v, const float scalar) {
		return vector2d(v.x / scalar, v.x / scalar);
	}

	inline friend
	float operator,(const vector2d& v1, const vector2d& v2) {
		return (v1.x * v2.x)+(v1.y * v2.y);
	}

	inline friend
	float abs(const vector2d& v) {
		return sqrt((v.x * v.x)+(v.y + v.y));
	}

	inline friend
	float abs_sq(const vector2d& v) {
		return (v.x * v.x)+(v.y + v.y);
	}

	inline friend
	vector2d& max(vector2d& v1, vector2d& v2) {
		return abs_sq(v1) > abs_sq(v2) ? v1 : v2;
	}

	inline friend
	vector2d& min(vector2d& v1, vector2d& v2) {
		return abs_sq(v1) < abs_sq(v2) ? v1 : v2;
	}

	inline friend
	float distance(const vector2d& v1, const vector2d& v2) {
		return sqrt((v1.x - v2.x)*(v1.x - v2.x)
				   +(v1.y - v2.y)*(v1.y - v2.y));
	}

	inline friend
	float distance_sq(const vector2d& v1, const vector2d& v2) {
		return (v1.x - v2.x)*(v1.x - v2.x)
			  +(v1.y - v2.y)*(v1.y - v2.y);
	}

	inline friend
	vector2d normalized(const vector2d& v) {
		return vector2d(v/abs(v));
	}

	inline
	vector2d& normalize() {
		return *this/=abs(*this);
	}

	using VECTOR2F::x;
	using VECTOR2F::y;
};

}//math

#endif /*VECTOR2D_HPP_*/

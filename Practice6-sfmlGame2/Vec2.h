#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <cmath>

using namespace std;

struct Vec2 {
	float x, y;

	Vec2() = default;
	Vec2(float x, float y)
		: x(x), y(y)  {};

	Vec2 operator + (const Vec2& v) const { return {x + v.x ,y + v.y }; };
	Vec2 operator - (const Vec2& v) const { return { x - v.x ,y - v.y }; };
	Vec2 operator * (float val) const { return {x * val, y * val}; };

	float distance() const { return { sqrt(x * x + y * y) }; };
	Vec2 normalized() const {
		float dist = distance();
		return dist ? Vec2(x / dist, y/dist) : Vec2();
	}
};


#endif

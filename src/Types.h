#pragma once
#include <math.h>
#include <time.h>
#include <string>

struct MyVec2
{
	int x, y;
	MyVec2() : x(0), y(0) {};
	MyVec2(int _xy) : x(_xy), y(_xy) {};
	MyVec2(int _x, int _y) : x(_x), y(_y) {};

	inline bool operator== (const MyVec2& v)const { return (x == v.x && y == v.y); };
	const MyVec2 operator- (const MyVec2& v) { return MyVec2(x - v.x, y - v.y); };
	const MyVec2 operator+ (const MyVec2& v) { return MyVec2(x + v.x, y + v.y); };
	const MyVec2 operator+= (const MyVec2& v) { x += v.x, y += v.y; return *this; };
	const MyVec2 operator/ (const MyVec2& v) { return MyVec2(x / v.x, y / v.y); };
	const MyVec2 operator/ (float a) const { return MyVec2(static_cast<int>(x) / a, static_cast<int>(y) / a); };
	const MyVec2 operator* (const MyVec2& v) { return MyVec2(x * v.x, y * v.y); };
	const MyVec2 operator* (float a) const { return MyVec2(static_cast<int>(x) * a, static_cast<int>(y) * a); };
	const MyVec2 operator* (int a) const { return MyVec2(x * a, y * a); };
	const MyVec2 operator*= (const MyVec2& v) { x *= v.x; y *= v.y; return *this; };
	const MyVec2 operator*= (const int& i) { x *= i; y *= i; return *this; };

	float mod() { return sqrt(pow(x, 2) + pow(y, 2)); };

	const static MyVec2 random(int minX, int maxX, int minY, int maxY) {
		return { ((rand() % (maxX - minX)) + minX) ,((rand() % (maxY - minY)) + minY) };
	};

};

struct MyVec2f
{
	float x, y;
	MyVec2f() : x(0.0f), y(0.0f) {};
	MyVec2f(float _xy) : x(_xy), y(_xy) {};
	MyVec2f(float _x, float _y) : x(_x), y(_y) {};

	inline bool operator== (const MyVec2f& v)const { return (x == v.x && y == v.y); };
	const MyVec2f operator- (const MyVec2f& v) { return MyVec2f(x - v.x, y - v.y); };
	const MyVec2f operator+ (const MyVec2f& v) { return MyVec2f(x + v.x, y + v.y); };
	const MyVec2f operator+= (const MyVec2f& v) { x += v.x, y += v.y; return *this; };
	const MyVec2f operator/ (const MyVec2f& v) const { return MyVec2f(x / v.x, y / v.y); };
	const MyVec2f operator/ (float a) const { return MyVec2f(x / a, y / a); };
	const MyVec2f operator* (const MyVec2f& v) const { return MyVec2f(x * v.x, y * v.y); };
	const MyVec2f operator* (float a) const { return MyVec2f(x * a, y * a); };
	const MyVec2f operator*= (const MyVec2f& v) { x *= v.x; y *= v.y; return *this; };
	const MyVec2f operator*= (const float& f) { x *= f; y *= f; return *this; };

	float mod() { return sqrt(pow(x, 2) + pow(y, 2)); };

	float length() const {
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	float sqrLength() {
		return x * x + y * y;
	}

	MyVec2f normalized() const {
		float l = length();
		if (l > 0.0001f) {
			return MyVec2f(x / l, y / l);
		}
		return MyVec2f(0, 0);
	}


};

struct MyRect
{
	int x, y, w, h;
	MyRect() : x(0), y(0), w(0), h(0) {};
	MyRect(int _x, int _y) : x(_x), y(_y), w(0), h(0) {};
	MyRect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};
};

struct Font {
	const std::string id;
	std::string path;
	int size;
};

struct Color {
	uint8_t r, g, b, a;
};

struct Text {
	std::string id;
	std::string text;
	Color color;
};
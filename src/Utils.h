#pragma once
#include <SDL.h> // Always needs to be included for an SDL app
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Types.h"


static MyRect SDLRectToMyRect(SDL_Rect r) { return MyRect(r.x, r.y, r.w, r.h); }

static SDL_Rect MyRectToSDLRect(const MyRect* r) { return SDL_Rect{ r->x, r->y, r->w, r->h }; }

static std::string FloatToStringFormat(float num, int decimals) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(decimals) << num;
	return static_cast<std::string>(stream.str());
}

static std::string IntToStringFormat(int num) {
	std::stringstream stream;
	stream << std::fixed << num;
	return static_cast<std::string>(stream.str());
}

static float dot(const MyVec2f& a, const MyVec2f& b) {
	return a.x * b.x + a.y * b.y;
}

static bool ExistCollision(MyVec2 p1, MyVec2 p2, float offset) {
	return abs((long)(MyVec2(p2 - p1)).mod()) < offset;

}
static bool ExistCollision(MyVec2 p1, MyRect r1) {
	return (p1.x > r1.x && p1.x < r1.x + r1.w) && (p1.y > r1.y && p1.y < r1.y + r1.h);
}
static bool ExistCollision(MyRect r1, MyRect r2) {
	//Check Rect r1 corners inside Rect r2
	return ExistCollision(MyVec2(r1.x, r1.y), r2) ||
		ExistCollision(MyVec2(r1.x + r1.w, r1.y), r2) ||
		ExistCollision(MyVec2(r1.x + r1.w, r1.y + r1.h), r2) ||
		ExistCollision(MyVec2(r1.x, r1.y + r1.h), r2) ||
		//Check Rect r2 corners inside Rect r1
		ExistCollision(MyVec2(r2.x, r2.y), r1) ||
		ExistCollision(MyVec2(r2.x + r2.w, r2.y), r1) ||
		ExistCollision(MyVec2(r2.x + r2.w, r2.y + r2.h), r1) ||
		ExistCollision(MyVec2(r2.x, r2.y + r2.h), r1);
}
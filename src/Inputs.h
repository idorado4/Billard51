#pragma once
#include "Types.h"
#include "Constants.h"
#include "SDL.h"

class Inputs
{

public:

	enum class InputKeys
	{
		NONE, ESC, MOUSE_LEFT, MOUSE_RIGHT, H, QUIT, COUNT
	};
	bool keyboardPressed[(int)InputKeys::COUNT] = {};
	bool keyboardKeyDown[(int)InputKeys::COUNT] = {};


	//Time Control
	clock_t lastTime{ clock() };
	float deltaTime{ 0.f };
	std::string inputText;
private:
	SDL_Event event;

	MyVec2 mousePosition;
	MyVec2 screenSize;

public:
	Inputs();

	MyVec2 GetMousePosition();
	void SetMousePosition(MyVec2 coords);
	void SetMousePosition(int x, int y);
	void SetScreenSize(MyVec2 _screenSize);

	inline const float* GetDeltaTime() { return &deltaTime; };

	bool IsKeyPressed(InputKeys key);

	bool KeyJustPressed(InputKeys key);

	void SetKeyValue(InputKeys key, bool value);

	void SetAllKeyDownToFalse();

	inline const MyVec2* getScreenSize() const
	{
		return &screenSize;
	};


	void UpdateInput();
	void UpdateDeltaTime();

private:
	bool PollEvent();

};


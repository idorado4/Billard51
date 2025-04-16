#include "Inputs.h"

Inputs::Inputs() : inputText("")
{
	SetScreenSize(MyVec2(SCREEN_WIDTH, SCREEN_HEIGHT));
}

MyVec2 Inputs::GetMousePosition() { return mousePosition; }
void Inputs::SetMousePosition(MyVec2 newPosition) { mousePosition = newPosition; }
void Inputs::SetMousePosition(int x, int y) { mousePosition = { x, y }; }
void Inputs::SetScreenSize(MyVec2 _screenSize) { screenSize = _screenSize; };

bool Inputs::IsKeyPressed(InputKeys key)
{
	return keyboardPressed[(int)key];
}

bool Inputs::KeyJustPressed(InputKeys key)
{
	return keyboardKeyDown[(int)key];
}

void Inputs::SetKeyValue(InputKeys key, bool value)
{
	if (!keyboardPressed[(int)key]) {
		keyboardKeyDown[(int)key] = value;
	}
	else {
		keyboardKeyDown[(int)key] = false;
	}
	keyboardPressed[(int)key] = value;
}

void Inputs::SetAllKeyDownToFalse()
{
	for (int i = 0; i < (int)InputKeys::COUNT; i++)
	{
		keyboardKeyDown[i] = false;
	}
}

void Inputs::UpdateDeltaTime() {
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
}

bool Inputs::PollEvent()
{
	return SDL_PollEvent(&event);
}

void Inputs::UpdateInput()
{

	SetAllKeyDownToFalse();

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			SetKeyValue(InputKeys::QUIT, true);
			break;
		case SDL_MOUSEMOTION:
			SetMousePosition(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) SetKeyValue(InputKeys::MOUSE_LEFT, true);
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) SetKeyValue(InputKeys::MOUSE_LEFT, false);
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) SetKeyValue(InputKeys::ESC, true);
			if (event.key.keysym.sym == SDLK_h) SetKeyValue(InputKeys::H, true);
			if (event.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
				inputText.pop_back();  // borra el último carácter
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_ESCAPE) SetKeyValue(InputKeys::ESC, false);
			if (event.key.keysym.sym == SDLK_h) SetKeyValue(InputKeys::H, false);
			break;
		case SDL_TEXTINPUT:
			inputText += event.text.text;
			break;
		default:
			break;
		}
	}

}
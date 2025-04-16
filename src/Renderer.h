#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include "Types.h"
#include "Constants.h"
#include "Utils.h"


class Renderer
{
private:
	static Renderer* renderer;

	SDL_Renderer* m_renderer = nullptr;
	SDL_Window* m_window = nullptr;

	std::unordered_map<std::string, SDL_Texture*> m_textureData;
	std::unordered_map<std::string, SDL_Rect*> m_rects;
	std::unordered_map<std::string, TTF_Font*> m_fontData;


	Renderer();
public:

	static Renderer* GetInstance();
	void Render();
	void Clear();

	void LoadTexture(const std::string& id, const std::string& path);
	MyVec2 LoadTextureText(const std::string& fontId, Text text);
	void LoadRect(const std::string& idRect, const MyRect& rect);

	void PushSprite(const std::string& id, const MyRect& frame, const MyRect& position);
	void PushSprite(const std::string& id, const std::string& idRectSprite, const std::string& idRectPos);

	void LoadFont(const Font& font);

	void PushImage(const std::string& id, const std::string& idRect);

	void PushImage(const std::string& id, const MyRect& rect);

	void ModifyTexture(const std::string& id, const std::string& newId);

	MyRect GetRect(const std::string& id);

	~Renderer();

};


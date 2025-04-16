#include "Renderer.h"

Renderer* Renderer::renderer = nullptr;

Renderer::Renderer()
{
	// SDL --- INIT ---
	const Uint8 sdlFlags{ SDL_INIT_VIDEO };
	if (SDL_Init(sdlFlags) != 0)
	{
		std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	// --- WINDOW ---
	m_window = SDL_CreateWindow("Billard 51", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) throw "Cannot initialize SDL_Window";

	// --- RENDERER ---
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) throw "Cannot initialize  SDL_Renderer";

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	//IMG --- INIT ---
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_imageinit";

	//TTF --- INIT ---
	if (TTF_Init() != 0) throw"Cannot initialize SDL_ttf";
}

Renderer::~Renderer()
{
	for (auto& t : m_textureData) SDL_DestroyTexture(t.second), t.second = nullptr;
	//for (auto& f : m_fontData) TTF_CloseFont(f.second), f.second = nullptr;
	for (auto& f : m_rects) { delete f.second; f.second = nullptr; };

	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;

	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

}

Renderer* Renderer::GetInstance()
{
	if (renderer == nullptr) {
		renderer = new Renderer();
	}
	return renderer;
}

void Renderer::Render() { SDL_RenderPresent(m_renderer); };
void Renderer::Clear() { SDL_RenderClear(m_renderer); };

void Renderer::LoadTexture(const std::string& id, const std::string& path) {
	//si la textura no existe, la creo. Si existe, la reemplazo

	SDL_Texture* texture{ IMG_LoadTexture(m_renderer, path.c_str()) };
	if (texture == nullptr) throw "Can not create texture";
	if (m_textureData[id]) {
		SDL_DestroyTexture(m_textureData[id]);
	}
	m_textureData[id] = texture;

};

MyVec2 Renderer::LoadTextureText(const std::string& fontId, Text text) {

	if (text.text.empty()) {
		return { 0,0 };
	}

	SDL_Surface* tmpSurf = TTF_RenderText_Blended(m_fontData[fontId], text.text.c_str(), SDL_Color{ text.color.r, text.color.g, text.color.b,text.color.a });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";

	if (m_textureData[text.id] != nullptr) {
		SDL_DestroyTexture(m_textureData[text.id]);
	}

	m_textureData[text.id] = SDL_CreateTextureFromSurface(m_renderer, tmpSurf); //hace un new
	int w = tmpSurf->w;
	int h = tmpSurf->h;

	SDL_FreeSurface(tmpSurf);

	return { w,h };
};

void Renderer::LoadRect(const std::string& idRect, const MyRect& rect) {
	if (m_rects[idRect]) {
		m_rects[idRect] = nullptr;
		delete m_rects[idRect];
	}
	m_rects[idRect] = new SDL_Rect{ rect.x,rect.y,rect.w,rect.h };
};

void Renderer::PushSprite(const std::string& id, const MyRect& frame, const MyRect& position)
{
	auto frame2 = MyRectToSDLRect(&frame);
	auto position2 = MyRectToSDLRect(&position);
	SDL_RenderCopy(m_renderer, m_textureData[id], &frame2, &position2);
}

void Renderer::PushSprite(const std::string& id, const  std::string& idRectSprite, const  std::string& idRectPos) {

	SDL_RenderCopy(m_renderer, m_textureData[id], m_rects[idRectSprite], m_rects[idRectPos]);
}

void Renderer::LoadFont(const Font& font) {
	TTF_Font* ttfFont{ TTF_OpenFont(font.path.c_str(), font.size) };
	if (ttfFont == nullptr) throw "Can't initialize TTF_Font";
	m_fontData[font.id] = ttfFont;
}

void Renderer::PushImage(const std::string& id, const std::string& idRect) {
	SDL_RenderCopy(m_renderer, m_textureData[id], nullptr, m_rects[idRect]);
}

void Renderer::PushImage(const std::string& id, const MyRect& rect) {
	auto rect2 = MyRectToSDLRect(&rect);
	SDL_RenderCopy(m_renderer, m_textureData[id], nullptr, &rect2);
}

void Renderer::ModifyTexture(const std::string& id, const std::string& newId)
{
	m_textureData[id] = m_textureData[newId];
}

MyRect Renderer::GetRect(const std::string& id)
{
	return SDLRectToMyRect(*m_rects[id]);
}
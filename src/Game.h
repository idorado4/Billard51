#pragma once
#include <cstdint>
#include "PlayScene.h"
#include "MenuScene.h"

class Game
{
public:
	enum class GameState { MENU, PLAY, EXIT };

private:
	GameState _gameState;

	uint64_t currentTick;
	uint64_t lastTick;
	double deltaTime;

public:
	Game();
	~Game();

	void Run();
};


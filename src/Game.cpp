#include "Game.h"



Game::Game()
{
	_gameState = GameState::MENU;
}

Game::~Game()
{
}

void Game::Run()
{
	srand(time(NULL));

	Inputs inputs;
	Audio audio;

	Scene* scene = new MenuScene();

	audio.Play("menu");

	while (_gameState != GameState::EXIT) {

		//--------------DELTA TIME--------------
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());
		//--------------DELTA TIME--------------

		inputs.UpdateInput();

		switch (_gameState)
		{
		case Game::GameState::MENU:
			switch (scene->GetState())
			{
			case Scene::SceneState::UPDATE:
				scene->Update(deltaTime, &inputs, &audio);
				scene->Draw();
				break;
			case Scene::SceneState::GOTO_PLAY:
				audio.Play("game");
				delete scene;
				scene = new PlayScene();
				_gameState = GameState::PLAY;
				break;
			case Scene::SceneState::EXIT:
				delete scene;
				_gameState = GameState::EXIT;
				break;
			default:
				break;
			}
			break;

		case Game::GameState::PLAY:
			switch (scene->GetState())
			{
			case Scene::SceneState::UPDATE:
				scene->Update(deltaTime, &inputs, &audio);
				scene->Draw();
				break;
			case Scene::SceneState::GOTO_MENU:
				audio.Play("menu");
				delete scene;
				scene = new MenuScene();
				_gameState = GameState::MENU;
				break;
			case Scene::SceneState::RESTART:
				delete scene;
				scene = new PlayScene();
				_gameState = GameState::PLAY;
				break;
			case Scene::SceneState::EXIT:
				delete scene;
				_gameState = GameState::EXIT;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	scene = nullptr;
}
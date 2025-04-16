#pragma once
#include "Scene.h"
#include "Table.h"
#include "Ball.h"
#include "Pocket.h"
#include "Player.h"

class PlayScene : public Scene
{
private:
	Table table;

	Ball balls[NUM_BALLS];

	Pocket pockets[NUM_POCKETS];

	bool drawPockets;
	bool canPlayerHit;
	bool canPlayerHitTwice;
	bool endGame;
	bool firstBallInPocket;
	bool pause;
	bool playerHit;
	int winnerHitCount;

	Player player1;
	Player player2;

	int stripeBallsLeft;
	int solidBallsLeft;

private:
	void InitBalls();
	void InitPockets();

public:
	PlayScene();

	void SetupTextHUD();
	void SetupHUDEndGame();


	//Logica de la escena
	void Update(double dt, Inputs* input, Audio* audio);
	void Draw();

	void CalculateBallPaths(double dt);
	void CheckWallCollision(Ball& ball);
	void CheckBallCollision(int index);
	void CheckPocketCollision(Ball& ball, int step);
	void RackBalls();

	void CheckWinCondition(Inputs* input);


	~PlayScene();
};


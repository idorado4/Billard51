#include "PlayScene.h"
#include <iostream>

PlayScene::PlayScene() : drawPockets(false), canPlayerHit(true), solidBallsLeft((NUM_BALLS - 2) / 2), stripeBallsLeft((NUM_BALLS - 2) / 2),
canPlayerHitTwice(false), endGame(false), firstBallInPocket(true), pause(false), playerHit(false), winnerHitCount(0)
{
	sceneState = SceneState::UPDATE;

	table = Table({ SCREEN_WIDTH / 2 - TABLE_WSIZE / 2, SCREEN_HEIGHT / 2 - TABLE_HSIZE / 2, TABLE_WSIZE, TABLE_HSIZE }, { 0, 0, TABLE_SPRITE_WSIZE, TABLE_SPRITE_HSIZE });

	InitBalls();
	RackBalls();

	InitPockets();

	player1 = Player(0);
	player1.SetTurn(true);
	player2 = Player(1);

	SetupTextHUD();
	SetupHUDEndGame();
}

void PlayScene::SetupTextHUD()
{
	//HUD
	Renderer* renderer = Renderer::GetInstance();
	renderer->LoadFont({ TTF_ID_GAMEOVER, GAMEOVER_FONT_PATH, UNIT_SIZE * 2 });

	//Return the size of the RECT created containing all text
	MyVec2 textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_SCORE_PL1_INACTIVE, TXT_HITS_P1, COLOR_WHITE });
	textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_SCORE_PL1_ACTIVE, TXT_HITS_P1, COLOR_GREEN });
	renderer->LoadRect(TXT_ID_SCORE_PL1, { SCREEN_WIDTH / 4 - textSize.x / 2, 50, textSize.x, textSize.y });

	textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_HITS_P1, player1.GetHitsString(), COLOR_WHITE });
	renderer->LoadRect(TXT_ID_HITS_P1, { SCREEN_WIDTH / 3 , 50, textSize.x, textSize.y });

	textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_SCORE_PL2_INACTIVE, TXT_HITS_P2,COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_SCORE_PL2_ACTIVE, TXT_HITS_P2,COLOR_GREEN });
	renderer->LoadRect(TXT_ID_SCORE_PL2, { SCREEN_WIDTH / 4 - textSize.x / 2, 100, textSize.x, textSize.y });

	textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_HITS_P2, player2.GetHitsString(), COLOR_WHITE });
	renderer->LoadRect(TXT_ID_HITS_P2, { SCREEN_WIDTH / 3, 100 , textSize.x, textSize.y });

	textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_EXIT_N, "Back To Menu", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_EXIT_H, "Back To Menu", COLOR_BLUE });
	renderer->LoadRect(BT_ID_EXIT, { SCREEN_WIDTH - SCREEN_WIDTH / 4 - textSize.x / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4 + textSize.y, textSize.x , textSize.y });

	textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_RESTART_N, "Restart", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_RESTART_H, "Restart", COLOR_BLUE });
	renderer->LoadRect(BT_ID_RESTART, { SCREEN_WIDTH / 4 - textSize.x / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4 + textSize.y, textSize.x , textSize.y });

	textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_PLAYING_STRIPES_INACTIVE, "Stripes", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_PLAYING_STRIPES_ACTIVE, "Stripes", COLOR_GREEN });
	renderer->LoadRect(TXT_ID_PLAYING_STRIPES, { SCREEN_WIDTH / 3 + textSize.x, 50, textSize.x , textSize.y });

	textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_PLAYING_SOLIDS_INACTIVE, "Solids", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_PLAYING_SOLIDS_ACTIVE, "Solids", COLOR_GREEN });
	renderer->LoadRect(TXT_ID_PLAYING_SOLIDS, { SCREEN_WIDTH / 3 + textSize.x, 100, textSize.x , textSize.y });
}

void PlayScene::SetupHUDEndGame()
{
	//HUD
	Renderer* renderer = Renderer::GetInstance();
	renderer->LoadFont({ TTF_ID_GAMEOVER, GAMEOVER_FONT_PATH, UNIT_SIZE * 2 });

	MyVec2 textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_INSERT_NAME, "Insert Name", COLOR_WHITE });
	renderer->LoadRect(TXT_ID_INSERT_NAME, { SCREEN_WIDTH / 2 - textSize.x / 2,  SCREEN_HEIGHT / 4 , textSize.x, textSize.y });

	textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_INPUT_NAME, "", COLOR_WHITE });
	renderer->LoadRect(TXT_ID_INPUT_NAME, { SCREEN_WIDTH / 2 - textSize.x / 2,  SCREEN_HEIGHT / 4 + textSize.y , textSize.x, textSize.y });

	textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_SAVE_RANKING_N, "Save", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_SAVE_RANKING_H, "Save", COLOR_GREEN });
	renderer->LoadRect(BT_ID_SAVE_RANKING, { SCREEN_WIDTH / 2 - textSize.x / 2, SCREEN_HEIGHT / 4 + textSize.y * 2, textSize.x , textSize.y });
}

void PlayScene::InitBalls()
{
	//La blanca
	balls[0] = Ball({ SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2, BALL_SIZE, BALL_SIZE }, { BALL_SPRITE_SIZE * 3, BALL_SPRITE_SIZE * 3, BALL_SPRITE_SIZE, BALL_SPRITE_SIZE }, Ball::EBallType::WHITE);

	int spriteRow = 0;
	int spriteCol = 0;

	for (int i = 1; i < NUM_BALLS; i++)
	{
		Ball::EBallType type = i < 8 ? Ball::EBallType::SOLID : i == 8 ? Ball::EBallType::BLACK : Ball::EBallType::STRIPE;
		balls[i] = Ball(
			{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, BALL_SIZE, BALL_SIZE },
			{ BALL_SPRITE_SIZE * spriteCol, BALL_SPRITE_SIZE * spriteRow, BALL_SPRITE_SIZE, BALL_SPRITE_SIZE },
			type);
		spriteCol++;
		if (spriteCol % 4 == 0) {
			spriteCol = 0;
			spriteRow++;
		}
	}
}

void PlayScene::RackBalls()
{
	// BALL PLACES (IT HAS TO BE RANDOM EXCEPT CORNERS AND 8)
	//       1
	//      9 10
	//    3  8  4
	//   11 12 13 14
	//  2  5  6  7  15

	//TODO Place balls correctly


	float xPos = SCREEN_WIDTH / 2;
	float yPos = SCREEN_HEIGHT / 2;
	balls[0].SetPosition(xPos, yPos);
	balls[0].SetInitPosition(xPos, yPos);


	//BALL1
	xPos = SCREEN_WIDTH / 2 + TABLE_WSIZE / 4 - BALL_SIZE * 3;
	yPos = SCREEN_HEIGHT / 2;
	balls[1].SetPosition(xPos, yPos);


	//BALL9
	xPos += BALL_SIZE - 6;
	yPos += BALL_SIZE - 6;
	balls[9].SetPosition(xPos, yPos);

	//BALL10
	yPos -= BALL_SIZE * 2 - 12;
	balls[10].SetPosition(xPos, yPos);

	//BALL3
	xPos += BALL_SIZE - 6;
	yPos += BALL_SIZE * 2 + 6;
	balls[3].SetPosition(xPos, yPos);

	//BALL8
	yPos = SCREEN_HEIGHT / 2;
	balls[8].SetPosition(xPos, yPos);

	//BALL4
	yPos -= (BALL_SIZE * 2) - 12;
	balls[4].SetPosition(xPos, yPos);

	//BALL11
	xPos += BALL_SIZE - 6;
	yPos += (BALL_SIZE * 4) - 6;
	balls[11].SetPosition(xPos, yPos);

	//BALL12
	yPos -= (BALL_SIZE * 2) - 12;
	balls[12].SetPosition(xPos, yPos);

	//BALL13
	yPos -= (BALL_SIZE * 2) - 12;
	balls[13].SetPosition(xPos, yPos);

	//BALL14
	yPos -= (BALL_SIZE * 2) - 12;
	balls[14].SetPosition(xPos, yPos);

	//BALL2
	xPos += BALL_SIZE - 6;
	yPos += (BALL_SIZE * 5) + 6;
	balls[2].SetPosition(xPos, yPos);

	//BALL5
	yPos -= (BALL_SIZE * 2) - 12;
	balls[5].SetPosition(xPos, yPos);


	//BALL6
	yPos -= (BALL_SIZE * 2) - 12;
	balls[6].SetPosition(xPos, yPos);


	//BALL7
	yPos -= (BALL_SIZE * 2) - 12;
	balls[7].SetPosition(xPos, yPos);


	//BALL15
	yPos -= (BALL_SIZE * 2) - 12;
	balls[15].SetPosition(xPos, yPos);
}

void PlayScene::InitPockets()
{
	//-------------------UPPER ROW HEIGHT---------------------------
	int xPos = SCREEN_WIDTH / 2;
	int yPos = SCREEN_HEIGHT / 2 - TABLE_HSIZE / 2 + TABLE_MARGINS * 0.7f;

	//UPPER MID
	pockets[1] = Pocket({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, POCKET_SIZE, POCKET_SIZE }, { 0, 0, POCKET_SPRITE_SIZE, POCKET_SPRITE_SIZE });
	pockets[1].SetPosition(xPos, yPos);

	//UPPER LEFT
	xPos = SCREEN_WIDTH / 2 - TABLE_WSIZE / 2 + TABLE_MARGINS;
	yPos = SCREEN_HEIGHT / 2 - TABLE_HSIZE / 2 + TABLE_MARGINS;
	pockets[0] = Pocket({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, POCKET_SIZE, POCKET_SIZE }, { 0, 0, POCKET_SPRITE_SIZE, POCKET_SPRITE_SIZE });
	pockets[0].SetPosition(xPos, yPos);

	//UPPER RIGHT
	xPos = SCREEN_WIDTH / 2 + TABLE_WSIZE / 2 - TABLE_MARGINS * 0.7f;
	pockets[2] = Pocket({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,POCKET_SIZE, POCKET_SIZE }, { 0, 0, POCKET_SPRITE_SIZE, POCKET_SPRITE_SIZE });
	pockets[2].SetPosition(xPos, yPos);

	//--------------------------------------------------------------

	//-------------------BOTTOM ROW HEIGHT---------------------------
	xPos = SCREEN_WIDTH / 2;
	yPos = SCREEN_HEIGHT / 2 + TABLE_HSIZE / 2 - TABLE_MARGINS * 0.7f;

	//BOTTOM MID
	pockets[4] = Pocket({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, POCKET_SIZE, POCKET_SIZE }, { 0, 0, POCKET_SPRITE_SIZE, POCKET_SPRITE_SIZE });
	pockets[4].SetPosition(xPos, yPos);

	yPos = SCREEN_HEIGHT / 2 + TABLE_HSIZE / 2 - TABLE_MARGINS;
	xPos = SCREEN_WIDTH / 2 - TABLE_WSIZE / 2 + TABLE_MARGINS;
	//BOTTOM LEFT
	pockets[3] = Pocket({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, POCKET_SIZE, POCKET_SIZE }, { 0, 0, POCKET_SPRITE_SIZE, POCKET_SPRITE_SIZE });
	pockets[3].SetPosition(xPos, yPos);


	//BOTTOM RIGHT
	xPos = SCREEN_WIDTH / 2 + TABLE_WSIZE / 2 - TABLE_MARGINS;
	pockets[5] = Pocket({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, POCKET_SIZE, POCKET_SIZE }, { 0, 0, POCKET_SPRITE_SIZE, POCKET_SPRITE_SIZE });
	pockets[5].SetPosition(xPos, yPos);

	//--------------------------------------------------------------

}

void PlayScene::CheckWinCondition(Inputs* input)
{
	if (!endGame) return;

	if (stripeBallsLeft != 0 && solidBallsLeft != 0) {
		if (player1.IsMyTurn()) {
			//EL 2 GANA
			winnerHitCount = player2.GetHits();
			//std::cout << "Player 2 wins hits:" << player2.GetHits() << std::endl;
		}
		else {
			//EL 1 GANA
			winnerHitCount = player1.GetHits();
			//std::cout << "Player 1 wins hits:" << player1.GetHits() << std::endl;
		}
	}
	else if (solidBallsLeft == 0) {
		if ((player1.IsMyTurn() && player1.IsPlayingSolids()) || (player2.IsMyTurn() && !player2.IsPlayingSolids())) {
			//GANA EL 1
			winnerHitCount = player1.GetHits();
			//std::cout << "Player 1 wins hits:" << player1.GetHits() << std::endl;
		}
		else if ((player1.IsMyTurn() && !player1.IsPlayingSolids()) || (player2.IsMyTurn() && player2.IsPlayingSolids())) {
			//EL 2 GANA
			winnerHitCount = player2.GetHits();
			//std::cout << "Player 2 wins hits:" << player2.GetHits() << std::endl;
		}
	}
	else if (stripeBallsLeft == 0) {
		if ((player1.IsMyTurn() && !player1.IsPlayingSolids()) || (player2.IsMyTurn() && player2.IsPlayingSolids())) {
			//GANA EL 1
			winnerHitCount = player1.GetHits();
			//std::cout << "Player 1 wins hits:" << player1.GetHits() << std::endl;
		}
		else if ((player1.IsMyTurn() && player1.IsPlayingSolids()) || (player2.IsMyTurn() && !player2.IsPlayingSolids())) {
			//EL 2 GANA
			winnerHitCount = player2.GetHits();
			//std::cout << "Player 2 wins hits:" << player2.GetHits() << std::endl;
		}
	}

	//std::cout << input->inputText << std::endl;

}

void PlayScene::Update(double dt, Inputs* input, Audio* audio)
{
	Renderer* renderer = Renderer::GetInstance();

	if (input->KeyJustPressed(Inputs::InputKeys::ESC)) {
		pause = !pause;
	}

	if (pause) {

		//EXIT
		if (ExistCollision(input->GetMousePosition(), renderer->GetRect(BT_ID_EXIT))) {
			renderer->ModifyTexture(BT_ID_EXIT, BT_ID_EXIT_H);
			if (input->KeyJustPressed(Inputs::InputKeys::MOUSE_LEFT))
			{
				sceneState = SceneState::GOTO_MENU;
			}
		}
		else renderer->ModifyTexture(BT_ID_EXIT, BT_ID_EXIT_N);

		//RESTART
		if (ExistCollision(input->GetMousePosition(), renderer->GetRect(BT_ID_RESTART))) {
			renderer->ModifyTexture(BT_ID_RESTART, BT_ID_RESTART_H);
			if (input->KeyJustPressed(Inputs::InputKeys::MOUSE_LEFT))
			{
				sceneState = SceneState::RESTART;
			}
		}
		else renderer->ModifyTexture(BT_ID_RESTART, BT_ID_RESTART_N);

		return;
	}

	renderer->ModifyTexture(TXT_ID_SCORE_PL1, player1.IsMyTurn() ? TXT_ID_SCORE_PL1_ACTIVE : TXT_ID_SCORE_PL1_INACTIVE);
	renderer->ModifyTexture(TXT_ID_SCORE_PL2, player2.IsMyTurn() ? TXT_ID_SCORE_PL2_ACTIVE : TXT_ID_SCORE_PL2_INACTIVE);

	if (player1.IsPlayingSolids() && !player2.IsPlayingSolids()) {
		renderer->ModifyTexture(TXT_ID_PLAYING_STRIPES, TXT_ID_PLAYING_SOLIDS_INACTIVE);
		renderer->ModifyTexture(TXT_ID_PLAYING_SOLIDS, TXT_ID_PLAYING_STRIPES_INACTIVE);
	}
	else if (!player1.IsPlayingSolids() && player2.IsPlayingSolids()) {
		renderer->ModifyTexture(TXT_ID_PLAYING_STRIPES, TXT_ID_PLAYING_STRIPES_INACTIVE);
		renderer->ModifyTexture(TXT_ID_PLAYING_SOLIDS, TXT_ID_PLAYING_SOLIDS_INACTIVE);
	}

	CheckWinCondition(input);

	if (!endGame) {
		MyVec2 mousePos = input->GetMousePosition();
		bool mousePressed = input->KeyJustPressed(Inputs::InputKeys::MOUSE_LEFT);

		//drawPockets = true; //HACERLO CON LA H

		if (mousePressed && canPlayerHit)
		{
			balls[0].Hit(mousePos);
			CalculateBallPaths(dt);
			canPlayerHit = false;
			playerHit = true;

			if (player1.IsMyTurn()) {
				player1.AddHit();
			}
			else {
				player2.AddHit();
			}
		}

		canPlayerHit = true;
		for (int i = 0; i < NUM_BALLS; i++)
		{
			balls[i].Update(dt, input);
			canPlayerHit &= balls[i].IsStopped();
		}

		//if (canPlayerHit) return;

		if (playerHit && canPlayerHit) {
			playerHit = false;
			if (player1.IsMyTurn()) {
				player1.SetTurn(false);
				player2.SetTurn(true);

			}
			else {
				player2.SetTurn(false);
				player1.SetTurn(true);
			}
		}

		MyVec2 size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_HITS_P1 , player1.GetHitsString(), COLOR_WHITE });
		renderer->LoadRect(TXT_ID_HITS_P1, { SCREEN_WIDTH / 3 , 50, size.x, size.y });

		size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_HITS_P2 , player2.GetHitsString(), COLOR_WHITE });
		renderer->LoadRect(TXT_ID_HITS_P2, { SCREEN_WIDTH / 3 , 100, size.x, size.y });
	}
	else {

		MyVec2 textSize = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_INPUT_NAME , input->inputText ,COLOR_WHITE });
		renderer->LoadRect(TXT_ID_INPUT_NAME, { SCREEN_WIDTH / 2 - textSize.x / 2,  SCREEN_HEIGHT / 4 + textSize.y , textSize.x, textSize.y });

		//Button save ranking
		if (ExistCollision(input->GetMousePosition(), renderer->GetRect(BT_ID_SAVE_RANKING)) && !input->inputText.empty()) {
			renderer->ModifyTexture(BT_ID_SAVE_RANKING, BT_ID_SAVE_RANKING_H);
			if (input->KeyJustPressed(Inputs::InputKeys::MOUSE_LEFT))
			{
				RankingList* rankingList = RankingList::GetInstance();
				rankingList->InsertPlayer(input->inputText, winnerHitCount);
				input->inputText.clear();
				rankingList->UpdateFile();
				sceneState = SceneState::GOTO_MENU;
			}
		}
		else renderer->ModifyTexture(BT_ID_SAVE_RANKING, BT_ID_SAVE_RANKING_N);
	}


}

void PlayScene::Draw()
{

	Renderer* renderer = Renderer::GetInstance();
	renderer->Clear();

	if (!endGame)
	{
		table.Draw();
		for (int i = 0; i < NUM_POCKETS && drawPockets; i++)
		{
			pockets[i].Draw();
		}
		for (int i = 0; i < NUM_BALLS; i++)
		{
			balls[i].Draw();
		}

		renderer->PushImage(TXT_ID_SCORE_PL1, TXT_ID_SCORE_PL1);
		renderer->PushImage(TXT_ID_HITS_P1, TXT_ID_HITS_P1);
		renderer->PushImage(TXT_ID_SCORE_PL2, TXT_ID_SCORE_PL2);
		renderer->PushImage(TXT_ID_HITS_P2, TXT_ID_HITS_P2);
		renderer->PushImage(TXT_ID_PLAYING_STRIPES, TXT_ID_PLAYING_STRIPES);
		renderer->PushImage(TXT_ID_PLAYING_SOLIDS, TXT_ID_PLAYING_SOLIDS);

		if (pause) {
			renderer->PushImage(BT_ID_EXIT, BT_ID_EXIT);
			renderer->PushImage(BT_ID_RESTART, BT_ID_RESTART);
		}
	}
	else {
		renderer->PushImage(TXT_ID_INSERT_NAME, TXT_ID_INSERT_NAME);
		renderer->PushImage(TXT_ID_INPUT_NAME, TXT_ID_INPUT_NAME);
		renderer->PushImage(BT_ID_SAVE_RANKING, BT_ID_SAVE_RANKING);


	}



	renderer->Render();

	renderer = nullptr;
	delete renderer;
}

void PlayScene::CalculateBallPaths(double dt)
{
	for (int ballIndex = 0; ballIndex < NUM_BALLS; ballIndex++)
	{
		balls[ballIndex].ClearPath();
	}

	float friction = 0.95f;

	for (int stepIndex = 0; stepIndex < BALL_STEPS; stepIndex++)
	{
		for (int ballIndex = 0; ballIndex < NUM_BALLS; ballIndex++)
		{
			Ball& currentBall = balls[ballIndex];
			if (!currentBall.IsVisible())
				continue;

			MyVec2f velocity = currentBall.GetVelocity();
			if (velocity.x != 0.0f || velocity.y != 0.0f) {
				currentBall.SetStopped(false);
			}
			MyVec2f position = currentBall.GetPosition();
			MyVec2f step = velocity * dt;

			position += step;
			velocity *= friction;

			currentBall.SetPosition(position);
			currentBall.SetVelocity(velocity);
			currentBall.AddPositionToPath(position);
		}

		for (int i = 0; i < NUM_BALLS; i++) {

			if (!balls[i].IsEnabled()) continue;

			CheckBallCollision(i);
			CheckPocketCollision(balls[i], stepIndex);
			CheckWallCollision(balls[i]);
		}

	}
}


void PlayScene::CheckWallCollision(Ball& ball)
{
	if (!ball.IsEnabled()) return;

	float restitution = 0.95f;
	MyVec2f pos = ball.GetPosition();
	MyVec2f vel = ball.GetVelocity();
	//LEFT-RIGHT

	if (pos.x - BALL_RADIUS < table.leftLimit()) {
		float overlap = abs((pos.x - BALL_RADIUS) - table.leftLimit());
		pos.x += overlap;
		vel.x *= -1 * restitution;
	}
	else if (pos.x + BALL_RADIUS > table.rightLimit()) {
		float overlap = abs((pos.x + BALL_RADIUS) - table.rightLimit());
		pos.x -= overlap;
		vel.x *= -1 * restitution;
	}

	//TOP BOTTOM
	if (pos.y - BALL_RADIUS < table.topLimit()) {
		float overlap = abs((pos.y - BALL_RADIUS) - table.topLimit());
		pos.y += overlap;
		vel.y *= -1 * restitution;
	}
	else if (pos.y + BALL_RADIUS > table.bottomLimit()) {
		float overlap = abs((pos.y + BALL_RADIUS) - table.bottomLimit());
		pos.y -= overlap;
		vel.y *= -1 * restitution;
	}

	ball.SetPosition(pos);
	ball.SetVelocity(vel);

}


void PlayScene::CheckBallCollision(int index)
{
	float radius = BALL_RADIUS;
	float restitution = 0.6f;
	Ball& ball = balls[index];

	for (int i = index; i < NUM_BALLS; i++)
	{
		Ball& other = balls[i];
		if (!other.IsEnabled()) continue;

		MyVec2f diff = ball.GetPosition() - other.GetPosition();
		float distance = sqrt(diff.x * diff.x + diff.y * diff.y);
		float minDist = radius + radius;

		if (distance < minDist && distance > 0.0f) {

			MyVec2f normal = diff * (1.0f / distance);

			// Separación
			float overlap = (minDist - distance) * 0.51f;
			ball.SetPosition(ball.GetPosition() + normal * overlap);
			other.SetPosition(other.GetPosition() - normal * overlap);

			/*MyVec2f vel = ball.GetVelocity();
			ball.SetVelocity(vel * -0.7f);
			other.SetVelocity(vel * 0.9f);*/

			MyVec2f relativeVel = ball.GetVelocity() - other.GetVelocity();
			float velAlongNormal = normal.x * relativeVel.x + normal.y * relativeVel.y;

			// Solo si se están acercando
			if (velAlongNormal < 0) {
				float impulse = -velAlongNormal * 0.1f; // Factor de rebote (0.5 = 50% de energía)

				ball.SetVelocity(ball.GetVelocity() + normal * impulse);
				other.SetVelocity(other.GetVelocity() - normal * impulse);
			}
		}
	}
}

void PlayScene::CheckPocketCollision(Ball& ball, int step)
{

	MyVec2f ballPos = ball.GetPosition();

	for (int i = 0; i < NUM_POCKETS; i++)
	{
		MyVec2f holePosition = pockets[i].GetPosition();

		MyVec2f toHole = holePosition - ballPos;
		float distSq = toHole.sqrLength();

		if (distSq <= POCKET_RADIUS * POCKET_RADIUS) {

			if (firstBallInPocket) {
				firstBallInPocket = false;

				Ball::EBallType type = ball.GetType();
				if (player1.IsMyTurn()) {
					player1.SetPlayingType(type == Ball::EBallType::SOLID);
					player2.SetPlayingType(type != Ball::EBallType::SOLID);
				}
				else {
					player2.SetPlayingType(type == Ball::EBallType::SOLID);
					player1.SetPlayingType(type != Ball::EBallType::SOLID);
				}
			}

			ball.GetInHole(step);
			ball.SetVelocity(MyVec2f(0, 0));

			Player currentPlayer = player1.IsMyTurn() ? player1 : player2;

			if (ball.GetType() == Ball::EBallType::STRIPE) {
				stripeBallsLeft--;
				if (currentPlayer.IsPlayingSolids()) {
					canPlayerHitTwice = true;
				}
			}
			else if (ball.GetType() == Ball::EBallType::SOLID) {
				solidBallsLeft--;
				if (!currentPlayer.IsPlayingSolids()) {
					canPlayerHitTwice = true;
				}
			}
			else if (ball.GetType() == Ball::EBallType::BLACK) {
				endGame = true;
			}


			break;
		}
	}
}



PlayScene::~PlayScene()
{
}

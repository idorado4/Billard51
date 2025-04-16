#include "MenuScene.h"

MenuScene::MenuScene()
{
	sceneState = SceneState::UPDATE;

	Renderer* renderer = Renderer::GetInstance();

	renderer->LoadFont({ TTF_ID_GAMEOVER, GAMEOVER_FONT_PATH, 150 });

	//BUTTON PLAY
	MyVec2 size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_PLAY_N, "Play", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_PLAY_H, "Play", COLOR_BLUE });
	renderer->LoadRect(BT_ID_PLAY, { SCREEN_WIDTH / 2 - size.x / 2, 20, size.x , size.y });

	//TEXT AUDIO
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_AUDIO, "Audio", COLOR_WHITE });
	renderer->LoadRect(TXT_ID_AUDIO, { SCREEN_WIDTH / 2 - size.x - 40, 80 , size.x, size.y });

	//BUTTONS AUDIO
	//Left
	size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_LEFT_AUDIO_N, " > ", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_LEFT_AUDIO_H, " > ", COLOR_BLUE });
	renderer->LoadRect(BT_ID_LEFT_AUDIO, { SCREEN_WIDTH / 2 - size.x / 2 - 20, 80, size.x , size.y });

	//Right
	size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_RIGHT_AUDIO_N, " < ", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_RIGHT_AUDIO_H, " < ", COLOR_BLUE });
	renderer->LoadRect(BT_ID_RIGHT_AUDIO, { SCREEN_WIDTH / 2 + size.x + 20, 80, size.x , size.y });

	//On-Off
	size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_ON_AUDIO_N, "On", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_ON_AUDIO_H, "On", COLOR_GREEN });
	size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_OFF_AUDIO_N, "Off", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_OFF_AUDIO_H, "Off", COLOR_RED });
	renderer->LoadRect(BT_ID_ONOFF_AUDIO, { SCREEN_WIDTH / 2 + size.x + 50, 80, size.x , size.y });

	//Delete Ranking
	size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_DELETE_RANK_N, "Delete Ranking", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_DELETE_RANK_H, "Delete Ranking", COLOR_RED });
	renderer->LoadRect(BT_ID_DELETE_RANK, { SCREEN_WIDTH / 2 - size.x / 2, 150, size.x , size.y });

	//Exit
	size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_EXIT_N, "Exit", COLOR_WHITE });
	renderer->LoadTextureText(TTF_ID_GAMEOVER, { BT_ID_EXIT_H, "Exit", COLOR_BLUE });
	renderer->LoadRect(BT_ID_EXIT, { SCREEN_WIDTH / 2 - size.x / 2, 220, size.x , size.y });

}

void MenuScene::Update(double dt, Inputs* input, Audio* audio)
{
	Renderer* renderer = Renderer::GetInstance();

	//BUTTON PLAY
	if (ExistCollision(input->GetMousePosition(), renderer->GetRect(BT_ID_PLAY))) {
		renderer->ModifyTexture(BT_ID_PLAY, BT_ID_PLAY_H);
		if (input->KeyJustPressed(Inputs::InputKeys::MOUSE_LEFT))
		{
			sceneState = SceneState::GOTO_PLAY;
		}
	}
	else renderer->ModifyTexture(BT_ID_PLAY, BT_ID_PLAY_N);

	//BUTTON AUDIO
	//LEFT
	if (ExistCollision(input->GetMousePosition(), renderer->GetRect(BT_ID_LEFT_AUDIO))) {
		renderer->ModifyTexture(BT_ID_LEFT_AUDIO, BT_ID_LEFT_AUDIO_H);
		if (input->KeyJustPressed(Inputs::InputKeys::MOUSE_LEFT))
		{
			audio->VolumeDown();
		}
	}
	else renderer->ModifyTexture(BT_ID_LEFT_AUDIO, BT_ID_LEFT_AUDIO_N);

	//RIGHT
	if (ExistCollision(input->GetMousePosition(), renderer->GetRect(BT_ID_RIGHT_AUDIO))) {
		renderer->ModifyTexture(BT_ID_RIGHT_AUDIO, BT_ID_RIGHT_AUDIO_H);
		if (input->KeyJustPressed(Inputs::InputKeys::MOUSE_LEFT))
		{
			audio->VolumeUp();
		}
	}
	else renderer->ModifyTexture(BT_ID_RIGHT_AUDIO, BT_ID_RIGHT_AUDIO_N);

	//Volume num
	MyVec2 size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_AUDIO_VALUE , audio->GetVolumeString(), COLOR_WHITE });
	renderer->LoadRect(TXT_ID_AUDIO_VALUE, { SCREEN_WIDTH / 2 , 80, size.x, size.y });

	//On-Off
	if (ExistCollision(input->GetMousePosition(), renderer->GetRect(BT_ID_ONOFF_AUDIO))) {
		renderer->ModifyTexture(BT_ID_ONOFF_AUDIO, audio->IsPlaying() ? BT_ID_OFF_AUDIO_H : BT_ID_ON_AUDIO_H);
		if (input->KeyJustPressed(Inputs::InputKeys::MOUSE_LEFT))
		{
			if (audio->IsPlaying()) {
				audio->Pause();
			}
			else {
				audio->Resume();
			}
		}
	}
	else renderer->ModifyTexture(BT_ID_ONOFF_AUDIO, audio->IsPlaying() ? BT_ID_OFF_AUDIO_N : BT_ID_ON_AUDIO_N);

	//Delete Ranking
	if (ExistCollision(input->GetMousePosition(), renderer->GetRect(BT_ID_DELETE_RANK))) {
		renderer->ModifyTexture(BT_ID_DELETE_RANK, BT_ID_DELETE_RANK_H);
		if (input->KeyJustPressed(Inputs::InputKeys::MOUSE_LEFT))
		{
			ranking.Delete();
		}
	}
	else renderer->ModifyTexture(BT_ID_DELETE_RANK, BT_ID_DELETE_RANK_N);

	//EXIT
	if (ExistCollision(input->GetMousePosition(), renderer->GetRect(BT_ID_EXIT))) {
		renderer->ModifyTexture(BT_ID_EXIT, BT_ID_EXIT_H);
		if (input->KeyJustPressed(Inputs::InputKeys::MOUSE_LEFT))
		{
			sceneState = SceneState::EXIT;
		}
	}
	else renderer->ModifyTexture(BT_ID_EXIT, BT_ID_EXIT_N);
}

void MenuScene::Draw()
{
	Renderer* renderer = Renderer::GetInstance();
	renderer->Clear();

	renderer->PushImage(BT_ID_PLAY, BT_ID_PLAY);
	renderer->PushImage(TXT_ID_AUDIO, TXT_ID_AUDIO);
	renderer->PushImage(BT_ID_LEFT_AUDIO, BT_ID_LEFT_AUDIO);
	renderer->PushImage(BT_ID_RIGHT_AUDIO, BT_ID_RIGHT_AUDIO);
	renderer->PushImage(BT_ID_ONOFF_AUDIO, BT_ID_ONOFF_AUDIO);
	renderer->PushImage(TXT_ID_AUDIO_VALUE, TXT_ID_AUDIO_VALUE);
	renderer->PushImage(BT_ID_DELETE_RANK, BT_ID_DELETE_RANK);
	renderer->PushImage(BT_ID_EXIT, BT_ID_EXIT);

	ranking.Draw();

	renderer->Render();

	renderer = nullptr;
	delete renderer;
}

MenuScene::~MenuScene()
{
}

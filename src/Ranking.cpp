#include "Ranking.h"

Ranking::Ranking()
{

	Renderer* renderer = Renderer::GetInstance();
	renderer->LoadFont({ TTF_ID_GAMEOVER, GAMEOVER_FONT_PATH, UNIT_SIZE * 2 });

	RankingList* rankingList = RankingList::GetInstance();
	MyVec2 size;


	for (int i = 0; i < rankingList->GetSize(); i++) {
		size = renderer->LoadTextureText(TTF_ID_GAMEOVER, { TXT_ID_RANKING_SCORES + std::to_string(i), rankingList->GetRankingData(i), COLOR_WHITE });
		renderer->LoadRect(TXT_ID_RANKING_SCORES + std::to_string(i), { SCREEN_WIDTH / 2 - size.x / 2, 400 + (i * size.y),size.x,size.y });
	}
}

void Ranking::Update()
{
}

void Ranking::Draw()
{
	Renderer* renderer = Renderer::GetInstance();
	RankingList* rankingList = RankingList::GetInstance();

	for (int i = 0; i < rankingList->GetSize(); i++) {
		renderer->PushImage(TXT_ID_RANKING_SCORES + std::to_string(i), TXT_ID_RANKING_SCORES + std::to_string(i));
	}
}

void Ranking::Delete()
{
	RankingList* rankingList = RankingList::GetInstance();
	rankingList->ClearFile();
}


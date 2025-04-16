#pragma once
#include <queue>
#include <string>
#include <fstream>
#include <iostream>
#include "Constants.h"


class RankingList
{
private:
	static RankingList* rankingList;


	struct playersScore {
		int score;
		std::string name;
	};

	std::vector<playersScore> ranking;

	RankingList();

public:
	static RankingList* GetInstance();

	void InsertPlayer(std::string name, int score);

	void UpdateFile();

	inline int GetSize()const { return ranking.size(); };

	void PrintPlayer(int playerIndex);
	
	std::string GetRankingData(int pos);

	void ClearFile();

	friend bool operator<(const RankingList::playersScore& playerScore1, const RankingList::playersScore& playerScore2);

};


#pragma once
#include "Types.h"

class Player
{

private:
	int numPlayer;
	int hits;
	bool isMyTurn;
	bool playingSolids;

public:
	Player();
	Player(int numPlayer);

	void SetTurn(bool value);
	bool IsMyTurn();
	void AddHit();
	int GetHits();
	std::string GetHitsString();
	bool IsPlayingSolids();
	void SetPlayingType(bool solids);

	~Player();
};


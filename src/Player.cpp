#include "Player.h"

Player::Player() : numPlayer(0), hits(0), isMyTurn(false), playingSolids(false)
{
}

Player::Player(int numPlayer) : numPlayer(numPlayer), hits(0), isMyTurn(false), playingSolids(false)
{
}

void Player::SetTurn(bool value)
{
	isMyTurn = value;
}

bool Player::IsMyTurn()
{
	return isMyTurn;
}

void Player::AddHit()
{
	hits++;
}

int Player::GetHits()
{
	return hits;
}

std::string Player::GetHitsString()
{
	return std::to_string(hits);
}

bool Player::IsPlayingSolids()
{
	return playingSolids;
}

void Player::SetPlayingType(bool solids)
{
	playingSolids = solids;
}

Player::~Player()
{
}

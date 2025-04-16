#include "Pocket.h"

Pocket::Pocket() : GameObject({ 0,0,0,0 }, { 0,0,0,0 }), position({ 0.0f, 0.0f }), radius(15.0f)
{

}

Pocket::Pocket(MyRect _transformPosition, MyRect _frame) : GameObject(_transformPosition, _frame),
position(_transformPosition.x + POCKET_SIZE / 2, _transformPosition.y + POCKET_SIZE / 2), radius(15.0f)
{
	Renderer::GetInstance()->LoadTexture(POCKET_ID, POCKET_PATH);
	Renderer::GetInstance()->LoadRect(POCKET_ID, _transformPosition);
}

void Pocket::Draw()
{
	Renderer::GetInstance()->PushSprite(POCKET_ID, frame, transform);
}

void Pocket::Update(const double dt, Inputs* input/*, Audio* audio*/)
{
}

float Pocket::GetRadius()
{
	return radius;
}

MyVec2f Pocket::GetCenter()
{
	return MyVec2f{ static_cast<float>(transform.x + POCKET_SIZE / 2), static_cast<float>(transform.y + POCKET_SIZE / 2) };
}

MyVec2f Pocket::GetPosition()
{
	return position;
}

void Pocket::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	SetTransformPosition(static_cast<int>(x) - POCKET_SIZE / 2, static_cast<int>(y) - POCKET_SIZE / 2);
}

void Pocket::SetPosition(MyVec2f newPosition)
{
	SetPosition(newPosition.x, newPosition.y);
}
Pocket::~Pocket()
{

}

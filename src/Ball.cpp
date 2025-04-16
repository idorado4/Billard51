#include "Ball.h"
#include <iostream>

Ball::Ball() : GameObject({ 0,0,0,0 }, { 0,0,0,0 }), type(EBallType::NONE), velocity({ 0,0 }),
position({ 0.0f, 0.0f }), initPosition({ 0.0f, 0.0f }), endPosition({ 0.0f, 0.0f }), currentStep(0), visible(true), stopped(true), enabled(true)
{
}

Ball::Ball(MyRect _transformPosition, MyRect _frame, EBallType _type) : GameObject(_transformPosition, _frame), type(_type), velocity({ 0,0 }),
position(_transformPosition.x + BALL_SIZE / 2, _transformPosition.y + BALL_SIZE / 2), initPosition({ position }), endPosition({}), currentStep(0),
visible(true), stopped(true), enabled(true)
{
	Renderer::GetInstance()->LoadTexture(BALLS_ID, BALLS_PATH);
	Renderer::GetInstance()->LoadRect(BALLS_ID, _transformPosition);
}

void Ball::Update(const double dt, Inputs* input)
{
	if (!path.empty() && currentStep < path.size() - 1 && visible) {

		auto step = path[currentStep];

		MyVec2f nextPosition = std::get<0>(step);
		SetPosition(nextPosition);
		position = nextPosition;
		currentStep++;

		bool holeIn = std::get<1>(step);
		visible = !holeIn;
	}

	if (!stopped && currentStep >= path.size() - 1) {
		stopped = true;
	}

	if (path.empty() && !stopped) {
		stopped = true;
	}


}

void Ball::Draw()
{
	if (!visible && type == EBallType::WHITE) {
		SetPosition(initPosition);
		visible = true;
	}
	else if (!visible && type == EBallType::BLACK) {
		//DE MOMENTO HAS PERDIDO, HACER VICTORIA SI CONVIENE
		stopped = true;
		return;
	}
	else if (!visible)
	{
		stopped = true;
		return;
	}

	Renderer::GetInstance()->PushSprite(BALLS_ID, frame, transform);
}

void Ball::SetVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void Ball::SetVelocity(MyVec2 newVelocity)
{
	velocity.x = newVelocity.x;
	velocity.y = newVelocity.y;
}

void Ball::SetVelocity(MyVec2f newVelocity)
{
	velocity = newVelocity;
}

MyVec2f Ball::GetVelocity()
{
	return velocity;
}

void Ball::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	SetTransformPosition(static_cast<int>(x) - BALL_SIZE / 2, static_cast<int>(y) - BALL_SIZE / 2);
}

void Ball::SetPosition(MyVec2f newPosition)
{
	SetPosition(newPosition.x, newPosition.y);
}

void Ball::SetInitPosition(float x, float y)
{
	initPosition.x = x;
	initPosition.y = y;
}
void Ball::SetInitPosition(MyVec2f initPos)
{
	SetInitPosition(initPos.x, initPos.y);
}


MyVec2f Ball::GetPosition()
{
	return position;
}

void Ball::AddPositionToPath(MyVec2f step)
{
	path.push_back(std::make_tuple(step, false));
}

MyVec2f Ball::GetCenter()
{
	return MyVec2f{ static_cast<float>(transform.x + BALL_SIZE / 2), static_cast<float>(transform.y + BALL_SIZE / 2) };
}

void Ball::Hit(const MyVec2 mousePos)
{
	MyVec2f mousePosf = { (float)mousePos.x, (float)mousePos.y };
	MyVec2f direction = GetPosition() - mousePosf;
	float distance = direction.length();
	float force = distance * 0.01f;
	velocity = direction.normalized() * force;
	stopped = false;
}

void Ball::ClearPath()
{
	path.clear();
	currentStep = 0;
}

void Ball::GetInHole(int step)
{
	std::get<1>(path[step]) = true;
	if (type != EBallType::WHITE)
	{
		enabled = false;
	}
}

bool Ball::IsVisible()
{
	return visible;
}

bool Ball::IsEnabled()
{
	return enabled;
}

void Ball::SetEnabled(bool value)
{
	enabled = value;
}

void Ball::SetStopped(bool value)
{
	stopped = value;
}

bool Ball::IsStopped()
{
	return stopped;
}

int Ball::PathSize()
{
	return path.size();
}

Ball::EBallType Ball::GetType()
{
	return type;
}


Ball::~Ball()
{
}

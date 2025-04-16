#pragma once
#include "GameObject.h"
#include "Table.h"
#include <tuple>

class Ball : public GameObject
{

public:
	enum class EBallType { NONE = 0, SOLID, STRIPE, WHITE, BLACK };

private:

	MyVec2f velocity;

	MyVec2f position;
	MyVec2f initPosition;
	MyVec2f endPosition;
	int currentStep;
	bool stopped;

	bool visible;
	bool enabled;
	
	EBallType type;
	std::vector<std::tuple<MyVec2f, bool>> path;

public:
	Ball();
	Ball(MyRect _position, MyRect _frame, EBallType _type);

	void Update(const double dt, Inputs* input/*, Audio* audio*/);
	void Draw();

	void SetVelocity(float x, float y);
	void SetVelocity(MyVec2 newVelocity);
	void SetVelocity(MyVec2f newVelocity);
	MyVec2f GetVelocity();
	void SetPosition(float x, float y);
	void SetPosition(MyVec2f newPosition);
	void SetInitPosition(float x, float y);
	void SetInitPosition(MyVec2f initPos);
	MyVec2f GetPosition();
	void AddPositionToPath(MyVec2f step);
	MyVec2f GetCenter();

	void Hit(const MyVec2 mousePos);
	void ClearPath();

	void GetInHole(int step);
	bool IsVisible();
	bool IsEnabled();
	void SetEnabled(bool value);
	void SetStopped(bool value);
	bool IsStopped();
	int PathSize();
	EBallType GetType();


	~Ball();

};


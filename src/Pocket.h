#pragma once
#include "GameObject.h"

class Pocket : public GameObject
{

private:
	//Center of the object
	MyVec2f position;
	float radius;

public:
	Pocket();
	Pocket(MyRect _position, MyRect _frame);

	void Draw();
	void Update(const double dt, Inputs* input/*, Audio* audio*/);

	float GetRadius();
	MyVec2f GetCenter();
	MyVec2f GetPosition();
	void SetPosition(float x, float y);
	void SetPosition(MyVec2f newPosition);

	~Pocket();

};


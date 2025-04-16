#pragma once
#include "GameObject.h"

class Table : public GameObject
{

private:
	//LIMITS
	float right, left, top, bottom;


public:
	Table();
	Table(MyRect _position, MyRect _frame);

	void Update(double dt, Inputs* input);
	void Draw();

	float leftLimit() const { return left; }
	float rightLimit() const { return right; }
	float topLimit() const { return top; }
	float bottomLimit() const { return bottom; }

	~Table();

};


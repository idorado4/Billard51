#pragma once
#include "Renderer.h"
//#include "Collision.h"
#include "Inputs.h"

class GameObject
{
protected:
	MyRect transform, frame;
public:
	GameObject();
	GameObject(MyRect _position, MyRect _frame);
	virtual void Update(const double dt, Inputs* input) = 0;
	virtual void Draw() = 0;
	virtual MyVec2 TransformPosition();
	virtual void SetTransformPosition(int x, int y);
	virtual void SetTransformPosition(MyVec2 newPosition);
	virtual MyVec2 Scale();
	virtual void SetScale(int w, int h);
	virtual void SetScale(MyVec2 newScale);
	virtual MyRect GetFrame();
};


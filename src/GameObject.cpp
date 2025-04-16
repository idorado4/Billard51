#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(MyRect _transform, MyRect _frame) : transform(_transform), frame(_frame) {}

MyVec2 GameObject::TransformPosition()
{
	return MyVec2{ transform.x, transform.y };
}

void GameObject::SetTransformPosition(int x, int y)
{
	transform.x = x;
	transform.y = y;
}

void GameObject::SetTransformPosition(MyVec2 newPosition)
{
	transform.x = newPosition.x;
	transform.y = newPosition.y;
}

MyVec2 GameObject::Scale()
{
	return MyVec2{ transform.w, transform.h };;
}

void GameObject::SetScale(int w, int h)
{
	transform.w = w;
	transform.h = h;
}

void GameObject::SetScale(MyVec2 newScale)
{
	transform.w = newScale.x;
	transform.h = newScale.y;
}

MyRect GameObject::GetFrame()
{
	return frame;
}

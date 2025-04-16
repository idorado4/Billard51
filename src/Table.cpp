#include "Table.h"

Table::Table() : GameObject({ 0,0,0,0 }, { 0,0,0,0 }), right(0.0f), left(0.0f), top(0.0f), bottom(0.0f)
{
}

Table::Table(MyRect _position, MyRect _frame) :
	GameObject(_position, _frame),
	right((float)_position.x + TABLE_WSIZE - TABLE_MARGINS),
	left((float)_position.x + TABLE_MARGINS),
	top((float)_position.y + TABLE_MARGINS),
	bottom((float)_position.y + TABLE_HSIZE - TABLE_MARGINS)
{
	Renderer::GetInstance()->LoadTexture(TABLE_ID, TABLE_PATH);
	Renderer::GetInstance()->LoadRect(TABLE_ID, _position);

}

void Table::Update(double dt, Inputs* input)
{

}

void Table::Draw()
{
	Renderer::GetInstance()->PushSprite(TABLE_ID, frame, transform);
}

Table::~Table()
{
}

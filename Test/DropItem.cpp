#include "DropItem.h"
extern double frame_time;

void DropItem::update()
{
	pos.y = std::sin(xDir/3.14);
	xDir += frame_time;
}

void DropItem::Draw(HDC mDC)
{
	int width = image.GetWidth() * 2;
	int height = image.GetHeight() * 2;
	image.Draw(mDC, pos.x - width / 2, pos.y - height / 2, width, height);
}

void DropItem::handle_collision(int otherLayer, int damage)
{
	if (otherLayer == player) {

	}
}

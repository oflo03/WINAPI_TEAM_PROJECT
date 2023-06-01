#include"Collider.h"

void Collider::detection()
{
	for (auto& other : COLL)
		if (this->shape == 1)
			if (other->shape == 1)
				if (this->pos - other->pos <= this->size + other->size)
					collisionMsg.emplace(Vector2D<int>(0, 0)); else;
			else if (other->shape == 2)
				if (((this->pos - other->pos) - (((this->pos - other->pos).Normalize() * other->radius))) <= this->size)
					collisionMsg.emplace(Vector2D<int>(0, 0)); else;
			else;
		else if (this->shape == 2)
			if (other->shape == 1)
				if (((this->pos - other->pos) - (((this->pos - other->pos).Normalize() * this->radius))) <= other->size)
					collisionMsg.emplace(Vector2D<int>(0, 0)); else;
			else if (other->shape == 2)
				if ((this->pos - other->pos).GetLenth() <= this->radius + other->radius)
					collisionMsg.emplace(Vector2D<int>(0, 0));
}


HBRUSH GREEN = CreateSolidBrush(RGB(0, 255, 0));
void Collider::draw_range(HDC mDC)
{
	RECT FR(pos.x - size.x, pos.y - size.y, pos.x + size.x, pos.y + size.y);
	if (this->shape == 1)
		FrameRect(mDC, &FR, GREEN);
	else if (this->shape == 2)
	{
		HBRUSH old = (HBRUSH)SelectObject(mDC, GREEN);
		Arc(mDC, FR.left, FR.top, FR.right, FR.bottom, pos.x, FR.top, pos.x, FR.top);
		SelectObject(mDC, old);
	}
}

void ColliderUpdate()
{
	for (auto& c : COLL)
		c->detection();

}
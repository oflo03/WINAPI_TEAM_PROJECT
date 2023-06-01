#include"Collider.h"

void Collider::detection()
{
	for (auto& other : COLL)
		if (this->shape == 1)
			if (other->shape == 1)
				if (this->pos - other->pos <= this->size + other->size)
					collisionMsg.emplace(Vector2D<Master*>(this->owner, other->owner)); else;
			else if (other->shape == 2)
				if (((this->pos - other->pos) - (((this->pos - other->pos).Normalize() * other->size.x))) <= this->size)
					collisionMsg.emplace(Vector2D<Master*>(this->owner, other->owner)); else;
			else;
		else if (this->shape == 2)
			if (other->shape == 1)
				if (((this->pos - other->pos) - (((this->pos - other->pos).Normalize() * this->size.x))) <= other->size)
					collisionMsg.emplace(Vector2D<Master*>(this->owner, other->owner)); else;
			else if (other->shape == 2)
				if ((this->pos - other->pos).GetLenth() <= this->size.x + other->size.x)
					collisionMsg.emplace(Vector2D<Master*>(this->owner, other->owner));
}

HBRUSH GREENB = CreateSolidBrush(RGB(0, 255, 0));
HPEN GREENP = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

void Collider::draw_range(HDC mDC)
{
	RECT FR(pos.x - size.x, pos.y - size.y, pos.x + size.x, pos.y + size.y);
	if (this->shape == 1)
		FrameRect(mDC, &FR, GREENB);
	else if (this->shape == 2)
	{
		HPEN old = (HPEN)SelectObject(mDC, GREENP);
		Arc(mDC, FR.left, FR.top, FR.right, FR.bottom, pos.x, FR.top, pos.x, FR.top);
		SelectObject(mDC, old);
	}
}

void ColliderUpdate()
{
	for (auto& c : COLL)
		c->detection();

}
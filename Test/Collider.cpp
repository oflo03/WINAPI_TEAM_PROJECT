#include"Master.h"

bool collisionable[6][6]
{
	0,1,1,1,1,1,
	1,0,0,1,0,1,
	1,0,0,1,0,0,
	1,1,1,1,1,0,
	1,0,0,1,0,1,
	1,1,0,0,0,0
};

void Collider::detection()
{
	for (auto& other : COLL) {
		if (this == other) continue;
		if (!collisionable[this->layer][other->layer]) continue;
		if (this->shape == 1)
			if (other->shape == 1)
				if (this->pos - other->pos <= this->size + other->size)
					collisionMsg.emplace(CollisionMessage(this->owner, other->layer)); else;
			else if (other->shape == 2)
				if (((this->pos - other->pos) - (((this->pos - other->pos).Normalize() * other->size.x))) <= this->size)
					collisionMsg.emplace(CollisionMessage(this->owner, other->layer)); else; else;
		else if (this->shape == 2)
			if (other->shape == 1)
				if (((this->pos - other->pos) - (((this->pos - other->pos).Normalize() * this->size.x))) <= other->size)
					collisionMsg.emplace(CollisionMessage(this->owner, other->layer)); else;
			else if (other->shape == 2)
				if ((this->pos - other->pos).GetLenth() <= this->size.x + other->size.x)
					collisionMsg.emplace(CollisionMessage(this->owner,other->layer));
	}
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
	CollisionMessage msg;
	while (!collisionMsg.empty())
	{
		msg = collisionMsg.front();
		msg.collided->handle_collision(msg.otherLayer);
	}
}
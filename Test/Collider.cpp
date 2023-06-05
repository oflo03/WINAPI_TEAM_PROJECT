#include"Collider.h"
#include"Master.h"

//	wall, player, rolled_player, enemy, playerBullet, enemyBullet
bool collisionable[6][6]
{
	0,0,0,0,0,0,
	1,0,0,1,0,1,
	1,0,0,1,0,0,
	1,1,1,1,1,0,
	1,0,0,1,0,0,
	1,1,0,0,0,0
};

std::queue<CollisionMessage> collisionMsg;


void Collider::detection()
{
	for (auto& other : COLL) {
		if (this == other.get()) continue;
		if (!collisionable[this->layer][other->layer]) continue;
		if (this->shape == rect)
			if (other->shape == rect)
				if (this->pos - other->pos <= this->size + other->size)
					collisionMsg.emplace(CollisionMessage(this->owner, other->layer)); else;
			else if (other->shape == circle)
				if (((this->pos - other->pos <= this->size + other->size) ||
					((this->pos - other->pos) > this->size) && ((this->pos - other->pos).Vabs() - this->size.Vabs()).GetLenth() < other->size.x))
					collisionMsg.emplace(CollisionMessage(this->owner, other->layer)); else; else;
		else if (this->shape == circle)
			if (other->shape == rect)
				if (((this->pos - other->pos <= this->size + other->size) ||
					((this->pos - other->pos) > other->size) && ((this->pos - other->pos).Vabs() - other->size.Vabs()).GetLenth() < this->size.x))
					collisionMsg.emplace(CollisionMessage(this->owner, other->layer)); else;
			else if (other->shape == circle)
				if ((this->pos - other->pos).GetLenth() <= this->size.x + other->size.x)
					collisionMsg.emplace(CollisionMessage(this->owner, other->layer));
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
	while (!collisionMsg.empty())
	{
		if (collisionMsg.front().collided)
			collisionMsg.front().collided->handle_collision(collisionMsg.front().otherLayer);
		collisionMsg.pop();
	}

	COLL.erase(std::remove_if(COLL.begin(), COLL.end(), [](const std::unique_ptr<Collider>& col) {return col->isInvalid; }), COLL.end());
}


bool isWallCollision(Vector2D<float> pos, Vector2D<float> size)
{
	for (auto& other : COLL) {
		if (other->layer != wall) continue;
		if (pos - other->pos <= size + other->size)
			return true;
	}
	return false;
}
#include"Collider.h"

void Collider::collision()
{
	for (auto& other : COLL)
		if (this->shape == 1)
			if (other->shape == 1)
				if (abs((this->pos - other->pos).x) <= this->size + other->size &&
					abs((this->pos - other->pos).y) <= this->size + other->size)
					collisionMsg.emplace(Vector2D<int>(0, 0)); else;
			else if (other->shape == 2)
				; else;
		else if (this->shape == 2)
			if (other->shape == 1)
				;
			else if (other->shape == 2)
				if ((this->pos - other->pos).GetLenth() <= this->size + other->size)
					collisionMsg.emplace(Vector2D<int>(0, 0));
}

void ColliderUpdate()
{
	for (auto& c : COLL)
		c->collision();

}
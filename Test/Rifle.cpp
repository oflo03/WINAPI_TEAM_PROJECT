#include"Rifle.h"

void Rifle::update()
{
	if (curTime)
		--curTime;
}
void Rifle::attack(std::vector<Bullet*>& bullets, const Vector2D<float>& hand)
{
	if (!curTime)
	{
		POINT mPos;
		GetCursorPos(&mPos);
		Vector2D<float> t = Vector2D<float>(mPos.x - hand.x, mPos.y - hand.y);
		t /= t.GetLenth();
		t.Rotate(uid(dre) % 15 - 7);
		bullets.emplace_back(new Bullet(RIFLE, hand + Vector2D<float>(t.x * 30, t.y * 30 - 30), t * 10));
		curTime = coolTime;
	}
}
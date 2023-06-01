#include"Shotgun.h"

void Shotgun::update()
{
	if (curTime)
		--curTime;
}
void Shotgun::attack(std::vector<Bullet*>& bullets, const Vector2D<float>& hand)
{
	if (!curTime)
	{
		POINT mPos;
		GetCursorPos(&mPos);
		Vector2D<float> t = Vector2D<float>(mPos.x - hand.x, mPos.y - hand.y);
		t /= t.GetLenth();
		t.Rotate(-10);
		for (int i = 0; i < 5; ++i)
		{
			bullets.emplace_back(new Bullet(SHOTGUN, hand + Vector2D<float>(t.x * 30, t.y * 30 - 30), t * 10));
			t.Rotate(5);
		}
		curTime = coolTime;
	}
}
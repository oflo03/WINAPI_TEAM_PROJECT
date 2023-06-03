#include"Weapon.h"

void Sword::update()
{
}
void Sword::attack(const Vector2D<float>& center)
{
}


void Pistol::update()
{
	if (curTime)
		--curTime;
	if (shotTime)
		shotTime--;
}
void Pistol::attack(const Vector2D<float>& hand)
{
	if (!curTime)
	{
		POINT mPos;
		GetCursorPos(&mPos);
		Vector2D<float> t = Vector2D<float>(mPos.x - hand.x, mPos.y - hand.y);
		t.Normalize();
		t.Rotate(uid(dre) % 11 - 5);
		Bullets.emplace_back(new Bullet(PISTOL, hand + Vector2D<float>(t.x * 30, t.y * 30 - 10), t * 10));
		curTime = coolTime;
		shotTime = 10;
	}

}


void Rifle::update()
{
	if (curTime)
		--curTime;
	if (shotTime)
		shotTime--;
}

void Rifle::attack(const Vector2D<float>& hand)
{
	if (!curTime)
	{
		POINT mPos;
		GetCursorPos(&mPos);
		Vector2D<float> t = Vector2D<float>(mPos.x - hand.x, mPos.y - hand.y);
		t /= t.GetLenth();
		t.Rotate(uid(dre) % 15 - 7);
		Bullets.emplace_back(new Bullet(RIFLE, hand + Vector2D<float>(t.x * 30, t.y * 30 - 10), t * 10));
		curTime = coolTime;
		shotTime = 5;
	}
}


void Shotgun::update()
{
	if (curTime)
		--curTime;
	if (shotTime)
		shotTime--;
}
void Shotgun::attack(const Vector2D<float>& hand)
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
			Bullets.emplace_back(new Bullet(SHOTGUN, hand + Vector2D<float>(t.x * 30, t.y * 30 - 10), t * 10));
			t.Rotate(5);
		}
		curTime = coolTime;
		shotTime = 7;
	}
}
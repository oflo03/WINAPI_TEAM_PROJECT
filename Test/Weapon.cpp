#include"Weapon.h"
#include"Player.h"

extern double frame_time;
extern bool lookRange;
extern bool collisionable[9][9];
extern HPEN GREENP;

void Sword::update()
{
	if (curTime)
		--curTime;
	if (frame > 0) {
		frame = (frame + frame_time * 4 * slash.frame);
		if (frame >= slash.frame) frame = 0;
	}
	if (frame > 4 && frame < 5)
	{
		Vector2D<float> mPos(cos(-angle * M_PI / 180) * attackRange, sin(-angle * M_PI / 180) * attackRange);
		mPos += centerPos;
		for (auto& other : COLL) {
			Vector2D<float> dot[4] = { Vector2D<float>(other->pos.x - other->size.x, other->pos.y - other->size.y),
			Vector2D<float>(other->pos.x + other->size.x, other->pos.y - other->size.y),
			Vector2D<float>(other->pos.x + other->size.x, other->pos.y + other->size.y),
			Vector2D<float>(other->pos.x - other->size.x, other->pos.y + other->size.y) };
			for (int i = 0; i < 4; i++) {
				if (collisionable[other->layer][playerMelee] && (dot[i] - centerPos).GetLenth() <= attackRange) {
					if ((mPos - centerPos).GetRadian(dot[i] - centerPos) <= 60) {
						other->owner->handle_collision(playerMelee, 10);
						break;
					}
				}
			}
		}
	}
}
void Sword::attack(const Vector2D<float>& center, const Vector2D<float>& mPos, int side)
{
	if (!curTime) {
		curTime = coolTime;
		frame = 0.1;
	}
}

void Sword::draw_weapon(HDC mDC, const Vector2D<float>& center, const Vector2D<float>& mPos)
{
	centerPos = center;
	if (frame == 0.0f) {
		angle = std::atan2(mPos.y - (center.y), mPos.x - center.x) * (180.0f / M_PI) * -1;
		int width = resource[0].GetWidth();
		int height = resource[0].GetHeight();
		CImage rotatedImage;
		rotatedImage.Create(width, height, 32);
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				Vector2D<float> rotatedPos = (Vector2D<float>(x - width / 2, y - height / 2)).Rotate(angle) + Vector2D<float>(width / 2, height / 2);
				if (rotatedPos.x >= 0 && rotatedPos.x < width && rotatedPos.y >= 0 && rotatedPos.y < height) {
					BYTE* srcPixel = (BYTE*)resource[0].GetPixelAddress(rotatedPos.x, rotatedPos.y);
					BYTE* destPixel = (BYTE*)rotatedImage.GetPixelAddress(x, y);
					memcpy(destPixel, srcPixel, sizeof(BYTE) * 4);
				}
			}
		}
		rotatedImage.TransparentBlt(mDC, center.x - width, center.y - height, width * 2, height * 2, RGB(0, 0, 0));
		rotatedImage.Destroy();
	}
	else {
		int width = slash.size.right;
		int height = slash.size.bottom;
		CImage temp;
		CImage rotatedImage;
		rotatedImage.Create(width, height, 32);
		temp.Create(width, height, 32);
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				BYTE* srcPixel = (BYTE*)slash.resource.GetPixelAddress((int)frame * width + x, y);
				BYTE* destPixel = (BYTE*)temp.GetPixelAddress(x, y);
				memcpy(destPixel, srcPixel, sizeof(BYTE) * 4);
			}
		}
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				Vector2D<float> rotatedPos = (Vector2D<float>(x - width / 2, y - height / 2)).Rotate(angle) + Vector2D<float>(width / 2, height / 2);
				if (rotatedPos.x >= 0 && rotatedPos.x < width && rotatedPos.y >= 0 && rotatedPos.y < height) {
					BYTE* srcPixel = (BYTE*)temp.GetPixelAddress(rotatedPos.x, rotatedPos.y);
					BYTE* destPixel = (BYTE*)rotatedImage.GetPixelAddress(x, y);
					memcpy(destPixel, srcPixel, sizeof(BYTE) * 4);
				}
			}
		}
		rotatedImage.TransparentBlt(mDC, center.x - slash.size.right, center.y - slash.size.bottom, slash.size.right * 2, slash.size.bottom * 2,
			0, 0, slash.size.right, slash.size.bottom, RGB(0, 0, 0)
		);
		if (lookRange)
		{
			Vector2D<float> lineP1 = Vector2D<float>(cos(-angle * M_PI / 180) * attackRange, sin(-angle * M_PI / 180) * attackRange);
			Vector2D<float> lineP2 = Vector2D<float>(cos(-angle * M_PI / 180) * attackRange, sin(-angle * M_PI / 180) * attackRange);
			lineP1 = lineP1.Normalize() * attackRange;
			lineP2 = lineP2.Normalize() * attackRange;
			lineP1.Rotate(-60);
			lineP2.Rotate(60);

			HPEN old = (HPEN)SelectObject(mDC, GREENP);
			MoveToEx(mDC, center.x + lineP1.x, center.y + lineP1.y, NULL);
			LineTo(mDC, center.x, center.y);
			LineTo(mDC, center.x + lineP2.x, center.y + lineP2.y);
			Arc(mDC, center.x - attackRange, center.y - attackRange, center.x + attackRange, center.y + attackRange,
				center.x + lineP2.x, center.y + lineP2.y, center.x + lineP1.x, center.y + lineP1.y);
			SelectObject(mDC, old);
		}
		rotatedImage.Destroy();
		temp.Destroy();
	}
}


void Pistol::update()
{
	if (curTime)
		--curTime;
	if (shotTime)
		shotTime--;
}
void Pistol::attack(const Vector2D<float>& hand, const Vector2D<float>& mPos, int side)
{
	if (!curTime && curAmmo > 0)
	{
		Vector2D<float> t = Vector2D<float>(mPos.x - hand.x, mPos.y - hand.y);
		t.Normalize();
		t.Rotate(uid(dre) % 11 - 5);
		Bullets.emplace_back(new Bullet(BPISTOL, side, hand + Vector2D<float>(t.x * 30, t.y * 30 - 10), t * 10));
		curTime = coolTime;
		shotTime = 10;
		curAmmo--;
	}

}

void Rifle::update()
{
	if (curTime)
		--curTime;
	if (shotTime)
		shotTime--;
}

void Rifle::attack(const Vector2D<float>& hand, const Vector2D<float>& mPos, int side)
{
	if (!curTime && curAmmo > 0)
	{
		Vector2D<float> t = Vector2D<float>(mPos.x - hand.x, mPos.y - hand.y);
		t /= t.GetLenth();
		t.Rotate(uid(dre) % 15 - 7);
		Bullets.emplace_back(new Bullet(BRIFLE, side, hand + Vector2D<float>(t.x * 30, t.y * 30 - 10), t * 10));
		curTime = coolTime;
		shotTime = 5;
		curAmmo--;
	}
}

void Shotgun::update()
{
	if (curTime)
		--curTime;
	if (shotTime)
		shotTime--;
}
void Shotgun::attack(const Vector2D<float>& hand, const Vector2D<float>& mPos, int side)
{
	if (!curTime && curAmmo > 0)
	{
		Vector2D<float> t = Vector2D<float>(mPos.x - hand.x, mPos.y - hand.y);
		t /= t.GetLenth();
		t.Rotate(-10);
		for (int i = 0; i < 5; ++i)
		{
			Bullets.emplace_back(new Bullet(BSHOTGUN, side, hand + Vector2D<float>(t.x * 30, t.y * 30 - 10), t * 10));
			t.Rotate(5);
		}
		curTime = coolTime;
		shotTime = 7;
		curAmmo--;
	}
}

void Rocket::update()
{
	if (curTime)
		--curTime;
	if (shotTime)
		shotTime--;
}
void Rocket::attack(const Vector2D<float>& hand, const Vector2D<float>& mPos, int side)
{
	if (!curTime && curAmmo > 0)
	{
		Vector2D<float> t = Vector2D<float>(mPos.x - hand.x, mPos.y - hand.y);
		t /= t.GetLenth();
		Bullets.emplace_back(new Bullet(BSHOTGUN, side, hand + Vector2D<float>(t.x * 30, t.y * 30 - 10), t * 10));
		curTime = coolTime;
		shotTime = 30;
		curAmmo--;
	}
}
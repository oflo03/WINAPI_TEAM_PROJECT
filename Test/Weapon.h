#pragma once
#include"Item.h"
#include"Bullet.h"
#include<random>

extern std::default_random_engine dre;
extern std::uniform_int_distribution<int> uid;

class Weapon
	: public Item
{
protected:
	int curAmmo;
	int maxAmmo;
	int damage;
	int angle;
	int coolTime;
	int curTime;
public:
	Weapon() :maxAmmo(0), damage(0),curAmmo(0), angle(0),coolTime(0),curTime(0) {}
	~Weapon() {
		resource.Destroy();
	}
	virtual void update() = 0;
	virtual void attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center) = 0;
	int GetCurAmmo() { return curAmmo; }
	void draw_weapon(HDC mDC, const Vector2D<float>& center)
	{
		POINT mPos;
		GetCursorPos(&mPos);
		angle = std::atan2(mPos.y - (center.y), mPos.x - center.x) * (180.0f / M_PI) * -1;

		int width = resource.GetWidth();
		int height = resource.GetHeight();
		CImage rotatedImage;
		rotatedImage.Create(width, height, 32);
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				Vector2D<float> rotatedPos = (Vector2D<float>(x - width / 2, y - height / 2)).Rotate(angle) + Vector2D<float>(width / 2, height / 2);
				if (rotatedPos.x >= 0 && rotatedPos.x < width && rotatedPos.y >= 0 && rotatedPos.y < height) {
					BYTE* srcPixel = (BYTE*)resource.GetPixelAddress(rotatedPos.x, rotatedPos.y);
					BYTE* destPixel = (BYTE*)rotatedImage.GetPixelAddress(x, y);
					memcpy(destPixel, srcPixel, sizeof(BYTE) * 4);
				}
			}
		}
		rotatedImage.TransparentBlt(mDC, center.x - resource.GetWidth(), center.y - resource.GetHeight(),
			resource.GetWidth() * 2, resource.GetHeight() * 2, RGB(0, 0, 0));
		rotatedImage.Destroy();
	}
};

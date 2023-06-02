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
	int shotTime;
	CImage reverseResource[2];
public:
	Weapon() :maxAmmo(0), damage(0), curAmmo(0), angle(0), coolTime(0), curTime(0) ,shotTime(0){}
	~Weapon() {
		for (int i = 0; i < 2; i++) {
			resource[i].Destroy();
			reverseResource[i].Destroy();
		}
	}
	virtual void update() = 0;
	virtual void attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center) = 0;
	void SetCurTime(int t) { curTime = t; }
	int GetCurAmmo() { return curAmmo; }
	void draw_weapon(HDC mDC, const Vector2D<float>& center)
	{
		POINT mPos;
		GetCursorPos(&mPos);
		angle = std::atan2(mPos.y - (center.y), mPos.x - center.x) * (180.0f / M_PI) * -1;
		float temp = angle;
		bool isShot = shotTime != 0;
		if (angle >= 90)
			angle = angle - 180;
		else if (angle <= -90)
			angle = angle + 180;
		int width = resource[isShot].GetWidth();
		int height = resource[isShot].GetHeight();
		CImage rotatedImage;
		rotatedImage.Create(width, height, 32);
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				Vector2D<float> rotatedPos = (Vector2D<float>(x - width / 2, y - height / 2)).Rotate(angle) + Vector2D<float>(width / 2, height / 2);
				if (rotatedPos.x >= 0 && rotatedPos.x < width && rotatedPos.y >= 0 && rotatedPos.y < height) {
					BYTE* srcPixel;
					if (angle == temp)
						srcPixel = (BYTE*)resource[isShot].GetPixelAddress(rotatedPos.x, rotatedPos.y);
					else
						srcPixel = (BYTE*)reverseResource[isShot].GetPixelAddress(rotatedPos.x, rotatedPos.y);
					BYTE* destPixel = (BYTE*)rotatedImage.GetPixelAddress(x, y);
					memcpy(destPixel, srcPixel, sizeof(BYTE) * 4);
				}
			}
		}
		rotatedImage.TransparentBlt(mDC, center.x - width, center.y - height, width * 2, height * 2, RGB(0, 0, 0));
		rotatedImage.Destroy();
	}
};

class Sword : public Weapon
{
public:
	Sword() :Weapon() {
		coolTime = cooltime[SWORD];
		curAmmo = 1;
		damage = 20;
		resource[0].Load(L"Item_Weapon_Sword.png");
		reverseResource[0].Load(L"Item_Weapon_Sword_Reverse.png");
		resource[1].Load(L"Item_Weapon_Sword.png");
		reverseResource[1].Load(L"Item_Weapon_Sword_Reverse.png");
	}
	virtual void update();
	virtual void attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center);
};

class Pistol :public Weapon
{
private:
public:
	Pistol() :Weapon() {
		coolTime = cooltime[PISTOL];
		curAmmo = 10;
		damage = 20;
		resource[0].Load(L"Item_Weapon_Pistol.png");
		reverseResource[0].Load(L"Item_Weapon_Pistol_Reverse.png");
		resource[1].Load(L"Item_Weapon_Pistol2.png");
		reverseResource[1].Load(L"Item_Weapon_Pistol_Reverse2.png");
	}
	virtual void update();
	virtual void attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center);
};

class Rifle :public Weapon
{
public:
	Rifle() :Weapon() {
		coolTime = cooltime[RIFLE];
		curAmmo = 10;
		damage = 20;
		resource[0].Load(L"Item_Weapon_Rifle.png");
		reverseResource[0].Load(L"Item_Weapon_Rifle_Reverse.png");
		resource[1].Load(L"Item_Weapon_Rifle2.png");
		reverseResource[1].Load(L"Item_Weapon_Rifle_Reverse2.png");
	}
	virtual void update();
	virtual void attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center);
};

class Shotgun :public Weapon
{
public:
	Shotgun() :Weapon() {
		coolTime = cooltime[SHOTGUN];
		curAmmo = 10;
		damage = 20;
		resource[0].Load(L"Item_Weapon_Shotgun.png");
		reverseResource[0].Load(L"Item_Weapon_Shotgun_Reverse.png");
		resource[1].Load(L"Item_Weapon_Shotgun2.png");
		reverseResource[1].Load(L"Item_Weapon_Shotgun_Reverse2.png");
	}
	virtual void update();
	virtual void attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center);
};
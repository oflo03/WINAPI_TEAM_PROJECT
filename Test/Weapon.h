#pragma once
#include"Item.h"
#include"Bullet.h"
#include<random>


extern std::default_random_engine dre;
extern std::uniform_int_distribution<int> uid;
extern std::vector<Bullet*> Bullets;

class Weapon
	: public Item
{
protected:
	int curAmmo;
	int maxAmmo;
	int angle;
	int coolTime;
	int curTime;
	int shotTime;
	CImage reverseResource[2];
public:
	Weapon() :maxAmmo(0), curAmmo(0), angle(0), coolTime(0), curTime(0), shotTime(0) {}
	~Weapon() {
		for (int i = 0; i < 2; i++) {
			resource[i].Destroy();
			reverseResource[i].Destroy();
		}
	}
	virtual void update() = 0;
	virtual void attack(const Vector2D<float>& center, const Vector2D<float>& mPos, int side) = 0;
	void ReLoad() { curAmmo = maxAmmo; };
	void Enemy() { maxAmmo /= 3,coolTime*=2, ReLoad(); };
	void SetCurTime(int t) { curTime = t; }
	void SetCurAmmo(int t) { curAmmo = t; }
	int GetCurTime() { return curTime; }
	int GetShotTime() { return shotTime; }
	int GetCurAmmo() { return curAmmo; }
	int GetMaxAmmo() { return maxAmmo; }
	bool IsReBound() { return (coolTime - curTime < 3); }
	bool IsFull() { return maxAmmo == curAmmo; }
	bool IsRunOut() { return (curAmmo == 0); }
	virtual void draw_weapon(HDC mDC, const Vector2D<float>& center, const Vector2D<float>& mPos) {
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
private:
	Animation slash;
	float frame;
	float attackRange;
	Vector2D<float> centerPos;
public:
	Sword() :Weapon() {
		coolTime = cooltime[SWORD];
		curAmmo = maxAmmo = 1;
		frame = 0;
		attackRange = 110;
		resource[0].Load(L"resources/Item_Weapon_Sword.png");
		reverseResource[0].Load(L"resources/Item_Weapon_Sword_Reverse.png");
		resource[1].Load(L"resources/Item_Weapon_Sword.png");
		reverseResource[1].Load(L"resources/Item_Weapon_Sword_Reverse.png");
		slash.resource.Load(L"resources/sword_attack.png");
		slash.frame = 8;
		slash.size = { 0,0,slash.resource.GetWidth() / slash.frame ,slash.resource.GetHeight() };
	}
	~Sword() {
		Weapon::~Weapon();
		slash.resource.Destroy();
	}
	virtual void update();
	virtual void attack(const Vector2D<float>& center, const Vector2D<float>& mPos, int side);
	virtual void draw_weapon(HDC mDC, const Vector2D<float>& center, const Vector2D<float>& mPos);
};

class Pistol :public Weapon
{
private:
public:
	Pistol() :Weapon() {
		coolTime = cooltime[PISTOL];
		curAmmo = maxAmmo = 15;
		resource[0].Load(L"resources/Item_Weapon_Pistol.png");
		reverseResource[0].Load(L"resources/Item_Weapon_Pistol_Reverse.png");
		resource[1].Load(L"resources/Item_Weapon_Pistol2.png");
		reverseResource[1].Load(L"resources/Item_Weapon_Pistol_Reverse2.png");
	}
	virtual void update();
	virtual void attack(const Vector2D<float>& center, const Vector2D<float>& mPos, int side);
};

class Rifle :public Weapon
{
public:
	Rifle() :Weapon() {
		coolTime = cooltime[RIFLE];
		curAmmo = maxAmmo = 30;
		resource[0].Load(L"resources/Item_Weapon_Rifle.png");
		reverseResource[0].Load(L"resources/Item_Weapon_Rifle_Reverse.png");
		resource[1].Load(L"resources/Item_Weapon_Rifle2.png");
		reverseResource[1].Load(L"resources/Item_Weapon_Rifle_Reverse2.png");
	}
	virtual void update();
	virtual void attack(const Vector2D<float>& center, const Vector2D<float>& mPos, int side);
};

class Shotgun :public Weapon
{
public:
	Shotgun() :Weapon() {
		coolTime = cooltime[SHOTGUN];
		curAmmo = maxAmmo = 8;
		resource[0].Load(L"resources/Item_Weapon_Shotgun.png");
		reverseResource[0].Load(L"resources/Item_Weapon_Shotgun_Reverse.png");
		resource[1].Load(L"resources/Item_Weapon_Shotgun2.png");
		reverseResource[1].Load(L"resources/Item_Weapon_Shotgun_Reverse2.png");
	}
	virtual void update();
	virtual void attack(const Vector2D<float>& center, const Vector2D<float>& mPos, int side);
};

class Rocket :public Weapon
{
public:
	Rocket() :Weapon() {
		coolTime = cooltime[ROCKET];
		curAmmo = maxAmmo = 1;
		resource[0].Load(L"resources/Item_Weapon_Rocket.png");
		reverseResource[0].Load(L"resources/Item_Weapon_Rocket_Reverse.png");
		resource[1].Load(L"resources/Item_Weapon_Rocket2.png");
		reverseResource[1].Load(L"resources/Item_Weapon_Rocket_Reverse2.png");
	}
	virtual void update();
	virtual void attack(const Vector2D<float>& center, const Vector2D<float>& mPos, int side);
};
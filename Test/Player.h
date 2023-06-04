#pragma once
#include<vector>
#include"Vector2D.h"
#include"Animation.h"
#include"State.h"
#include"Bullet.h"
#include"Weapon.h"
#include"Master.h"

class PlayerState;


class Player
	:public Master
{
protected:
	Animation animation[6];
	CImage hand;
	float frame;
	float angle;
	Vector2D<float> pos;
	Vector2D<float> lastPos;
	Vector2D<float> handPos;
	Vector2D<float> mPos;
	Vector2D<float> dir;
	int direction;
	PlayerState* state;
	int velocity;
	int selectedWeapon;
	std::vector<Weapon*> myWeapons;
public:
	Player(float x, float y) : pos(x, y), dir(0, 0), frame(0), angle(90), direction(FRONT), state(nullptr), selectedWeapon(SWORD), velocity(200) {}
	Player() : pos(400, 300), dir(0, 0), frame(0), angle(90), direction(FRONT), state(nullptr), selectedWeapon(SWORD), velocity(200) {}
	virtual void draw_character(HDC mDC) = 0;
	virtual void handle_event() = 0;
	virtual void update() = 0;
	virtual void SetImage(int state) = 0;
	virtual void SetDirection() = 0;
	virtual void attack() { myWeapons[selectedWeapon]->attack(handPos,mPos,playerBullet); };
	void DestroyImage() { for (int i = 0; i < 6; i++) animation[i].resource.Destroy(); }
	void SetPos(Vector2D<float> temp) { pos = temp; }
	Vector2D<float> GetPos() { return pos; }
	void SetDir(Vector2D<float> temp) { dir = temp; }
	Vector2D<float> GetDir() { return dir; }
	double GetVelocity() { return velocity; };
	void SetDirection(int direction) { this->direction = direction; }
	bool GetIfRoll();
	int GetWeapon() { return selectedWeapon; }
	void SetWeaponTime(int t) { myWeapons[selectedWeapon]->SetCurTime(t); }
	void SetWeapon(int type) { if (myWeapons[type]->GetCurAmmo() > 0)selectedWeapon = type, myWeapons[selectedWeapon]->SetCurTime(10); }
	void SetWeaponUp() { do selectedWeapon += 5, selectedWeapon %= 6; while (myWeapons[selectedWeapon]->GetCurAmmo() == 0); }
	void SetWeaponDown() { do selectedWeapon += 1, selectedWeapon %= 6; while (myWeapons[selectedWeapon]->GetCurAmmo() == 0); }
};

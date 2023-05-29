#pragma once
#include<vector>
#include"Vector2D.h"
#include"Animation.h"
#include"State.h"
#include"Weapon.h"

class PlayerState;

enum STATE
{
	STATE_IDLE, STATE_RUN, STATE_ROLL
};

enum DIRECTION
{
	FRONT, FRONT_RIGHT, FRONT_LEFT, BACK, BACK_RIGHT, BACK_LEFT
};

class Player
{
protected:
	Animation animation[6];
	CImage hand;
	float frame;
	Vector2D<float> pos;
	Vector2D<float> handPos;
	Vector2D<float> dir;
	int direction;
	PlayerState* state;
	int velocity;
	int selectedWeapon;
	std::vector<Weapon*> myWeapons;
public:
	Player(float x, float y) : pos(x, y), dir(0, 0), frame(0), direction(FRONT), state(nullptr),selectedWeapon(SWORD), velocity(200) {}
	Player() : pos(400, 300), dir(0, 0), frame(0), direction(FRONT), state(nullptr), selectedWeapon(SWORD), velocity(200) {}
	virtual void draw_character(HDC mDC) = 0;
	virtual void handle_event() = 0;
	virtual void update() = 0;
	virtual void SetImage(int state) = 0;
	virtual void SetDirection() = 0;
	void DestroyImage() { for (int i = 0; i < 6; i++) animation[i].resource.Destroy(); }
	void SetPos(Vector2D<float> temp) { pos = temp; }
	Vector2D<float> GetPos() { return pos; }
	void SetDir(Vector2D<float> temp) { dir = temp; }
	Vector2D<float> GetDir() { return dir; }
	double GetVelocity() { return velocity; };
	void SetDirection(int direction) { this->direction = direction; }
	void SetWeapon(int type) { if (myWeapons[type]->GetCurAmmo() > 0)this->selectedWeapon = type; }
};

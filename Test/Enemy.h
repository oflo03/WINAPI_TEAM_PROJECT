#pragma once
#include"Master.h"
#include"Player.h"

extern RECT screen;


class Enemy : public Master
{
protected:
	CImage shadow;
	float frame;
	float angle;
	Vector2D<float> pos;
	Vector2D<float> dir;
	Vector2D<float> lastPos;
	int direction;
	int attackCoolTime;
	int state;
	int HP;
	float velocity;
	float attackRange;
	bool targetLocked;
public:
	Player* target;
	Enemy(float x, float y) : pos(x, y), dir(0, 0), frame(0), angle(90), direction(FRONT), state(STATE_IDLE), velocity(0) ,target(Player::getInstance(1)),targetLocked(false), attackCoolTime(0){}
	Enemy() : pos(screen.right/2, screen.bottom/2), dir(0, 0), frame(0), angle(90), direction(FRONT), state(STATE_IDLE), velocity(0),target(Player::getInstance(1)), targetLocked(false), attackCoolTime(0) {}
	virtual ~Enemy() {}
	virtual void draw_character(HDC mDC) = 0;
	virtual void handle_event() = 0;
	virtual void update() = 0;
	virtual void attack()=0;
	virtual void SetDirection() = 0;
	void SetPos(Vector2D<float> temp) { pos = temp; }
	Vector2D<float> GetPos() const { return pos; }
	void SetDir(Vector2D<float> temp) { dir = temp; }
	Vector2D<float> GetDir() const { return dir; }
	double GetVelocity() { return velocity; };
	void SetDirection(int direction) { this->direction = direction; }
	bool attackable() { 
		return (target!=nullptr&&(target->GetPos() - pos).GetLenth() <= attackRange);
	}
};



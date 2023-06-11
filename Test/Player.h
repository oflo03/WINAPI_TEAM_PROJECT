#pragma once
#include<vector>
#include"Vector2D.h"
#include"Animation.h"
#include"State.h"
#include"Bullet.h"
#include"Weapon.h"
#include"Master.h"
#include"SoundManager.h"

class PlayerState;
class Marin;

extern Vector2D<float> camPos;
extern Vector2D<float> monitorSize;
extern Vector2D<float> spawnpoint[4];

enum playertype
{
	marin, pilot, knight
};
extern int selectedPlayer;

class Player
	:public Master
{
private:
	static Player* instance;
protected:
	Player(float x, float y) : pos(x, y), dir(0, 0), frame(0), damageCnt(0), angle(90), direction(FRONT), state(nullptr), selectedWeapon(SWORD), velocity(200), hp(6), curstate(STATE_IDLE) {}
	Player() : pos(960, 1000), dir(0, 0), frame(0), damageCnt(0), angle(90), direction(FRONT), state(nullptr), selectedWeapon(SWORD), velocity(200), hp(6), curstate(STATE_IDLE) {}
	CImage hand;
	CImage shadow[2];
	float frame;
	float damageCnt;
	float angle;
	Vector2D<float> pos;
	Vector2D<float> lastPos;
	Vector2D<float> handPos;
	Vector2D<float> mPos;
	Vector2D<float> dir;
	int direction;
	PlayerState* state;
	int curstate;
	int hp;
	int velocity;
	int selectedWeapon;
	std::vector<Weapon*> myWeapons;
public:
	static Player* getInstance();
	static void init();
	static void Destroy() { delete instance; }
	virtual void draw_character(HDC mDC) = 0;
	virtual void handle_event() = 0;
	virtual void update() = 0;
	virtual void SetDirection() = 0;
	virtual void attack() { 
		myWeapons[selectedWeapon]->attack(handPos, mPos, playerBullet);
		switch (selectedWeapon)
		{
		case SWORD:
			break;
		case PISTOL:
			if(SoundManager::getInstance()->isPlaying(PISTOL_SHOT))
				SoundManager::getInstance()->play(PISTOL_SHOT);
			break;
		case RIFLE:
			if (SoundManager::getInstance()->isPlaying(RIFLE_SHOT))
			SoundManager::getInstance()->play(RIFLE_SHOT);
			break;
		case SHOTGUN:
			if (SoundManager::getInstance()->isPlaying(SHOTGUN_SHOT))
			SoundManager::getInstance()->play(SHOTGUN_SHOT);
			break;
		case ROCKET:
			if (SoundManager::getInstance()->isPlaying(ROCKET_SHOT))
			SoundManager::getInstance()->play(ROCKET_SHOT);
			break;
		default:
			break;
		}
	}
	void SetPos(Vector2D<float> temp) { pos = temp; }
	Vector2D<float> GetPos() { return pos; }
	float GetAngle() { return angle; }
	void SetDir(Vector2D<float> temp) { dir = temp; }
	Vector2D<float> GetDir() { return dir; }
	Vector2D<float> GetMouseVector() { return (mPos - handPos).Normalize(); }
	double GetVelocity() { return velocity; };
	void SetDirection(int direction) { this->direction = direction; }
	void WeaponReload(int type) { myWeapons[type]->ReLoad(); }
	bool GetIfRoll();
	int GetWeaponCurAmmo() { return myWeapons[selectedWeapon]->GetCurAmmo(); }
	int GetWeaponMaxAmmo() { return myWeapons[selectedWeapon]->GetMaxAmmo(); }
	bool GetIfWeaponFull(int type) { return myWeapons[type]->IsFull(); }
	int GetWeapon() { return selectedWeapon; }
	int GetHP() { return hp; }
	void SetWeaponTime(int t) { myWeapons[selectedWeapon]->SetCurTime(t); }
	void SetWeapon(int type) { if (!myWeapons[type]->IsRunOut()) selectedWeapon = type, myWeapons[selectedWeapon]->SetCurTime(cooltime[type] - 3); }
	void SetWeaponUp() { do selectedWeapon += 4, selectedWeapon %= 5; while (myWeapons[selectedWeapon]->IsRunOut()); }
	void SetWeaponDown() { do selectedWeapon += 1, selectedWeapon %= 5; while (myWeapons[selectedWeapon]->IsRunOut()); }
	void SetCurState(int state) { curstate = state; }
	void SetCurAmmoZero(int type) { myWeapons[type]->SetCurAmmo(0); }
};

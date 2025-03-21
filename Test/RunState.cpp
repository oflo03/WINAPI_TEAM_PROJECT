#include "RunState.h"
#include"IdleState.h"
#include"RollState.h"
#include"SoundManager.h"

extern double frame_time;

RunState::~RunState()
{
}

PlayerState* RunState::handle_event(Player& player)
{
	float dirX = 0, dirY = 0;
	bool isMove = false;
	if (GetAsyncKeyState('D')) {
		dirX = 1;
		isMove = true;
	}
	else if (GetAsyncKeyState('A')) {
		dirX = -1;
		isMove = true;
	}
	else dirX = 0;
	if (GetAsyncKeyState('W')) {
		dirY = -1;
		isMove = true;
	}
	else if (GetAsyncKeyState('S')) {
		dirY = 1;
		isMove = true;
	}
	else dirY = 0;
	player.SetDirection();
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		player.attack();
	if (GetAsyncKeyState(VK_RBUTTON) & 1) {
		if (dirX == 1 && dirY == 0)
			player.SetDirection(FRONT_RIGHT);
		else if (dirX == 1 && dirY == 1)
			player.SetDirection(FRONT_RIGHT);
		else if (dirX == 0 && dirY == 1)
			player.SetDirection(FRONT);
		else if (dirX == -1 && dirY == 1)
			player.SetDirection(FRONT_LEFT);
		else if (dirX == -1 && dirY == 0)
			player.SetDirection(FRONT_LEFT);
		else if (dirX == -1 && dirY == -1)
			player.SetDirection(BACK_LEFT);
		else if (dirX == 0 && dirY == -1)
			player.SetDirection(BACK);
		else if (dirX == 1 && dirY == -1)
			player.SetDirection(BACK_RIGHT);
		player.SetDir(Vector2D<float>(0, 0));
		return new RollState(dirX, dirY);
	}
	if (GetAsyncKeyState('1') & 0x8000 && player.GetWeapon() != SWORD) {
		player.SetWeapon(SWORD);
	}
	if (GetAsyncKeyState('2') & 0x8000 && player.GetWeapon() != PISTOL) {
		player.SetWeapon(PISTOL);
		if(SoundManager::getInstance()->isPlaying(PISTOL_RELOAD))
				SoundManager::getInstance()->play(PISTOL_RELOAD);
	}
	if (GetAsyncKeyState('3') & 0x8000 && player.GetWeapon() != RIFLE) {
		player.SetWeapon(RIFLE);
		if (SoundManager::getInstance()->isPlaying(RIFLE_RELOAD))
				SoundManager::getInstance()->play(RIFLE_RELOAD);
	}
	if (GetAsyncKeyState('4') & 0x8000 && player.GetWeapon() != SHOTGUN) {
		player.SetWeapon(SHOTGUN);
			if (SoundManager::getInstance()->isPlaying(SHOTGUN_RELOAD))
				SoundManager::getInstance()->play(SHOTGUN_RELOAD);
	}
	if (GetAsyncKeyState('5') & 0x8000 && player.GetWeapon() != ROCKET) {
		player.SetWeapon(ROCKET);
			if (SoundManager::getInstance()->isPlaying(ROCKET_RELOAD))
				SoundManager::getInstance()->play(ROCKET_RELOAD);
	}
	if (GetAsyncKeyState(VK_CONTROL) & 1)
		player.SetWeaponUp();
	if (GetAsyncKeyState(VK_TAB) & 1)
		player.SetWeaponDown();
	if (GetAsyncKeyState(VK_XBUTTON1) & 1)
		player.SetWeaponUp();
	if (GetAsyncKeyState(VK_XBUTTON2) & 1)
		player.SetWeaponDown();
	if (isMove) {
		player.SetDir(Vector2D<float>(dirX, dirY));
		if(!SoundManager::getInstance()->isPlaying(WALK))
			SoundManager::getInstance()->play(WALK);
		return nullptr;
	}
	return new IdleState();
}

void RunState::update(Player& player)
{
	if (player.GetDir().GetLenth() == 1) {
		player.SetPos(player.GetPos() + player.GetDir() * player.GetVelocity() * frame_time);
	}
	else {
		player.SetPos(player.GetPos() + player.GetDir() * (sqrt(2) / 2) * player.GetVelocity() * frame_time);
	}
}

void RunState::enter(Player& player)
{
	player.SetCurState(STATE_RUN);
}


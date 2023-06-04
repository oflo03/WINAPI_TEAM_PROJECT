#pragma once
#include"Player.h"
#include"Weapon.h"

class Player;

class PlayerState
{
public:
	virtual void enter(Player& player) = 0;
	virtual void exit(Player& player) = 0;
	virtual PlayerState* handle_event(Player& player) = 0;
	virtual void update(Player& player) = 0;
};

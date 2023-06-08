#include"Marin.h"
#include"Player.h"

void Player::init()
{
	Marin::init();
}

Player* Player::getInstance(int character) {
	if (instance == nullptr) {
		switch (character)
		{
		case 1:
			instance = new Marin(400,300);
			break;
		case 2:
			break;
		default:
			break;
		}
	}
	return instance;
}


Player* Player::instance = nullptr;
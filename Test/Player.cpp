#include"Marin.h"
#include"Player.h"

Player* Player::getInstance(int character) {
	if (instance == nullptr) {
		switch (character)
		{
		case 1:
			instance = new Marin;
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
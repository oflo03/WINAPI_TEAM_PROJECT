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
			instance = new Marin(224, 640);
			//instance = new Marin(224, 256);		//	1�������� ��ȯ ��ǥ
			// instance = new Marin(960, 256);		//  2�������� ��ȯ ��ǥ
			// instance = new Marin(224, 640);		//  3�������� ��ȯ ��ǥ
			// instance = new Marin(960, 1000);		//  4�������� ��ȯ ��ǥ
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
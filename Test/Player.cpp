#include"Marin.h"
#include"Pilot.h"
#include"Knight.h"
#include"Player.h"

void Player::init()
{
	Marin::init();
	Pilot::init();
	Knight::init();
}


int selectedPlayer;

Player* Player::getInstance() {
	if (instance == nullptr) {
		currentCharacter = selectedPlayer;
		switch (selectedPlayer) {
		case marin:
			//instance = new Marin(960, 640);
			instance = new Marin(224, 256);		//	1�������� ��ȯ ��ǥ
			// instance = new Marin(960, 256);		//  2�������� ��ȯ ��ǥ
			// instance = new Marin(224, 640);		//  3�������� ��ȯ ��ǥ
			// instance = new Marin(960, 1000);		//  4�������� ��ȯ ��ǥ
			break;
		case pilot:
			instance = new Pilot(960, 640);
			break;
		case knight:
			instance = new Knight(224, 256);
			break;
		default:
			break;
		}
	}
	return instance;
}


Player* Player::instance = nullptr;
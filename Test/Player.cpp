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
			instance = new Marin(224, 256);		//	1스테이지 소환 좌표
			// instance = new Marin(960, 256);		//  2스테이지 소환 좌표
			// instance = new Marin(224, 640);		//  3스테이지 소환 좌표
			// instance = new Marin(960, 1000);		//  4스테이지 소환 좌표
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
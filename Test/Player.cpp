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

void Player::Destroy() {
	Marin::destroy();
	Pilot::destroy();
	Knight::destroy();
	instance->myWeapons.clear();
	delete instance;
	instance = nullptr;
}

Vector2D<float> spawnpoint[4]{
	Vector2D<float>(224,256),
	Vector2D<float>(960,256),
	Vector2D<float>(224,540),
	Vector2D<float>(960,1000)
};

int selectedPlayer;

Player* Player::getInstance() {
	if (instance == nullptr) {
		switch (selectedPlayer) {
		case marin:
			instance = new Marin(spawnpoint[0].x, spawnpoint[0].y);
			break;
		case pilot:
			instance = new Pilot(spawnpoint[0].x, spawnpoint[0].y);
			break;
		case knight:
			instance = new Knight(spawnpoint[0].x, spawnpoint[0].y);
			break;
		default:
			break;
		}
	}
	return instance;
}


Player* Player::instance = nullptr;
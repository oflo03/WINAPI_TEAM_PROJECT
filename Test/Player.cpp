#include"Marin.h"
#include"Knight.h"
#include"Player.h"

void Player::init()
{
	Marin::init();
	Knight::init();
}

void Player::Destroy() {
	if (instance == nullptr)
		return;
	delete instance;
	Marin::destroy();
	Knight::destroy();
	instance->myWeapons.clear();
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
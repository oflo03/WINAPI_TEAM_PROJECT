#pragma once
#include"Enemy.h"

class EnemyManager {
private:
	static EnemyManager* instance;
	std::vector<Enemy*> enemy;
	EnemyManager() {}
	EnemyManager(const EnemyManager& other) {}
	~EnemyManager();
public:
	static EnemyManager* getInstance();
	void init(int stage);
	static void destroy();
	void spawn(int type, float x, float y);
	void delete_enemy(Enemy* e);
	void handle_event();
	void update();
	void draw(HDC mDC);
};


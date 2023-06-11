#pragma once
#include"Enemy.h"

extern Animation spawnAnim;

class EnemyManager {
private:
	static EnemyManager* instance;
	std::vector<Enemy*> enemy;
	EnemyManager() {}
	EnemyManager(const EnemyManager& other) {}
	~EnemyManager();
public:
	static EnemyManager* getInstance();
	static void init();
	static void destroy();
	void Clear();
	void SetEnemy(int stage);
	void spawn(int type, float x, float y);
	void delete_enemy(Enemy* e);
	bool isclear();
	void handle_event();
	void update();
	void draw(HDC mDC);
};


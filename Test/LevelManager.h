#pragma once

class LevelManager
{
protected:
	int stage, phase;
	static LevelManager* instance;
public:
	LevelManager() :stage(1), phase(1) {}
	static void init();
	static void destroy();
	static LevelManager* getInstance();
	void update();
	void loadNextStage();
	int GetStage() { return stage; }
};
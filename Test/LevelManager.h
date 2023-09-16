#pragma once

class LevelManager
{
protected:
	int stage, phase;
	static LevelManager* instance;
public:
	LevelManager();
	~LevelManager();
	static LevelManager* getInstance();
	static void release();
	void update();
	void loadNextStage();
	int GetStage() { return stage; }
};
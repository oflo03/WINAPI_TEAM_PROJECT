#pragma once
#include"Sound.h"
#include<memory>
#include <vector>

enum SOUND {
	TitleState,
	MainState,
	BUTTONCLICK,
	WALK,
	ROLLING,
	EMPTY,
	ENEMYDEATH,
	ENEMYHURT,
	CURSORON,
	PISTOL_RELOAD,
	PISTOL_SHOT,
	RIFLE_RELOAD,
	RIFLE_SHOT,
	SHOTGUN_RELOAD,
	SHOTGUN_SHOT,
	ROCKET_RELOAD,
	ROCKET_SHOT,
	PLAYER_DEATH,
	PLAYER_HURT,
	SWORD_ATK,
	GAME_OVER,
	BOSSSCENE
};

class SoundManager
{
private:
	static SoundManager* instance;
	std::vector<std::unique_ptr<Sound>> sounds;
	SoundManager();
	~SoundManager();
public:
	static SoundManager* getInstance();
	static void release();
	void play(int type);
	void pause(int type);
	void resume(int type);
	void stop(int type);
	void volumeUp(int type);
	void volumeDown(int type);
	void update(int type);
	bool isPlaying(int type);
};


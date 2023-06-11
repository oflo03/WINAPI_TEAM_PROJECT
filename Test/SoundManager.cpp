#include "SoundManager.h"

SoundManager* SoundManager::instance;

SoundManager::SoundManager()
{
	Sound::init();
	sounds.emplace_back(new Sound("resources/BGM_TitleState.WAV", true));
	sounds.emplace_back(new Sound("resources/BGM_PlayState.WAV", true));
	sounds.emplace_back(new Sound("resources/menu_characterselect.WAV", false));
	sounds.emplace_back(new Sound("resources/dodge_roll.WAV", false));
	sounds.emplace_back(new Sound("resources/dodge_leap.WAV", false));
	sounds.emplace_back(new Sound("resources/empty.WAV", false));
	sounds.emplace_back(new Sound("resources/enemy_death.WAV", false));
	sounds.emplace_back(new Sound("resources/enemy_hurt.WAV", false));
	sounds.emplace_back(new Sound("resources/menu_confirm.WAV", false));
	sounds.emplace_back(new Sound("resources/Pistol_reload.WAV", false));
	sounds.emplace_back(new Sound("resources/Pistol_shot.WAV", false));
	sounds.emplace_back(new Sound("resources/Rifle_reload.WAV", false));
	sounds.emplace_back(new Sound("resources/Rifle_shot.WAV", false));
	sounds.emplace_back(new Sound("resources/Shotgun_reload.WAV", false));
	sounds.emplace_back(new Sound("resources/Shotgun_shot.WAV", false));
	sounds.emplace_back(new Sound("resources/Rocketx_reload.WAV", false));
	sounds.emplace_back(new Sound("resources/Rocketx_shot.WAV", false));
	sounds.emplace_back(new Sound("resources/player_death.WAV", false));
	sounds.emplace_back(new Sound("resources/player_hurt.WAV", false));
	sounds.emplace_back(new Sound("resources/Sword_attack.WAV", false));
	sounds.emplace_back(new Sound("resources/main_gameover.WAV", false));
	sounds.emplace_back(new Sound("resources/boss_intro.WAV", false));
}

SoundManager::~SoundManager()
{
	sounds.clear();
	Sound::release();
}

SoundManager* SoundManager::getInstance()
{
	if (instance == nullptr)
		instance = new SoundManager;
	return instance;
}

void SoundManager::release()
{
	if (instance != nullptr)
		delete instance;
}

void SoundManager::play(int type)
{
	sounds[type]->play();
}

void SoundManager::pause(int type)
{
	sounds[type]->pause();
}

void SoundManager::resume(int type)
{
	sounds[type]->resume();
}

void SoundManager::stop(int type)
{
	sounds[type]->stop();
}

void SoundManager::volumeUp(int type)
{
	sounds[type]->volumeUp();
}

void SoundManager::volumeDown(int type)
{
	sounds[type]->volumeDown();
}

void SoundManager::update(int type)
{
	sounds[type]->update();
}

bool SoundManager::isPlaying(int type)
{
	return sounds[type]->isPlaying();
}

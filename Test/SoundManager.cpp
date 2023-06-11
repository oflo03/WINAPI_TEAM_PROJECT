#include "SoundManager.h"

SoundManager* SoundManager::instance;

SoundManager::SoundManager()
{
	Sound::init();
	sounds.emplace_back(new Sound("BGM_TitleState.WAV", true));
	sounds.emplace_back(new Sound("BGM_PlayState.WAV", true));
	sounds.emplace_back(new Sound("menu_characterselect.WAV", false));
	sounds.emplace_back(new Sound("dodge_roll.WAV", false));
	sounds.emplace_back(new Sound("dodge_leap.WAV", false));
	sounds.emplace_back(new Sound("empty.WAV", false));
	sounds.emplace_back(new Sound("enemy_death.WAV", false));
	sounds.emplace_back(new Sound("enemy_hurt.WAV", false));
	sounds.emplace_back(new Sound("menu_confirm.WAV", false));
	sounds.emplace_back(new Sound("Pistol_reload.WAV", false));
	sounds.emplace_back(new Sound("Pistol_shot.WAV", false));
	sounds.emplace_back(new Sound("Rifle_reload.WAV", false));
	sounds.emplace_back(new Sound("Rifle_shot.WAV", false));
	sounds.emplace_back(new Sound("Shotgun_reload.WAV", false));
	sounds.emplace_back(new Sound("Shotgun_shot.WAV", false));
	sounds.emplace_back(new Sound("Rocketx_reload.WAV", false));
	sounds.emplace_back(new Sound("Rocketx_shot.WAV", false));
	sounds.emplace_back(new Sound("player_death.WAV", false));
	sounds.emplace_back(new Sound("player_hurt.WAV", false));
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

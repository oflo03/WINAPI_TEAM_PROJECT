#include "Sound.h"

FMOD::System* Sound::system = nullptr;

Sound::Sound(const std::string& path, bool loop)
{
	if (loop)
		system->createSound(path.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
	else
		system->createSound(path.c_str(), FMOD_LOOP_OFF, 0, &sound);
	channel = nullptr;
	volume = 1;
}

Sound::~Sound()
{
	sound->release();
}

void Sound::init()
{
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, NULL);
}

void Sound::release()
{
	system->close();
	system->release();
}

void Sound::play()
{
	system->playSound(sound, nullptr, false, &channel);
}

void Sound::pause()
{
	channel->setPaused(true);
}

void Sound::resume()
{
	channel->setPaused(false);
}

void Sound::stop()
{
	channel->stop();
}

void Sound::volumeUp()
{
	channel->setVolume(volume+=0.5);
}

void Sound::volumeDown()
{
	if(volume-0.5>=0)
	channel->setVolume(volume -= 0.5);
}

void Sound::update()
{
	system->update();
}

bool Sound::isPlaying()
{
	bool isPlaying;
	channel->isPlaying(&isPlaying);
	return isPlaying;
}

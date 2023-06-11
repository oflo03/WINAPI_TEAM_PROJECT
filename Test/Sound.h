#pragma once
#include "fmod.hpp"
#include <string>

class Sound
{
private:
	static FMOD::System* system;
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	float volume;
public:
	Sound(const std::string& path,bool loop);
	~Sound();
	static void init();
	static void release();
	void play();
	void pause();
	void resume();
	void stop();
	void volumeUp();
	void volumeDown();
	void update();
};


#pragma once
#include "fmod.hpp"
#include <string>

class Sound
{
private:
	static FMOD::System* system;
	FMOD::Sound* sound;
	FMOD::Channel* channel;
public:
	Sound(const std::string& path,bool loop);
	~Sound();
	static void init();
	static void release();
	static void update();
	void play();
	void pause();
	void resume();
	void stop();
	void volumeSet(double n);
	bool isPlaying();
};


#pragma once
#include "SDL_mixer.h"
#include <string>

class Audio
{
private:
	Mix_Music* menuMusic = nullptr;
	Mix_Music* gameMusic = nullptr;

	bool playing;
	int volume; //0 to 4 -- 0% to 100%
public:
	Audio();
	void Play(std::string playMusic);
	void Pause();
	void Resume();
	bool IsPaused();
	bool IsPlaying();
	void VolumeUp();
	void VolumeDown();
	int GetVolume();
	std::string GetVolumeString();
	void SetPlaying(bool p);
};


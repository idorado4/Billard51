#include "Audio.h"

Audio::Audio() {

	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error: SDL:MixerInit";

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "Error: SDL:MixerInit";
	}

	menuMusic = { Mix_LoadMUS("../res/au/menu.mp3") };
	if (!menuMusic) throw "Error loading audio";

	gameMusic = { Mix_LoadMUS("../res/au/game_theme.mp3") };
	if (!gameMusic) throw "Error loading audio";

	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

	playing = true;
	volume = 2;
}

//Recibe un string para saber que música debe reproducir
void Audio::Play(std::string playMusic)
{
	if (IsPlaying()) {
		if (playMusic == "menu") {
			Mix_PlayMusic(menuMusic, -1);
		}
		else if (playMusic == "game") {
			Mix_PlayMusic(gameMusic, -1);
		}
	}
}

void Audio::Pause()
{
	Mix_PauseMusic();
	playing = false;
}

void Audio::Resume()
{
	Mix_ResumeMusic();
	playing = true;
}

bool Audio::IsPaused()
{
	return Mix_PausedMusic();
}

bool Audio::IsPlaying()
{
	return playing;
}

void Audio::VolumeUp()
{
	volume++;
	if (volume >= 5) {
		volume = 4;
	}
	Mix_VolumeMusic((MIX_MAX_VOLUME / 4) * volume);
}

void Audio::VolumeDown()
{
	volume--;
	if (volume < 0) {
		volume = 0;
	}
	Mix_VolumeMusic((MIX_MAX_VOLUME / 4) * volume);
}

int Audio::GetVolume()
{
	return 25 * volume;
}

std::string Audio::GetVolumeString()
{
	return std::to_string(GetVolume());
}

void Audio::SetPlaying(bool p)
{
	playing = p;
}
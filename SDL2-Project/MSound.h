#pragma once
#include <SDL_mixer.h>
#include<iostream>
#include "MSound.h"
// for msound i used https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php to help me with adding sound effects and background music and these 2 videos as well https://www.youtube.com/watch?v=o0nyxxWRPnA and https://www.youtube.com/watch?v=I-TB5gUJS60
// but i cannot get wav files to work for this part gameMusic = Mix_LoadMUS("assets/assets/Spare_Song_1.ogg"); i only found .ogg files to work and play music for the background.
class MSound {
	// these sounds will play when game start by default
	Mix_Music* gameMusic = NULL;
	Mix_Music* menuMusic = NULL;

	Mix_Chunk** sounds;

public:
	// sound noises plays sfx 
	enum SOUNDNAME {
		EXPLOSION,
		COIN
	};
	// this formats opensound and then makes new sounds
	MSound() {
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		{
			printf("%s", Mix_GetError());
		}

		sounds = new Mix_Chunk * [5];

		// fx these are for the coin and explosion noises
		sounds[COIN] = Mix_LoadWAV("assets/Select2.wav");
		sounds[EXPLOSION] = Mix_LoadWAV("assets/Massive_Explosion.wav");


		//Load Music / background music or game music
		gameMusic = Mix_LoadMUS("assets/Spare_Song_1.ogg");
		if (gameMusic == NULL)
		{
			printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		}
		Mix_Volume(0, MIX_MAX_VOLUME);
		playGameMusic();
	}

	void playGameMusic() {
		Mix_PlayMusic(gameMusic, -1);
	}

	void playSound(SOUNDNAME id) {
		Mix_PlayChannel(-1, sounds[id], 0);
	}
};
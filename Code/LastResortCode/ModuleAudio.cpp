#include "Globals.h"
#include "Application.h"
#include "Module.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


ModuleAudio::ModuleAudio() : Module()
{
	
	for (uint i = 0; i < MAX_MUSICS; ++i)
		musics[i] = nullptr;
	for (uint i = 0; i < MAX_SOUNDEFECTS; ++i)
		sfx[i] = nullptr;

	//musics = new Music[MAX_MUSICS];
	//sfx = new Sfx[MAX_SOUNDEFECTS];
}

ModuleAudio::~ModuleAudio() {}

bool ModuleAudio::Init()
{
	LOG("Init Image library");
	bool ret = true;
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_VolumeMusic(GENERAL_MUSIC_VOLUME);

	return ret;
}

bool ModuleAudio::CleanUp()
{
	LOG("Freeing audios and Mixer library and shutdown mixer");

	for (uint i = 0; i < MAX_SOUNDEFECTS; ++i) {
		if (sfx[i] != nullptr) {
			Mix_FreeChunk(sfx[i]);
		}
	}

	for (uint i = 0; i < MAX_MUSICS; ++i) {
		if (musics[i] != nullptr) {
			Mix_FreeMusic(musics[i]);
		}
	}

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}
Mix_Music* const ModuleAudio::LoadMUS(const char* path) {

	Mix_Music *music = nullptr;

	music = Mix_LoadMUS(path);

	if (music == nullptr)
	{
		LOG("Unable to load music Mix Error: %s\n", Mix_GetError());
	}
	else
	{
		musics[last_music++] = music;
	}
	return music;
}

bool ModuleAudio::UnloadMUS(Mix_Music * music) {


	bool ret = false;

	if (music != nullptr)
	{
		for (int i = 0; i < MAX_MUSICS; ++i)
		{
			if (musics[i] == music)
			{
				Mix_FreeMusic(music);
				musics[i] = nullptr;
				ret = true;
				break;
			}
		}
		
	}

	return ret;
}

Mix_Chunk* const ModuleAudio::LoadSFX(const char* path) {

	Mix_Chunk *chunk;
	chunk = Mix_LoadWAV(path);

	if (chunk == nullptr)
	{
		LOG("Unable to load sfx Mix Error: %s\n", Mix_GetError());
	}
	else
		sfx[last_chunk++] = chunk;

	return chunk;
}

bool ModuleAudio::ControlMUS(Mix_Music* music, Audio_State state) {

	bool music_found = false;

	for (uint i = 0; i < last_music; ++i) {
		if (musics[i] == music) {
			music_found = true;
		}
	}
	
	if (!music_found) {
		LOG("Music not found ControlMUS");
	}
	else {
		switch (state)
		{
		case PLAY_AUDIO:
			if (!Mix_PlayingMusic()) 
				Mix_PlayMusic(music, 3);
			else
				LOG("Music is already playing");
			break;
		case STOP_AUDIO:
			if (!Mix_PausedMusic())
				Mix_PauseMusic();
			else
				LOG("Music is already stopped");
			break;

		default:
			break;
		}
	}
	return true;
}

bool ModuleAudio::ControlSFX(Mix_Chunk* chunk, Audio_State state) {
	
	bool sfx_found = false;
	for (uint i = 0; i <= last_music; ++i) {
		if (sfx[i] == chunk) {
			sfx_found = true;
		}
	}


	if (!sfx_found) {
		LOG("Music not found ControlSFX");
		return false;
	}
	else {
		switch (state)
		{
		case PLAY_AUDIO:
			LOG("Chunck is already playing");
				Mix_PlayChannel( -1, chunk, 0);
		default:
			LOG("Chunck has not this audio state");
			return false;
			break;
		}
	}
	return true;
}

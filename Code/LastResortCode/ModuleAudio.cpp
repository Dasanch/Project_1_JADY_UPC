#include "Globals.h"
#include "Application.h"
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

	return ret;
}



bool ModuleAudio::CleanUp()
{
	LOG("Freeing audios and Mixer library and shutdown mixer");

	for (uint i = 0; i < MAX_SOUNDEFECTS; ++i)
		if (sfx[i] != nullptr) {
			Mix_FreeChunk(sfx[i]);
		}

	for (uint i = 0; i < MAX_MUSICS; ++i)
		if (musics[i] != nullptr) {
			Mix_FreeMusic(musics[i]);
		}

	

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}


Mix_Chunk* const ModuleAudio::LoadSfx(const char* path) {

	Mix_Chunk *chunk;

	chunk = Mix_LoadWAV(path);
	if (chunk == NULL)
	{
		LOG("Unable to load sfx Mix Error: %s\n", Mix_GetError());
	}
	else
	{
		sfx[last_chunk++] = chunk;
	}
	return chunk;
}

Mix_Music* const ModuleAudio::LoadMUS(const char* path) {

	Mix_Music *music = NULL;

	music = Mix_LoadMUS(path);
	if (music == NULL)
	{
		LOG("Unable to load music Mix Error: %s\n", Mix_GetError());
	}
	else
	{
		musics[last_music++] = music;
	}
	return music;
}

//void ModuleAudio::PlayMusic(const char* path) {
//	uint i = 0;
//	while (musics[i] != path) {
//
//	}
//}

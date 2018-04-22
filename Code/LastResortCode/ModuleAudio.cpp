#include "Globals.h"
#include "Application.h"
#include "Module.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

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

update_status ModuleAudio::Update() {

	if (App->input->keyboard[SDL_SCANCODE_KP_PLUS] == KEY_STATE::KEY_DOWN) {
		volumeMUS += 5;
		if (volumeMUS > 180) {
			volumeMUS = 180;
		}	
		Mix_VolumeMusic(volumeMUS);
	}
	if (App->input->keyboard[SDL_SCANCODE_KP_MINUS] == KEY_STATE::KEY_DOWN) {
		volumeMUS -= 5;
		if (volumeMUS < 0) {
			volumeMUS = 0;
		}
		Mix_VolumeMusic(volumeMUS);
	}
	return UPDATE_CONTINUE;
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

	if (music != nullptr)
	{
		for (int i = 0; i < MAX_MUSICS; ++i)
		{
			if (musics[i] == nullptr)
			{
				musics[i] = music;
				return music;
			}
		}
	}
	else
		LOG("Unable to load music Mix Error: %s\n", Mix_GetError());

	return music;
}

Mix_Chunk* const ModuleAudio::LoadSFX(const char* path) {

	Mix_Chunk *chunk;
	chunk = Mix_LoadWAV(path);

	if (chunk != nullptr)
	{
		for (int i = 0; i < MAX_SOUNDEFECTS; ++i)
		{
			if (sfx[i] == nullptr)
			{
				sfx[i] = chunk;
				return chunk;
			}
		}
	}
	else
		LOG("Unable to load sfx Mix Error: %s\n", Mix_GetError());

	return chunk;
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

bool ModuleAudio::UnloadSFX(Mix_Chunk * sound_fx) {


	bool ret = false;

	if (sound_fx != nullptr)
	{
		for (int i = 0; i < MAX_MUSICS; ++i)
		{
			if (sfx[i] == sound_fx)
			{
				Mix_FreeChunk(sound_fx);
				sfx[i] = nullptr;
				ret = true;
				break;
			}
		}

	}
	return ret;
}


bool ModuleAudio::ControlMUS(Mix_Music* music, Audio_State state) {

	bool music_found = false;

	for (uint i = 0; i <MAX_MUSICS ; ++i) {
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

	for (uint i = 0; i < MAX_SOUNDEFECTS; ++i) {
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
			Mix_VolumeChunk(chunk, volumeSFX);
			Mix_PlayChannel( -1, chunk, 0);
			break;
		default:
			LOG("Chunck has not this audio state");
			return false;
			break;
		}
	}
	return true;
}

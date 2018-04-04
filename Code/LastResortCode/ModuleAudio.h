#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_MUSICS 3
#define MAX_SOUNDEFECTS 20


enum Music_State {
	PLAY,
	STOP, 
	RESUME
};

struct Sfx {
	Mix_Chunk *chunk;
	char *file;
};

class ModuleAudio : public Module {
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Chunk* const LoadSfx(const char* path);
	Mix_Music* const LoadMUS(const char* path);
	void PlayMusic(const char* path);

private:
	Mix_Music *musics [MAX_MUSICS];
	Mix_Chunk *sfx [MAX_SOUNDEFECTS];
	uint last_chunk = 0;
	uint last_music = 0;
};


#endif // __ModuleAudio_H__
#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_MUSICS 3
#define MAX_SOUNDEFECTS 20


enum Audio_State {
	PLAY_AUDIO,
	STOP_AUDIO, 
};

struct Music {
	Mix_Music * music;
	char *name;
};

struct Sfx {
	Mix_Chunk *chunk;
	char *name;
};

class ModuleAudio : public Module {
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Chunk* const LoadSfx(const char* path, char *name);
	Mix_Music* const LoadMUS(const char* path, char *name);
	void ControlMUS (char* name, Audio_State state);

private:
	Music musics[MAX_MUSICS];
	Sfx sfx[MAX_SOUNDEFECTS];
	uint last_chunk = 0;
	uint last_music = 0;
};


#endif // __ModuleAudio_H__
#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_MUSICS 8
#define MAX_SOUNDEFECTS 20
#define GENERAL_MUSIC_VOLUME 15 //0 to 180
#define GENERAL_SFX_VOLUME 20 //0 to 100

typedef struct _Mix_Music Mix_Music;

enum Audio_State {
	PLAY_AUDIO,
	STOP_AUDIO, 
};

//struct Music {
//	Mix_Music * music;
//	char *name;
//};
//
//struct Sfx {
//	Mix_Chunk *chunk;
//	char *name;
//};

class ModuleAudio : public Module {
public:
	ModuleAudio();
	~ModuleAudio();
	
	bool Init();
	update_status Update();
	bool CleanUp();

	Mix_Chunk* const LoadSFX(const char* path);
	Mix_Music* const LoadMUS(const char* path);
	bool ControlMUS (Mix_Music* music, Audio_State state);
	bool ControlSFX(Mix_Chunk* chunk, Audio_State state);
	bool UnloadMUS(Mix_Music* music);
	bool UnloadSFX(Mix_Chunk* chunk);
private: 

	Mix_Music* musics[MAX_MUSICS];
	Mix_Chunk* sfx[MAX_SOUNDEFECTS];
	int volumeMUS = GENERAL_MUSIC_VOLUME;
	int volumeSFX= GENERAL_SFX_VOLUME;
	uint last_chunk = 0;
	uint last_music = 0;
};


#endif // __ModuleAudio_H__

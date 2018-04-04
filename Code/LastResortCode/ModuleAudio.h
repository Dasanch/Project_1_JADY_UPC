#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"

#define MAX_SOUNDEFECTS 20

struct Mix_Music;
struct Mix_Chunk;

class ModuleAudio : public Module {
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

private:
	Mix_Music *level_music;
	Mix_Chunk *sfx [MAX_SOUNDEFECTS];
	uint last_chunk = 0;
};


#endif // __ModuleAudio_H__
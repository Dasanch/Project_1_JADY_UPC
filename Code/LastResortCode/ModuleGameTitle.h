#ifndef __MODULEGAMETITLE_H__
#define __MODULEGAMETITLE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
typedef struct _Mix_Music Mix_Music;

struct SDL_Texture;

class ModuleGameTitle : public Module
{
public:
	ModuleGameTitle();
	~ModuleGameTitle();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * TitleTexture = nullptr;
	SDL_Texture *L1Texture;
	SDL_Texture *A2Texture;
	SDL_Rect LastResortRect;

	Animation L1;
	Animation A2;
	
	float current_frame;
	float currenA2 = 0;

	//audios
	Mix_Music* Titlemusic = nullptr;
};

#endif // __MODULEGAMETITLE_H__

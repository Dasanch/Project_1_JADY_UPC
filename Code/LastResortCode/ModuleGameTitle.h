#ifndef __MODULEGAMETITLE_H__
#define __MODULEGAMETITLE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

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
	SDL_Rect LastResortRect;

	Animation L1;
	Animation A2;
	
	float current_frame;
};

#endif // __MODULEGAMETITLE_H__

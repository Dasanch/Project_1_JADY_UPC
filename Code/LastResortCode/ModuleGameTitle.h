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

	SDL_Texture * graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect roof;
	SDL_Rect foreground;
	SDL_Rect background;
	Animation water;
};

#endif // __MODULEGAMETITLE_H__

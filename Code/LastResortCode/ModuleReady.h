#ifndef __ModuleStageReady_H__
#define __ModuleStageReady_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStageReady : public Module
{
public:
	ModuleStageReady();
	~ModuleStageReady();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//Textures
	SDL_Texture* backgroundReady = nullptr;

	//Rectangles
	SDL_Rect BGroundReady;
	SDL_Rect backgroundBlack;
	Uint32 start_time;
	Uint32 current_time;

};

#endif

#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();

public:
	
	SDL_Texture * groundAndTunel = nullptr;
	SDL_Texture* PurpleBuildings = nullptr;
	SDL_Texture* BackgroundBuildings = nullptr;
	SDL_Texture* Boss1Background = nullptr;

	SDL_Rect BGBuildings;
	SDL_Rect ground;
	SDL_Rect PBuildings;


	


};

#endif
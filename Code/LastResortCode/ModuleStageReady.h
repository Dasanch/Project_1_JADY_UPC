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
	//SDL_Texture* map2Text = nullptr;
	

	//Rectangles
	SDL_Rect BGroundReady;
	SDL_Rect backgroundBlack;
	

	// Background movement (position) values
	/*float movementx = 0;
	float movementxBack = 0;
	float movementxPlanetsBack = 0;
	float movementy = -55;*/
};

#endif

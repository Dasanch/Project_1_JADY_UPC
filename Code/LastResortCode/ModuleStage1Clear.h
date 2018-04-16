#ifndef __ModuleStage1Clear_H__
#define __ModuleStage1Clear_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStage1Clear : public Module
{
public:
	ModuleStage1Clear();
	~ModuleStage1Clear();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//Textures
	SDL_Texture* backgroundStageClear1 = nullptr;

	//Rectangles
	SDL_Rect BGroundStageClear1;
	SDL_Rect backgroundBlack;


};

#endif

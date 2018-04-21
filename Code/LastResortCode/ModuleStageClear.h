#ifndef __ModuleStage1Clear_H__
#define __ModuleStage1Clear_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStageClear : public Module
{
public:
	ModuleStageClear();
	~ModuleStageClear();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//Textures
	SDL_Texture* backgroundStageClear1 = nullptr;
	SDL_Texture* Players_Texture;
	//Rectangles
	SDL_Rect BGroundStageClear1;
	SDL_Rect backgroundBlack;

	SDL_Rect Player1 = { 64,3,32,12 };
	SDL_Rect Player2 = { 262,3,32,11 };

};

#endif

#ifndef __ModuleContinue_H__
#define __ModuleContinue_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleContinue : public Module
{
public:
	ModuleContinue();
	~ModuleContinue();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	//Textures
	SDL_Texture* backgroundCont = nullptr;


	//Rectangles
	SDL_Rect BGroundCont;
	SDL_Rect BBlack;
	
};

#endif

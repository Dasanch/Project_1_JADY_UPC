#ifndef __ModuleStageClear_H__
#define __ModuleStageClear_H__

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
public:
	Mix_Music * lvlComplitedMusic;
	Uint32 start_time;
	Uint32 current_time;

};

#endif

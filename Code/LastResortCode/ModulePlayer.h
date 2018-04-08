#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();

public:

	SDL_Texture* PlayerTexture = nullptr;
	iPoint position;

	Animation ShipOne;
	float CurrentFrame =NULL;
	float ignitionSpeed = NULL;
	float releaseSpeed=NULL;

	float playerSpeed=NULL;


};

#endif
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
	bool CleanUp();

public:
	iPoint position;
	float const movementSpeed = 1;

	SDL_Texture* PlayerTexture = nullptr;
	Animation shipPlayer1;
	float yAxis = 0;
	const float keyPressSpeed = 0.05f;
	const float keyReleaseSpeed = 0.05f;
	int currentFrame;
	float const transitionLimit = 0.5f;
	float const MaxLimit = 0.90f;
	enum ShipFrames
	{
		MaxUp,
		TransitionUp,
		Idle,
		TransitionDown,
		MaxDown
	};
};

#endif
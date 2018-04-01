#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "SDL_image\include\SDL_image.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	//TileMaplvl1
	ground.x = 0;
	ground.y = 0;
	ground.w = 4408;
	ground.h = 239;

	PBuildings.h = 160;
	PBuildings.w = 1303;
	PBuildings.x = 0;
	PBuildings.y = 20;

	BGBuildings.x = 0;
	BGBuildings.y = 0;
	BGBuildings.w = 304;
	BGBuildings.h = 176;
	
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	groundAndTunel = App->textures->Load("../Game/Assets/TileMaplvl1Ground&Tunel.png");
	PurpleBuildings = App->textures->Load("../Game/Assets/midGroundBuildingsFull.png");
	BackgroundBuildings = App->textures->Load("../Game/Assets/firstCameraMovBuilding04.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	int speedBG = 1;
	SDL_RenderCopy(App->render->renderer, BackgroundBuildings, NULL, &BGBuildings);

	int speedPB = 1;
	SDL_RenderCopy(App->render->renderer, PurpleBuildings, NULL, &PBuildings);
	if (PBuildings.x > -PBuildings.w)
	{
		PBuildings.x -= speedPB;
		BGBuildings.x -= speedBG;
		if (BGBuildings.x == -BGBuildings.w)
		{
			BGBuildings.x = 0;
		}
	}


	int speed = 1;
	SDL_RenderCopy(App->render->renderer, groundAndTunel, NULL, &ground);
	ground.x -= speed;


	

	return UPDATE_CONTINUE;
}
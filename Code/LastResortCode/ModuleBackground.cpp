#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "SDL_image\include\SDL_image.h"

#define midgroundOffset 32

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
	PBuildings.y = 0; 

	BGBuildings.x = 0;
	BGBuildings.y = 0;
	BGBuildings.w = 803;
	BGBuildings.h = 160;

	//Midground lights
	midgndLightsAnim01.PushBack({   1,  1, 95, 86 });
	midgndLightsAnim01.PushBack({  98,  1, 95, 86 });
	midgndLightsAnim01.PushBack({ 195 , 1 ,95, 86 });
	midgndLightsAnim01.PushBack({ 292 , 1 ,95, 86 });
	midgndLightsAnim01.PushBack({ 389 , 1 ,95, 86 });
	midgndLightsAnim01.PushBack({ 486 , 1 ,95, 86 });
	midgndLightsAnim01.PushBack({ 583 , 1 ,95, 86 });
	midgndLightsAnim01.speed = 0.08f;
	//!TO IMPLEMENT: Adjust animation speed
	//!TO IMPLEMENT: Create middlegroundLights01, 02...
	
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
	Boss1Background = App->textures->Load("../Game/Assets/StaticBackground.png");
	midgroundLightsTx = App->textures->Load("../Game/Assets/MidgroundLights.png");
	return ret;
}



// Update: draw background
update_status ModuleBackground::Update()
{
	App->render->camera.x -= 1; //CAMERA AUTO MOV

	App->render->Blit(Boss1Background, 0, 0, NULL, 0.0f); //everytime printed->need change
	App->render->Blit(BackgroundBuildings, 0, 0, &BGBuildings, 0.25f);
	App->render->Blit(PurpleBuildings, 0, midgroundOffset, &PBuildings, 0.50f);
	App->render->Blit(groundAndTunel, 0, 0, &ground, 1.0f);

	//Midground lights
	App->render->Blit(midgroundLightsTx, 40, midgroundOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), 0.50f);
	//Positions calculated from the png
	//!TO IMPLEMENT: See when the background loops so we can put the lights over again

	// Draw everything --------------------------------------
	/*int speedBG = 1;
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
	ground.x -= speed;*/


	

	return UPDATE_CONTINUE;
}
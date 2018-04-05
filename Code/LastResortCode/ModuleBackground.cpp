#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "SDL_image\include\SDL_image.h"
#include <stdlib.h>
#include <time.h> //Asure that we can use this library

#define midgndOffset 32
#define midgndSpeed 0.5f
//midgndLoopDist = Distance when the first building on the tilemap repeats
#define midgndLoopDist 512

#define streetLightDist 64
#define streetLightLoopDist 64

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
	midgndLightsAnim01.PushBack({   1, 1, 95, 86 });
	midgndLightsAnim01.PushBack({  98, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 195, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 292, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 389, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 486, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 583, 1, 95, 86 });
	midgndLightsAnim01.speed = 0.08f;

	midgndLightsAnim02.PushBack({   1, 88, 37, 61 });
	midgndLightsAnim02.PushBack({  39, 88, 37, 61 });
	midgndLightsAnim02.PushBack({  77, 88, 37, 61 });
	midgndLightsAnim02.PushBack({ 115, 88, 37, 61 });
	midgndLightsAnim02.PushBack({ 153, 88, 37, 61 });
	midgndLightsAnim02.PushBack({ 191, 88, 37, 61 });
	midgndLightsAnim02.PushBack({ 229, 88, 37, 61 });
	midgndLightsAnim02.speed = 0.08f;

	midgndLightsAnim03.PushBack({   1, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 110, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 219, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 328, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 437, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 546, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 655, 150, 108, 47 });
	midgndLightsAnim03.speed = 0.08f;

	midgndLightsAnim04.PushBack({   1, 198, 15, 12 });
	midgndLightsAnim04.PushBack({  17, 198, 15, 12 });
	midgndLightsAnim04.PushBack({  33, 198, 15, 12 });
	midgndLightsAnim04.PushBack({  49, 198, 15, 12 });
	midgndLightsAnim04.PushBack({  65, 198, 15, 12 });
	midgndLightsAnim04.PushBack({  81, 198, 15, 12 });
	midgndLightsAnim04.PushBack({   97, 198, 15, 12 });
	midgndLightsAnim04.speed = 0.08f;

	midgndLightsAnim05.PushBack({  1, 211,  48, 93 });
	midgndLightsAnim05.PushBack({ 50, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 99, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 148, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 197, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 246, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 295, 211, 48, 93 });
	midgndLightsAnim05.speed = 0.08f;

	midgndLightsAnim06.PushBack({ 1, 305,  61, 77 });
	midgndLightsAnim06.PushBack({ 63, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 125, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 187, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 249, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 311, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 373, 305, 61, 77 });
	midgndLightsAnim06.speed = 0.08f;
	//!TO IMPLEMENT: Adjust animation speed

	//Street Lights

	streetLightsAnim.PushBack({ 0,0, 48, 65 });
	streetLightsAnim.PushBack({ 49, 0, 48, 65 });
	streetLightsAnim.PushBack({ 98, 0, 48, 65 });
	streetLightsAnim.PushBack({ 147, 0, 48, 65 });
	streetLightsAnim.PushBack({ 98, 0, 48, 65 });
	streetLightsAnim.PushBack({ 49, 0, 48, 65 });
	streetLightsAnim.speed = 0.10f;

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
	streetLightsTx = App->textures->Load("../Game/Assets/StreetLights.png");

	srand(time(NULL));

	for (int i = 1; i < 27; ++i) {
		randoms[i] = rand() % 6 + 1;
	}
	return ret;
}



// Update: draw background
update_status ModuleBackground::Update()
{
	App->render->camera.x -= 1; //CAMERA AUTO MOV

	App->render->Blit(Boss1Background, 0, 0, NULL, 0.0f); //everytime printed->need change
	App->render->Blit(BackgroundBuildings, 0, 0, &BGBuildings, 0.25f);
	App->render->Blit(PurpleBuildings, 0, midgndOffset, &PBuildings, midgndSpeed);
	

	//Midground lights
	//- Loop 1
	App->render->Blit(midgroundLightsTx,  40, midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, 184, midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, 234, midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, 329, midgndOffset +  2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, 392, midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, 471, midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
	//- Loop 2
	App->render->Blit(midgroundLightsTx, midgndLoopDist +  40, midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, midgndLoopDist + 184, midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, midgndLoopDist + 234, midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, midgndLoopDist + 329, midgndOffset + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, midgndLoopDist + 392, midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, midgndLoopDist + 471, midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
	//- Loop 3
	App->render->Blit(midgroundLightsTx, midgndLoopDist * 2 + 40, midgndOffset +  28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, midgndLoopDist * 2 + 184, midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, midgndLoopDist * 2 + 234, midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, midgndLoopDist * 2 + 329, midgndOffset +  2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, midgndLoopDist * 2 + 392, midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgroundLightsTx, midgndLoopDist * 2 + 471, midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);

	//Positions calculated from the png
	//!TO IMPLEMENT: See when the background loops so we can put the lights over again
	//IMPLEMENTATION 01- Possible implementation with ifs comparing the camera.x with the position.x of each rect of animation
	//IMPLEMENTATION 02
	//int loops; //Each time it repeats goes to a next loop
	//=/ it would change all of them at the same time
	//App->render->Blit(midgroundLightsTx, midgndLoopDist * loops + 40, midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);



	App->render->Blit(groundAndTunel, 0, 0, &ground, 1.0f);

	//Street Lights

	App->render->Blit(streetLightsTx, 40 , 136, &streetLightsAnim.GetCurrentFrame(), 1.0f);
	for (int i = 1; i < 27; ++i) {
		App->render->Blit(streetLightsTx, 40 + streetLightDist*i, 136, &streetLightsAnim.GetFrame(randoms[i]), 1.0f);

	}
	

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
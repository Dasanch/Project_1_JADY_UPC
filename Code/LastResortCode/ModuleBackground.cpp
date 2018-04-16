#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "SDL_image\include\SDL_image.h"
#include <stdlib.h>
#include <time.h>
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleStageReady.h"
#include "ModuleAudio.h"
#include "ModuleGameOver.h"//delete (provitional)
#include "ModuleContinue.h" 
#include "ModuleParticles.h"
#include "ModuleCollision.h"

#define midgndLoopDist 512 //midgndLoopDist = Distance when the first building on the tilemap repeats
#define midgndOffset 32
#define midgndSpeed 0.4f
#define backgroundspeed 0.2f
#define bckgndSpeed 0.25f
#define foregndSpeed 1.0f
#define tunnelLightDist 256
#define orangeLaserSpeed 0.25f

#define streetLightDist 64
#define roadLightDist 121

ModuleBackground::ModuleBackground()
{
	frame = 0;
	srand((unsigned int)time(NULL));
	for (int i = 1; i < 27; ++i) {
		randoms[i] = (rand() % 6 + 1);
	}

	TakeTileMap();
	TakeTunnelLights();
	TakeBckLights();
	TakeMidLights();
	TakeStreetLights();
	TakeOrangeLaser();
	TakeBlueLaser();
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	//textures-----------------------------------------------------------------------
	groundAndTunel = App->textures->Load("Assets/TileMaplvl1Ground&Tunel.png");
	PurpleBuildings = App->textures->Load("Assets/midGroundBuildingsFull.png");
	BackgroundBuildings = App->textures->Load("Assets/firstCameraMovBuilding04.png");
	LasersTx = App->textures->Load("Assets/Lasers_bg.png");
	Boss1Background = App->textures->Load("Assets/StaticBackground.png");
	bckgndLightsTx = App->textures->Load("Assets/BackgroundLights.png");
	midgndLightsTx = App->textures->Load("Assets/MidgroundLights.png");
	tunnelLightsTx = App->textures->Load("Assets/TunnelLights.png");
	streetLightsTx = App->textures->Load("Assets/StreetLights.png");
	//audios------------------------------------------------------------------------
	music_01 = App->audio->LoadMUS("Assets/stage1.ogg");
	App->audio->ControlMUS(music_01, PLAY_AUDIO);
	
	//Enable------------------------------------------------------------------------
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	//"Reset ship position when fadetoblackends" 
	App->player->position.x = 0;
	App->player->position.y = 100;
	//Static enemy
	staticEnemyTx = App->textures->Load("Assets/NeoGeo/StaticEnemy.png");
	App->collision->AddCollider({ 500, 100, 128, 128 }, COLLIDER_WALL);

	return ret;

}

bool ModuleBackground::CleanUp()
{
	LOG("Unloading background assets");
	//textures-----------------------------------------------------------------------
	App->textures->Unload(groundAndTunel);
	App->textures->Unload(PurpleBuildings);
	App->textures->Unload(BackgroundBuildings);
	App->textures->Unload(LasersTx);
	App->textures->Unload(Boss1Background);
	App->textures->Unload(bckgndLightsTx);
	App->textures->Unload(midgndLightsTx);
	App->textures->Unload(tunnelLightsTx);
	App->textures->Unload(streetLightsTx);
	//audios------------------------------------------------------------------------
	App->audio->ControlMUS(music_01, STOP_AUDIO);
	App->audio->UnloadMUS(music_01);
	//Modules-----------------------------------------------------------------------
	App->player->Disable(); //Disable the player module
	App->particles->Disable();
	App->collision->Disable();
	App->render->camera.x = 0;
	//------------------------------------------------------------------------------
	return true;
}


// Update: draw background
update_status ModuleBackground::Update()
{
	// Move camera forward -----------------------------

	App->player->position.x += 1;
	App->render->camera.x -= 3;

	//-------------------------------------------------
	//int speed = 2;

	////Camera movement
	//if (App->render->camera.x > -((4400 / foregndSpeed) * SCREEN_SIZE))
	//{
	//	App->render->camera.x -= speed; //CAMERA AUTO MOV

	//}

	//Boss buildings--------------------------------------
	if (App->render->camera.x < -(3800 * SCREEN_SIZE))
	{
		App->render->Blit(Boss1Background, 0, 0, NULL, 0.0f);
	}

	//Background buildings-----------------------------------------------------------------------
	if (App->render->camera.x > -((3800 / foregndSpeed) * SCREEN_SIZE))
	{
		App->render->Blit(BackgroundBuildings, 0, 0, &BGBuildings, bckgndSpeed);
	}
	
	//Background lights-----------------------------------------------------------------------------
	App->render->Blit(bckgndLightsTx, -9, 0, &bckgndLightsAnim01.GetCurrentFrame(), bckgndSpeed);
	App->render->Blit(bckgndLightsTx, 504, 1, &bckgndLightsAnim01.GetCurrentFrame(), bckgndSpeed);
	App->render->Blit(bckgndLightsTx,634,10, &bckgndLightsAnim02.GetCurrentFrame(), bckgndSpeed);
	App->render->Blit(bckgndLightsTx, 122, 10, &bckgndLightsAnim02.GetCurrentFrame(), bckgndSpeed);
	App->render->Blit(bckgndLightsTx,88,50, &bckgndLightsAnim03.GetCurrentFrame(), bckgndSpeed);
	App->render->Blit(bckgndLightsTx, 600,50, &bckgndLightsAnim03.GetCurrentFrame(), bckgndSpeed);
	App->render->Blit(bckgndLightsTx,321,0 , &bckgndLightsAnim04.GetCurrentFrame(), bckgndSpeed);
	App->render->Blit(bckgndLightsTx, 167 ,0 , &bckgndLightsAnim05.GetCurrentFrame(), bckgndSpeed);
	App->render->Blit(bckgndLightsTx, 679, 0, &bckgndLightsAnim05.GetCurrentFrame(), bckgndSpeed);
	App->render->Blit(bckgndLightsTx,240,32, &bckgndLightsAnim06.GetCurrentFrame(), bckgndSpeed);
	

	//Orange Laser-----------------------------------------------------------------------------

	if (App->render->camera.x > -((2000 / foregndSpeed) * SCREEN_SIZE) && App->render->camera.x <= (-33)* SCREEN_SIZE* foregndSpeed)
	{
		orangeLaserAnim.LoopAnimation();
		if (frame < 2 ) {
			frame++;
			if (orangeLaserAnim.current_frame < orangeLaserAnim.last_frame/ 2)
				App->render->FlippedBlit(LasersTx, 359- orangeLaserAnim.GetFrame().w, 0, &orangeLaserAnim.GetFrame(), orangeLaserSpeed);
			else
				App->render->Blit(LasersTx, 358, 0, &orangeLaserAnim.GetFrame(), orangeLaserSpeed);
		}
		else
			frame = 0;
	}

	//Background lights
	//App->render->Blit(bckgndLightsTx, , , &bckgndLightsAnim01.GetCurrentFrame(), bckgndSpeed);
	//App->render->Blit(bckgndLightsTx, , , &bckgndLightsAnim02.GetCurrentFrame(), bckgndSpeed);
	//App->render->Blit(bckgndLightsTx, , , &bckgndLightsAnim03.GetCurrentFrame(), bckgndSpeed);
	//App->render->Blit(bckgndLightsTx, , , &bckgndLightsAnim04.GetCurrentFrame(), bckgndSpeed);
	//App->render->Blit(bckgndLightsTx, , , &bckgndLightsAnim05.GetCurrentFrame(), bckgndSpeed);
	//App->render->Blit(bckgndLightsTx, , , &bckgndLightsAnim06.GetCurrentFrame(), bckgndSpeed);

	//Midground buildings-------------------------------------------------------------------------------------------------------
	
	//MOVE UP DOWN 
	/*if (App->render->camera.x > -((2000 / foregndSpeed) * SCREEN_SIZE))
	{
		if (App->render->camera.x <= -324 && App->render->camera.x >= -663)
		{
			App->render->Blit(PurpleBuildings, 0, 0, &PBuildings, midgndSpeed);
			//Midground lights
			//- Loop 1
			App->render->Blit(midgndLightsTx, 40, 0 + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, 184, 0 + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, 234, 0 + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, 329, 0 + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, 392, 0 + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, 471, 0 + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
			//- Loop 2
			App->render->Blit(midgndLightsTx, midgndLoopDist + 40, 0 + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist + 184, 0 + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist + 234, 0 + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist + 329, 0 + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist + 392, 0 + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist + 471, 0 + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
			//- Loop 3
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 40, 0 + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 184, 0 + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 234, 0 + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 329, 0 + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 392, 0 + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 471, 0 + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
			//Positions calculated from the png
		}

		else {
			App->render->Blit(PurpleBuildings, 0, midgndOffset, &PBuildings, midgndSpeed);
			//Midground lights
			//- Loop 1
			App->render->Blit(midgndLightsTx, 40, midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, 184, midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, 234, midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, 329, midgndOffset + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, 392, midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, 471, midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
			//- Loop 2
			App->render->Blit(midgndLightsTx, midgndLoopDist + 40, midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist + 184, midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist + 234, midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist + 329, midgndOffset + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist + 392, midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist + 471, midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
			//- Loop 3
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 40, midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 184, midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 234, midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 329, midgndOffset + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 392, midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
			App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 471, midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
			//Positions calculated from the png
		}
		
	}*/

	if (App->render->camera.x > -((2000 / foregndSpeed) * SCREEN_SIZE)) {
		App->render->Blit(PurpleBuildings, 0, midgndOffset, &PBuildings, midgndSpeed);
		//Midground lights
		//- Loop 1
		App->render->Blit(midgndLightsTx, 40, midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, 184, midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, 234, midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, 329, midgndOffset + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, 392, midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, 471, midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
		//- Loop 2
		App->render->Blit(midgndLightsTx, midgndLoopDist + 40, midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, midgndLoopDist + 184, midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, midgndLoopDist + 234, midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, midgndLoopDist + 329, midgndOffset + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, midgndLoopDist + 392, midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, midgndLoopDist + 471, midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
		//- Loop 3
		App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 40, midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 184, midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 234, midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 329, midgndOffset + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 392, midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
		App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 471, midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
		//Positions calculated from the png
	}



	//Blue Lasers-------------------------------------------------------------------------------------------
	blueLaserAnim.LoopAnimation();

	if (blueLaserAnim.current_frame < blueLaserAnim.last_frame / 2) {
		App->render->Blit(LasersTx, 201 - blueLaserAnim.GetFrame().w, -40, &blueLaserAnim.GetFrame(), midgndSpeed);
		App->render->Blit(LasersTx, 713 - blueLaserAnim.GetFrame().w, -40, &blueLaserAnim.GetFrame(), midgndSpeed);
		App->render->Blit(LasersTx, 793 - blueLaserAnim.GetFrame().w, -8, &blueLaserAnim.GetFrame(), midgndSpeed);
		App->render->Blit(LasersTx, 857 - blueLaserAnim.GetFrame().w, -56, &blueLaserAnim.GetFrame(), midgndSpeed);
	}
	else {
		App->render->Blit(LasersTx, 200, -40, &blueLaserAnim.GetFrame(), midgndSpeed);
		App->render->Blit(LasersTx, 712, -40, &blueLaserAnim.GetFrame(), midgndSpeed);
		App->render->Blit(LasersTx, 792, -8, &blueLaserAnim.GetFrame(), midgndSpeed);
		App->render->Blit(LasersTx, 856, -56, &blueLaserAnim.GetFrame(), midgndSpeed);
	}
		

	//Ground and tunnel-----------------------------------------------------------------------------------
	/*
    if (App->render->camera.x > -((5000 / foregndSpeed) * SCREEN_SIZE))
	{
		App->render->Blit(groundAndTunel, 0, 0, &ground, foregndSpeed);
	}*/

	//-----Move Up and Down---------------------------------------------------------------
	
	//MOVE UP DOWN 
	/*if (App->render->camera.x > -((5000 / foregndSpeed) * SCREEN_SIZE))
	{
		if (App->render->camera.x <= -324 && App->render->camera.x >= -663)
		{
			App->render->Blit(groundAndTunel, 0, -15, &ground, foregndSpeed);
		}

		else {
			App->render->Blit(groundAndTunel, 0, 0, &ground, foregndSpeed);
		}
	}*/

	if (App->render->camera.x > -((5000 / foregndSpeed) * SCREEN_SIZE)) {

		App->render->Blit(groundAndTunel, 0, 0, &ground, foregndSpeed);
	}

	//--------------------------------------------------------------------------------------------

	//Street Lights-----------------------------------------------------------------------------------------
	if (App->render->camera.x > -((2000 / foregndSpeed) * SCREEN_SIZE))
	{
		//1
		App->render->Blit(streetLightsTx, 40, 136, &streetLightsAnim01.GetCurrentFrame(), 1.0f);
		for (int i = 1; i < 27; ++i) {
			App->render->Blit(streetLightsTx, 40 + streetLightDist * i, 136, &streetLightsAnim01.AddFrame(randoms[i]), foregndSpeed);
		}
		//2
		App->render->Blit(streetLightsTx, 0, 217, &streetLightsAnim02.GetCurrentFrame(), 1.0f);
		for (int i = 1; i < 14; ++i) {
			App->render->Blit(streetLightsTx, 0 + roadLightDist * i, 217, &streetLightsAnim02.AddFrame(randoms[i]), foregndSpeed);
		}
	}


	//Tunnel lights----------------------------------------------------------------------------------------
	if (App->render->camera.x < -((1000 / foregndSpeed) * SCREEN_SIZE) && App->render->camera.x > -((4000 / foregndSpeed) * SCREEN_SIZE))
	{
		App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 0, 0, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
		App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 1, 0, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
		App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 2, 0, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
		App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 3, 0, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
		App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 4, 0, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
		App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 5, 0, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
		App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 6, 0, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
		App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 7, 0, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
		//Could be implemented with a for, but probably all the frames would be the same
		//2048 = distance from the start of the tilemap to the first light
	}
	

	//Change scenes on button press
	if (App->input->keyboard[SDL_SCANCODE_SPACE])
	{
		App->fade->FadeToBlack(this, App->scene_ready, 0.5f);
	}
	if (App->input->keyboard[SDL_SCANCODE_G])
	{
		App->fade->FadeToBlack(this, App->scene_gameover, 0.0); 
	}
	if (App->input->keyboard[SDL_SCANCODE_C])
	{
		App->fade->FadeToBlack(this, App->scene_continue, 0.0);
	}

	//Static enemy
	App->render->Blit(staticEnemyTx, 500, 100, NULL, foregndSpeed);

	return UPDATE_CONTINUE;
}

void ModuleBackground::TakeTileMap()
{
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
}
void ModuleBackground::TakeTunnelLights()
{
	tunnelLightsAnim.PushBack({ 1,   1, 116, 168 });
	tunnelLightsAnim.PushBack({ 118,   1, 116, 168 });
	tunnelLightsAnim.PushBack({ 235,   1, 116, 168 });
	tunnelLightsAnim.PushBack({ 352,   1, 116, 168 });
	tunnelLightsAnim.PushBack({ 1, 169, 116, 168 });
	tunnelLightsAnim.PushBack({ 118, 169, 116, 168 });
	tunnelLightsAnim.PushBack({ 235, 169, 116, 168 });
	tunnelLightsAnim.PushBack({ 352, 169, 116, 168 });
	tunnelLightsAnim.speed = 0.02f;
}

void ModuleBackground::TakeBckLights()
{
	//1
	bckgndLightsAnim01.PushBack({ 1,  1, 89, 78 });
	bckgndLightsAnim01.PushBack({ 91,  1, 89, 78 });
	bckgndLightsAnim01.PushBack({ 181,  1, 89, 78 });
	bckgndLightsAnim01.PushBack({ 271,  1, 89, 78 });
	bckgndLightsAnim01.PushBack({ 361,  1, 89, 78 });
	bckgndLightsAnim01.PushBack({ 1, 80, 89, 78 });
	bckgndLightsAnim01.PushBack({ 91, 80, 89, 78 });
	bckgndLightsAnim01.PushBack({ 181, 80, 89, 78 });
	bckgndLightsAnim01.speed = 0.08f;
	//2
	bckgndLightsAnim02.PushBack({ 271, 80, 12, 16 });
	bckgndLightsAnim02.PushBack({ 284, 80, 12, 16 });
	bckgndLightsAnim02.PushBack({ 297, 80, 12, 16 });
	bckgndLightsAnim02.PushBack({ 310, 80, 12, 16 });
	bckgndLightsAnim02.PushBack({ 323, 80, 12, 16 });
	bckgndLightsAnim02.PushBack({ 336, 80, 12, 16 });
	bckgndLightsAnim02.PushBack({ 349, 80, 12, 16 });
	bckgndLightsAnim02.PushBack({ 362, 80, 12, 16 });
	bckgndLightsAnim02.speed = 0.08f;
	//3
	bckgndLightsAnim03.PushBack({ 1, 161, 64, 75 });
	bckgndLightsAnim03.PushBack({ 66, 161, 64, 75 });
	bckgndLightsAnim03.PushBack({ 131, 161, 64, 75 });
	bckgndLightsAnim03.PushBack({ 196, 161, 64, 75 });
	bckgndLightsAnim03.PushBack({ 261, 161, 64, 75 });
	bckgndLightsAnim03.PushBack({ 326, 161, 64, 75 });
	bckgndLightsAnim03.PushBack({ 391, 161, 64, 75 });
	bckgndLightsAnim03.PushBack({ 1, 239, 64, 75 });
	bckgndLightsAnim03.speed = 0.08f;
	//4
	bckgndLightsAnim04.PushBack({ 1, 315, 167, 89 });
	bckgndLightsAnim04.PushBack({ 169, 315, 167, 89 });
	bckgndLightsAnim04.PushBack({ 337, 315, 167, 89 });
	bckgndLightsAnim04.PushBack({ 1, 405, 167, 89 });
	bckgndLightsAnim04.PushBack({ 169, 405, 167, 89 });
	bckgndLightsAnim04.PushBack({ 337, 405, 167, 89 });
	bckgndLightsAnim04.PushBack({ 1, 495, 167, 89 });
	bckgndLightsAnim04.PushBack({ 169, 495, 167, 89 });
	bckgndLightsAnim04.speed = 0.08f;
	//5
	bckgndLightsAnim05.PushBack({ 1, 585, 31, 58 });
	bckgndLightsAnim05.PushBack({ 33, 585, 31, 58 });
	bckgndLightsAnim05.PushBack({ 65, 585, 31, 58 });
	bckgndLightsAnim05.PushBack({ 97, 585, 31, 58 });
	bckgndLightsAnim05.PushBack({ 129, 585, 31, 58 });
	bckgndLightsAnim05.PushBack({ 161, 585, 31, 58 });
	bckgndLightsAnim05.PushBack({ 193, 585, 31, 58 });
	bckgndLightsAnim05.PushBack({ 225, 585, 31, 58 });
	bckgndLightsAnim05.speed = 0.08f;
	//6
	bckgndLightsAnim06.PushBack({ 1, 644, 47, 51 });
	bckgndLightsAnim06.PushBack({ 49, 644, 47, 51 });
	bckgndLightsAnim06.PushBack({ 97, 644, 47, 51 });
	bckgndLightsAnim06.PushBack({ 145, 644, 47, 51 });
	bckgndLightsAnim06.PushBack({ 193, 644, 47, 51 });
	bckgndLightsAnim06.PushBack({ 241, 644, 47, 51 });
	bckgndLightsAnim06.PushBack({ 289, 644, 47, 51 });
	bckgndLightsAnim06.PushBack({ 337, 644, 47, 51 });
	bckgndLightsAnim06.speed = 0.08f;
}

void ModuleBackground::TakeMidLights()
{
	//1
	midgndLightsAnim01.PushBack({ 1, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 98, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 195, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 292, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 389, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 486, 1, 95, 86 });
	midgndLightsAnim01.PushBack({ 583, 1, 95, 86 });
	midgndLightsAnim01.speed = 0.05f;
	//2
	midgndLightsAnim02.PushBack({ 1, 88, 37, 61 });
	midgndLightsAnim02.PushBack({ 39, 88, 37, 61 });
	midgndLightsAnim02.PushBack({ 77, 88, 37, 61 });
	midgndLightsAnim02.PushBack({ 115, 88, 37, 61 });
	midgndLightsAnim02.PushBack({ 153, 88, 37, 61 });
	midgndLightsAnim02.PushBack({ 191, 88, 37, 61 });
	midgndLightsAnim02.PushBack({ 229, 88, 37, 61 });
	midgndLightsAnim02.speed = 0.04f;
	//3
	midgndLightsAnim03.PushBack({ 1, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 110, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 219, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 328, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 437, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 546, 150, 108, 47 });
	midgndLightsAnim03.PushBack({ 655, 150, 108, 47 });
	midgndLightsAnim03.speed = 0.03f;
	//4
	midgndLightsAnim04.PushBack({ 1, 198, 15, 12 });
	midgndLightsAnim04.PushBack({ 17, 198, 15, 12 });
	midgndLightsAnim04.PushBack({ 33, 198, 15, 12 });
	midgndLightsAnim04.PushBack({ 49, 198, 15, 12 });
	midgndLightsAnim04.PushBack({ 65, 198, 15, 12 });
	midgndLightsAnim04.PushBack({ 81, 198, 15, 12 });
	midgndLightsAnim04.PushBack({ 97, 198, 15, 12 });
	midgndLightsAnim04.speed = 0.03f;
	//5
	midgndLightsAnim05.PushBack({ 1, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 50, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 99, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 148, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 197, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 246, 211, 48, 93 });
	midgndLightsAnim05.PushBack({ 295, 211, 48, 93 });
	midgndLightsAnim05.speed = 0.03f;
	//6
	midgndLightsAnim06.PushBack({ 1, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 63, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 125, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 187, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 249, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 311, 305, 61, 77 });
	midgndLightsAnim06.PushBack({ 373, 305, 61, 77 });
	midgndLightsAnim06.speed = 0.03f;
}

void ModuleBackground::TakeStreetLights()
{
	//1
	streetLightsAnim01.PushBack({ 0,0, 48, 65 });
	streetLightsAnim01.PushBack({ 49, 0, 48, 65 });
	streetLightsAnim01.PushBack({ 98, 0, 48, 65 });
	streetLightsAnim01.PushBack({ 147, 0, 48, 65 });
	streetLightsAnim01.PushBack({ 98, 0, 48, 65 });
	streetLightsAnim01.PushBack({ 49, 0, 48, 65 });
	streetLightsAnim01.speed = 0.10f;
	//2
	streetLightsAnim02.PushBack({ 0,66, 61, 20 });
	streetLightsAnim02.PushBack({ 62,66, 61, 20 });
	streetLightsAnim02.PushBack({ 124,66, 61, 20 });
	streetLightsAnim02.PushBack({ 186,66, 61, 20 });
	streetLightsAnim02.PushBack({ 0,87, 61, 20 });
	streetLightsAnim02.PushBack({ 186,66, 61, 20 });
	streetLightsAnim02.PushBack({ 124,66, 61, 20 });
	streetLightsAnim02.PushBack({ 62,66, 61, 20 });
	streetLightsAnim02.speed = 0.10f;
}

void ModuleBackground::TakeOrangeLaser()
{
	orangeLaserAnim.PushBack({ 121 ,145, 142, 145 });
	orangeLaserAnim.PushBack({ 121 ,145, 142, 145 });
	orangeLaserAnim.PushBack({ 121 ,145, 142, 145 });
	orangeLaserAnim.PushBack({ 0 ,145, 121, 145 });
	orangeLaserAnim.PushBack({ 0 ,145, 121, 145 });
	orangeLaserAnim.PushBack({ 0 ,145, 121, 145 });
	orangeLaserAnim.PushBack({ 393 ,0, 99, 145 });
	orangeLaserAnim.PushBack({ 312 ,0, 81, 145 });
	orangeLaserAnim.PushBack({ 247 ,0, 65, 145 });
	orangeLaserAnim.PushBack({ 195 ,0, 52, 145 });
	orangeLaserAnim.PushBack({ 157 ,0, 38, 145 });
	orangeLaserAnim.PushBack({ 132 ,0, 25, 145 });
	orangeLaserAnim.PushBack({ 132 ,0, 25, 145 });
	orangeLaserAnim.PushBack({ 157 ,0, 38, 145 });
	orangeLaserAnim.PushBack({ 195 ,0, 52, 145 });
	orangeLaserAnim.PushBack({ 247 ,0, 65, 145 });
	orangeLaserAnim.PushBack({ 312 ,0, 81, 145 });
	orangeLaserAnim.PushBack({ 393 ,0, 99, 145 });
	orangeLaserAnim.PushBack({ 0 ,145, 121, 145 });
	orangeLaserAnim.PushBack({ 0 ,145, 121, 145 });
	orangeLaserAnim.PushBack({ 0 ,145, 121, 145 });
	orangeLaserAnim.PushBack({ 121 ,145, 142, 145 });
	orangeLaserAnim.PushBack({ 121 ,145, 142, 145 });
	orangeLaserAnim.PushBack({ 121 ,145, 142, 145 });
	orangeLaserAnim.speed = 0.4f;
}

void ModuleBackground::TakeBlueLaser()
{
	blueLaserAnim.PushBack({ 0,290, 38, 88 });
	blueLaserAnim.PushBack({ 38,290, 30, 88 });
	blueLaserAnim.PushBack({ 68,290, 5, 88 });
	blueLaserAnim.PushBack({ 73,290, 5, 88 });
	blueLaserAnim.PushBack({ 78,290, 27, 88 });
	blueLaserAnim.PushBack({ 105,290, 36, 88 });
	blueLaserAnim.speed = 0.25f;
}

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStage01.h"
#include "SDL_image\include\SDL_image.h"
#include <stdlib.h>
#include <time.h>
#include "Player1.h"
#include "Player2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleReady.h"
#include "ModuleAudio.h"
#include "ModuleGameOver.h"//delete (provisional)
#include "ModuleContinue.h" 
#include "ModuleParticles.h"
#include "ModuleStageClear.h"
#include "ModuleCollision.h"
#include "ModuleUnit.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"
#include "ModulePowerups.h"
#include "ModuleStage02.h"

#define midgndLoopDist 512 //midgndLoopDist = Distance when the first building on the tilemap repeats
#define midgndOffset 32
#define midgndSpeed 0.25f
#define backgroundspeed 0.25f
#define bckgndSpeed 0.12f
#define foregndSpeed 0.5f
#define tunnelLightDist 256
#define orangeLaserSpeed 0.12f

#define streetLightDist 64
#define roadLightDist 128

ModuleStage01::ModuleStage01()
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

ModuleStage01::~ModuleStage01()
{}

// Load assets
bool ModuleStage01::Start()
{
	LOG("Loading stage01 assets");
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
	App->player1->Enable();
	App->player2->Enable();
	App->unit1->Enable();
	App->unit1->playerToFollow = App->player1;
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->ui->ShowUi();
	App->ui->current_stage = this;
	App->powerups->Enable();
	//Player variable reset--------------------------------------------------------
	App->player1->winlvl = false;
	App->player2->winlvl = false;
	//"Reset ship position when fadetoblackends"----------------------------------
	App->player1->Reset_Positions(); 
	App->player2->Reset_Positions();
	//Enemies---------------------------------------------------------------------

	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 540, 78);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 580, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 610, 78);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 610, 150);

	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 675, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 660, 35);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 700, 35);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 740, 35);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 780, 35);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 820, 35, LASER);

	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 850, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 890, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 930, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 970, 150, SPEED);

	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 990, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1030, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1035, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1085, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1087, 70);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1130, 55);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1175, 65);

	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1250, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1285, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1320, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1355, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1385, 45, LASER);

	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1257, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1295, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1335, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1375, 150, LASER);

	App->enemies->AddEnemy(ENEMY_TYPES::METALCROW, 1500, SCREEN_HEIGHT);

	//- Basic diagonal enemies
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1650, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1690, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1730, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1770, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1810, 105);

	//Enemies that follow a straight line
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1840, 105);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1870, 105);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1900, 105);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 1930, 105);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERDROPPER, 3500, 180,LASER);

	//Start of the tunnel
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 3540, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 3580, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 3620, 45);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERDROPPER, 7700, 45, LASER);
	App->enemies->AddEnemy(ENEMY_TYPES::METALCROW, 8500, SCREEN_HEIGHT+50);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 8100, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 8000, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 8050, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 8100, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC, 8150, 80);
	//End of the tunnel

	//define moveCamera struct values
	
	MoveCamera.ymgPos = 0;
	MoveCamera.yroadPos = 0;
	MoveCamera.temporalSubstraction = MoveCamera.yroadPos;
	MoveCamera.xbetween_mov = 140 * SCREEN_SIZE;//91 * SCREEN_SIZE;
	MoveCamera.last_positionCam = 0;
	MoveCamera.vel_road = 0.5f;
	MoveCamera.vel_buildings = 0.23f;
	MoveCamera.ymax_road = -15;
	MoveCamera.ymin_road = 10;
	MoveCamera.loop = 0;
	MoveCamera.maxloop = 5; //¿?


	//Moving camera funtions variables;
	//App->render->camera.y = -20;
	Start_time_y = SDL_GetTicks();
	stop_time = false;
	StatetCamY = CameraDown;
 	up = false;
    down = false;
	cameraDown = false;
	cameraUp = false;

	//Time variables
	Start_time = SDL_GetTicks();

	//Change to stage clear variables
	App->player1->start_timer = App->player2->start_timer = false;

	App->player1->FadeToBlackAlfa = 0;
	backgroundBlack.w = SCREEN_WIDTH * SCREEN_SIZE;
	backgroundBlack.h = SCREEN_HEIGHT * SCREEN_SIZE;

	return ret;
}

bool ModuleStage01::CleanUp()
{
	LOG("Unloading stage01 assets");
	
	//textures-----------------------------------------------------------------------
	App->textures->Unload(groundAndTunel);
	App->textures->Unload(PurpleBuildings);
	App->textures->Unload(BackgroundBuildings);
	App->textures->Unload(Boss1Background);
	App->textures->Unload(LasersTx);
	App->textures->Unload(streetLightsTx);
	App->textures->Unload(midgndLightsTx);
	App->textures->Unload(bckgndLightsTx);
	App->textures->Unload(tunnelLightsTx);
	//audios------------------------------------------------------------------------
	App->audio->ControlMUS(music_01, STOP_AUDIO);
	App->audio->UnloadMUS(music_01);
	//Modules-----------------------------------------------------------------------
	App->player1->Disable();
	App->player2->Disable();
	App->unit1->Disable();
	App->unit2->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->enemies->Disable();
	App->powerups->Disable();
	App->ui->HideUi();
	//camera------------------------------------------------------------------------
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	App->render->relative_camera.x = 0;
	App->render->relative_camera.y = 0;
	//------------------------------------------------------------------------------
	
	return true;
}


// Update: draw background
update_status ModuleStage01::Update()
{
	//Time 
	Current_time = SDL_GetTicks();
	// Move camera forward -------------------------------------------------------------------
	//App->render->camera.x -= 1;
	//Boss buildings----------------------------------------------------------------------------

	App->render->Blit(Boss1Background, 0, 0, NULL, 0.0f);

	//Background buildings-----------------------------------------------------------------------
	App->render->Blit(BackgroundBuildings, 0, 0, &BGBuildings, bckgndSpeed, true);

	//Background lights-----------------------------------------------------------------------------
	App->render->Blit(bckgndLightsTx, -9, 0, &bckgndLightsAnim01.GetCurrentFrame(), bckgndSpeed, true);
	App->render->Blit(bckgndLightsTx, 504, 1, &bckgndLightsAnim01.GetCurrentFrame(), bckgndSpeed, true);
	App->render->Blit(bckgndLightsTx, 634, 10, &bckgndLightsAnim02.GetCurrentFrame(), bckgndSpeed, true);
	App->render->Blit(bckgndLightsTx, 122, 10, &bckgndLightsAnim02.GetCurrentFrame(), bckgndSpeed, true);
	App->render->Blit(bckgndLightsTx, 88, 50, &bckgndLightsAnim03.GetCurrentFrame(), bckgndSpeed, true);
	App->render->Blit(bckgndLightsTx, 600, 50, &bckgndLightsAnim03.GetCurrentFrame(), bckgndSpeed, true);
	App->render->Blit(bckgndLightsTx, 321, 0, &bckgndLightsAnim04.GetCurrentFrame(), bckgndSpeed, true);
	App->render->Blit(bckgndLightsTx, 167, 0, &bckgndLightsAnim05.GetCurrentFrame(), bckgndSpeed, true);
	App->render->Blit(bckgndLightsTx, 679, 0, &bckgndLightsAnim05.GetCurrentFrame(), bckgndSpeed, true);
	App->render->Blit(bckgndLightsTx, 240, 32, &bckgndLightsAnim06.GetCurrentFrame(), bckgndSpeed, true);

	//Orange Laser-----------------------------------------------------------------------------

	orangeLaserAnim.LoopAnimation();
	if (frame < 2) {
		frame++;
		if (orangeLaserAnim.current_frame < orangeLaserAnim.last_frame / 2)
			App->render->FlippedBlit(LasersTx, 359 - orangeLaserAnim.GetFrame().w, -5, &orangeLaserAnim.GetFrame(), orangeLaserSpeed);
		else
			App->render->Blit(LasersTx, 358, -5, &orangeLaserAnim.GetFrame(), orangeLaserSpeed, true);
	}
	else
		frame = 0;




	//Midground lights-------------------------------------------------------------------------------------------

	App->render->Blit(PurpleBuildings, 0, MoveCamera.ymgPos + midgndOffset, &PBuildings, midgndSpeed); //Mod Y=32

	//- Loop 1
	App->render->Blit(midgndLightsTx, 40, MoveCamera.ymgPos + midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, 184, MoveCamera.ymgPos + midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, 234, MoveCamera.ymgPos + midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, 329, MoveCamera.ymgPos + midgndOffset + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, 392, MoveCamera.ymgPos + midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, 471, MoveCamera.ymgPos + midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
	//- Loop 2
	App->render->Blit(midgndLightsTx, midgndLoopDist + 40, MoveCamera.ymgPos + midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, midgndLoopDist + 184, MoveCamera.ymgPos + midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, midgndLoopDist + 234, MoveCamera.ymgPos + midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, midgndLoopDist + 329, MoveCamera.ymgPos + midgndOffset + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, midgndLoopDist + 392, MoveCamera.ymgPos + midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, midgndLoopDist + 471, MoveCamera.ymgPos + midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
	//- Loop 3
	App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 40, MoveCamera.ymgPos + midgndOffset + 28, &midgndLightsAnim01.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 184, MoveCamera.ymgPos + midgndOffset + 18, &midgndLightsAnim02.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 234, MoveCamera.ymgPos + midgndOffset + 97, &midgndLightsAnim03.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 329, MoveCamera.ymgPos + midgndOffset + 2, &midgndLightsAnim04.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 392, MoveCamera.ymgPos + midgndOffset + 50, &midgndLightsAnim05.GetCurrentFrame(), midgndSpeed);
	App->render->Blit(midgndLightsTx, midgndLoopDist * 2 + 471, MoveCamera.ymgPos + midgndOffset + 36, &midgndLightsAnim06.GetCurrentFrame(), midgndSpeed);
	//Positions calculated from the png

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


	App->render->Blit(groundAndTunel, 0, MoveCamera.yroadPos, &ground, foregndSpeed); //Mod Y


//Street Lights-----------------------------------------------------------------------------------------

	//1
	App->render->Blit(streetLightsTx, 40, MoveCamera.yroadPos + 136, &streetLightsAnim01.GetCurrentFrame(), foregndSpeed);
	for (int i = 1; i < 27; ++i) {
		App->render->Blit(streetLightsTx, 40 + streetLightDist * i, MoveCamera.yroadPos + 136, &streetLightsAnim01.AddFrame(randoms[i]), foregndSpeed);
	}
	//2
	App->render->Blit(streetLightsTx, -7, MoveCamera.yroadPos + 217, &streetLightsAnim02.GetCurrentFrame(), foregndSpeed);
	for (int i = 1; i < 14; ++i) {
		App->render->Blit(streetLightsTx, -7 + roadLightDist * i, MoveCamera.yroadPos + 217, &streetLightsAnim02.AddFrame(randoms[i]), foregndSpeed);
	}

	//Tunnel lights----------------------------------------------------------------------------------------

	App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 0, MoveCamera.yroadPos, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
	App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 1, MoveCamera.yroadPos, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
	App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 2, MoveCamera.yroadPos, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
	App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 3, MoveCamera.yroadPos, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
	App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 4, MoveCamera.yroadPos, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
	App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 5, MoveCamera.yroadPos, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
	App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 6, MoveCamera.yroadPos, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
	App->render->Blit(tunnelLightsTx, 2048 + tunnelLightDist * 7, MoveCamera.yroadPos, &tunnelLightsAnim.GetCurrentFrame(), foregndSpeed);
	//2048 = distance from the start of the tilemap to the first light

//MoveCam();

//Fade to black -----------------------------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN)  //win
	{
		if (App->player1->winlvl == false && App->player2->winlvl == false)
		{
			App->player1->winlvl = App->player2->winlvl = true;
			App->player1->numLvlwin = App->player2->numLvlwin = 1;
		}
		App->fade->FadeToBlack(App->stage01, App->stageclearScene, 3.5f);
	}
	if (App->input->keyboard[SDL_SCANCODE_F9] == KEY_DOWN)  //win
	{
		App->fade->FadeToBlack(this, App->stage02, 0.5f);
	}
	//------------------------------------------------------------------------------------------
	return UPDATE_CONTINUE;
}

//move up down camera

void ModuleStage01::MoveCam() {

	if (stop_time == false)
	{
		Current_time_y = SDL_GetTicks();
		if (Current_time_y - Start_time_y > 5000)
			switch (StatetCamY)
			{
			case CameraDown:
				StatetCamY = CameraUp;
				down = true;
				stop_time = true;
				break;
			case CameraUp:
				StatetCamY = CameraDown;
				up = true;
				stop_time = true;
				break;

			}

	}
	if (down)
	{
		if (App->render->camera.y < 26 * SCREEN_SIZE)
		{
			App->player1->position.y += 1;
			App->player2->position.y += 1;
			App->render->camera.y += SCREEN_SIZE;
			App->render->relative_camera.y += 1;
		}

		else {
			stop_time = false;
			down = false;
			Start_time_y = SDL_GetTicks();
			if (App->render->camera.x >= (1400 / foregndSpeed) * SCREEN_SIZE)
			{
				stop_time = true;
				cameraDown = true;

			}


		}
	}
	if (up)
	{
		if (App->render->camera.y > -33 * SCREEN_SIZE)
		{
			App->player1->position.y -= 1;
			App->player2->position.y -= 1;
			App->render->camera.y -= SCREEN_SIZE;
			App->render->relative_camera.y -= 1;
		}

		else {
			stop_time = false;
			up = false;
			Start_time_y = SDL_GetTicks();
			if (App->render->camera.x >= (1400 / foregndSpeed) * SCREEN_SIZE)
			{
				stop_time = true;
				cameraUp = true;
			}


		}
	}
	if (cameraUp)
	{
		if (App->render->camera.y < 0)
		{
			App->render->camera.y += SCREEN_SIZE;
		}
	}
	if (cameraDown)
	{
		if (App->render->camera.y > 0)
		{
			App->render->camera.y -= SCREEN_SIZE;
		}
	}
}

void ModuleStage01::TakeTileMap()
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
void ModuleStage01::TakeTunnelLights()
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

void ModuleStage01::TakeBckLights()
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

void ModuleStage01::TakeMidLights()
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

void ModuleStage01::TakeStreetLights()
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

void ModuleStage01::TakeOrangeLaser()
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

void ModuleStage01::TakeBlueLaser()
{
	blueLaserAnim.PushBack({ 0,290, 38, 88 });
	blueLaserAnim.PushBack({ 38,290, 30, 88 });
	blueLaserAnim.PushBack({ 68,290, 5, 88 });
	blueLaserAnim.PushBack({ 73,290, 5, 88 });
	blueLaserAnim.PushBack({ 78,290, 27, 88 });
	blueLaserAnim.PushBack({ 105,290, 36, 88 });
	blueLaserAnim.speed = 0.25f;
	blueLaserAnim.pingpong = true;
}

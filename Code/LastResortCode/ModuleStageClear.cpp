#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL_image\include\SDL_image.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStage01.h"
#include "ModuleStage02.h"
#include "ModuleAudio.h"
#include "ModuleReady.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"

ModuleStageClear::ModuleStageClear()
{

	// BackgroundsRect  


	//Stage1Clear
	BGroundStageClear1.x = 0;
	BGroundStageClear1.y = 32;
	BGroundStageClear1.w = 213;
	BGroundStageClear1.h = 16;

	//Black
	backgroundBlack.x = 0;
	backgroundBlack.y = 0;
	backgroundBlack.w = SCREEN_WIDTH;
	backgroundBlack.h = SCREEN_HEIGHT;

}

ModuleStageClear::~ModuleStageClear()
{}

// Load assets
bool ModuleStageClear::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	backgroundStageClear1 = App->textures->Load("Assets/UI.png");

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(App->render->renderer, &backgroundBlack);

	
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

bool ModuleStageClear::CleanUp()
{
	//Remove all memory leaks

	LOG("Unloading ready scene");
	App->player1->Disable();
	App->player2->Disable();
	App->textures->Unload(backgroundStageClear1);
	return true;
}


// Update: draw background

update_status ModuleStageClear::Update()
{
	// Draw everything
	//SDL_Rect PLAYER1 = { 64, 3, 32, 12 };
	//App->render->Blit(App->player1->PlayerTexture, 70 , 120 , &PLAYER1 ,0.0f); //MAGIC NUMBERS
	if(App->player1->numLvlwin == App->player2->numLvlwin == 1)
	{

		App->render->Blit(backgroundStageClear1, 40 , 60 , &BGroundStageClear1, 0.0f); //MAGIC NUMBERS

	}

	// Make that pressing SPACE loads another stage
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->readyScene, 0.5f);
	}

	// Win/Lose button
	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_DOWN) //lose
	{
		App->fade->FadeToBlack(this, App->gameoverScene, 0.5f);
	}


	return UPDATE_CONTINUE;
}
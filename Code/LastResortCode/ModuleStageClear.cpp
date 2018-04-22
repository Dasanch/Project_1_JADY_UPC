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
#include "ModuleGameTitle.h"

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
	Players_Texture = App->textures->Load("Assets/SpaceShip_player1.png");

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(App->render->renderer, &backgroundBlack);

	lvlComplitedMusic = App->audio->LoadMUS("Assets/General/Fx/Stage clear.ogg");
	App->audio->ControlMUS(lvlComplitedMusic, PLAY_AUDIO);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	start_time = SDL_GetTicks();

	return ret;
}

bool ModuleStageClear::CleanUp()
{
	//Remove all memory leaks
	App->audio->ControlMUS(lvlComplitedMusic, STOP_AUDIO);
	App->audio->UnloadMUS(lvlComplitedMusic);

	LOG("Unloading ready scene");
	App->textures->Unload(backgroundStageClear1);
	App->textures->Unload(Players_Texture);
	return true;
}


// Update: draw background

update_status ModuleStageClear::Update()
{
	// Draw everything
	current_time = SDL_GetTicks() - start_time;
	App->render->Blit(Players_Texture, 70, 120, &Player1, 0.0f); 
	App->render->Blit(Players_Texture, 200, 120, &Player2, 0.0f);
	if(App->player1->numLvlwin == App->player2->numLvlwin == 1)
	{

		App->render->Blit(backgroundStageClear1, 40 , 60 , &BGroundStageClear1, 0.0f); //MAGIC NUMBERS
		

	}
	if (current_time > 6000)
	{
		App->fade->FadeToBlack(this, App->readyScene, 0.5f);
	}
	// Make that pressing SPACE loads another stage
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->titleScene, 0.5f);
		App->player1->winlvl = App->player2->winlvl = false;
		App->player1->numLvlwin = App->player2->numLvlwin = 0;
	}

	// Win/Lose button
	//if (App->input->keyboard[SDL_SCANCODE_G] == KEY_DOWN) //lose
	//{
	//	App->fade->FadeToBlack(this, App->gameoverScene, 0.5f);
	//	App->player1->winlvl = App->player2->winlvl = false;
	//	App->player1->numLvlwin = App->player2->numLvlwin = 0;
	//}


	return UPDATE_CONTINUE;
}
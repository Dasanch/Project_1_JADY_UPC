#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "SDL_image\include\SDL_image.h"
#include "ModuleStage1Clear.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "Module2lvlScene.h"
#include "ModuleAudio.h"
#include "ModuleStageReady.h"

ModuleStage1Clear::ModuleStage1Clear()
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

ModuleStage1Clear::~ModuleStage1Clear()
{}

// Load assets
bool ModuleStage1Clear::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	backgroundStageClear1 = App->textures->Load("Assets/UI.png");

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(App->render->renderer, &backgroundBlack);

	//App->player->Enable();
	App->player->Disable();

	return ret;
}

bool ModuleStage1Clear::CleanUp()
{
	//Remove all memory leaks

	LOG("Unloading ready scene");
	App->player->Disable(); //Disable the player module
	App->textures->Unload(backgroundStageClear1);
	return true;
}


// Update: draw background

update_status ModuleStage1Clear::Update()
{
	// Draw everything

	//App->render->Blit(backgroundReady, 0, 0, NULL, 0.0f);

	App->render->Blit(backgroundStageClear1, 40 /*SCREEN_WIDTH/2*/, 60 /*SCREEN_HEIGHT/2*/, &BGroundStageClear1, 0.0f); //MAGIC NUMBERS


																											  // make so pressing SPACE other stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(this, App->scene_ready, 0.5f);
	}



	return UPDATE_CONTINUE;
}
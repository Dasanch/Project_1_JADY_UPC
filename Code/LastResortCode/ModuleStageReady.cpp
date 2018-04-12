#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "SDL_image\include\SDL_image.h"
#include <stdlib.h>
#include <time.h>
#include "ModuleStageReady.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "Module2lvlScene.h"
#include "ModuleAudio.h"

ModuleStageReady::ModuleStageReady()
{

	// BackgroundsRect  


	//Ready
	BGroundReady.x = 0;
	BGroundReady.y = 112;
	BGroundReady.w = 80;
	BGroundReady.h = 16;

	//Black
	backgroundBlack.x = 0;
	backgroundBlack.y = 0;
	backgroundBlack.w = SCREEN_WIDTH;
	backgroundBlack.h = SCREEN_HEIGHT;

}

ModuleStageReady::~ModuleStageReady()
{}

// Load assets
bool ModuleStageReady::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	backgroundReady = App->textures->Load("Assets/UI.png");

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(App->render->renderer, &backgroundBlack);

	//App->player->Enable();
	App->player->Disable();

	return ret;
}

bool ModuleStageReady::CleanUp()
{
	//Remove all memory leaks

	LOG("Unloading ready scene");
	App->player->Disable(); //Disable the player module
	App->textures->Unload(backgroundReady);
	return true;
}


// Update: draw background

update_status ModuleStageReady::Update()
{
	// Draw everything

	//App->render->Blit(backgroundReady, 0, 0, NULL, 0.0f);

	App->render->Blit(backgroundReady, 110 /*SCREEN_WIDTH/2*/, 100 /*SCREEN_HEIGHT/2*/, &BGroundReady, 0.0f); //MAGIC NUMBERS


	// make so pressing SPACE other stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(this, App->scene_lvl2, 0.5f); //this=scene_ready
	}



	return UPDATE_CONTINUE;
}


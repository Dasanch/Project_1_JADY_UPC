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

ModuleStageReady::ModuleStageReady()
{
	
	// BackgroundsRect  


		//Ready
	BGroundReady.x = 0;
	BGroundReady.y = 0;
	BGroundReady.w = 0;
	BGroundReady.h = 0;

		//Black
	backgroundBlack.x = 0;
	backgroundBlack.y = 0;
	backgroundBlack.w = 0;
	backgroundBlack.h = 0;

}

ModuleStageReady::~ModuleStageReady()
{}

// Load assets
bool ModuleStageReady::Start()
{
	LOG("Loading background assets");	
	bool ret = true;					
	
	backgroundReady = App->textures->Load("Assets/UI.png");
	/*
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &backgroundBlack);

	SDL_RenderPresent(renderer);*/

	//App->player->Enable();
	App->player->Disable();

	return ret;
}

bool ModuleStageReady::CleanUp()
{
	LOG("Unloading ready scene");

	App->player->Disable(); // TODO 1: Disable the player module

	return true;
}

/*
bool ModuleStageReady::CleanUp()
{
	App->player->Disable();

	//LOG("Unloading players stage");
	App->textures->Unload(backgroundReady);

	return true;
}*/

// Update: draw background

update_status ModuleStageReady::Update()
{
	// Draw everything

	App->render->Blit(backgroundReady, 0, 0, NULL, 0.0f);
	

																			// TODO 2: make so pressing SPACE other stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		//App->fade->FadeToBlack(this, App-> , 0.5f); //this=scene_ready
	}



	return UPDATE_CONTINUE;
}


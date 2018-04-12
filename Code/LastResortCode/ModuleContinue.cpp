#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
<<<<<<< HEAD
#include "ModuleBackground.h"
#include "SDL_image\include\SDL_image.h"
#include <stdlib.h>
#include <time.h>
#include "ModuleContinue.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "Module2lvlScene.h"
#include "ModuleAudio.h"
#include "ModuleGameTitle.h"

ModuleContinue::ModuleContinue()
{

	// BackgroundsRect  


}

ModuleContinue::~ModuleContinue()
{}

// Load assets
bool ModuleContinue::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	backgroundCont = App->textures->Load("Assets/continue.png");

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(App->render->renderer, &BBlack);

	App->player->Disable();

	return ret;
}

bool ModuleContinue::CleanUp()
{
	// TODO 5: Remove all memory leaks

	LOG("Unloading ready scene");
	App->player->Disable(); // TODO 1: Disable the player module
	App->textures->Unload(backgroundCont);
	return true;
}


// Update: draw background

update_status ModuleContinue::Update()
{
	// Draw everything


	App->render->Blit(backgroundCont, 110 /*SCREEN_WIDTH/2*/, 100 /*SCREEN_HEIGHT/2*/, &BGroundCont, 0.0f); //MAGIC NUMBERS



																											  // TODO 2: make so pressing SPACE other stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(this, App->GameTitle, 0.5f); //this=scene_ready
	}


=======
#include "ModuleAudio.h"
#include "ModulePlayer.h" //Remove
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h"
#include "ModuleGameOver.h"
#include "ModuleContinue.h"

ModuleContinue::ModuleContinue() {

}
ModuleContinue:: ~ModuleContinue() {}

bool ModuleContinue::Start() {
	LOG("Loading ModuleContinue assets");
	bool ret = true;
	//textures-----------------------------------------------------------------------

	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------
	App->player->Disable();
	//------------------------------------------------------------------------------
	return ret;
}

bool ModuleGameOver::CleanUp() {
	LOG("Unloading ModuleContinue assets");
	//textures----------------------------------------------------------------------

	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------

	//------------------------------------------------------------------------------
	return true;
}

update_status ModuleGameOver::Update() {
>>>>>>> e76574445e14842f0932ccecef5ce952dd97c6d2

	return UPDATE_CONTINUE;
}
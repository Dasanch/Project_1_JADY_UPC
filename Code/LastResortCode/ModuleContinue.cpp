#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h" //Remove
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h"
#include "ModuleGameOver.h"
#include "ModuleContinue.h"

ModuleContinue::ModuleContinue() {
	//Number animation-------------------------------------------------------------
	for (int i = 0; i < 10; ++i) {
		if (i < 8)
			numbersAnim.PushBack({ 32 * i, 0, 32, 32 });
		else
			numbersAnim.PushBack({ 32 * (i - 8), 32, 32, 32 });
	}

	//Fire animation----------------------------------------------------------------
	for (int i = 0; i < 14; ++i) {
		if (i < 8)
			fireAnim.PushBack({ 32 * i, 96, 32, 32 });
		else
			fireAnim.PushBack({ 32 * (i - 8), 128, 32, 32 });
	}
	fireAnim.speed = 0.1f;
}

ModuleContinue:: ~ModuleContinue() {}

bool ModuleContinue::Start() {
	LOG("Loading ModuleContinue assets");
	bool ret = true;
	//timer--------------------------------------------------------------------------
	start_time = SDL_GetTicks();
	//textures-----------------------------------------------------------------------
	backgroundTex = App->textures->Load("Assets/Continue/backgrounds.png");
	continueTex = App->textures->Load("Assets/Continue/continue.png");
	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------
	App->player->Disable();
	//------------------------------------------------------------------------------
	return ret;
}

bool ModuleContinue::CleanUp() {
	LOG("Unloading ModuleContinue assets");
	//textures----------------------------------------------------------------------
	App->textures->Unload(backgroundTex);
	App->textures->Unload(continueTex);
	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------

	//------------------------------------------------------------------------------
	return true;
}

update_status ModuleContinue::Update() {
	//Timer-------------------------------------------------------------------------
	current_time = SDL_GetTicks() - start_time;
	//Fire--------------------------------------------------------------------------
	fireAnim.GetCurrentFrame();
	for (int i = 0; i < 7; --i) {
		App->render->Blit(continueTex, 21 + 32*i, 96, &fireAnim.AddFrame(-i), 1.0f);
	}
	App->render->Blit(continueTex, 253, 96, &fireAnim.AddFrame(-7), 1.0f);
	//-----------------------------------------------------------------------------
	return UPDATE_CONTINUE;
}
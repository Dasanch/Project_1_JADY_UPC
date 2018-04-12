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

	return UPDATE_CONTINUE;
}
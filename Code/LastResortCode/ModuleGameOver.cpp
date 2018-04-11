#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h"
#include "ModuleGameOver.h"

ModuleGameOver::ModuleGameOver() {

}
ModuleGameOver:: ~ModuleGameOver() {}

bool ModuleGameOver::Start() {
	LOG("Loading ModuleGameOver assets");
	bool ret = true;
	//textures-----------------------------------------------------------------------
	
	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------
	App->player->Disable();
	//------------------------------------------------------------------------------
	return ret;
}

bool ModuleGameOver::CleanUp() {
	// TODO : Remove all memory leaks
	LOG("Unloading background assets");
	//textures----------------------------------------------------------------------

	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------

	//------------------------------------------------------------------------------
	return true;
}

update_status ModuleGameOver::Update() {

	return UPDATE_CONTINUE;
}
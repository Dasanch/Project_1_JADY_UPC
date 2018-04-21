
#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"

ModuleUI::ModuleUI() {
}
ModuleUI:: ~ModuleUI() {}

bool ModuleUI::Start() {
	LOG("Loading Module UI assets");
	bool ret = true;
	//Fonts-------------------------------------------------------------------------
	App->fonts->Load("Assets/Fonts/blue_chars.png", "0123456789^[]ABCDEFGHIJKLMNOPQRSTUVWXYZ_-.,&#", 1); //font id = 0
	//textures----------------------------------------------------------------------

	//audios------------------------------------------------------------------------


	//------------------------------------------------------------------------------
	return ret;
}

bool ModuleUI::CleanUp() {
	LOG("Unloading Module UI assets");
	//Fonts-------------------------------------------------------------------------
	App->fonts->UnLoad(0);
	//textures----------------------------------------------------------------------

	//audios------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	return true;
}

update_status ModuleUI::Update() {
	
	return UPDATE_CONTINUE;
}

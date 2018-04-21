
#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

ModuleUI::ModuleUI() {

}
ModuleUI:: ~ModuleUI() {}

bool ModuleUI::Start() {
	LOG("Loading Module UI assets");
	bool ret = true;
	//textures-----------------------------------------------------------------------

	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------
	
	//------------------------------------------------------------------------------
	return ret;
}

bool ModuleUI::CleanUp() {
	LOG("Unloading Module UI assets");
	//textures----------------------------------------------------------------------

	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------

	//------------------------------------------------------------------------------
	return true;
}

update_status ModuleUI::Update() {

	return UPDATE_CONTINUE;
}

#include "Globals.h"
#include "Application.h"
#include "ModuleGameTitle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

ModuleGameTitle::ModuleGameTitle()
{

}
ModuleGameTitle::~ModuleGameTitle()
{}
bool Start()
{
	LOG("Loading background assets");
	bool ret = true;
	App->player->Enable();
	

	return ret;
}
update_status ModuleGameTitle::Update() {
	return UPDATE_CONTINUE;
}
bool ModuleGameTitle::CleanUp() {
	LOG("Unloading Title scene");
	App->player->Disable();
	return true;
}
#include "Globals.h"
#include "Application.h"
#include "ModuleGameTitle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h"
#include "ModuleAudio.h"


ModuleGameTitle::ModuleGameTitle()
{

}
ModuleGameTitle::~ModuleGameTitle()
{}
bool ModuleGameTitle:: Start()
{
	LOG("Loading background assets");
	bool ret = true;
	
	App->player->Enable();
	App->audio->Disable();
	
	return ret;
}
update_status ModuleGameTitle::Update() {
	if (App->input->keyboard[SDL_SCANCODE_ESCAPE]==1)
	{
		App->fade->FadeToBlack(App->GameTitle,App->background,1);
	}

	return UPDATE_CONTINUE;
}
bool ModuleGameTitle::CleanUp() {
	LOG("Unloading Title scene");
	App->player->Disable();
	return true;
}
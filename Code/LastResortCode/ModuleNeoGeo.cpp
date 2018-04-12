#include "Globals.h"
#include "Application.h"
#include "ModuleNeoGeo.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h"
#include "ModuleAudio.h"
#include "ModuleGameTitle.h"


ModuleNeoGeo::ModuleNeoGeo()
{

}

ModuleNeoGeo::~ModuleNeoGeo()
{

}

bool ModuleNeoGeo::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	neogeoTx = App->textures->Load("Assets/NeoGeo/NeoGeoPlaceHolder.png");//Provisional, it will change to the NeoGeo texture later
	snkTx = App->textures->Load("Assets/NeoGeo/SNK.png");
	proGearSpecTx = App->textures->Load("Assets/NeoGeo/ProGearSpec.png");

	return ret;
}
update_status ModuleNeoGeo::Update()
{

	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App-> GameTitle, 0.5f);
	}

	App->render->Blit(neogeoTx, 0, 0, NULL, 0.0f);

	return UPDATE_CONTINUE;
}
bool ModuleNeoGeo::CleanUp() {
	LOG("Unloading NeoGeo scene");
	// Disable player, neogeoTx, snkTx, proGearSpecTx
	App->player->Disable(); 
	App->textures->Unload(neogeoTx);
	App->textures->Unload(snkTx);
	App->textures->Unload(proGearSpecTx);


	return true;
}
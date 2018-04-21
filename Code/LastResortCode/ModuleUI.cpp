
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
	lives_score_p1 = { 0,0,24,16};
	live_score_p2 = { 160,16,24,16};
	pow = { 0,16,96,8};
	push_p2= { 159,0,96,16 };
	top = { 96,0,63,16};

}
ModuleUI:: ~ModuleUI() {}

bool ModuleUI::Start() {
	LOG("Loading Module UI assets");
	bool ret = true;
	//Fonts-------------------------------------------------------------------------
	App->fonts->Load("Assets/Fonts/blue_chars.png", "0123456789^[]ABCDEFGHIJKLMNOPQRSTUVWXYZ_-.,&#", 1); //font id = 0
	//textures----------------------------------------------------------------------
	uiTex = App->textures->Load("Assets/UI.png");
	//audios------------------------------------------------------------------------


	//------------------------------------------------------------------------------
	return ret;
}

bool ModuleUI::CleanUp() {
	LOG("Unloading Module UI assets");
	//Fonts-------------------------------------------------------------------------
	App->fonts->UnLoad(0);
	//textures----------------------------------------------------------------------
	App->textures->Unload(uiTex);
	//audios------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	return true;
}

update_status ModuleUI::Update() {

	App->render->Blit(uiTex, 16, 16, &lives_score_p1, 0.0f);
	App->render->Blit(uiTex, 256, 16, &live_score_p2, 0.0f);
	/*App->render->Blit(uiTex, 192, 16, &push_p2, 0.0f);*/
	App->render->Blit(uiTex, 112, 16, &top, 0.0f);
	App->render->Blit(uiTex, 24, 208, &pow, 0.0f);
	App->render->Blit(uiTex, 184, 208, &pow, 0.0f);
	
	
	

	return UPDATE_CONTINUE;
}

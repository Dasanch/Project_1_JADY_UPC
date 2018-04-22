
#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include <stdio.h>


ModuleUI::ModuleUI() {
	lives_score_p1 = { 0,0,32,16};
	live_score_p2 = { 160,16,40,16};
	pow = { 0,16,96,8};
	push_p2= { 159,0,96,16 };
	top = { 96,0,63,16};

}
ModuleUI:: ~ModuleUI() {}

bool ModuleUI::Start() {
	LOG("Loading Module UI assets");
	bool ret = true;
	//Fonts-------------------------------------------------------------------------
	App->fonts->Load("Assets/Fonts/blue_chars.png", "0123456789[]ABCDEFGHIJKLMNOPQRSTUVWXYZ_-.,&#", 1); //font id = 0
	//textures----------------------------------------------------------------------
	uiTex = App->textures->Load("Assets/UI.png");

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

update_status  ModuleUI::PreUpdate() { 
	

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleUI::Update() {
	str_score_p1 = new char[MAX_NUMBERS_SCORE];
	str_score_p2 = new char[MAX_NUMBERS_SCORE];
	str_lives_p1 = new char[1];
	str_lives_p2 = new char[1];

	lives_p1 = App->player1->lives;
	snprintf(str_lives_p1, 4 * sizeof(str_lives_p1), "%d", lives_p1);

	lives_p2 = App->player2->lives;
	snprintf(str_lives_p2, 4 * sizeof(str_lives_p2), "%d", lives_p2);

	score_p1 = App->player1->score;
	snprintf(str_score_p1, 4 * sizeof(str_score_p1), "%d", score_p1);

	score_p2 = App->player1->score;
	snprintf(str_score_p2, 4 * sizeof(str_score_p2), "%d", score_p2);

	//Static UI-----------------------------------------------------
	App->render->Blit(uiTex, 16, 16, &lives_score_p1, 0.0f);
	App->render->Blit(uiTex, 256, 16, &live_score_p2, 0.0f);
	App->render->Blit(uiTex, 112, 16, &top, 0.0f);
	App->render->Blit(uiTex, 24, 208, &pow, 0.0f);
	App->render->Blit(uiTex, 184, 208, &pow, 0.0f);
	/*App->render->Blit(uiTex, 192, 16, &push_p2, 0.0f);*/ //push button p2
    //Variable UI----------------------------------------------------
	App->fonts->BlitText(48, 24, 0, str_lives_p1);
	App->fonts->BlitText(264, 24, 0, str_lives_p2);
	App->fonts->BlitText(264, 24, 0, str_score_p1);
	App->fonts->BlitText(264, 24, 0, str_score_p2);

	delete[](str_score_p1);
	delete[](str_score_p2);
	delete[](str_lives_p1);
	delete[](str_lives_p2);
	str_score_p1 = nullptr;
	str_score_p2 = nullptr;
	str_lives_p1 = nullptr;
	str_lives_p2 = nullptr;

	return UPDATE_CONTINUE;
}

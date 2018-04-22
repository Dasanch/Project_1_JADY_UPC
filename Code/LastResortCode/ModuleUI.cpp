
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
#include "ModuleFadetoBlack.h"
#include "ModuleContinue.h"
#include <stdio.h>
#include <string.h>


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
	str_lives_p1 = new char[4];
	str_lives_p2 = new char[4];

	if (p1_isDead && p2_isDead) {
		p1_isDead = false;
		p2_isDead = false;
		App->fade->FadeToBlack(current_stage, App->continueScene, 0.1f);
		lives_p1 = 2;
		lives_p2 = 2;
	}

	snprintf(str_lives_p1, 4 * sizeof(str_lives_p1), "%d", lives_p1);
	snprintf(str_lives_p2, 4 * sizeof(str_lives_p2), "%d", lives_p2);
	snprintf(str_score_p1, 4 * sizeof(str_score_p1), "%d", score_p1);
	snprintf(str_score_p2, 4 * sizeof(str_score_p2), "%d", score_p2);



	if (showUI == true) {
		//Static UI-----------------------------------------------------
		App->render->Blit(uiTex, 16, 16, &lives_score_p1, 0.0f);
		App->render->Blit(uiTex, 256, 16, &live_score_p2, 0.0f);
		App->render->Blit(uiTex, 112, 16, &top, 0.0f);
		App->render->Blit(uiTex, 24, 208, &pow, 0.0f);
		App->render->Blit(uiTex, 184, 208, &pow, 0.0f);	/*App->render->Blit(uiTex, 192, 16, &push_p2, 0.0f);*/ //Remember 1.0

		//Variable UI----------------------------------------------------
		App->fonts->BlitText(48, 24, 0, str_lives_p1);  //lives player 1
		App->fonts->BlitText(264, 24, 0, str_lives_p2); //lives player 2
		//-------------score player 1------------------------------------
		if (score_p1 == 0) {
			App->fonts->BlitText( 72, 16, 0, "00"); 
		}
		else {
			App->fonts->BlitText(88- 8*strlen(str_score_p1) , 16, 0, str_score_p1);
		}
		//-------------score player 2------------------------------------
		if (score_p2 == 0) {
			App->fonts->BlitText(256, 16, 0, "00");
		}
		else {
			App->fonts->BlitText(272 - 8 * strlen(str_score_p2), 16, 0, str_score_p2);
		}
	}
	App->fonts->BlitText(208, 216, 0, "CREDITS_00");//credits

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

void ModuleUI::ShowUi() {
	if (showUI == false) {
		showUI = true;
	}
	
}
void ModuleUI::HideUi() {
	if (showUI == true) {
		showUI = false;
	}
}
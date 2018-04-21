#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameOver.h"
#include "ModuleContinue.h"
#include "ModuleGameTitle.h"
#include "ModuleStageClear.h"


#define MAX_ALPHA 255
#define MIN_ALPHA 0

ModuleGameOver::ModuleGameOver() {
	//White Rect-----------------------------------------
	white_rect.x = 0;
	white_rect.y = 0;
	white_rect.w = SCREEN_WIDTH* SCREEN_SIZE;
	white_rect.h = SCREEN_HEIGHT* SCREEN_SIZE;
	//Black Rect-----------------------------------------
	black_rect.x = 0;
	black_rect.y = 0;
	black_rect.w = SCREEN_WIDTH* SCREEN_SIZE;
	black_rect.h = SCREEN_HEIGHT* SCREEN_SIZE;
	//Normal GameOver------------------------------------
	go_rect.x = 0;
	go_rect.y = 0;
	go_rect.w = 260;
	go_rect.h = 160;
	//White GameOver-------------------------------------
	white_go_rect.x = 0;
	white_go_rect.y = 0;
	white_go_rect.w = 260;
	white_go_rect.h = 160;
	//Metal GameOver--------------------------------------
	metal_go_rect.x = 0;
	metal_go_rect.y = 320;
	metal_go_rect.w = 234;
	metal_go_rect.h = 132;
	//Black Metal GameOver--------------------------------
	black_metal_go_rect.x = 260;
	black_metal_go_rect.y = 160;
	black_metal_go_rect.w = 234;
	black_metal_go_rect.h = 132;
}
ModuleGameOver:: ~ModuleGameOver() {}

bool ModuleGameOver::Start() {
	LOG("Loading ModuleGameOver assets");
	bool ret = true;
	start_time = SDL_GetTicks(); 
	whiteAlpha = MIN_ALPHA;
	blackAlpha = MAX_ALPHA;
	black_go_Alpha = MIN_ALPHA;
	//textures-----------------------------------------------------------------------
	goTex = App->textures->Load("Assets/GameOver.png");
	//------------------------------------------------------------------------------
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

bool ModuleGameOver::CleanUp() {

	LOG("Unloading ModuleGameOver assets");
	//textures----------------------------------------------------------------------
	App->textures->Unload(goTex);
	//audios------------------------------------------------------------------------
	if(App->continueScene->continue_and_go != nullptr)
	App->audio->ControlMUS(App->continueScene->continue_and_go, STOP_AUDIO);
	App->audio->UnloadMUS(App->continueScene->continue_and_go);
	//------------------------------------------------------------------------------
	return true;
}

update_status ModuleGameOver::Update() {
	//Timer---------------------------------------------------------------------
	current_time = SDL_GetTicks() - start_time;
	//Normal GameOver , Metal GameOve & Black Metal GameOverr---------------------
	if (current_time < 2800)
		App->render->Blit(goTex, 19, 32, &go_rect, 1.0);
	else if (current_time >= 3200) {
		black_go_Alpha = MIN_ALPHA + (current_time - 3200) / (2000 / 255);
		if (black_go_Alpha > MAX_ALPHA) {
			black_go_Alpha = MAX_ALPHA;
		}
		SDL_SetTextureAlphaMod(goTex, black_go_Alpha);
		SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_ADD);
		App->render->Blit(goTex, 35, 46, &metal_go_rect, 1.0);
		SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(goTex, 255);
	}
	//Black -------------------------------------------------------------------
	if (current_time >= 0 && current_time < 1400) {

		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (int)blackAlpha);
		SDL_RenderFillRect(App->render->renderer, &black_rect);
		blackAlpha = MAX_ALPHA - (current_time) / (1400 / 255);
		if (blackAlpha < MIN_ALPHA) {
			blackAlpha = MIN_ALPHA;
		}
	}
	//White Rect----------------------------------------------------------------
	if (current_time >= 1400 && current_time < 2800) {
		SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_ADD);
		SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (int)whiteAlpha);
		SDL_RenderFillRect(App->render->renderer, &white_rect);
		SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

		whiteAlpha = (current_time - 1400) / (1400 / 255);
		if (whiteAlpha > MAX_ALPHA) {
			whiteAlpha = MAX_ALPHA;
		}
	}
	if (current_time >= 2800 && current_time < 4200) {

		SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (int)whiteAlpha);
		SDL_RenderFillRect(App->render->renderer, &white_rect);

		whiteAlpha = MAX_ALPHA - (current_time - 2800) / (1400 / 255);
		if (whiteAlpha < MIN_ALPHA) {
			whiteAlpha = MIN_ALPHA;
		}
	}
	//Limit time--------------------------------------------------------------
	if (current_time > 7700) {
		App->fade->FadeToBlack(this, App->titleScene, 0.5f);
	}
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 0.1f);// Defect RenderDraColor

	// Win/Lose button
	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN) //win
	{
		App->fade->FadeToBlack(this, App->stageclearScene, 0.5f);
	}

	return UPDATE_CONTINUE;
}
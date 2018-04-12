#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h" //REMEMBER DELETE
#include "ModuleGameOver.h"


#define MAX_ALPHA 255
#define MIN_ALPHA 0

ModuleGameOver::ModuleGameOver() {
	//White Rect
	white_rect.x = 0;
	white_rect.y = 0;
	white_rect.w = SCREEN_WIDTH* SCREEN_SIZE;
	white_rect.h = SCREEN_HEIGHT* SCREEN_SIZE;
	//Black Rect
	black_rect.x = 0;
	black_rect.y = 0;
	black_rect.w = SCREEN_WIDTH* SCREEN_SIZE;
	black_rect.h = SCREEN_HEIGHT* SCREEN_SIZE;
	//Normal GameOver
	go_rect.x = 0;
	go_rect.y = 0;
	go_rect.w = 260;
	go_rect.h = 160;
	//White GameOver 
	white_go_rect.x = 0;
	white_go_rect.y = 0;
	white_go_rect.w = 260;
	white_go_rect.h = 160;
	//Metal GameOver
	metal_go_rect.x = 0;
	metal_go_rect.y = 320;
	metal_go_rect.w = 234;
	metal_go_rect.h = 132;
	//White Metal GameOver

	whiteAlpha = MIN_ALPHA;
	white_goAlpha = MIN_ALPHA;
}
ModuleGameOver:: ~ModuleGameOver() {}

bool ModuleGameOver::Start() {
	LOG("Loading ModuleGameOver assets");
	bool ret = true;
	init_time = SDL_GetTicks(); 
	//textures-----------------------------------------------------------------------
	goTex = App->textures->Load("Assets/GameOver.png");
	white_goTex = App->textures->Load("Assets/WhiteGameOver.png");
	SDL_SetTextureBlendMode(white_goTex, SDL_BLENDMODE_ADD);
	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------
	App->player->Disable();
	//------------------------------------------------------------------------------
	return ret;
}

bool ModuleGameOver::CleanUp() {

	LOG("Unloading ModuleGameOver assets");
	//textures----------------------------------------------------------------------
	App->textures->Unload(goTex);
	App->textures->Unload(white_goTex);
	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------

	//------------------------------------------------------------------------------
	return true;
}

update_status ModuleGameOver::Update() {
	//Timer---------------------------------------------------------------------
	current_time = SDL_GetTicks() - init_time;
	//Black Rect (background)---------------------------------------------------
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(App->render->renderer, &black_rect);
	//Normal GameOver-----------------------------------------------------------
	App->render->Blit(goTex, 19, 32, &go_rect, 1.0);
	//Metal GameOver-------------------------------------------------------------
	/*App->render->Blit(goTex, 35, 46, , 1.0);*/

	//White GameOver------------------------------------------------------------
	SDL_SetTextureAlphaMod(white_goTex, (int) white_goAlpha);
	App->render->Blit(white_goTex, 19, 32, &white_go_rect, 1.0);
	if (white_goAlpha < MAX_ALPHA) {
		white_goAlpha= white_goAlpha+ 0.9f;
	}
	//White Rect----------------------------------------------------------------
	if (current_time >= 1400) {
		SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (int)whiteAlpha);
		SDL_RenderFillRect(App->render->renderer, &white_rect);
		whiteAlpha = whiteAlpha + 4.0f;
		if (whiteAlpha > MAX_ALPHA) {
			whiteAlpha = MAX_ALPHA;
		}
	}
	//---------------------------------------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_G]) {
		App->fade->FadeToBlack(this, App->background, 0.5f);
	}

	return UPDATE_CONTINUE;
}
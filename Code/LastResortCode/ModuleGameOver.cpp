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

#define METAL_GAMEOVER 0
#define MAX_ALPHA 255

ModuleGameOver::ModuleGameOver() {
	//White
	white.x = 0;
	white.y = 0;
	white.w = SCREEN_WIDTH* SCREEN_SIZE;
	white.h = SCREEN_HEIGHT* SCREEN_SIZE;
	//Metal
	gameOverAnim.PushBack({ 0, 320, 234, 132 });

	whiteAlpha = MAX_ALPHA;
}
ModuleGameOver:: ~ModuleGameOver() {}

bool ModuleGameOver::Start() {
	LOG("Loading ModuleGameOver assets");
	bool ret = true;
	//textures-----------------------------------------------------------------------
	gameover = App->textures->Load("Assets/GameOver.png");
	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------
	App->player->Disable();
	//------------------------------------------------------------------------------
	return ret;
}

bool ModuleGameOver::CleanUp() {

	LOG("Unloading ModuleGameOver assets");
	//textures----------------------------------------------------------------------
	App->textures->Unload(gameover);
	//audios------------------------------------------------------------------------

	//modules-----------------------------------------------------------------------

	//------------------------------------------------------------------------------
	return true;
}

update_status ModuleGameOver::Update() {

	//Metal GameOver
	App->render->Blit(gameover, 35, 46, &gameOverAnim.frames[METAL_GAMEOVER], 1.0);

	if (App->input->keyboard[SDL_SCANCODE_G]) {
		App->fade->FadeToBlack(this, App->background, 0.5f);
	}

	//White Rect 
	SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, whiteAlpha);
	SDL_RenderFillRect(App->render->renderer, &white);
	--whiteAlpha;

	return UPDATE_CONTINUE;
}
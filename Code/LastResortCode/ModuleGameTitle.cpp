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
	LastResortRect.x = 0;
	LastResortRect.y = 0;
	LastResortRect.w = 240;
	LastResortRect.h = 31;
}
ModuleGameTitle::~ModuleGameTitle()
{}
bool ModuleGameTitle:: Start()
{
	LOG("Loading background assets");
	bool ret = true;
	
	TitleTexture = App->textures->Load("Assets/UI-TitleScreen.png");
	
	return ret;
}
update_status ModuleGameTitle::Update() {

	App->render->Blit(TitleTexture, ((SCREEN_WIDTH-LastResortRect.w)/2), ((SCREEN_HEIGHT - LastResortRect.h) / 2), &LastResortRect, 0.0f);
	if (App->input->keyboard[SDL_SCANCODE_SPACE]==1)
	{
		App->fade->FadeToBlack(this,App->background,0.5f);
	}

	return UPDATE_CONTINUE;
}
bool ModuleGameTitle::CleanUp() {
	LOG("Unloading Title scene");
	App->player->Disable();
	return true;
}
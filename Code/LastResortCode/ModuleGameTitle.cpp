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

	for (int i = 0; i <= 460; i += 48)
	{
			L1.PushBack({ i,0,46,57 });

	}
	for (int i = 0; i <= 432; i += 48)
	{
		L1.PushBack({ i,59,46,57 });

	}
	L1.PushBack({ 336,118,46,57 });//32 
	L1.PushBack({ 384,118,46,57 });//32 
	L1.PushBack({ 432,118,46,57 });//32 
	L1.PushBack({ 0,177,46,57 });
	L1.PushBack({ 48,177,46,57 });
	L1.PushBack({ 96,177,46,60 });
	L1.PushBack({ 144,177,47,63 });
	L1.PushBack({ 193,177,47,66 });
	L1.PushBack({ 242,177,47,69 });
	L1.PushBack({ 291,177,47,77 });
	L1.PushBack({ 340,177,48,84 });
	L1.PushBack({ 390,177,48,88 });
	L1.PushBack({ 440,177,48,94 });//42
	L1.PushBack({ 0,273,47,106 });
	L1.PushBack({ 49,273,47,118});
	L1.PushBack({ 98,273,45,123 });
	L1.PushBack({ 145,273,45,122 });
	L1.PushBack({ 192,273,45,122 });
	L1.PushBack({ 239,273,45,121 });
	L1.PushBack({ 286,273,23,117 });
	L1.PushBack({ 311,273,23,116 });
	L1.PushBack({ 336,273,23,114 });
	L1.PushBack({ 361,273,23,112 });
	L1.PushBack({ 386,273,23,96 });
	L1.PushBack({ 411,273,23,107 });
	L1.PushBack({ 436,273,23,102 });//55
	L1.PushBack({ 461,273,21,101 });
	L1.PushBack({ 484,273,21,92 });
	L1.PushBack({ 0,398,21,81 });
	L1.PushBack({ 23,398,21,83 });
	L1.PushBack({ 46,398,21,79 });
	L1.PushBack({ 69,398,20,76 });
	L1.PushBack({ 111,398,15,58 });
	L1.PushBack({ 128,398,14,37 });
	L1.PushBack({ 144,398,13,25 });
	current_frame = 0;
	//---------------------------------------------------------------
	A2.PushBack({ 0,0,10,15 });
	A2.PushBack({ 11,0,12,24 });
	A2.PushBack({ 23,0,13,38 });
	A2.PushBack({ 36,0,13,45 });
	A2.PushBack({ 49,0,13,56 });
	A2.PushBack({ 62,0,13,63 });
	A2.PushBack({ 62,0,13,63 });
}
ModuleGameTitle::~ModuleGameTitle()
{}
bool ModuleGameTitle:: Start()
{
	LOG("Loading background assets");
	bool ret = true;
	
	TitleTexture = App->textures->Load("Assets/UI-TitleScreen.png");
	L1Texture= App->textures->Load("Assets/LastResortTitle/L1Atlas.1.png");
	return ret;
}
update_status ModuleGameTitle::Update() {

	
	App->render->Blit(L1Texture, 10, 30, &L1.frames[(int)current_frame], 0.0f);
	if (App->input->keyboard[SDL_SCANCODE_A] == 1 && current_frame>0)
	{
		current_frame -= 0.2f;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1 && current_frame<61)
	{
		current_frame += 0.2f;
	}
	/*App->render->Blit(TitleTexture, ((SCREEN_WIDTH-LastResortRect.w)/2), ((SCREEN_HEIGHT - LastResortRect.h) / 2), &LastResortRect, 0.0f);*/
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
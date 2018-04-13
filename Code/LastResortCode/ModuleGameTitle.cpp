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
	L1.PushBack({ 49,273,47,118 });
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
	L1.PushBack({ 144,398,13,25 }); //64

	//---------------------------------------------------------------
	A2.PushBack({ 0,0,10,15 });
	A2.PushBack({ 11,0,12,24 });
	A2.PushBack({ 23,0,13,38 });
	A2.PushBack({ 36,0,13,45 });
	A2.PushBack({ 49,0,13,56 });
	A2.PushBack({ 62,0,13,63 });
	A2.PushBack({ 75,0,13,72 });
	A2.PushBack({ 88,0,13,80 });
	A2.PushBack({ 101,0,14,87 });
	A2.PushBack({ 115,0,19,92 });//10
	A2.PushBack({ 134,0,20,96 });
	A2.PushBack({ 154,0,22,100 });
	A2.PushBack({ 176,0,22,101 });
	A2.PushBack({ 198,0,24,106 });
	A2.PushBack({ 222,0,25,108 });
	A2.PushBack({ 256,0,30,112 });
	A2.PushBack({ 286,0,34,115 });
	A2.PushBack({ 320,0,38,114 });
	A2.PushBack({ 358,0,41,122 });
	A2.PushBack({ 399,0,47,122 });
	A2.PushBack({ 0,122,47,119 });
	A2.PushBack({ 47,122,47,106 });
	A2.PushBack({ 94,122,51,94 });
	A2.PushBack({ 145,122,51,84 });
	A2.PushBack({ 196,122,51,77 });
	A2.PushBack({ 247,122,51,71 });
	A2.PushBack({ 298,122,51,67 });
	A2.PushBack({ 349,122,51,63 });
	A2.PushBack({ 400,122,50,61 });
	A2.PushBack({ 0,241,50,60 });
	A2.PushBack({ 50,241,50,57 });
	A2.PushBack({ 100,241,50,57 });
	for (int i = 150; i <= 400;i+=50) {

		A2.PushBack({ i,241,50,57 });
	}
	for (int j=301;j<=358;j+=57)
	{
		for (int i = 0; i <= 400; i += 50) {

			A2.PushBack({ i,j,50,57 });
		}
	}
	for (int i = 0; i < 5; i++)
	{
		A2.PushBack({ 50*i,415,50,57 });
	}
	A2.speed = 0.2;
	A2.loop=false;
}
ModuleGameTitle::~ModuleGameTitle()
{}
bool ModuleGameTitle:: Start()
{
	LOG("Loading background assets");
	bool ret = true;
	
	TitleTexture = App->textures->Load("Assets/UI-TitleScreen.png");
	L1Texture= App->textures->Load("Assets/LastResortTitle/L1Atlas.1.png");
	A2Texture = App->textures->Load("Assets/LastResortTitle/A2.png");
	current_frame = 64;
	Titlemusic=App->audio->LoadMUS("Assets/LastResortTitle/02-LAST-RESORT-TITLE.ogg");
	App->audio->ControlMUS(Titlemusic, PLAY_AUDIO);
	return ret;
}
update_status ModuleGameTitle::Update() {


	/*App->render->Blit(A2Texture, 60, 30, &A2.frames[(int)currenA2], 0.0f);*/
	//App->render->Blit(L1Texture, 10, 30, &L1.frames[(int)current_frame], 0.0f);
	//App->render->Blit(A2Texture, 60, 30, &A2.GetCurrentFrame(), 0.0f);
	/*if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		currenA2 += 0.1f;
	}*/
	if (current_frame>0)
	{
		
		current_frame -= 0.2f;

	}
	
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
	//audios------------------------------------------------------------------------
	App->audio->ControlMUS(Titlemusic, STOP_AUDIO);
	App->audio->UnloadMUS(Titlemusic);
	return true;
}
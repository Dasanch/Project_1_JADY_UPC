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
	/*for (int i=0;i<171;i+=57)
	{
		for (int j = 0; j<512; j += 46)
		{
			if (i != 460 && j!=114)
			{
				L1.PushBack({ i,j,46,57 });
			}
			
		}
	}
	L1.PushBack({ 460,114,46,60 });
	L1.PushBack({ 0,174,46,63 });
	L1.PushBack({ 94,174,47,69 });
	L1.PushBack({ 141,174,46,77 });*/


}
ModuleGameTitle::~ModuleGameTitle()
{}
bool ModuleGameTitle:: Start()
{
	LOG("Loading background assets");
	bool ret = true;
	
	TitleTexture = App->textures->Load("Assets/UI-TitleScreen.png");
	L1Texture= App->textures->Load("Assets/LastResortTitle/Tittle 1L.png");
	return ret;
}
update_status ModuleGameTitle::Update() {

	/*if (current_frame>=0)
	{
		App->render->Blit(L1Texture, 0, 0, &L1.frames[current_frame],0.0f);
		--current_frame;
	}*/
	
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
	App->textures->Unload(TitleTexture);
	App->textures->Unload(L1Texture);
	return true;
}
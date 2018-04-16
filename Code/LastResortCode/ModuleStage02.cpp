
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameTitle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModuleContinue.h"
#include "ModuleAudio.h"
#include "ModuleStage02.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"

Module2lvlScene::Module2lvlScene()
{
	BckSpamRect.x = 0;
	BckSpamRect.y = 35;
	BckSpamRect.w = 80;
	BckSpamRect.h = 68;

	BckSpamRect2.x = 0;
	BckSpamRect2.y = 0;
	BckSpamRect2.w = 80;
	BckSpamRect2.h = 35;
}

bool Module2lvlScene::Start()
{
	
	bool ret = true;
	//Enable
	App->player->Enable();
	App->player2->Enable();
	App->particles->Enable();
	App->collision->Enable();


	App->player->position.x = 0;
	App->player->position.y = 130;
	App->player2->position.x = 0;
	App->player2->position.y = 110;
	lvl2Text = App->textures->Load("Assets/lvl2/Background_2.png");
	lvl2ground = App->textures->Load("Assets/lvl2/Foreground_2.png");
	BckSpam= App->textures->Load("Assets/lvl2/Backgroundlvl2Spritesheet.png");
	//audios------------------------------------------------------------------------
	lvl2Music = App->audio->LoadMUS("Assets/lvl2/04-THE-RUINS-OF-METRO-STAGE-2-_-TYRANNICAL-BOSS-2-.ogg");
	App->audio->ControlMUS(lvl2Music, PLAY_AUDIO);
	return ret;
}
update_status Module2lvlScene::Update() {
	int speedcamera = 5;
	float backgroundspeed=0.2f;
	float groundspeed = 0.3f;
	/*if(App->render->camera.x>-(3576 *SCREEN_SIZE)/backgroundspeed)*/
	
	// Move camera forward -----------------------------

	App->player->position.x += 1;
	App->player2->position.x += 1;
	App->render->camera.x -= 3;


	App->render->Blit(lvl2Text, 0, 0, NULL, backgroundspeed);
	App->render->Blit(lvl2ground, 2000, 0, NULL, groundspeed);

	App->render->Blit(BckSpam, 390, SCREEN_HEIGHT-BckSpamRect.h, &BckSpamRect, groundspeed);
	App->render->Blit(BckSpam, 1450, SCREEN_HEIGHT - BckSpamRect.h, &BckSpamRect, groundspeed);
	App->render->Blit(BckSpam, 1800, SCREEN_HEIGHT - BckSpamRect.h, &BckSpamRect, groundspeed);
	App->render->Blit(BckSpam, 1600, 0, &BckSpamRect2, groundspeed);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		//App->fade->FadeToBlack(this, App->GameTitle, 0.5f);
		App->fade->FadeToBlack(this, App->continueScene, 0.2f);
	}

	return UPDATE_CONTINUE;
}

bool Module2lvlScene::CleanUp() {

	LOG("Unloading ready scene");
	App->render->camera.x = 0;
	App->player->Disable();
	App->player2->Disable();

	App->textures->Unload(lvl2Text);
	App->textures->Unload(lvl2ground);
	App->textures->Unload(BckSpam);
	//audios------------------------------------------------------------------------
	App->audio->ControlMUS(lvl2Music, STOP_AUDIO);
	App->audio->UnloadMUS(lvl2Music);
	//Modules-----------------------------------------------------------------------
	App->player->Disable();
	App->player2->Disable();
	App->particles->Disable();
	App->collision->Disable();
	return true;
}
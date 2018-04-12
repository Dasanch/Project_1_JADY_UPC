#include "Module2lvlScene.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameTitle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModuleContinue.h"

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
	App->player->Enable();
	App->player->position.x = 0;
	App->player->position.y = 130;
	lvl2Text = App->textures->Load("Assets/lvl2/Background_2.png");
	lvl2ground = App->textures->Load("Assets/lvl2/Foreground_2.png");
	BckSpam= App->textures->Load("Assets/lvl2/Backgroundlvl2Spritesheet.png");

	return ret;
}
update_status Module2lvlScene::Update() {
	int speedcamera = 5;
	float backgroundspeed=0.2f;
	float groundspeed = 0.3f;
	/*if(App->render->camera.x>-(3576 *SCREEN_SIZE)/backgroundspeed)*/
	if (App->render->camera.x > App->render->getCameraPosition(3576, backgroundspeed))
	{
		App->render->camera.x -= speedcamera;
		}
	
	App->render->Blit(lvl2Text, 0, 0, NULL, backgroundspeed);
	App->render->Blit(lvl2ground, 2000, 0, NULL, groundspeed);

	App->render->Blit(BckSpam, 390, SCREEN_HEIGHT-BckSpamRect.h, &BckSpamRect, groundspeed);
	App->render->Blit(BckSpam, 1450, SCREEN_HEIGHT - BckSpamRect.h, &BckSpamRect, groundspeed);
	App->render->Blit(BckSpam, 1800, SCREEN_HEIGHT - BckSpamRect.h, &BckSpamRect, groundspeed);
	App->render->Blit(BckSpam, 1600, 0, &BckSpamRect2, groundspeed);
	
<<<<<<< HEAD
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		//App->fade->FadeToBlack(this, App->GameTitle, 0.5f);
		App->fade->FadeToBlack(this, App->scene_continue, 0.5f);
	}
=======
>>>>>>> bf441af1002d46da22e2e333a0a481fe7958ec01

	return UPDATE_CONTINUE;
}

bool Module2lvlScene::CleanUp() {

	LOG("Unloading ready scene");
	App->render->camera.x = 0;
	App->player->Disable();

	App->textures->Unload(lvl2Text);
	App->textures->Unload(lvl2ground);
	App->textures->Unload(BckSpam);
	return true;
}
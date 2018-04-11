#include "Module2lvlScene.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameTitle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
Module2lvlScene::Module2lvlScene()
{
}

bool Module2lvlScene::Start()
{
	
	bool ret = true;
	App->player->Enable();
	App->player->position.x = 0;
	App->player->position.y = 130;
	lvl2Text = App->textures->Load("Assets/lvl1/Background_2.png");
	lvl2ground = App->textures->Load("Assets/lvl1/Foreground_2.png");

	return ret;
}
update_status Module2lvlScene::Update() {
	int speedcamera = 5;
	float backgroundspeed=0.2f;
	/*if(App->render->camera.x>-(3576 *SCREEN_SIZE)/backgroundspeed)*/
	if (App->render->camera.x > App->render->getCameraPosition(3576, backgroundspeed))
	{
		App->render->camera.x -= speedcamera;
		}
	
	App->render->Blit(lvl2Text, 0, 0, NULL, backgroundspeed);
	App->render->Blit(lvl2ground, 2000, 0, NULL, 0.3);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->GameTitle, 0.5f);
	}

	return UPDATE_CONTINUE;
}
bool Module2lvlScene::CleanUp() {
	App->render->camera.x = 0;
	App->player->Disable();
	return true;
}
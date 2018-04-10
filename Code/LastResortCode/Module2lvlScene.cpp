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

	lvl2Text = App->textures->Load("Assets/Background_2.png");
	

	return ret;
}
update_status Module2lvlScene::Update() {

	App->render->camera.x--;
	App->render->Blit(lvl2Text, 0, 0, NULL, 0.2);
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
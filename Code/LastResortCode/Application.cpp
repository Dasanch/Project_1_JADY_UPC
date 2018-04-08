#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameTitle.h"
#include "ModuleStageReady.h"


Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = background = new ModuleBackground();
	modules[5] = player = new ModulePlayer();
	modules[6] = audio = new ModuleAudio();
<<<<<<< HEAD
	modules[7] = scene_ready = new ModuleStageReady();
	modules[8] = fade = new ModuleFadeToBlack();
	
=======
	modules[7] = fade = new ModuleFadeToBlack();
	modules[8] = GameTitle = new ModuleGameTitle();
	modules[9] = scene_ready = new ModuleStageReady();
>>>>>>> da16a1cb325a07dca1108c7cb69a36a7206ef41f
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;
	// Player will be enabled on the first update of a new scene
	player->Disable();

	// Disable the map that you do not start with
	background->Disable();

	player->Disable();
	scene_ready->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

<<<<<<< HEAD
	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
=======
	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
>>>>>>> da16a1cb325a07dca1108c7cb69a36a7206ef41f
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

<<<<<<< HEAD

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
=======
	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
>>>>>>> da16a1cb325a07dca1108c7cb69a36a7206ef41f
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}
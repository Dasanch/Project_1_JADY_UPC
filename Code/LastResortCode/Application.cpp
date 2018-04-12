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
#include "ModuleNeoGeo.h"
#include "Module2lvlScene.h"
#include "ModuleGameOver.h"
#include "ModuleContinue.h"


Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio();
	modules[5] = background = new ModuleBackground();
	modules[6] = scene_lvl2 = new Module2lvlScene();
	modules[7] = player = new ModulePlayer();
	modules[8] = GameTitle = new ModuleGameTitle();
	modules[9] = scene_ready = new ModuleStageReady();
	modules[10] = scene_gameover = new ModuleGameOver();
	modules[11] = scene_continue = new ModuleContinue();
	modules[12] = fade = new ModuleFadeToBlack();// !IMPORTANT! Remmember: fade always needs to be the last one module 
	//modules[10] = neogeoScene = new ModuleNeoGeo();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;


	// Disable all stopped modules here
	background->Disable();
	player->Disable(); // Player will be enabled on the first update of a new scene
	scene_ready->Disable();
	scene_gameover->Disable();
	scene_continue->Disable();
	//GameTitle->Disable();//NeoGeoModule goes first
	scene_lvl2->Disable();

	// Disable the map that you do not start with
	// ---

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}
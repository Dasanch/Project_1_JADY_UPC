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
#include "ModuleParticles.h"
#include "ModuleCollision.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = background = new ModuleBackground();
	modules[i++] = scene_lvl2 = new Module2lvlScene();
	//Add module orbit here (particles are rendererd in front of the orbit)
	modules[i++] = particles = new ModuleParticles();//!IMPORTANT: Module particles must be after the level modules and before the player module (note that particles are always rendered behind the player ship)
	modules[i++] = player = new ModulePlayer();
	modules[i++] = neogeoScene = new ModuleNeoGeo();
	modules[i++] = GameTitle = new ModuleGameTitle();
	modules[i++] = scene_ready = new ModuleStageReady();
	modules[i++] = scene_gameover = new ModuleGameOver();
	modules[i++] = scene_continue = new ModuleContinue();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = fade = new ModuleFadeToBlack();// !IMPORTANT! Remmember: fade always needs to be the last one module 
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
	audio->Disable();
	GameTitle->Disable();
	player->Disable(); // Player will be enabled on the first update of a new scene
	background->Disable();
	scene_lvl2->Disable();
	scene_ready->Disable();
	scene_gameover->Disable();
	scene_continue->Disable();

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
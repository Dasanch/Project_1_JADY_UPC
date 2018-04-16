#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleStage01.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameTitle.h"
#include "ModuleReady.h"
#include "ModuleNeoGeo.h"
#include "ModuleStage02.h"
#include "ModuleGameOver.h"
#include "ModuleContinue.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleStage1Clear.h"

Application::Application()
{
	int i = 0;
	//General modules------------------------------------------
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = audio = new ModuleAudio();
	//Stages----------------------------------------------------
	modules[i++] = stage01 = new ModuleStage01();
	modules[i++] = stage02 = new Module2lvlScene();
	//Add module orbit here (particles are rendererd in front of the orbit)
	modules[i++] = particles = new ModuleParticles();//!IMPORTANT: Module particles must be after the level modules and before the player module (note that particles are always rendered behind the player ship)
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = neogeoScene = new ModuleNeoGeo();
	modules[i++] = titleScene = new ModuleGameTitle();
<<<<<<< HEAD
	modules[i++] = scene_ready = new ModuleStageReady();
	modules[i++] = scene_gameover = new ModuleGameOver();
	modules[i++] = scene_continue = new ModuleContinue();
	modules[i++] = scene_stage1clear = new ModuleStage1Clear();
=======
	modules[i++] = readyScene = new ModuleStageReady();
	modules[i++] = gameoverScene = new ModuleGameOver();
	modules[i++] = continueScene = new ModuleContinue();
>>>>>>> 27dd58dc9d8bfb1f49b5e5ca1a7950e7c7666cd8
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
	titleScene->Disable();
	player->Disable(); // Player will be enabled on the first update of a new scene
<<<<<<< HEAD
	background->Disable();
	scene_lvl2->Disable();
	scene_ready->Disable();
	scene_gameover->Disable();
	scene_continue->Disable();
	scene_stage1clear->Disable();
=======
	stage01->Disable();
	stage02->Disable();
	readyScene->Disable();
	gameoverScene->Disable();
	continueScene->Disable();
>>>>>>> 27dd58dc9d8bfb1f49b5e5ca1a7950e7c7666cd8

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
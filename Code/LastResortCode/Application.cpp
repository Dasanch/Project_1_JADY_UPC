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
<<<<<<< HEAD

=======
>>>>>>> 000f94830e87cc7e8bd57c3c13907146cc2964d9

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
<<<<<<< HEAD
	modules[8] = neogeoScene = new ModuleNeoGeo();
	modules[9] = GameTitle = new ModuleGameTitle();
	modules[10] = scene_ready = new ModuleStageReady();
	modules[11] = gameover = new ModuleGameOver();
	modules[12] = cont = new ModuleContinue();
	modules[13] = fade = new ModuleFadeToBlack();// !IMPORTANT! Remmember: fade always needs to be the last one module 
=======
	modules[8] = GameTitle = new ModuleGameTitle();
	modules[9] = scene_ready = new ModuleStageReady();
<<<<<<< HEAD
	modules[10] = scene_gameover = new ModuleGameOver();
	modules[11] = scene_continue = new ModuleContinue();
=======
	modules[10] = gameover = new ModuleGameOver();
	modules[11] = cont = new ModuleContinue();
>>>>>>> 000f94830e87cc7e8bd57c3c13907146cc2964d9
	modules[12] = fade = new ModuleFadeToBlack();// !IMPORTANT! Remmember: fade always needs to be the last one module 
	//modules[10] = neogeoScene = new ModuleNeoGeo();
>>>>>>> 607239fb0354019a9810df2be752100e5c8193ae
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
<<<<<<< HEAD
	scene_gameover->Disable();
	scene_continue->Disable();
=======
	cont->Disable();
	gameover->Disable();
<<<<<<< HEAD
=======
	audio->Disable();
>>>>>>> 000f94830e87cc7e8bd57c3c13907146cc2964d9
	//GameTitle->Disable();//NeoGeoModule goes first
	scene_lvl2->Disable();
>>>>>>> 607239fb0354019a9810df2be752100e5c8193ae

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
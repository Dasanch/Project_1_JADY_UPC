#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleStage01.h"
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
#include "ModuleStageClear.h"
#include "ModuleUnit.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModulePowerups.h"

Application::Application()
{
	int i = 0;
	//General modules------------------------------------------
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = fonts = new ModuleFonts();
	modules[i++] = audio = new ModuleAudio();
	//Stages----------------------------------------------------
	modules[i++] = stage01 = new ModuleStage01();
	modules[i++] = stage02 = new Module2lvlScene();
	modules[i++] = powerups = new ModulePowerups();
	modules[i++] = unit1 = new ModuleUnit();
	modules[i++] = unit2 = new ModuleUnit();
	modules[i++] = particles = new ModuleParticles();//!IMPORTANT: Module particles must be after the level modules and before the player module (note that particles are always rendered behind the player ship)
	modules[i++] = neogeoScene = new ModuleNeoGeo();
	modules[i++] = titleScene = new ModuleGameTitle();
	modules[i++] = readyScene = new ModuleStageReady();
	modules[i++] = gameoverScene = new ModuleGameOver();
	modules[i++] = continueScene = new ModuleContinue();
	modules[i++] = stageclearScene = new ModuleStageClear();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = player1 = new Player1();
	modules[i++] = player2 = new Player2();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = fade = new ModuleFadeToBlack();// !IMPORTANT! Remmember: fade always needs to be before module ui
	modules[i++] = ui = new ModuleUI();

}

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;
	// Disable all stopped modules here-----------------------------------
	titleScene->Disable();
	player1->Disable(); // Player will be enabled on the first update of a new scene
	player2->Disable();
	stage01->Disable();
	stage02->Disable();
	readyScene->Disable();
	gameoverScene->Disable();
	continueScene->Disable();
	stageclearScene->Disable();
	unit1->Disable();
	unit2->Disable();
	enemies->Disable();
	particles->Disable();
	collision->Disable();
	ui->HideUi();
	powerups->Disable();

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
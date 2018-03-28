#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	//TileMaplvl1
	Background.Rect.x = 0;
	Background.Rect.y = 0;
	Background.Rect.w = 4408;
	Background.Rect.h = 239;
	Background.Speed = 1;
	
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("/Assets/TileMaplvl1Ground&Tunel.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	


	

	return UPDATE_CONTINUE;
}
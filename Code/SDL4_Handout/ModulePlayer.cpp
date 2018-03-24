#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	
	position.x = 0;
	position.y = 130;
	
	//Up 
	ship.PushBack({ 0, 0, 32, 12 }); //UpShip = 0;
	ship.PushBack({ 32, 0, 32, 12 }); // MiddleUpShip = 1;

	// The ship when it does not move up or down 
	ship.PushBack({ 64, 3, 32, 12 }); //Frame num 2;
	//Down
	ship.PushBack({ 95, 0, 32, 12 }); // Frame num 3
	ship.PushBack({ 128, 0, 32, 12 }); //  Frame num 4

	ship.speed = 1;


	


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/SpaceShip_player1.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &ship;
	int speed = 3;
	int StaticShip = 2;
	int MiddleUpShip = 1;
	int UpShip = 0;
	int MiddleDownShip = 3;
	int DownShip = 4;
	int InstanFrameNum=3;

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		if (StaticShip == InstanFrameNum)
		{
			InstanFrameNum = MiddleUpShip;
		}
		else
		{
			InstanFrameNum = UpShip;
		}
		
		
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		if (StaticShip == InstanFrameNum)
		{
			InstanFrameNum = MiddleDownShip;
		}
		else
		{
			InstanFrameNum = DownShip;
		}
		position.y += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
	
		position.x -= speed;
	}
	

	

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->ReturnFrame(InstanFrameNum);

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}
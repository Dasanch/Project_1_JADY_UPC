#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer() //Constructor 
{
	
	position.x = 0;
	position.y = 130;
	
	ShipOne.PushBack({ 0, 0, 32, 12 }); //UpShip = 0;
	ShipOne.PushBack({ 32, 0, 32, 12 }); // MiddleUpShip = 1;
	ShipOne.PushBack({ 64, 3, 32, 12 }); //idle =2;
	ShipOne.PushBack({ 95, 0, 32, 12 }); //MiddleDownShip=  3
	ShipOne.PushBack({ 128, 4, 32, 11 }); //  DownShip= 4


	


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;

	PlayerTexture = App->textures->Load("Assets/SpaceShip_player1.png"); // arcade version
	CurrentFrame = 2;
	ignitionSpeed = 0.2f;
	releaseSpeed = 0.1f;
	
	

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	/*
	Animation* current_animation = &ship;
	int speed = 3;
	*/
	int shipWidth = 32;
	int shipHeight = 13;

	int UpShip = 0;
	int MiddleUpShip = 1;
	int StaticShip = 2;
	int MiddleDownShip = 3;
	int DownShip = 4;

	playerSpeed = 1.4f;
	int speed = 0.5f;

	Animation* current_animation = &ShipOne;

	if (App->input->keyboard[SDL_SCANCODE_W] == 1 && App->input->keyboard[SDL_SCANCODE_S] == 0)
	{
		
		if (CurrentFrame > UpShip)
		{
			CurrentFrame -= ignitionSpeed;
		}
		
		if (position.y > 0)
		{
			position.y -= playerSpeed;
		}
		
	}
	
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		CurrentFrame += ignitionSpeed;

		if (CurrentFrame >= 5)
		{
		CurrentFrame = 4.99;
		}

		if (position.y < SCREEN_HEIGHT-shipHeight)
		{
			position.y += playerSpeed;
		}

		playerSpeed += speed;
		position.y += (int)playerSpeed;
		if (playerSpeed >= speed + 1) //returns correct value to cast incrementer
			playerSpeed = speed;

		if (position.y + (int)playerSpeed >= SCREEN_HEIGHT - 8) // 8 = player height/2 + required offset
			position.y = 216; //target max down player position (original game pixel)
		
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 0 && CurrentFrame < StaticShip )
	{
		CurrentFrame += releaseSpeed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 0 && CurrentFrame > StaticShip)
	{
		CurrentFrame -= releaseSpeed;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		if (position.x > 0)
		{
			position.x -= playerSpeed;
		}
		
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == 1 && App->input->keyboard[SDL_SCANCODE_A] == 0)
	{
		position.x += playerSpeed;
		if (position.x <SCREEN_SIZE)
		{
			position.x += playerSpeed;
		}

	}
	

	

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->frames[(int)CurrentFrame];

	App->render->Blit(PlayerTexture, position.x, position.y , &r,0.0f);
	
	return UPDATE_CONTINUE;
}
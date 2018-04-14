#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer() //Constructor 
{

	position.x = 0;
	position.y = 130;

	shipPlayer1.PushBack({   0, 3, 32, 12 });	//0 = UpShip
	shipPlayer1.PushBack({  32, 3, 32, 12 });	//1 = MiddleUpShip
	shipPlayer1.PushBack({  64, 3, 32, 12 });	//2 = idle
	shipPlayer1.PushBack({  96, 3, 32, 12 });	//3 = MiddleDownShip
	shipPlayer1.PushBack({ 128, 3, 32, 12 });	//4 = DownShip

}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	bool ret = true;
	LOG("Loading player textures");

	PlayerTexture = App->textures->Load("Assets/SpaceShip_player1.png"); // arcade version

	return ret;
}

update_status ModulePlayer::Update()
{
	//INPUT
	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.x -= movementSpeed;
		if (position.x < 0)
		{
			position.x = 0;
		}
	}
	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.x += movementSpeed;
		if (position.x > SCREEN_WIDTH - 32)//32 = pixel width of the player ship
		{
			position.x = SCREEN_WIDTH - 32;
		}
	}
	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.y -= movementSpeed;
		if(position.y < 0)
		{
			position.y = 0;
		}
		//ANIMATION
		yAxis -= keyPressSpeed;
		//We check that the yAxis doesn't get bellow -1
		if(yAxis < -1)
		{
			yAxis = -1;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.y += movementSpeed;
		if (position.y > SCREEN_HEIGHT - 12)//12 = pixel height of the player ship
		{
			position.y = SCREEN_HEIGHT - 12;
		}
		//ANIMATION
		yAxis += keyPressSpeed;
		//We check that the yAxis doesn't get above 1
		if (yAxis > 1)
		{
			yAxis = 1;
		}
	}

	//If there isn't any input on the y axis
	if (App->input->keyboard[SDL_SCANCODE_W] == false && App->input->keyboard[SDL_SCANCODE_S] == false)
	{
		if(yAxis > 0.1)
		{
			//Decrement the y axis
			yAxis -= keyReleaseSpeed;
		}
		else if (yAxis < -0.1)
		{
			//Increment the y axis
			yAxis += keyReleaseSpeed;
		}
	}

	//RENDER
	//Check what is the value of the yAxis variable
	//-Idle
	if (yAxis > -transitionLimit && yAxis < transitionLimit)
	{
		currentFrame = Idle;
	}
	//-Transitions
	if (yAxis >= transitionLimit && yAxis < MaxLimit)
	{
		currentFrame = TransitionDown;
	}
	if (yAxis <= -transitionLimit && yAxis > -MaxLimit)
	{
		currentFrame = TransitionUp;
	}
	//-Maximums
	if(yAxis >= MaxLimit)
	{
		currentFrame = MaxDown;
	}
	if(yAxis <= -MaxLimit)
	{
		currentFrame = MaxUp;
	}

	App->render->Blit(PlayerTexture, position.x, position.y, &shipPlayer1.frames[currentFrame], 0.0f);

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(PlayerTexture);


	return true;
}
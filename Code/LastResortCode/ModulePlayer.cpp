#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"

ModulePlayer::ModulePlayer() //Constructor 
{

	shipPlayer1.PushBack({   0, 3, 32, 12 });	//0 = UpShip
	shipPlayer1.PushBack({  32, 3, 32, 12 });	//1 = MiddleUpShip
	shipPlayer1.PushBack({  64, 3, 32, 12 });	//2 = idle
	shipPlayer1.PushBack({  96, 3, 32, 12 });	//3 = MiddleDownShip
	shipPlayer1.PushBack({ 128, 3, 32, 12 });	//4 = DownShip

	//Player Basic Shoot Particle

	basicShot_p.anim.PushBack({ 148,127, 15,7 });
	basicShot_p.anim.speed = 0.0f;
	basicShot_p.speed = { 1, 0 };
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	bool ret = true;
	LOG("Loading player textures");
	PlayerTexture = App->textures->Load("Assets/SpaceShip_player1.png"); // arcade version
	//Reset Position
	position.x = 10 ;
	position.y = 100 ;

	//We add a collider to the player
	playerCol = App->collision->AddCollider({ position.x, position.y, 32, 12 }, COLLIDER_PLAYER, this);
	playerColPosX = position.x;
	playerColPosY = position.y;

	return ret;
}

update_status ModulePlayer::Update()
{
	//INPUT
	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.x -= movementSpeed;
		playerColPosX -= movementSpeed;
<<<<<<< HEAD
<<<<<<< HEAD

		//if (position.x < App->render->camera.x - SCREEN_WIDTH / 2)
		//{
		//	position.x = App->render->camera.x - SCREEN_WIDTH/2;
		//}
=======
=======
>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550
		if (position.x < 0)
		{
			position.x = 0;
		}
<<<<<<< HEAD
>>>>>>> parent of d64c0f2... Player collider now matches the player
=======
>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550
	}
	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.x += movementSpeed;
		playerColPosX += movementSpeed;
<<<<<<< HEAD
<<<<<<< HEAD
		//if (position.x > SCREEN_WIDTH - 32)//32 = pixel width of the player ship
		//{
		//	position.x = SCREEN_WIDTH - 32;
		//}
=======
=======
>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550
		if (position.x > SCREEN_WIDTH - 32)//32 = pixel width of the player ship
		{
			position.x = SCREEN_WIDTH - 32;
		}
<<<<<<< HEAD
>>>>>>> parent of d64c0f2... Player collider now matches the player
=======
>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550
	}
	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.y -= movementSpeed;
		playerColPosY -= movementSpeed;
<<<<<<< HEAD
<<<<<<< HEAD

		//if(position.y < 0)
		//{
		//	position.y = 0;
		//}

=======
=======
>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550
		if(position.y < 0)
		{
			position.y = 0;
		}
<<<<<<< HEAD
>>>>>>> parent of d64c0f2... Player collider now matches the player
=======
>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550
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
		playerColPosY += movementSpeed;
<<<<<<< HEAD
<<<<<<< HEAD

		//if (position.y > SCREEN_HEIGHT - 12)//12 = pixel height of the player ship
		//{
		//	position.y = SCREEN_HEIGHT - 12;
		//}

=======
=======
>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550
		if (position.y > SCREEN_HEIGHT - 12)//12 = pixel height of the player ship
		{
			position.y = SCREEN_HEIGHT - 12;
		}
<<<<<<< HEAD
>>>>>>> parent of d64c0f2... Player collider now matches the player
=======
>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550
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

	//COLLISION
	//- We update the collider position
<<<<<<< HEAD
<<<<<<< HEAD

	playerColPosX += 0.5f;//0.5f = tilemap speed
	playerCol->SetPos(playerColPosX, playerColPosY);

=======
	playerColPosX += 0.5f;//0.5f = tilemap speed
	playerCol->SetPos(playerColPosX, playerColPosY);
>>>>>>> parent of d64c0f2... Player collider now matches the player

=======
	playerColPosX += 0.5f;//0.5f = tilemap speed
	playerCol->SetPos(playerColPosX, playerColPosY);

>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550
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
	//SHOTS WITH B

<<<<<<< HEAD
	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
=======
	App->render->Blit(PlayerTexture, position.x, position.y, &shipPlayer1.frames[currentFrame], 0.0f);

	//SHOTS WITH M
	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN)
>>>>>>> parent of d64c0f2... Player collider now matches the player
	{
		App->particles->AddParticle(basicShot_p, App->render->camera.x + position.x, App->render->camera.y + position.y, PlayerTexture, COLLIDER_PLAYER_SHOT,500);

	}
	//Draw player 1
<<<<<<< HEAD

<<<<<<< HEAD
	App->render->Blit(PlayerTexture, position.x, position.y, &shipPlayer1.frames[currentFrame], 0.0f);
=======
=======
	App->render->Blit(PlayerTexture, position.x, position.y, &shipPlayer1.frames[currentFrame], 0.0f);
>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550
	/*
	// TODO 3: Update collider position to player position

	// Draw everything --------------------------------------
	//App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	App->render->Blit(PlayerTexture, position.x, position.y, &(current_animation->GetCurrentFrame()));
	*/
<<<<<<< HEAD
>>>>>>> parent of d64c0f2... Player collider now matches the player
=======
>>>>>>> 7bb6257cb3cc75ae6c97e4c7a1b849c460ee2550

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(PlayerTexture);


	return true;
}

//Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2)
{
	App->fade->FadeToBlack((Module*)App->background,(Module*)App->GameTitle, 0.5f);
}
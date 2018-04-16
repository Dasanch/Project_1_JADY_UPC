#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleStage01.h"

ModulePlayer2::ModulePlayer2() //Constructor 
{
	position.x = 0;
	position.y = 130;
	//Player animation-----------------------------------------
	shipPlayer2.PushBack({ 0, 3, 32, 12 });  	//0 = UpShip
	shipPlayer2.PushBack({ 32, 3, 32, 12 });	//1 = MiddleUpShip
	shipPlayer2.PushBack({ 64, 3, 32, 12 });	//2 = idle
	shipPlayer2.PushBack({ 96, 3, 32, 12 });	//3 = MiddleDownShip
	shipPlayer2.PushBack({ 128, 3, 32, 12 });	//4 = DownShip
	//Player Basic Shot Particle-----------------------------
	basicShot_p.anim.PushBack({ 148,127, 15,7 });
	basicShot_p.speed.x = 9;
	basicShot_p.anim.loop = false;
	basicShot_p.life = 3000;
}

ModulePlayer2::~ModulePlayer2()
{}

bool ModulePlayer2::Start()
{
	bool ret = true;
	LOG("Loading player assets");
	//textures-----------------------------------------------------------------------
	PlayerTexture = App->textures->Load("Assets/SpaceShip_player1.png"); // arcade version
	//audios-------------------------------------------------------------------------
	basic_shoot_sfx = App->audio->LoadSFX("Assets/004. Shot - center.wav");
	//colliders-------------------------------------------------------------------------
	playerCol = App->collision->AddCollider({ position.x, position.y, 32, 12 }, COLLIDER_PLAYER, this);
	return ret;
}

update_status ModulePlayer2::Update()
{
	//Input--------------------------------------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.x -= movementSpeed;
	}
	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.x += movementSpeed;
	}
	if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.y -= movementSpeed;

		//ANIMATION
		yAxis -= keyPressSpeed;
		//We check that the yAxis doesn't get bellow -1
		if (yAxis < -1)
		{
			yAxis = -1;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.y += movementSpeed;

		//ANIMATION
		yAxis += keyPressSpeed;
		//We check that the yAxis doesn't get above 1
		if (yAxis > 1)
		{
			yAxis = 1;
		}
	}

	//If there isn't any input on the y axis
	if (App->input->keyboard[SDL_SCANCODE_U] == false && App->input->keyboard[SDL_SCANCODE_J] == false)
	{
		if (yAxis > 0.1)
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

	//Collision------------------------------------------------------------------------------
	//- We update the collider position
	playerCol->SetPos(position.x, position.y);

	//Render--------------------------------------------------------------------------------
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
	if (yAxis >= MaxLimit)
	{
		currentFrame = MaxDown;
	}
	if (yAxis <= -MaxLimit)
	{
		currentFrame = MaxUp;
	}
	//Basic shoot-------------------------------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN) {
		App->audio->ControlSFX(basic_shoot_sfx, PLAY_AUDIO);
		App->particles->AddParticle(basicShot_p, position.x + 20, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
	}
	//Draw ship-------------------------------------------------------------------------
	App->render->Blit(PlayerTexture, position.x, position.y, &shipPlayer2.frames[currentFrame]);

	return UPDATE_CONTINUE;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player assets");
	//textures------------------------------------------------------------------
	App->textures->Unload(PlayerTexture);
	//audios------------------------------------------------------------------
	App->audio->UnloadSFX(basic_shoot_sfx);
	return true;
}

//Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer2::OnCollision(Collider* collider1, Collider* collider2)
{
	App->fade->FadeToBlack((Module*)App->stage01, (Module*)App->titleScene, 0.5f);
}
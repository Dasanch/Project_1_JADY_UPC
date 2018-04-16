#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer() //Constructor 
{
	position.x = 0;
	position.y = 130;
	//Movement animation-----------------------------------------
	shipPlayer1.PushBack({ 0, 3, 32, 12 });	    //0 = UpShip
	shipPlayer1.PushBack({ 32, 3, 32, 12 });	//1 = MiddleUpShip
	shipPlayer1.PushBack({ 64, 3, 32, 12 });	//2 = idle
	shipPlayer1.PushBack({ 96, 3, 32, 12 });	//3 = MiddleDownShip
	shipPlayer1.PushBack({ 128, 3, 32, 12 });	//4 = DownShip
	//Initial animation-----------------------------------------
	//TODO Alejandro
	//Death animation-------------------------------------------
	//TODO Alejandro
	//Basic Shot Particle---------------------------------------
	basicShot.anim.PushBack({ 148,127, 15,7 });
	basicShot.anim.speed = 0.0f;
	basicShot.speed.x = 10;
	basicShot.anim.loop = false;
	basicShot.life = 3000;
	//Shot Fire Particle----------------------------------------
	shotFire.anim.PushBack({ 148,127, 15,7 });
	//Death Explosion Particle----------------------------------
	explosion01.anim.PushBack({ 148,127, 15,7 });
	//Basic Shot Explosion Particle-----------------------------
	explosion02.anim.PushBack({ 148,127, 15,7 });
	

}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	bool ret = true;
	LOG("Loading player assets");
	//textures-----------------------------------------------------------------------
	PlayerTexture = App->textures->Load("Assets/SpaceShip_player1.png"); // arcade version
	//audios-------------------------------------------------------------------------
	basic_shot_sfx = App->audio->LoadSFX("Assets/004. Shot - center.wav");
	//colliders-------------------------------------------------------------------------
	playerCol = App->collision->AddCollider({ position.x, position.y, 32, 12 }, COLLIDER_PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	//Input--------------------------------------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.x -= movementSpeed;
	
		if (position.x < -(App->render->camera.x / App->render->cameraspeed))
			position.x = -App->render->camera.x / App->render->cameraspeed;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.x += movementSpeed;
		if (position.x+playerwidth > -(App->render->camera.x / App->render->cameraspeed)+ App->render->camera.w)
			position.x = -(App->render->camera.x / App->render->cameraspeed) + App->render->camera.w-playerwidth;

	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.y -= movementSpeed;
		if (position.y < 0)
			position.y = 0;

		//ANIMATION
		yAxis -= keyPressSpeed;
		//We check that the yAxis doesn't get bellow -1
		if (yAxis < -1)
		{
			yAxis = -1;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		//MOVEMENT
		position.y += movementSpeed;
		if (position.y > SCREEN_HEIGHT - 12)
			position.y = SCREEN_HEIGHT - 12;
		//ANIMATION
		yAxis += keyPressSpeed;
		//We check that the yAxis doesn't get above 1
		if (yAxis > 1)
		{
			yAxis = 1;
		}
	}
	//If there isn't any input on the y axis
	if (App->input->keyboard[SDL_SCANCODE_S] == false)
	{
		if (yAxis > 0.1)
		{
			yAxis -= keyReleaseSpeed;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_W] == false)
	{
		if (yAxis < -0.1)
		{
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
	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN) {
		App->audio->ControlSFX(basic_shot_sfx, PLAY_AUDIO);
		App->particles->AddParticle(basicShot, position.x + 20, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
	}
	//Draw ship-------------------------------------------------------------------------
	App->render->Blit(PlayerTexture, position.x, position.y, &shipPlayer1.frames[currentFrame]);

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player assets");
	//textures------------------------------------------------------------------
	App->textures->Unload(PlayerTexture);
	//audios------------------------------------------------------------------
	App->audio->UnloadSFX(basic_shot_sfx);
	return true;
}

//Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2)
{
	App->fade->FadeToBlack((Module*)App->stage01, (Module*)App->titleScene, 0.5f);
}
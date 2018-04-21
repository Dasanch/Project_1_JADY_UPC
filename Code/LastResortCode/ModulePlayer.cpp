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
{}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	bool ret = true;
	LOG("Loading player assets");
	//variables-----------------------------------------------------------------------
	godMode = false;
	isShooting = false;
	shoot = false;
	canMove = false;
	canShoot = false;
	isDying = false;
	shipAnimations = ShipAnimations::Initial;
	start_time = SDL_GetTicks();
	//textures-----------------------------------------------------------------------
	PlayerTexture = App->textures->Load("Assets/SpaceShip_player1.png"); // arcade version																 
	//audios-------------------------------------------------------------------------
	basic_shot_sfx = App->audio->LoadSFX("Assets/004. Shot - center.wav"); 
	death_sfx = App->audio->LoadSFX("Assets/005. Death.wav");
	//colliders----------------------------------------------------------------------
	playerCol = App->collision->AddCollider({ position.x, position.y, 32, 12 }, colType, this);
	//animations-----------------------------------------------------------------------
	deathAnim.Reset();
	return ret;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player assets");
	//textures------------------------------------------------------------------
	App->textures->Unload(PlayerTexture);
	//audios------------------------------------------------------------------
	App->audio->UnloadSFX(basic_shot_sfx);
	App->audio->UnloadSFX(death_sfx);

	return true;
}

update_status ModulePlayer::Update()
{
	//Debug Modes----------------------------------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN && !isDying)
	{
		if (godMode == true) {
			colType = COLLIDER_PLAYER;
			playerCol->type = COLLIDER_PLAYER;
			godMode = false;
		}
		else {
			colType = COLLIDER_NONE;
			playerCol->type = COLLIDER_NONE;
			godMode = true;
		}
	}
	//Timer----------------------------------------------------------------------------
	current_time = SDL_GetTicks() - start_time; //Delete if it has not use
	//Movement-------------------------------------------------------------------------
	if (canMove == true)
		MovementInput();
	//Shots----------------------------------------------------------------------------
	if (canShoot == true) {
		ShotInput();
	}
	//Lock the unit--------------------------------------------------------------------
	if (Lock())
	{
		if (locked == true) { locked = false; }
		else { locked = true; }
	}
	//Collision------------------------------------------------------------------------
	playerCol->SetPos(position.x, position.y); //We update the collider position

	//Ship Animation-------------------------------------------------------------------
	ShipAnimation();

	return UPDATE_CONTINUE;
}

//Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2)
{
	App->particles->AddParticle(App->particles->death_explosion, position.x, position.y , PlayerTexture, COLLIDER_NONE);
	App->audio->ControlSFX(death_sfx, PLAY_AUDIO);
	isDying = true;
	canMove = false;
	canShoot = false;
	shipAnimations = ShipAnimations::Death;
}

void  ModulePlayer::ShotInput() {
	//Basic shoot-------------------------------------------------------------------
	if (Shoot() == true) {
		App->audio->ControlSFX(basic_shot_sfx, PLAY_AUDIO);
		App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
		if (isShooting == false)
			shoot = true;
	}
	//----------Ship Fire-------------------------------------------
	if (shoot == true) {
		if (shotFire.finished == false) {
			isShooting = true;
			App->render->Blit(PlayerTexture, position.x + 32, position.y + 1, &shotFire.GetFrameEx());
		}
		else {
			shotFire.finished = false;
			isShooting = false;
			shoot = false;
		}
	}
}

void ModulePlayer::MovementInput() {

	if (MoveLeft() == true)	{
		//---------Movment-----------------------------------------------------------
		position.x -= movementSpeed;
	
		if (position.x < (App->render->camera.x / App->render->cameraspeed))
			position.x = App->render->camera.x / App->render->cameraspeed;
	}
	if (MoveRight() == true) {
		//---------Movment-----------------------------------------------------------
		position.x += movementSpeed;
		if (position.x + playerwidth > (App->render->camera.x / App->render->cameraspeed) + App->render->camera.w)
			position.x = (App->render->camera.x / App->render->cameraspeed) + App->render->camera.w - playerwidth;
	}
	if (MoveUp() == true) {
		//---------Movment-----------------------------------------------------------
		position.y -= movementSpeed;
		if (position.y <(App->render->camera.y / App->render->cameraspeed))
			position.y = (App->render->camera.y / App->render->cameraspeed) ;
		/*if (position.y < 0)
			position.y = 0;*/
		//---------Animation---------------------------------------------------------
		yAxis -= keyPressSpeed;
		//We check that the yAxis doesn't get bellow -1
		if (yAxis < -1) {
			yAxis = -1;
		}
	}
	if (MoveDown() == true)	{
		//---------Movment-----------------------------------------------------------
		position.y += movementSpeed;
		
		
		//---------Animation---------------------------------------------------------
		yAxis += keyPressSpeed;
		//We check that the yAxis doesn't get above 1
		if (yAxis > 1)
		{
			yAxis = 1;
		}
	}
	//If there isn't any input on the y axis
	if (MoveDown() == false) {
		if (yAxis > 0.1) {
			yAxis -= keyReleaseSpeed;
		}
	}

	if (MoveUp() == false) {
		if (yAxis < -0.1) {
			yAxis += keyReleaseSpeed;
		}
	}
}
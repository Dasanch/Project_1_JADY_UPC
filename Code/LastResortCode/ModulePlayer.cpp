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
#include "ModuleStageClear.h"
#include "ModuleStage01.h"
#include "ModuleUnit.h"

ModulePlayer::ModulePlayer() //Constructor 
{}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	bool ret = true;
	LOG("Loading player assets");
	//variables-----------------------------------------------------------------------
	lives = 2;
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
	return true;
}

void ModulePlayer::Reappear() {
	shipAnimations = ShipAnimations::Initial;
	isShooting = false;
	shoot = false;
	canMove = false;
	canShoot = false;
	start_time = SDL_GetTicks();
	deathAnim.Reset();
	position.x = initPosition.x;
	position.y = initPosition.y + App->render->relative_camera.y;
}

void ModulePlayer::InitPosition() {
	position.x = initPosition.x;
	position.y = initPosition.y;
}


update_status ModulePlayer::PreUpdate()
{
	//Movement-------------------------------------------------------------------------
	if (canMove == true)
		MovementInput();
	//If the movement is not on preupdate, the player will move after the unit, causing weird visual effects

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::Update()
{
	//Timer----------------------------------------------------------------------------
	current_time = SDL_GetTicks() - start_time; //Delete if it has not use
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
	//Shots----------------------------------------------------------------------------
	if (canShoot == true) {
		ShotInput();
	}
	//Lock the unit--------------------------------------------------------------------
	if (Lock())
	{
		if (unit_locked == true) { unit_locked = false; }
		else { unit_locked = true; }
	}
	//Collision------------------------------------------------------------------------
	playerCol->SetPos(position.x, position.y); //We update the collider position

	//Ship Animation-------------------------------------------------------------------
	ShipAnimation();

	//Winlvl
	if (winlvl)
	{
		Winlvl();
		/*if (start_timer)
		{


			FadeToBlackAlfa += 1;
			SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, FadeToBlackAlfa);
			SDL_RenderFillRect(App->render->renderer, &backgroundBlack);


		}*/
		/*if (FadeToBlackAlfa > 255)
		{*/
			
		/*}*/
	}
	return UPDATE_CONTINUE;
}


void ModulePlayer::ShipAnimation() {

	switch (shipAnimations) {
	case Initial:
		current_animation = &initAnim.GetFrameEx();
		if (initAnim.finished == true) {
			shipAnimations = ShipAnimations::Movment;
			if (godMode == false) {
				colType = COLLIDER_PLAYER;
				playerCol->type = COLLIDER_PLAYER;
			}
			initAnim.Reset();
			canMove = true;
			canShoot = true;
			break;
		}
		//Draw ship---------------------------------------------------
		if (initAnim.current_frame > 4) {
			App->render->Blit(PlayerTexture, position.x + 32 - (current_animation->w), position.y + 6 - (current_animation->h / 2), current_animation);
		}
		else {
			App->render->Blit(PlayerTexture, position.x - 40, position.y + 6 - (current_animation->h / 2), current_animation);
		}
		//------------------------------------------------------------
		break;
	case Movment:
		//Idle--------------------------------------------------------
		if (yAxis > -transitionLimit && yAxis < transitionLimit) {
			currentFrame = Idle;
		}
		//Transitions-------------------------------------------------
		if (yAxis >= transitionLimit && yAxis < MaxLimit) {
			currentFrame = TransitionDown;
		}
		if (yAxis <= -transitionLimit && yAxis > -MaxLimit) {
			currentFrame = TransitionUp;
		}
		//Maximums---------------------------------------------------
		if (yAxis >= MaxLimit) {
			currentFrame = MaxDown;
		}
		if (yAxis <= -MaxLimit) {
			currentFrame = MaxUp;
		}
		//Draw ship--------------------------------------------------
		current_animation = &shipAnim.frames[currentFrame]; //It set the animation frame 
		App->render->Blit(PlayerTexture, position.x, position.y, current_animation);
		//-----------------------------------------------------------
		break;
	case Death:

		if (deathAnim.finished == true) {
			PlayerDies();
		}

		else if (isDying) {
			colType = COLLIDER_NONE;
			playerCol->type = COLLIDER_NONE;
			current_animation = &deathAnim.GetFrameEx();
			App->render->Blit(PlayerTexture, position.x + 32 - current_animation->w, position.y + 6 - current_animation->h / 2, current_animation);
		}
		break;
	}
}


void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2)
{
	App->particles->AddParticle(App->particles->death_explosion, position.x, position.y , PlayerTexture, COLLIDER_NONE);
	isDying = true;
	canMove = false;
	canShoot = false;
	shipAnimations = ShipAnimations::Death;
}

void  ModulePlayer::ShotInput() {
	//Basic shoot-------------------------------------------------------------------
	if (Shoot() == true)
	{
		if(powerup_type == powerupType::NOPOWERUP)
		{
			//Basic shoot
			App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
		}
		if (powerup_type == powerupType::LASER)
		{
			switch(powerup_upgrades)
			{
			case 1:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
				break;
			case 2:
				//Laser shot
				break;
			case 3:
				//Laser shot
				//Laser rings
				break;
			}
		}
		if (powerup_type == powerupType::HOMING)
		{
			switch (powerup_upgrades)
			{
			case 1:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
				break;
			case 2:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
				//2 missiles on the sides
				break;
			case 3:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
				//6 missiles on the sides
				break;
			}
		}
		if (powerup_type == powerupType::GROUND)
		{
			switch (powerup_upgrades)
			{
			case 1:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
				break;
			case 2:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
				//Missiles up and down
				break;
			case 3:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
				//Missiles up and down that destoy the ground
				break;
			}
		}
		if (isShooting == false) { shoot = true; }
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
		position.x -= (int)movementSpeed;
	
		if (position.x < (App->render->camera.x / App->render->cameraspeed))
			position.x = App->render->camera.x / App->render->cameraspeed;
	}
	if (MoveRight() == true) {
		//---------Movment-----------------------------------------------------------
		position.x += (int)movementSpeed;
		if (position.x + playerwidth > (App->render->camera.x / App->render->cameraspeed) + App->render->camera.w)
			position.x = (App->render->camera.x / App->render->cameraspeed) + App->render->camera.w - playerwidth;
	}
	if (MoveUp() == true) {
		//---------Movment-----------------------------------------------------------
		position.y -= (int)movementSpeed;
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

		if (position.y <(App->render->camera.y / App->render->cameraspeed) + SCREEN_HEIGHT - 12)

		position.y += (int)movementSpeed;

		
		
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
void ModulePlayer::Winlvl()
{
	if (godMode == false)
	{
		colType = COLLIDER_NONE;
		playerCol->type = COLLIDER_NONE;
		godMode = true;
	}
	
	canShoot = false;
	canMove = false;
	Winposition();
}

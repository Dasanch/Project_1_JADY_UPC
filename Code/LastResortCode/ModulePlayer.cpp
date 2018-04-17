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
	//Movement animation-----------------------------------------
	shipPlayer1.PushBack({ 0, 3, 32, 12 });	    //0 = UpShip
	shipPlayer1.PushBack({ 32, 3, 32, 12 });	//1 = MiddleUpShip
	shipPlayer1.PushBack({ 64, 3, 32, 12 });	//2 = idle
	shipPlayer1.PushBack({ 96, 3, 32, 12 });	//3 = MiddleDownShip
	shipPlayer1.PushBack({ 128, 3, 32, 12 });	//4 = DownShip
	//Initial animation-----------------------------------------
	initAnim.PushBack({ 0, 122, 111, 2 });
	initAnim.PushBack({ 0, 124, 117, 3 });
	initAnim.PushBack({ 0, 127, 88, 4 });
	initAnim.PushBack({ 0, 131, 86, 8 });
	//-----------------------------------------
	initAnim.PushBack({ 0, 139, 64, 25 });
	initAnim.PushBack({ 0, 164, 64, 25 });
	initAnim.PushBack({ 0, 189, 64, 25 });
	initAnim.PushBack({ 0, 214, 64, 25 });
	initAnim.PushBack({ 64, 139, 64, 25 });
	initAnim.PushBack({ 64, 164, 64, 25 });
	initAnim.PushBack({ 64, 189, 64, 25 });
	initAnim.PushBack({ 64, 214, 64, 25 });
	initAnim.PushBack({ 128, 139, 64, 25 });
	initAnim.PushBack({ 128, 164, 64, 25 });
	initAnim.speed = 0.2f;
	initAnim_p = { 40, 78 };
	//Death animation-------------------------------------------
	//TODO Alejandro
	//Basic Shot Particle---------------------------------------
	basicShot.anim.PushBack({ 0,247, 15,7 });
	basicShot.anim.speed = 0.0f;
	basicShot.speed.x = 10;
	basicShot.anim.loop = false;
	basicShot.life = 3000;
	//Shot Fire Particle----------------------------------------
	shotFire.PushBack({ 125, 247, 10,9 });
	shotFire.PushBack({ 137, 247, 10,9 });
	shotFire.PushBack({ 125, 258, 13,12 });
	shotFire.speed = 0.2f;
	shotFire.loop = true;
	//Death Explosion Particle----------------------------------
	death_explosion.anim.PushBack({ 148,127, 10,7 });
	//Basic Shot Explosion Particle-----------------------------
	basic_explosion.anim.PushBack({ 148,127, 15,7 });
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	bool ret = true;
	LOG("Loading player assets");
	//variables-----------------------------------------------------------------------
	isShooting = false;
	shoot = false;
	canMove = false;
	canShoot = false;
	shipAnimations = ShipAnimations:: Initial;
	start_time = SDL_GetTicks();
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
	//Timer--------------------------------------------------------------------------
	current_time = SDL_GetTicks() - start_time; //Delete if it has not use
	//Movement-------------------------------------------------------------------------
	if (canMove == true)
		MovementInput();
	//Shots----------------------------------------------------------------------------
	if (canShoot == true) {
		ShotInput();
	}
	//Collision------------------------------------------------------------------------
	playerCol->SetPos(position.x, position.y); //We update the collider position

	//Ship Animation-------------------------------------------------------------------
	switch (shipAnimations) {
	case Initial:
		current_animation = &initAnim.GetFrameEx();
		if (initAnim.finished == true) {
			shipAnimations = ShipAnimations::Movment;
			canMove = true;
			canShoot = true;
			break;
		}
		//Draw ship---------------------------------------------------
		if (initAnim.current_frame > 4) {
			App->render->Blit(PlayerTexture, initAnim_p.x - (current_animation->w / 2), initAnim_p.y - (current_animation->h / 2), current_animation);
		}
		else {
			App->render->Blit(PlayerTexture, position.x - 40, initAnim_p.y - (current_animation->h / 2), current_animation);
		}
		initAnim_p.x += 1; //Increment pivot for follow position.x
		//------------------------------------------------------------
		break;
	case Movment: //Check what is the value of the yAxis variable
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
		current_animation = &shipPlayer1.frames[currentFrame]; //It set the animation frame 
		App->render->Blit(PlayerTexture, position.x, position.y,  current_animation);
		//-----------------------------------------------------------
		break;
	case Death:

		break;
	}
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

void  ModulePlayer::ShotInput() {
	//Basic shoot-------------------------------------------------------------------
	if (Shoot() == true) {
		App->audio->ControlSFX(basic_shot_sfx, PLAY_AUDIO);
		App->particles->AddParticle(basicShot, position.x + 32, position.y + 3, PlayerTexture, COLLIDER_PLAYER_SHOT, 0);
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
		if (position.x < -(App->render->camera.x / App->render->cameraspeed))
			position.x = -App->render->camera.x / App->render->cameraspeed;
	}
	if (MoveRight() == true) {
		//---------Movment-----------------------------------------------------------
		position.x += movementSpeed;
		if (position.x + playerwidth > -(App->render->camera.x / App->render->cameraspeed) + App->render->camera.w)
			position.x = -(App->render->camera.x / App->render->cameraspeed) + App->render->camera.w - playerwidth;
	}
	if (MoveUp() == true) {
		//---------Movment-----------------------------------------------------------
		position.y -= movementSpeed;
		if (position.y < 0)
			position.y = 0;
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
		if (position.y > SCREEN_HEIGHT - 12)
			position.y = SCREEN_HEIGHT - 12;
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
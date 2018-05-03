#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h" 
#include "p2Point.h"
#include "ModulePowerups.h"

struct SDL_Texture;
struct Collider; //SHOT
struct Particle;
struct Mix_Chunk;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void MovementInput(); //Added 
	void ShotInput(); //Added 
	void OnCollision(Collider*, Collider*);
	void Reappear();
	void InitPosition();
	void ShipAnimation();

	//Functions that will be rewritten in each player
	//virtual void LoadSprites();
	virtual bool MoveUp() = 0;
	virtual bool MoveDown() = 0;
	virtual bool MoveLeft() = 0;
	virtual bool MoveRight() = 0;
	virtual bool Shoot() = 0;
	virtual bool Lock() = 0;
	virtual void Reset_Positions() = 0;
	virtual void PlayerDies() = 0;
	virtual void KillUnit() = 0;

public:
	//Variables--------------------------------------------
	Mix_Chunk* init_sfx = nullptr;
	//--------Gameplay-----------------------------
	int powerup_upgrades = 0;
	powerupType powerup_type = powerupType::NOPOWERUP;
	//--------States--------------------------------
	bool isAppearing;
	bool isDying;
	bool isShooting = false;
	bool shoot = false;
	bool unit_locked = false;
	//--------Debug Modes--------------------------
	bool godMode;
	//--------Time---------------------------------
	Uint32 start_time;
	Uint32 current_time;
	//--------Movment------------------------------
	iPoint position;
	iPoint initPosition;
	float movementSpeed = 2;//It can't be const because the speed powerup modifies this value
	bool canMove;
	bool canShoot;
	//-------Ship Animation-----------------------------
	int const playerwidth = 32;
	int const playerheight = 16;
	float yAxis = 0;//This value will control the animation of the ship. It will increase up to 1 when S is pressed and it will decrease up to -1 when W is pressed. When none of those keys are pressed, it will progressively go back to 0.
	const float keyPressSpeed = 0.05f;//The speed at which the ship will change its frame when the key is pressed
	const float keyReleaseSpeed = 0.05f;//The speed at which the ship goes basck to the idle frame when the key is release
	int currentFrame;//The frame we'll render. It will take a value from the ShipFrames enumerator
	float const transitionLimit = 0.5f;//This indicates when the ship will transition from its idle animation to its transition animation
	float const MaxLimit = 0.90f;//This indicates when the ship will transition from its transition animation to its max animation
	enum ShipFrames
	{
		MaxUp,
		TransitionUp,
		Idle,
		TransitionDown,
		MaxDown
	};
	enum ShipAnimations
	{
		Initial,
		Movement,
		Death
	} shipAnimations;

	//Animations--------------------------------------------
	SDL_Rect *current_animation = nullptr; //pointer to the only one animation 
	Animation shipAnim;
	Animation shotFire; //Animation infront of ship when we are shooting basic shots
	Animation initAnim;
	Animation deathAnim;
	Animation ShotLaserBasic;
	//Textures---------------------------------------------
	SDL_Texture* PlayerTexture = nullptr;
	//Collision--------------------------------------------
	Collider* playerCol = nullptr;
	COLLIDER_TYPE shot_colType;

	//Win variables
	bool winlvl;
	int numLvlwin;
	void Winlvl();
	virtual void Winposition()=0; 
	bool start_timer;
	bool LaserPowerUp = false;
	int FadeToBlackAlfa;
	SDL_Rect backgroundBlack;
	

};

#endif
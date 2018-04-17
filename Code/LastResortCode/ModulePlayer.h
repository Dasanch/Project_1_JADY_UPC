#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h" 
#include "p2Point.h"

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
	update_status Update();
	bool CleanUp();
	void MovementInput(); //Added 
	void ShotInput(); //Added 
	void OnCollision(Collider*, Collider*);


public:
	//Animations--------------------------------------------
	SDL_Rect *current_animation = nullptr; //pointer to the only one animation 
	Animation shipPlayer1;
	Animation shotFire; //Animation infront of ship when we are shooting basic shots
	Animation initAnim;
	iPoint initAnim_p; //Initial animation pivot
	Animation deathAnim;
	//Textures---------------------------------------------
	SDL_Texture* PlayerTexture = nullptr;
	//Collision--------------------------------------------
	Collider* playerCol = nullptr;
	//Particles--------------------------------------------
	Particle death_explosion; //Death explosion 
	Particle basic_explosion; //Basic Shot Explosion
	Particle basicShot;
	//Audios-----------------------------------------------
	Mix_Chunk* basic_shot_sfx = nullptr;
	//Variables--------------------------------------------
	//--------Time---------------------------------
	//Time variables
	Uint32 start_time;
	Uint32 current_time;
	//--------Shots--------------------------------
	bool isShooting = false;
	bool shoot = false;
	//--------Movment------------------------------
	iPoint position;
	float const movementSpeed = 2;
	bool canMove;
	bool canShoot;
	//-------Animation-----------------------------
	int const playerwidth = 32;
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
		Movment,
		Death
	} shipAnimations;

public:
	//Functions that will be rewritten in each player
	//virtual void LoadSprites();
	virtual bool MoveUp() = 0;
	virtual bool MoveDown() = 0;
	virtual bool MoveLeft() = 0;
	virtual bool MoveRight() = 0;
	virtual bool Shoot() = 0;
};

#endif
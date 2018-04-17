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
	void OnCollision(Collider*, Collider*);

public:
	//Animations--------------------------------------------
	Animation* current_animation = nullptr;
	Animation shipPlayer1;
	Animation shotFire; //Animation infront of ship when we are shooting basic shots
	//Textures----------------------------------------------
	SDL_Texture* PlayerTexture = nullptr;
	//Collision-----------------------------------------
	Collider* playerCol = nullptr;
	//Particles----------------------------------------------
	Particle death_explosion; //Death explosion 
	Particle basic_explosion; //Basic Shot Explosion
	Particle basicShot;
	//Audios-------------------------------------------
	Mix_Chunk* basic_shot_sfx = nullptr;
	//Variables--------------------------------------------
	//-----------Shots-------------------------------------
	bool isShooting = false;
	bool shoot = false;
	//-----------Animation---------------------------------
	int const playerwidth = 32;
	iPoint position;
	float const movementSpeed = 2;
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
};

#endif
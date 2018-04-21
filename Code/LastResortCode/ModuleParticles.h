#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;
struct Mix_Chunk;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	SDL_Texture* texture = nullptr;
	Particle* collision_fx = nullptr;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, SDL_Texture *tex ,COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:
	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	//PLAYER------------------------------------------------
	Particle death_explosion; //Death explosion 
	Particle basic_explosion; //Basic Shot Explosion
	Particle basicShot;
	//GENERAL-----------------------------------------------
	Particle g_explosion01;
	Particle g_explosion02;
	Mix_Chunk* g_explosion01_1sfx = nullptr;
	//Mix_Chunk* g_explosion01_2sfx = nullptr;
	//Mix_Chunk* g_explosion01_3sfx = nullptr;
	Mix_Chunk* g_explosion02_1sfx = nullptr;
	//Mix_Chunk* g_explosion02_2sfx = nullptr;
	//Mix_Chunk* g_explosion02_3sfx = nullptr;
};

#endif // __MODULEPARTICLES_H__


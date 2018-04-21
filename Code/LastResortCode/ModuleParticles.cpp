#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
	//PLAYER-----------------------------------------------------------------//
	//Basic Shot Explosion Particle-----------------------------
	basic_explosion.anim.PushBack({ 305,263, 16,16 }); //1
	basic_explosion.anim.PushBack({ 287,263, 16,16 }); //2
	basic_explosion.anim.PushBack({ 285,247, 13,13 }); //3
	basic_explosion.anim.PushBack({ 271,263, 14,14 }); //4
	basic_explosion.anim.PushBack({ 300,247, 14,14 }); //5
	basic_explosion.anim.PushBack({ 316,247, 14,14 }); //6
	basic_explosion.anim.PushBack({ 217,247, 12,12 }); //7
	basic_explosion.anim.loop = false;
	basic_explosion.anim.speed = 0.3f;
	//Basic Shot Particle---------------------------------------
	basicShot.anim.PushBack({ 0,247, 15,7 });
	basicShot.anim.speed = 0.0f;
	basicShot.speed.x = 12;
	basicShot.anim.loop = false;
	basicShot.collision_fx = &basic_explosion;
	//Basic shot particle---------------------------------------
	unitShot.anim.PushBack({ 155, 288, 13, 13});
	unitShot.anim.PushBack({ 170, 288, 13, 13 });
	unitShot.anim.PushBack({ 155, 303, 13, 13 });
	unitShot.anim.PushBack({ 170, 303, 13, 13 });
	unitShot.anim.PushBack({ 155, 318, 13, 13 });
	unitShot.anim.PushBack({ 170, 318, 13, 13 });
	unitShot.anim.PushBack({ 155, 333, 13, 13 });
	unitShot.anim.PushBack({ 170, 333, 13, 13 });
	unitShot.anim.loop = true;
	unitShot.anim.speed = 0.3f;
	unitShot.collision_fx = &unit_explosion;
	//unitShot.speed.x = 5;
	//unitShot.speed.y = -5;//These speeds need to be changed depending in which way the orbit was when they were thrown
	//Basic shot explosion--------------------------------------
	unit_explosion.anim.PushBack({ 244, 263, 16, 16});
	unit_explosion.anim.PushBack({ 226, 263, 16, 16});
	unit_explosion.anim.PushBack({ 224, 247, 14, 14});
	unit_explosion.anim.PushBack({ 210, 263, 14, 14});
	unit_explosion.anim.PushBack({ 239, 247, 14, 14});
	unit_explosion.anim.PushBack({ 255, 247, 14, 14});
	unit_explosion.anim.PushBack({ 208, 247, 14, 14});
	unit_explosion.anim.loop = false;
	unit_explosion.anim.speed = 0.3f;
	//Death Explosion Particle----------------------------------
	for (int i = 0; i < 5; ++i) {
		death_explosion.anim.PushBack({ 244 + 32 * i ,288, 32,32 });
	}

	death_explosion.anim.speed = 0.2f;
	death_explosion.anim.loop = false;

	//GENERAL---------------------------------------------------------------//
	//General explosion 02 particle-----------------------------
	g_explosion02.anim.PushBack({ 0,0,32,32 });
	g_explosion02.anim.PushBack({ 32,0,32,32 });
	g_explosion02.anim.PushBack({ 64,0,16,16 });
	g_explosion02.anim.PushBack({ 80,0,20,20 });
	g_explosion02.anim.PushBack({ 100,0,25,25 });
	g_explosion02.anim.PushBack({ 0,32,26,26 });
	g_explosion02.anim.PushBack({ 26,32,32,32 });
	g_explosion02.anim.PushBack({ 58,32,32,32 });
	g_explosion02.anim.PushBack({ 90,32,32,32 });
	g_explosion02.anim.PushBack({ 0,64,32,32 });
	g_explosion02.anim.PushBack({ 32,64,32,32 });
	g_explosion02.anim.PushBack({ 64,64,32,32 });
	g_explosion02.anim.PushBack({ 96,64,32,32 });
	g_explosion02.anim.PushBack({ 0,96,31,32 });
	g_explosion02.anim.PushBack({ 31,96,30,32 });
	g_explosion02.anim.PushBack({ 61,96,30,32 });
	g_explosion02.anim.loop = false;
	g_explosion02.anim.speed = 0.3f;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading ModuleParticles assets ");
	//textures-------------------------------------------------
	graphics = App->textures->Load("Assets/General/Fx/Explosion_2.png");
	//particles-----------------------------------------------
	g_explosion02.texture = graphics;
	//audios--------------------------------------------------
	g_explosion01_1sfx = App->audio->LoadSFX("Assets/General/Fx/Explosion_1.wav");
	g_explosion02_1sfx = App->audio->LoadSFX("Assets/General/Fx/Explosion_2.wav");

	//--------------------------------------------------------
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	//textures--------------------------------------------------
	App->textures->Unload(graphics);
	//audios---------------------------------------------------

	//----------------------------------------------------------
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;
	
		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}

		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(p->texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				//App->audio->PlayFx(p->fx);
			}
		}

	}
	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, SDL_Texture *tex,  COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->texture = tex; // texture
			if (collider_type != COLLIDER_NONE)
				//Updated for not spawn it since 1 frame on x,y animation rect values
				p->collider = App->collision->AddCollider({p->position.x, p->position.y ,p->anim.GetCurrentFrame().w, p->anim.GetCurrentFrame().h }, collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if (active[i]->collision_fx != nullptr)
				AddParticle(*active[i]->collision_fx, active[i]->position.x, active[i]->position.y, active[i]->texture);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}
// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	collision_fx(p.collision_fx), born(p.born), life(p.life) , texture(p.texture) //struct texture added
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr) {
		collider->SetPos(position.x, position.y);
		if (collider->type == COLLIDER_PLAYER_SHOT && position.x > App->render->relative_camera.x + SCREEN_WIDTH) {
			ret = false;
		}
	}
	return ret;
}


#include "Application.h"
#include "MiddleBosslvl1.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"


//-------------------------------------------------------Torso--------------------------------------------------------------------------------------
Enemy_MetalCraw_Torso::Enemy_MetalCraw_Torso(int x, int y) : Enemy(x, y)
{
	torso.PushBack({ 138,372,42,59 });
	torso.PushBack({ 180,373,42,57 });
	torso.speed = 0.0f;
	animation = &torso;

	collider = App->collision->AddCollider({ 0, 6, 42, 42 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	lives = 20;
	start_time = SDL_GetTicks();
}

void Enemy_MetalCraw_Torso::Move()
{
	current_time = SDL_GetTicks() - start_time;
	if (current_time > 3700)
	{
		position.x += 1.0f;
		if(position.y>50)
		position.y -= 1.0f;
	}
	
	


}


//--------------------------------------------------------------------Arm---------------------------------------------------------------------------------------
Enemy_MetalCraw_Arm::Enemy_MetalCraw_Arm(int x, int y) : Enemy(x, y)
{
	Arm.PushBack({ 0,248,46,62 });
	Arm.PushBack({ 46,248,46,62 });
	Arm.PushBack({ 92,248,46,62 });
	Arm.PushBack({ 138,248,46,62 });
	Arm.PushBack({ 184,248,46,62 });
	Arm.speed = 0.2f;
	animation = &Arm;

	collider = App->collision->AddCollider({ 0, 6, 42, 42 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	lives = 20;
	start_time = SDL_GetTicks();
}
void Enemy_MetalCraw_Arm::Move()
{
	current_time = SDL_GetTicks() - start_time;
	if (current_time > 3700)
	{
		position.x += 1.0f;
		if (position.y>50)
			position.y -= 1.0f;
	}

}







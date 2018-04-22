
#include "Application.h"
#include "MiddleBosslvl1.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "Player1.h"
#include "Player2.h"
#include<math.h>

//-------------------------------------------------------Torso--------------------------------------------------------------------------------------
Enemy_MetalCraw::Enemy_MetalCraw(int x, int y, powerupType pu_t ) : Enemy(x, y, pu_t)
{
	torso.PushBack({ 254,373,42,54 });
	torso.PushBack({ 138,372,42,59 });
	torso.PushBack({ 180,373,42,57 });
	torso.speed = 0.0f;
	animation = &torso;

	Arm.PushBack({ 0,248,46,62 });
	Arm.PushBack({ 46,248,46,62 });
	Arm.PushBack({ 92,248,46,62 });
	Arm.PushBack({ 138,248,46,62 });
	Arm.PushBack({ 184,248,46,62 });
	Arm.speed = 0.2f;
	
	Leg = {222,406,18,24};

	Lights.PushBack({0,458,30,30});
	Lights.PushBack({ 30,458,30,30 });
	Lights.PushBack({ 60,458,30,30 });
	Lights.PushBack({ 90,458,30,30 });
	Lights.speed = 0.2f;

	collider = App->collision->AddCollider({ -97, 6, 42, 42 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	lives = 20;
	start_time = SDL_GetTicks();
	numparticles = 0;
}

void Enemy_MetalCraw::Move()
{
	current_time = SDL_GetTicks() - start_time;
	if (current_time > 3100 && current_time < 10000)
	{
		position.x += 1.0f;
		if(position.y>50)
		position.y -= 1.0f;
	}
	if (current_time > 5000)
	{
		numparticles += 1;
		if (numparticles <= 1)
		{
			App->particles->AddParticle(App->particles->MiddleBossShot, position.x-10, position.y-10, App->enemies->sprites, COLLIDER_ENEMY);
		App->particles->AddParticle(App->particles->MiddleBossShot, position.x+50, position.y+10, App->enemies->sprites, COLLIDER_ENEMY);
		App->particles->AddParticle(App->particles->MiddleBossShot, position.x-10, position.y+50, App->enemies->sprites, COLLIDER_ENEMY);
		App->particles->AddParticle(App->particles->MiddleBossShot, position.x+50, position.y+10, App->enemies->sprites, COLLIDER_ENEMY);
		}
		App->particles->VectorMiddleBossShots.x = (position.x - App->player1->position.x) / (sqrt  (pow(position.x - App->player1->position.x, 2) + pow(position.y - App->player1->position.y, 2) ));
		App->particles->VectorMiddleBossShots.y = (position.y - App->player1->position.y) / (sqrt(pow(position.x - App->player1->position.x, 2) + pow(position.y - App->player1->position.y, 2)));
		
	}
	if ( current_time > 20000)
	{
		position.x -= 1.0f;
	}
	


}
void  Enemy_MetalCraw::Draw(SDL_Texture* sprites)
{

	if (collider != nullptr)
		collider->SetPos(position.x, position.y + App->render->relative_camera.y);

	if (animation != nullptr)
	{
		App->render->Blit(sprites, position.x-9 , position.y + 9 + App->render->relative_camera.y, &(Lights.GetCurrentFrame()));
		App->render->Blit(sprites, position.x + 20, position.y + 9 + App->render->relative_camera.y, &(Lights.GetCurrentFrame()));

		App->render->Blit(sprites, position.x-43, position.y-6 + App->render->relative_camera.y, &(Arm.GetCurrentFrame()));
		App->render->FlippedBlit(sprites, position.x+ 39, position.y-6 + App->render->relative_camera.y, &(Arm.GetCurrentFrame()));
	

		App->render->Blit(sprites, position.x - 3, position.y + 35 + App->render->relative_camera.y, &Leg);
		App->render->FlippedBlit(sprites, position.x +27, position.y + 35 + App->render->relative_camera.y, &Leg);

		App->render->Blit(sprites, position.x, position.y + App->render->relative_camera.y, &(animation->GetCurrentFrame()));
	}
		

}


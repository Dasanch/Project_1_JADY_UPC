#include "Application.h"
#include "MiddleBosslvl1.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"


//-------------------------------------------------------Torso--------------------------------------------------------------------------------------
Enemy_MetalCraw::Enemy_MetalCraw(int x, int y) : Enemy(x, y)
{
	/*torso.PushBack({ 138,372,42,59 });*/
	torso.PushBack({ 180,373,42,57 });
	torso.speed = 0.0f;
	animation = &torso;

	Arm.PushBack({ 0,248,46,62 });
	Arm.PushBack({ 46,248,46,62 });
	Arm.PushBack({ 92,248,46,62 });
	Arm.PushBack({ 138,248,46,62 });
	Arm.PushBack({ 184,248,46,62 });
	Arm.speed = 0.2f;

	collider = App->collision->AddCollider({ -97, 6, 42, 42 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	lives = 20;
	start_time = SDL_GetTicks();
}

void Enemy_MetalCraw::Move()
{
	current_time = SDL_GetTicks() - start_time;
	if (current_time > 3000)
	{
		position.x += 1.0f;
		if(position.y>50)
		position.y -= 1.0f;
	}
	
	


}
void  Enemy_MetalCraw::Draw(SDL_Texture* sprites)
{

	if (collider != nullptr)
		collider->SetPos(position.x, position.y + App->render->relative_camera.y);

	if (animation != nullptr)
	{
		App->render->Blit(sprites, position.x-42, position.y-5 + App->render->relative_camera.y, &(Arm.GetCurrentFrame()));
		App->render->FlippedBlit(sprites, position.x+ 42, position.y-5 + App->render->relative_camera.y, &(Arm.GetCurrentFrame()));
		App->render->Blit(sprites, position.x, position.y + App->render->relative_camera.y, &(animation->GetCurrentFrame()));
	}
		

}


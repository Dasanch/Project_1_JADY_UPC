#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePowerups.h"
#include "Powerup.h"

ModulePowerups::ModulePowerups()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
		powerups[i] = nullptr;
}

ModulePowerups::~ModulePowerups()
{

}

bool ModulePowerups::Start()
{
	powerupTx = App->textures->Load("Assets/General/Enemies/PowerUps.png");
	return true;
}

update_status ModulePowerups::Update()
{
	//Move the powerups
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			powerups[i]->position.x -= 10;//Change to the speed in which the camera moves
		}
	}

	//Render the powerups
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			//- Collider
			if (powerups[i]->collider != nullptr)
			{
				//powerups[i]->collider->SetPos(powerups[i]->position.x, powerups[i]->position.y + App->render->relative_camera.y);
				//Causes an error. Needs to be fixed
			}
			//- Sprite
			if (powerups[i]->animation != nullptr)
			{
				App->render->Blit(powerupTx, powerups[i]->position.x, powerups[i]->position.y + App->render->relative_camera.y, &(powerups[i]->animation->GetCurrentFrame()));
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModulePowerups::PostUpdate()
{
	//Check camera position to decide what to despawn
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			if (powerups[i]->position.x  < App->render->relative_camera.x - DESPAWN_MARGIN)
			{
				LOG("DeSpawning powerup at %d", powerups[i]->position.x);
				delete powerups[i];
				powerups[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

bool ModulePowerups::CleanUp()
{
	LOG("Freeing all powerups");

	App->textures->Unload(powerupTx);

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			delete powerups[i];
			powerups[i] = nullptr;
		}
	}

	return true;
}

bool ModulePowerups::AddPowerup(powerupType type)
{
	bool ret = false;

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (queue[i].type == powerupType::NOPOWERUP)
		{
			queue[i].type = type;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModulePowerups::OnCollision(Collider* c1, Collider* c2)
{

}
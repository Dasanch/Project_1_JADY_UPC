#ifndef __ModulePowerups_H__
#define __ModulePowerups_H__

#include "Module.h"

#define MAX_POWERUPS 10
#define DESPAWN_MARGIN 50

//This module follows the structure of the module enemies
//But it doesn't spawn. It only moves, renders and despawns powerups
//Because powerups are spawned via AddPowerup when an enemy dies

enum powerupType
{
	NOPOWERUP,
	SPEED,
	DESPEED,
	LASER,
	HOMING,
	GROUND
};

class Powerup;
struct PowerupInfo
{
	powerupType type = powerupType::NOPOWERUP;
};
//We don't need x and y positions on powerupinfo (as opposed to enemy info) because we won't be checking their positions to spawn them
struct SDL_Texture;

class ModulePowerups : public Module
{
public:
	ModulePowerups();
	~ModulePowerups();

	bool Start();
	update_status Update();//We grab all our powerups and we render them
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddPowerup(powerupType);

private:
	PowerupInfo queue[MAX_POWERUPS];
	Powerup* powerups[MAX_POWERUPS];
	SDL_Texture* powerupTx = nullptr;
};
#endif
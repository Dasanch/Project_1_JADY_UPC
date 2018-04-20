#include "Module.h"
#define MAXPOWERUPS 50//The number of powerups this method can hold

enum powerupType
{
	noPowerup,
	speed,
	despeed,
	laser,
	homing,
	ground
};

class ModulePowerups : public Module
{
public:
	ModulePowerups();
	~ModulePowerups();

	bool Start();
	update_status Update();//We grab all our powerups and we render them
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddPowerup(powerupType, int, int);


private:
	//Powerup* powerups[];
	//SDL_Texture* powerupSprites;
};

class Powerup
{
	powerupType type = noPowerup;
	int x, y;
};
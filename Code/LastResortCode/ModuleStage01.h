#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
typedef struct _Mix_Music Mix_Music;

class ModuleStage01 : public Module
{
public:
	ModuleStage01();
	~ModuleStage01();

	bool Start();
	update_status Update();
	bool CleanUp();

	//Supportive functions
	void TakeTileMap();
	void TakeTunnelLights();
	void TakeBckLights();
	void TakeMidLights();
	void TakeStreetLights();
	void TakeOrangeLaser();
	void TakeBlueLaser();
public:
	uint randoms[27];
	uint frame;

	//Audios
	Mix_Music* music_01 = nullptr;

	SDL_Texture * groundAndTunel = nullptr;
	SDL_Texture* PurpleBuildings = nullptr;
	SDL_Texture* BackgroundBuildings = nullptr;
	SDL_Texture* Boss1Background = nullptr;

	//SDL_Texture* midgroundLightsTx = nullptr;
	SDL_Texture* LasersTx = nullptr;
	SDL_Texture* streetLightsTx = nullptr;
	SDL_Texture* midgndLightsTx = nullptr;
	SDL_Texture* bckgndLightsTx = nullptr;
	SDL_Texture* tunnelLightsTx = nullptr;

	SDL_Rect BGBuildings;
	SDL_Rect ground;
	SDL_Rect PBuildings;

	Animation tunnelLightsAnim;

	//Background lights
	Animation bckgndLightsAnim01;
	Animation bckgndLightsAnim02;
	Animation bckgndLightsAnim03;
	Animation bckgndLightsAnim04;
	Animation bckgndLightsAnim05;
	Animation bckgndLightsAnim06;

	//Middleground lights
	Animation midgndLightsAnim01;
	Animation midgndLightsAnim02;
	Animation midgndLightsAnim03;
	Animation midgndLightsAnim04;
	Animation midgndLightsAnim05;
	Animation midgndLightsAnim06;

	//Street Lights animation
	Animation streetLightsAnim01;
	Animation streetLightsAnim02;

	//Lasers animation
	Animation orangeLaserAnim;
	Animation blueLaserAnim;

	//Static enemy
	SDL_Texture* staticEnemyTx = nullptr;
};

#endif
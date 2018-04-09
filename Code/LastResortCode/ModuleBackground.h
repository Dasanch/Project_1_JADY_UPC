#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	uint randoms[27];
	uint frame;

	SDL_Texture * groundAndTunel = nullptr;
	SDL_Texture* PurpleBuildings = nullptr;
	SDL_Texture* BackgroundBuildings = nullptr;
	SDL_Texture* Boss1Background = nullptr;

	//SDL_Texture* midgroundLightsTx = nullptr;
	SDL_Texture* orangeLaserTx = nullptr;
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
	//Orange Laser animation
	Animation orangLaserAnim;
};

#endif
#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

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

	struct MoveUD {
		int xbetween_mov;
		int ymax_road;
		int ymin_road;
		//int ymax_road;
		int ymin_buildings;
		int ymax_buildings;
		//int ymin_road;
		int last_positionCam;
		int loop; //13?
		int maxloop;

		float vel_road;
		float vel_buildings;

		int yroadPos;
		int ymgPos;

		float temporalSubstraction;
		float temporalSubstractionBuildings;
	
		bool up;

	}MoveCamera;

	void MoveCam();

public:
	uint randoms[27];
	uint frame;
	//Audios
	Mix_Music* music_01 = nullptr;

	SDL_Texture* groundAndTunel = nullptr;
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
	Uint32 Start_time;
	Uint32 Current_time;

	//Move Camera
	Uint32 Start_time_y;
	Uint32 Current_time_y;
	bool stop_time;
	enum stateCam
	{
		CameraDown,
		CameraUp,
	};
	stateCam StatetCamY = CameraDown;
		bool up=false;
	bool down=false;
	bool cameraUp;
	bool cameraDown;

	//Win variables
	bool win;

	
	SDL_Rect backgroundBlack;
};

#endif
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleStage01;
class ModulePlayer;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleGameTitle;
class ModuleStageReady;
class Module2lvlScene;
class ModuleGameOver;
class ModuleContinue;
class ModuleNeoGeo;
class ModuleParticles;
class ModuleCollision;
class ModuleEnemies;


class Application
{
public:

	Module * modules[NUM_MODULES] = { nullptr };

	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleStage01* stage01 = nullptr;
	ModulePlayer* player = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleNeoGeo* neogeoScene = nullptr;
	ModuleGameTitle* titleScene = nullptr;
	ModuleStageReady* readyScene = nullptr;
	Module2lvlScene* stage02 = nullptr;
	ModuleGameOver* gameoverScene = nullptr;
	ModuleContinue* continueScene = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleCollision* collision = nullptr;
	

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__
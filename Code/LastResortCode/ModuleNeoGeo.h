#ifndef __MODULENEOGEO_H__
#define __MODULENEOGEO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#define NEOGEOWIDTH 227

struct SDL_Texture;
typedef struct _Mix_Music Mix_Music;

class ModuleNeoGeo : public Module
{
public:
	ModuleNeoGeo();
	~ModuleNeoGeo();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music * neogeoMusic = nullptr;

	//NEO GEO
	SDL_Texture * neogeoTx = nullptr;
	Animation neogeoAnim;
	const float neogeoAnimSpeed = 0.5f;

	//Max 330 Pro Gear Spec
	SDL_Texture * proGearSpecTx = nullptr;
	SDL_Rect proGearSpecRect;
	SDL_Rect blackCoverRect;
	int cover01PosX = 89;
	int cover02PosX = 89;
	int coverSpeed;

	//SNK
	SDL_Texture * snkTx = nullptr;
	Animation snkAnim;
	const int snkWidth = 72;
	const int snkHeight = 19;

	//Transition from white to black
	int currentFade = 255;
};

#endif // __MODULENEOGEO_H__

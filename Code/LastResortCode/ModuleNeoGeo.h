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
	enum AnimationStates
	{
		NeoGeo = 0,
		Max330ProGearSpecLine1,
		Max330ProGearSpecLine2,
		SNK,
		Finish
	};

	AnimationStates currentAnimation = NeoGeo;

	//NEO GEO
	SDL_Texture * neogeoTx = nullptr;
	Animation neogeoAnim;
	const float neogeoAnimSpeed = 0.5f;
	const int neogeoWidth = 230;
	const int neogeoHeight = 40;

	//Transition from white to black
	int currentFade = 255;

	//Max 330 Pro Gear Spec
	SDL_Texture * proGearSpecTx = nullptr;
	SDL_Rect proGearSpecRect;
	SDL_Rect blackCoverRect;
	int cover01PosX = 89;
	int cover02PosX = 89;
	int currentFrame = 0;
	const int frameLimit = 2;
	const int coverSpeed = 8;
	const int proGearSpecPosX = 89;
	const int proGearSpecWidth = 133;
	Uint32 startTime;
	Uint32 currentTime;

	//SNK
	SDL_Texture * snkTx = nullptr;
	Animation snkAnim;
	const int snkWidth = 72;
	const int snkHeight = 19;

	//Music
	Mix_Music * neogeoMusic = nullptr;
};

#endif // __MODULENEOGEO_H__

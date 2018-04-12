#ifndef __MODULENEOGEO_H__
#define __MODULENEOGEO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#define NEOGEOWIDTH 227

struct SDL_Texture;

class ModuleNeoGeo : public Module
{
public:
	ModuleNeoGeo();
	~ModuleNeoGeo();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * neogeoTx = nullptr;
	SDL_Rect neogeoRect;
	Animation neogeoAnim;

	//SDL_Texture * snkTx = nullptr;
	//SDL_Texture * proGearSpecTx = nullptr;
	//SDL_Rect snkRect;
	//SDL_Rect proGearSpecRect;
};

#endif // __MODULENEOGEO_H__

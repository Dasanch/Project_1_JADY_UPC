#ifndef _MODULEUI_H_
#define _MODULEUI_H_
#include "Module.h"
#include "Globals.h"
struct SDL_Texture;
struct SDL_Rect;
class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture *uiTex = nullptr;
	SDL_Rect lives_score_p1;
	SDL_Rect live_score_p2;
	SDL_Rect pow;
	SDL_Rect top;
	SDL_Rect push_p2;

};
#endif // !_MODULEUI_H_

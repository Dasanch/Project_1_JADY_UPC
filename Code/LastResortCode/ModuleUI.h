#ifndef _MODULEUI_H_
#define _MODULEUI_H_
#include "Module.h"
#include "Globals.h"

#define MAX_NUMBERS_SCORE 6

struct SDL_Texture;
struct SDL_Rect;
class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	void HideUi();
	void ShowUi();


public:
	Module* current_stage = nullptr;

	char *str_score_p1= nullptr;
	char *str_score_p2 = nullptr;
	char *str_lives_p1 = nullptr;
	char *str_lives_p2 = nullptr;
	//Player data---------------------------------
	int score_p1 =0;
	int score_p2= 0; 
	int lives_p1 =2;
	int lives_p2= 2;
	bool p1_isDead = false;
	bool p2_isDead = false;
	bool p1_Unit= false;
	bool p2_Unit = false;
	bool godMode = false;
	//General data--------------------------------
	int credits;
	bool showUI = true;
	//-------------------------------------------

	SDL_Texture *uiTex = nullptr;
	SDL_Rect lives_score_p1;
	SDL_Rect live_score_p2;
	SDL_Rect pow;
	SDL_Rect top;
	SDL_Rect push_p2;

};
#endif // !_MODULEUI_H_

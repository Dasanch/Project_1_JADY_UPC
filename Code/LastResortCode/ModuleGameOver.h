#ifndef _ModuleGameOver_H_
#define _ModuleGameOver_H_
#include "Module.h"
#include "Globals.h"
#include "Animation.h"
struct SDL_Texture;
typedef struct _Mix_Music Mix_Music;

class ModuleGameOver : public Module
{
public:
	ModuleGameOver();
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();
private:
	int whiteAlpha;
	SDL_Texture* gameover = nullptr;
	SDL_Rect white;
	Animation gameOverAnim;

};
#endif // !_ModuleGameOver_H_


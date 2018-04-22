#include "Globals.h"
#include "Application.h"
#include "ModuleGameTitle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Player1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStage01.h"
#include "ModuleAudio.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleStage02.h"



ModuleGameTitle::~ModuleGameTitle()
{}
bool ModuleGameTitle:: Start()
{
	LOG("Loading title assets");
	bool ret = true;
	start_time = SDL_GetTicks(); //fixed the real time that we start this module
	//textures--------------------------------------------------------------------------------
	L1Texture= App->textures->Load("Assets/LastResortTitle/L1Atlas.1.png");
	A2Texture = App->textures->Load("Assets/LastResortTitle/A2.png");
	S3Texture = App->textures->Load("Assets/LastResortTitle/S3.png");
	T4Texture = App->textures->Load("Assets/LastResortTitle/T4.png");
	R5Texture = App->textures->Load("Assets/LastResortTitle/R5.png");
	E6Texture = App->textures->Load("Assets/LastResortTitle/E6.png");
	S7Texture = App->textures->Load("Assets/LastResortTitle/S7.png");
	O8Texture = App->textures->Load("Assets/LastResortTitle/O8.png");
	R9Texture = App->textures->Load("Assets/LastResortTitle/R9.png"); //2LASTCHAR
	T10Texture = App->textures->Load("Assets/LastResortTitle/T10.png");
	//audios--------------------------------------------------------------------------------
	Titlemusic=App->audio->LoadMUS("Assets/LastResortTitle/02-LAST-RESORT-TITLE.ogg");
	App->audio->ControlMUS(Titlemusic, PLAY_AUDIO);
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	return ret;
}
bool ModuleGameTitle::CleanUp() {
	LOG("Unloading Title scene");
	App->player1->Disable();
	L1.Reset();
	A2.Reset();
	S3.Reset();
	T4.Reset();
	R5.Reset();
	E6.Reset();
	S7.Reset();
	O8.Reset();
	R9.Reset(); //2LASTCHAR
	T10.Reset();
	//textures----------------------------------------------------------------------
	
	App->textures->Unload(L1Texture);
	App->textures->Unload(A2Texture);
	App->textures->Unload(S3Texture);
	App->textures->Unload(T4Texture);
	App->textures->Unload(R5Texture);
	App->textures->Unload(E6Texture);
	App->textures->Unload(S7Texture);
	App->textures->Unload(O8Texture);
	App->textures->Unload(R9Texture);
	App->textures->Unload(T10Texture);
	//audios------------------------------------------------------------------------
	App->audio->ControlMUS(Titlemusic, STOP_AUDIO);
	App->audio->UnloadMUS(Titlemusic);

	return true;
}
update_status ModuleGameTitle::Update() {
	//timer------------------------------------------------------------------------
	current_time = SDL_GetTicks() - start_time; //current time init 0 and increment from star_time 

	//title letters---------------------------------------------------------------------
	/*App->render->Blit(A2Texture, 60, 30, &A2.frames[(int)currenA2], 0.0f);*/
	App->render->Blit(L1Texture, 56, 16, &L1.GetCurrentFrame(), 0.0f);
	if(current_time>300)
	App->render->Blit(A2Texture, 103, 15, &A2.GetCurrentFrame(), 0.0f);
	if (current_time>600)
	App->render->Blit(S3Texture, 164, 16, &S3.GetCurrentFrame(), 0.0f);
	if (current_time>900)
	App->render->Blit(T4Texture, 208, 13, &T4.GetCurrentFrame(), 0.0f);
	if (current_time>1200)
	App->render->Blit(R5Texture, 20, 88, &R5.GetCurrentFrame(), 0.0f);
	if (current_time>1500)
	App->render->Blit(E6Texture, 70, 88, &E6.GetCurrentFrame(), 0.0f);
	if (current_time>1800)
	App->render->Blit(S7Texture, 114, 88, &S7.GetCurrentFrame(), 0.0f);
	if (current_time>2100)
	App->render->Blit(O8Texture, 147, 85, &O8.GetCurrentFrame(), 0.0f);
	if (current_time>2400)
	App->render->Blit(R9Texture, 194, 88, &R9.GetCurrentFrame(), 0.0f);
	if (current_time>2600)
	App->render->Blit(T10Texture,  238,  85, &T10.GetCurrentFrame(), 0.0f);
	

	/*App->render->Blit(TitleTexture, ((SCREEN_WIDTH-LastResortRect.w)/2), ((SCREEN_HEIGHT - LastResortRect.h) / 2), &LastResortRect, 0.0f);*/

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN || current_time>18000) //refix it please 
	{
		App->fade->FadeToBlack(this, App->stage01, 0.0f);
	}
	if (App->input->keyboard[SDL_SCANCODE_F9] == KEY_DOWN) //refix it please 
	{
		App->fade->FadeToBlack(this, App->stage02, 0.0f);
	}
	// Win/Lose button
	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN) //win
	{
		App->fade->FadeToBlack(this, App->stageclearScene, 0.5f);
	}

	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_DOWN) //lose
	{
		App->fade->FadeToBlack(this, App->gameoverScene, 0.5f);
	}
	

	return UPDATE_CONTINUE;
}

ModuleGameTitle::ModuleGameTitle()
{
	L1.PushBack({ 144,398,13,25 }); //64
	L1.PushBack({ 128,398,14,37 });
	L1.PushBack({ 111,398,15,58 });
	L1.PushBack({ 69,398,20,76 });
	L1.PushBack({ 46,398,21,79 });
	L1.PushBack({ 23,398,21,83 });
	L1.PushBack({ 0,398,21,81 });
	L1.PushBack({ 484,273,21,92 });
	L1.PushBack({ 461,273,21,101 });
	L1.PushBack({ 436,273,23,102 });//55
	L1.PushBack({ 411,273,23,107 });
	L1.PushBack({ 386,273,23,96 });
	L1.PushBack({ 361,273,23,112 });
	L1.PushBack({ 336,273,23,114 });
	L1.PushBack({ 311,273,23,116 });
	L1.PushBack({ 286,273,23,117 });
	L1.PushBack({ 239,273,45,121 });
	L1.PushBack({ 192,273,45,122 });
	L1.PushBack({ 145,273,45,122 });
	L1.PushBack({ 98,273,45,123 });
	L1.PushBack({ 49,273,47,118 });
	L1.PushBack({ 0,273,47,106 });
	L1.PushBack({ 440,177,48,94 });//42
	L1.PushBack({ 390,177,48,88 });
	L1.PushBack({ 340,177,48,84 });
	L1.PushBack({ 291,177,47,77 });
	L1.PushBack({ 242,177,47,69 });
	L1.PushBack({ 193,177,47,66 });
	L1.PushBack({ 144,177,47,63 });
	L1.PushBack({ 96,177,46,60 });
	L1.PushBack({ 48,177,46,57 });
	L1.speed = speed;
	L1.loop = false;

	//A2---------------------------------------------------------------
	A2.PushBack({ 1,0,10,15 });
	A2.PushBack({ 11,0,12,24 });
	A2.PushBack({ 23,0,13,38 });
	A2.PushBack({ 36,0,13,45 });
	A2.PushBack({ 49,0,13,56 });
	A2.PushBack({ 62,0,13,63 });
	A2.PushBack({ 75,0,13,72 });
	A2.PushBack({ 88,0,13,80 });
	A2.PushBack({ 101,0,14,87 });
	A2.PushBack({ 115,0,19,92 });//10
	A2.PushBack({ 134,0,20,96 });
	A2.PushBack({ 154,0,22,100 });
	A2.PushBack({ 176,0,22,101 });
	A2.PushBack({ 198,0,24,106 });
	A2.PushBack({ 222,0,25,108 });
	A2.PushBack({ 256,0,30,112 });
	A2.PushBack({ 286,0,34,115 });
	A2.PushBack({ 320,0,38,114 });
	A2.PushBack({ 358,0,41,122 });
	A2.PushBack({ 399,0,47,122 });
	A2.PushBack({ 0,122,47,119 });
	A2.PushBack({ 47,122,47,106 });
	A2.PushBack({ 94,122,51,94 });
	A2.PushBack({ 145,122,51,84 });
	A2.PushBack({ 196,122,51,77 });
	A2.PushBack({ 247,122,51,71 });
	A2.PushBack({ 298,122,51,67 });
	A2.PushBack({ 349,122,51,63 });
	A2.PushBack({ 400,122,50,61 });
	A2.PushBack({ 0,241,50,60 });
	A2.PushBack({ 50,241,50,57 });
	A2.speed = speed;
	A2.loop = false;

	//S3--------------------------------------------------------
	S3.PushBack({ 0,0,14,20 });
	S3.PushBack({ 14,0,14,57 });
	S3.PushBack({ 28,0,23,70 });
	S3.PushBack({ 51,0,23,73 });
	S3.PushBack({ 74,0,24,79 });
	S3.PushBack({ 98,0,25,77 });
	S3.PushBack({ 123,0,29,89 });
	S3.PushBack({ 152,0,29,97 });
	S3.PushBack({ 181,0,29,100 });
	S3.PushBack({ 210,0,31,103 });
	S3.PushBack({ 210,0,31,103 });
	S3.PushBack({ 241,0,31,107 });
	S3.PushBack({ 272,0,31,110 });
	S3.PushBack({ 303,0,31,107 });
	S3.PushBack({ 334,0,31,114 });
	S3.PushBack({ 334,0,31,114 });
	S3.PushBack({ 365,0,31,115 });
	S3.PushBack({ 365,0,31,115 });
	S3.PushBack({ 0,115,31,118 });
	S3.PushBack({ 31,115,31,114 });
	S3.PushBack({ 62,115,31,120 });
	S3.PushBack({ 93,115,31,120 });
	S3.PushBack({ 124,115,32,122 });
	S3.PushBack({ 156,115,32,125 });
	S3.PushBack({ 188,115,32,123 });
	S3.PushBack({ 220,115,32,110 });
	S3.PushBack({ 252,115,32,101 });
	S3.PushBack({ 284,115,32,91 });
	S3.PushBack({ 316,115,32,83 });
	S3.PushBack({ 348,115,32,76 });
	S3.PushBack({ 380,115,32,69 });
	S3.PushBack({ 0,240,32,64 });
	S3.PushBack({ 32,240,32,61 });
	S3.PushBack({ 64,240,32,59 });
	S3.PushBack({ 96,240,32,58 });
	S3.loop = false;
	S3.speed = speed;

	//T4----------------------------------------------------------------------
	T4.PushBack({ 0,0,46,70 });
	T4.PushBack({ 46,0,46,73 });
	T4.PushBack({ 92,0,46,79 });
	T4.PushBack({ 138,0,46,84 });
	T4.PushBack({ 184,0,48,92 });
	T4.PushBack({ 232,0,48,93 });
	T4.PushBack({ 280,0,48,97 });
	T4.PushBack({ 328,0,48,103 });
	T4.PushBack({ 376,0,48,103 });
	T4.PushBack({ 424,0,48,109 });
	T4.PushBack({ 472,0,48,97 });
	T4.PushBack({ 0,109,48,114 });
	T4.PushBack({ 48,109,48,116 });
	T4.PushBack({ 96,109,48,118 });
	T4.PushBack({ 144,109,48,119 });
	T4.PushBack({ 192,109,48,120 });
	T4.PushBack({ 240,109,48,121 });
	T4.PushBack({ 288,109,48,117 });
	T4.PushBack({ 336,109,48,123 });
	T4.PushBack({ 384,109,48,123 });
	T4.PushBack({ 432,109,48,127 });
	T4.PushBack({ 480,109,48,128 });
	T4.PushBack({ 0,237,48,119 });
	T4.PushBack({ 48,237,48,108 });
	T4.PushBack({ 96,237,48,101 });
	T4.PushBack({ 144,237,46,90 });
	T4.PushBack({ 190,237,46,81 });
	T4.PushBack({ 236,237,46,73 });
	T4.PushBack({ 282,237,46,66 });
	T4.PushBack({ 328,237,46,62 });
	T4.PushBack({ 374,237,46,61 });
	T4.PushBack({ 420,237,46,59 });
	T4.speed = speed;
	T4.loop = false;
	//R5------------------------------------------------
	R5.PushBack({ 0,0,31,61 });
	R5.PushBack({ 31,0,31,69 });
	R5.PushBack({ 62,0,38,76 });
	R5.PushBack({ 100,0,39,81 });
	R5.PushBack({ 139,0,39,87 });
	R5.PushBack({ 178,0,39,89 });
	R5.PushBack({ 217,0,43,92 });
	R5.PushBack({ 260,0,45,100 });
	R5.PushBack({ 305,0,45,103 });
	R5.PushBack({ 350,0,45,106 });
	R5.PushBack({ 395,0,45,112 });
	R5.PushBack({ 440,0,45,112 });
	R5.PushBack({ 0,112,45,114 });
	R5.PushBack({ 45,112,45,118 });
	R5.PushBack({ 90,112,45,118 });
	R5.PushBack({ 135,112,45,119 });
	R5.PushBack({ 180,112,45,116 });
	R5.PushBack({ 225,112,45,122 });
	R5.PushBack({ 270,112,45,123 });
	R5.PushBack({ 315,112,45,122 });
	R5.PushBack({ 360,112,45,125 });
	R5.PushBack({ 405,112,45,123 });
	R5.PushBack({ 450,112,45,114 });
	R5.PushBack({ 0,237,45,102 });
	R5.PushBack({ 45,237,46,91 });
	R5.PushBack({ 91,237,46,83 });
	R5.PushBack({ 137,237,47,75 });
	R5.PushBack({ 184,237,47,68 });
	R5.PushBack({ 231,237,47,63 });
	R5.PushBack({ 278,237,47,60 });
	R5.PushBack({ 325,237,48,59 });
	R5.PushBack({ 373,237,48,58 });
	R5.speed = speed;
	R5.loop = false;
	//E6------------------------------------------------
	E6.PushBack({ 0,0,37,58 });
	E6.PushBack({ 37,0,39,61 });
	E6.PushBack({ 76,0,40,69 });
	E6.PushBack({ 116,0,40,73 });
	E6.PushBack({ 156,0,41,79 });
	E6.PushBack({ 197,0,41,83 });
	E6.PushBack({ 238,0,41,92 });
	E6.PushBack({ 279,0,41,97 });
	E6.PushBack({ 320,0,41,97 });
	E6.PushBack({ 361,0,41,104 });
	E6.PushBack({ 402,0,41,107 });
	E6.PushBack({ 443,0,41,110 });
	E6.PushBack({ 0,110,41,112 });
	E6.PushBack({ 41,110,41,114 });
	E6.PushBack({ 82,110,41,116 });
	E6.PushBack({ 123,110,41,118 });
	E6.PushBack({ 164,110,41,119 });
	E6.PushBack({ 205,110,41,120 });
	E6.PushBack({ 246,110,41,121 });
	E6.PushBack({ 287,110,41,122 });
	E6.PushBack({ 328,110,41,125 });
	E6.PushBack({ 369,110,41,119 });
	E6.PushBack({ 410,110,44,112 });
	E6.PushBack({ 454,110,44,99 });
	E6.PushBack({ 0,235,44,88 });
	E6.PushBack({ 44,235,44,78 });
	E6.PushBack({ 88,235,44,70 });
	E6.PushBack({ 132,235,44,65 });
	E6.PushBack({ 176,235,44,61 });
	E6.PushBack({ 220,235,44,60 });
	E6.PushBack({ 264,235,43,59 });
	E6.PushBack({ 307,235,42,57 });
	E6.PushBack({ 349,235,42,57 });
	E6.speed = speed;
	E6.loop = false;

	//S7---------------------------------------------
	S7.PushBack({ 0,0,14,28 });
	S7.PushBack({ 14,0,14,57 });
	S7.PushBack({ 28,0,23,70 });
	S7.PushBack({ 51,0,23,73 });
	S7.PushBack({ 74,0,24,79 });
	S7.PushBack({ 98,0,25,77 });
	S7.PushBack({ 123,0,29,89 });
	S7.PushBack({ 152,0,29,97 });
	S7.PushBack({ 181,0,29,100 });
	S7.PushBack({ 181,0,29,100 });
	S7.PushBack({ 210,0,31,103 });
	S7.PushBack({ 241,0,31,107 });
	S7.PushBack({ 272,0,31,110 });
	S7.PushBack({ 303,0,31,107 });
	S7.PushBack({ 334,0,31,114 });
	S7.PushBack({ 365,0,31,115 });
	S7.PushBack({ 396,0,31,118 });
	S7.PushBack({ 427,0,31,114 });
	S7.PushBack({ 458,0,31,120 });
	S7.PushBack({ 0,120,31,120 });
	S7.PushBack({ 31,120,32,122 });
	S7.PushBack({ 63,120,32,125 });
	S7.PushBack({ 95,120,32,123 });
	S7.PushBack({ 127,120,32,110 });
	S7.PushBack({ 159,120,32,101 });
	S7.PushBack({ 191,120,32,91 });
	S7.PushBack({ 223,120,32,83 });
	S7.PushBack({ 255,120,32,76 });
	S7.PushBack({ 287,120,32,69 });
	S7.PushBack({ 319,120,32,64 });
	S7.PushBack({ 351,120,32,61 });
	S7.PushBack({ 383,120,32,59 });
	S7.PushBack({ 415,120,32,58 });
	S7.speed = speed;
	S7.loop = false;
	//O8------------------------------
	O8.PushBack({ 0,0,20,58 });
	O8.PushBack({ 20,0,20,66 });
	O8.PushBack({ 40,0,28,76 });
	O8.PushBack({ 68,0,29,79 });
	O8.PushBack({ 97,0,34,84 });
	O8.PushBack({ 131,0,34,89 });
	O8.PushBack({ 165,0,35,96 });
	O8.PushBack({ 200,0,37,99 });
	O8.PushBack({ 237,0,38,104 });
	O8.PushBack({ 275,0,44,106 });
	O8.PushBack({ 319,0,44,109 });
	O8.PushBack({ 368,0,44,111 });
	O8.PushBack({ 0,111,45,114 });
	O8.PushBack({ 45,111,45,118 });
	O8.PushBack({ 90,111,46,120 });
	O8.PushBack({ 136,111,46,121 });
	O8.PushBack({ 182,111,46,120 });
	O8.PushBack({ 228,111,48,123 });
	O8.PushBack({ 276,111,48,122 });
	O8.PushBack({ 324,111,48,122 });
	O8.PushBack({ 372,111,48,126 });
	O8.PushBack({ 0,237,50,122 });
	O8.PushBack({ 50,237,50,116 });
	O8.PushBack({ 100,237,50,104 });
	O8.PushBack({ 150,237,50,192 });
	O8.PushBack({ 200,237,50,82 });
	O8.PushBack({ 250,237,49,74 });
	O8.PushBack({ 299,237,49,68 });
	O8.PushBack({ 348,237,49,63 });
	O8.PushBack({ 0,359,48,61 });
	O8.PushBack({ 48,359,48,61 });
	O8.PushBack({ 48,359,48,60 });
	O8.PushBack({ 96,359,48,59 });
	O8.speed = speed;
	O8.loop = false;
	//R9------------------------------ //2LASTCHAR
	R9.PushBack({ 186,902,31,61 });
	R9.PushBack({ 155,902,31,69 });
	R9.PushBack({ 117,902,38,76 });
	R9.PushBack({ 78,902,39,81 });
	R9.PushBack({ 39,902,39,87 });
	R9.PushBack({ 0,902,39,89 });
	R9.PushBack({ 180,790,43,92 });
	R9.PushBack({ 135,790,45,100 });
	R9.PushBack({ 90,790,45,103 });
	R9.PushBack({ 45,790,45,106 });
	R9.PushBack({ 0,790,45,112 });
	R9.PushBack({ 180,671,45,112 });
	R9.PushBack({ 135,671,45,114 });
	R9.PushBack({ 90,671,45,118 });
	R9.PushBack({ 45,671,45,118 });
	R9.PushBack({ 0,671,45,119 });
	R9.PushBack({ 180,546,45,116 });
	R9.PushBack({ 135,546,45,122 });
	R9.PushBack({ 90,546,45,123 });
	R9.PushBack({ 45,546,45,122 });
	R9.PushBack({ 0,546,45,125 });
	R9.PushBack({ 182,423,45,123 });
	R9.PushBack({ 137,423,45,114 });
	R9.PushBack({ 92,423,45,102 });
	R9.PushBack({ 46,423,46,91 });
	R9.PushBack({ 0,423,46,83 });
	R9.PushBack({ 189,348,47,75 });
	R9.PushBack({ 142,348,47,68 });
	R9.PushBack({ 95,348,47,63 });
	R9.PushBack({ 48,348,47,60 });
	R9.PushBack({ 0,348,48,59 });
	R9.PushBack({ 192,290,48,58 });
	R9.speed = speed;
	R9.loop = false;

	//T10------------------------------  //2LASTCHAR
	T10.PushBack({ 330,374,46,70 });
	T10.PushBack({ 284,374,46,73 });
	T10.PushBack({ 238,374,46,79 });
	T10.PushBack({ 192,374,46,84 });
	T10.PushBack({ 144,374,48,92 });
	T10.PushBack({ 96,374,48,93 });
	T10.PushBack({ 48,374,48,97 });
	T10.PushBack({ 0,374,48,103 });
	T10.PushBack({ 432,253,48,103 });
	T10.PushBack({ 384,253,48,109 });
	T10.PushBack({ 336,253,48,97 });
	T10.PushBack({ 288,253,48,114 });
	T10.PushBack({ 240,253,48,116 });
	T10.PushBack({ 192,253,48,118 });
	T10.PushBack({ 144,253,48,119 });
	T10.PushBack({ 96,253,48,120 });
	T10.PushBack({ 48,253,48,121 });
	T10.PushBack({ 0,253,48,117 });
	T10.PushBack({ 426,125,48,123 });
	T10.PushBack({ 378,125,48,123 });
	T10.PushBack({ 330,125,48,127 });
	T10.PushBack({ 282,125,48,128 });
	T10.PushBack({ 234,125,48,119 });
	T10.PushBack({ 186,125,48,108 });
	T10.PushBack({ 138,125,48,101 });
	T10.PushBack({ 92,125,46,90 });
	T10.PushBack({ 46,125,46,81 });
	T10.PushBack({ 0,125,46,73 });
	T10.PushBack({ 460,59,46,66 });
	T10.PushBack({ 414,59,46,62 });
	T10.PushBack({ 368,59,46,61 });
	T10.PushBack({ 322,59,46,61 });
	T10.PushBack({ 276,59,46,59 });
	T10.speed = speed;
	T10.loop = false;

}
#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class Animation
{
public:
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];
	float current_frame = 0;
	int last_frame = 0;

	bool invert = false;
	bool first_loop = true;
public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}
	SDL_Rect&  ReturnFrame(int i)
	{
		return frames[i];
	}
	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= last_frame)
			current_frame = 0;
		return frames[(int)current_frame];
	}

	SDL_Rect& GetFrame()
	{
		return frames[(int)current_frame];
	}
	SDL_Rect& AddFrame(uint added_frames)
	{
		uint i = 0;
		float frame = current_frame;
		while (i < added_frames) {
			++frame;
			if (frame >= last_frame)
				frame = 0;
			++i;
		}
		return frames[(int)frame];
	}

	SDL_Rect& LoopAnimation()
	{
		if (first_loop) {
			first_loop = false;
			return frames[0];
		}
		else {
			if (invert == false) {

				if (current_frame >= last_frame) {
					current_frame = last_frame -0.1f ;
					invert = true;
				}
				else
					current_frame += speed;
			}
			else {
				if (current_frame < 0) {
					current_frame = 0;
					invert = false;
				}
				else
					current_frame -= speed;
			}
		}
		return frames[(int)current_frame];
	}
};

#endif
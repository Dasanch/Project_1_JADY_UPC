#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class Animation
{
public:
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

private:
	float current_frame;
	int last_frame = 0;

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
	SDL_Rect& GetFrame(uint random)
	{
		uint i = 0;
		float frame = current_frame;
		while (i < random) {
			++frame;
			if (frame > last_frame)
				frame = 0;
			++i;
		}
		return frames[(int)frame];
	}

};

#endif
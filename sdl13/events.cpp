#include <SDL/SDL.h>
#include "events.h"

void GetEvents(bool keybuffer[SDL_NUM_SCANCODES], bool mouse[16])
{
	SDL_Event e;

	SDL_PollEvent(&e);
	if (e.type == SDL_KEYDOWN)
	{
		for (int i = 0; i <= SDL_NUM_SCANCODES; i++)
		{
			if (e.key.keysym.scancode == i)
			{
				keybuffer[i] = true;
			}
			else
			{
				keybuffer[i] = false;
			}
		}
		

	}

	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		for (int i = 0; i <= 16; i++)
		{
			if (e.button.button == i)
			{
				mouse[i] = true;
			}
			else
			{
				mouse[i] = false;
			}
		}

	}

}
// sdl13.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"
#include <SDL/SDL.h>
#undef main


int main()
{
	bool quit = false;
	int i = 0;

	// SDL Events
	SDL_Event e;


	SDL_Surface* m_surface = NULL; // create surface object, referenced by pointer
	m_surface = SDL_LoadBMP("");
	SDL_Renderer* renderer; // create renderer object, reference by pointer
	SDL_Init(SDL_INIT_EVERYTHING); // initialize all SDL layers
	SDL_Window* screen = SDL_CreateWindow("SDL Demo", // create our window objecdt reference by pointer, with Title
		SDL_WINDOWPOS_UNDEFINED, // x position
		SDL_WINDOWPOS_UNDEFINED, // y position
		640, 480, // width , height
		SDL_WINDOW_OPENGL); // window flags
	while(!quit)
	{
		renderer = SDL_CreateRenderer(screen, -1, 0); // make renderer-type object from screen, assign to renderer object
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // object, r,g,b, alpha
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // object, r,g,b, alpha
		rhombus *rhombus1 = new rhombus(30, 30, 400, 200);
		
		rhombus1->drawRhombus(renderer, *rhombus1 );
		SDL_BlitSurface(m_surface, NULL, m_surface, NULL);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, m_surface);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer); // show
		SDL_Delay(5);

		while (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_Q)
				{
					quit = true;
				}
			}
		
	}

	SDL_Delay(500);
	SDL_FreeSurface(m_surface);
	SDL_Quit();


    return 0;
}


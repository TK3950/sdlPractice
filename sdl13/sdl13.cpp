// sdl13.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"
#include <list>
#include <SDL/SDL.h>
#undef main



void UpdateScreen(SDL_Renderer* re, SDL_Surface* surf)
{
	SDL_BlitSurface(surf, NULL, surf, NULL);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(re, surf);
	SDL_RenderCopy(re, texture, NULL, NULL);
	SDL_RenderPresent(re); // show
	SDL_Delay(5);
}



void SetRhombuses(SDL_Renderer* re, std::list<rhombus*> rhombuses)
{
	SDL_SetRenderDrawColor(re, 0, 0, 0, 255); // object, r,g,b, alpha
	if (!(rhombuses.empty()))
	{
		rhombuses.front()->rhombus::drawRhombus(re, *rhombuses.front());
	}
}

void SetRectangles(SDL_Renderer* re, std::list<rectangle*> rectangles)
{

	SDL_SetRenderDrawColor(re, 0, 0, 0, 255); // object, r,g,b, alpha
	if (!(rectangles.empty()))
	{
		rectangles.front()->rectangle::drawRectangle(re, *rectangles.front());
	}
}

void SetBackground(SDL_Renderer* re)
{
	SDL_SetRenderDrawColor(re, 255, 255, 255, 255); // object, r,g,b, alpha
	SDL_RenderClear(re);
}



int main()
{
	bool quit = false;
	SDL_Event e;
	SDL_Surface* m_surface = NULL; // create surface object, referenced by pointer
	SDL_Renderer* renderer = NULL; // create renderer object, reference by pointer
	SDL_Init(SDL_INIT_EVERYTHING); // initialize all SDL layers
	SDL_Window* screen = SDL_CreateWindow("SDL Demo", // create our window objecdt reference by pointer, with Title
		SDL_WINDOWPOS_UNDEFINED, // x position
		SDL_WINDOWPOS_UNDEFINED, // y position
		640, 480, // width , height
		SDL_WINDOW_OPENGL); // window flags
	m_surface = SDL_LoadBMP("");
	renderer = SDL_CreateRenderer(screen, -1, 0); // make renderer-type object from screen, assign to renderer object

	std::list<rhombus*> rhombuses;
	std::list<rectangle*> rectangles;

	while (!quit)
	{
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_Q)
			{
				quit = true;
			}
		}

		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_RIGHT)
			{
				rhombus *r1 = new rhombus(0, 0, 100, 50);
				rhombuses.push_front(r1);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Information", "You right-clicked! This adds a rhombus!", screen);
				
			}

			if (e.button.button == SDL_BUTTON_LEFT)
			{
				rectangle *r1 = new rectangle(0, 0, 100, 50);
				rectangles.push_front(r1);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Information", "You left-clicked! This adds a rectangle!", screen);

			}

		}
		SetBackground(renderer);
		SetRhombuses(renderer, rhombuses);
		SetRectangles(renderer, rectangles);
		UpdateScreen(renderer, m_surface);
	}
	SDL_Delay(500);
	SDL_FreeSurface(m_surface);
	SDL_Quit();


    return 0;
}


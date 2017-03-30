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



void SetShapes(SDL_Renderer* re, std::list<shape*> shapes)
{
	SDL_SetRenderDrawColor(re, 0, 0, 0, 255); // object, r,g,b, alpha
	if (!(shapes.empty()))
	{
		shapes.front()->shape::drawShape(re, shapes.front());
	}

}

void ClearAll(SDL_Renderer* re)
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
	ClearAll(renderer);
	std::list<shape*> shapes;

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
				shape *r1 = new shape(shape::TK_RHOMBUS, 10, 10, 100, 50);
				shapes.push_front(r1);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Information", "You right-clicked! This adds a rhombus!", screen);
				
			}

			if (e.button.button == SDL_BUTTON_LEFT)
			{
				shape *r1 = new shape(shape::TK_RECTANGLE, 0, 0, 100, 50);
				shapes.push_front(r1);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Information", "You left-clicked! This adds a rectangle!", screen);

			}

		}
		
		SetShapes(renderer, shapes);
		UpdateScreen(renderer, m_surface);
	}
	SDL_Delay(500);
	SDL_FreeSurface(m_surface);
	SDL_Quit();


    return 0;
}


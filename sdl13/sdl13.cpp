// sdl13.cpp : Defines the entry point for the console application.
// 

// TODO: create a clean buffer for handling events, i.e. a keypress buffer

#include "stdafx.h"
#include <list>
#include <SDL/SDL.h>
#undef main


#define TK_WINDOW_WIDTH 1000
#define TK_WINDOW_HEIGHT 680


void UpdateScreen(SDL_Renderer* re, SDL_Surface* surf)
{
	SDL_BlitSurface(surf, NULL, surf, NULL);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(re, surf);
	SDL_RenderCopy(re, texture, NULL, NULL);
	SDL_RenderPresent(re); // show
	SDL_Delay(5);
}



void SetShapes(SDL_Renderer* re, std::list<shape*> shapes) // Simple method to render all shapes in a non-empty list
{
	SDL_SetRenderDrawColor(re, 0, 0, 0, 255); // object, r,g,b, alpha
	if (!(shapes.empty()))
	{
		for (std::list<shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
		{
			shapes.front()->shape::drawShape(re, *it);
		}
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
		TK_WINDOW_WIDTH, TK_WINDOW_HEIGHT, // width , height
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

			if (e.key.keysym.scancode == SDL_SCANCODE_D)
			{
				if (shapes.front()->posx < TK_WINDOW_WIDTH)
				{
					shapes.front()->posx = shapes.front()->posx + 1;
				}
			}

			if (e.key.keysym.scancode == SDL_SCANCODE_A)
			{
				if (shapes.front()->posx > 0)
				{
					shapes.front()->posx = shapes.front()->posx - 1;
				}
			}

			if (e.key.keysym.scancode == SDL_SCANCODE_S)
			{
				if (shapes.front()->posy < TK_WINDOW_HEIGHT)
				{
					shapes.front()->posy = shapes.front()->posy + 1;
				}
			}

			if (e.key.keysym.scancode == SDL_SCANCODE_W)
			{
				if (shapes.front()->posy > 0)
				{
					shapes.front()->posy = shapes.front()->posy - 1;
				}
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
		
		ClearAll(renderer);
		SetShapes(renderer, shapes);
		UpdateScreen(renderer, m_surface);
	}
	SDL_Delay(500);
	SDL_FreeSurface(m_surface);
	SDL_Quit();


    return 0;
}


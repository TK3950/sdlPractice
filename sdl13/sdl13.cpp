// sdl13.cpp : Defines the entry point for the console application.
// 

// TODO: create a clean buffer for handling events, i.e. a keypress buffer

#include "stdafx.h"
#include <list>
#include <SDL/SDL.h>
#include "events.h"
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
		GetEvents(keybuffer ,mousebuffer);
		
		ClearAll(renderer);
		SetShapes(renderer, shapes)
		UpdateScreen(renderer, m_surface);
	}
	SDL_Delay(500);
	SDL_FreeSurface(m_surface);
	SDL_Quit();


    return 0;
}


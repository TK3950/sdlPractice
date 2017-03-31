// sdl13.cpp : Defines the entry point for the console application.
// 

// TODO: create a clean buffer for handling events, i.e. a keypress buffer

#include "stdafx.h"
#include <list>
#include <SDL/SDL.h>
#include "events.h"
#include "tksdl.h"
#undef main


#define TK_WINDOW_WIDTH 1000
#define TK_WINDOW_HEIGHT 680






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
#pragma region Generic Variables.
	bool quit = false;
	bool keybuffer[SDL_NUM_SCANCODES];
	bool mousebuffer[16];
#pragma endregion


#pragma region SDL Setup
	SDL_Renderer* r = NULL;
	SDL_Surface* s = NULL;
	SDL_Window* w = NULL;
	SDL_Event* e = NULL;
	std::list<shape*> sh;
	TKSCENE *scene = new TKSCENE(r,  s,  w,  e, sh);
	
#pragma endregion

	
	ClearAll(scene->rr);
	shape *r1 = new shape(shape::TK_RECTANGLE, 0, 0, 100, 50);
	scene->shapes.push_front(r1);

	while (!quit)
	{
		//GetAllEvents(keybuffer ,mousebuffer);
		
		ClearAll(scene->rr);
		SetShapes(scene->rr, scene->shapes);
		scene->shapes.front()->posx = scene->shapes.front()->posx + 1;
		scene->UpdateScreen(scene->rr, scene->ss);
		SDL_Delay(50);
	}
	SDL_Delay(500);
	SDL_FreeSurface(scene->ss);
	SDL_Quit();


    return 0;
}


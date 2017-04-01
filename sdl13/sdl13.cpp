// sdl13.cpp : Defines the entry point for the console application.
// 

// TODO: create a clean buffer for handling events, i.e. a keypress buffer


#include <list>
#include <SDL/SDL.h>
#include "tksdl.h"
#undef main


#define TK_WINDOW_WIDTH 1000
#define TK_WINDOW_HEIGHT 680



extern bool TK_QUIT = false;


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



#pragma region SDL Setup
	SDL_Renderer* r = NULL;
	SDL_Surface* s = NULL;
	SDL_Window* w = NULL;
	SDL_Event e;
	std::list<shape*> sh;
	TKSCENE *scene = new TKSCENE(r,  s,  w,  &e, sh);
	
#pragma endregion

	
	ClearAll(scene->rr);
	SetShapes(scene->rr, scene->shapes);
	scene->UpdateScreen(scene->rr, scene->ss); // first display

	while (!TK_QUIT)
	{
		int response = GetAllEvents(scene);
		TK_QUIT = (response == 20) ? true : false;
		
		if (true) // find a way to call this only when needed. i.e. when the scene has changed
		{
			ClearAll(scene->rr);
			SetShapes(scene->rr, scene->shapes);
			scene->UpdateScreen(scene->rr, scene->ss); // we should only call if something changed
			SDL_Delay(5); // just a small thread delay, remove if it gets slow
		}

	}
	SDL_Delay(500);
	SDL_FreeSurface(scene->ss);
	SDL_Quit();


    return 0;
}


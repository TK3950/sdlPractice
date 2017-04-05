// sdl13.cpp : Defines the entry point for the console application.
// 

// TODO: create a clean buffer for handling events, i.e. a keypress buffer


#include <list>
#include <SDL/SDL.h>
#include "tksdl.h"
#include <windows.h>
#undef main


#define TK_WINDOW_WIDTH 1000
#define TK_WINDOW_HEIGHT 680



extern bool TK_QUIT = false;



void SetShapes(SDL_Renderer* re, color* pc, color* sc, color* ac, std::vector<shape*> shapes) // Simple method to render all shapes in a non-empty list
{
	
	if (!(shapes.empty()))
	{
		for (unsigned int i = 0; i < shapes.size(); ++i)
		{
			// look for shapes that escape our bounds
			// and return them to within the bounds
			if (shapes.at(i)->posx < 0)
			{
				shapes.at(i)->posx = 0;
			}
			if (shapes.at(i)->posx+shapes.at(i)->width > TK_WINDOW_WIDTH)
			{
				shapes.at(i)->posx = TK_WINDOW_WIDTH - shapes.at(i)->width;
			}

			if (shapes.at(i)->posy < 0)
			{
				shapes.at(i)->posy = 0;
			}
			if (shapes.at(i)->posy + shapes.at(i)->height > TK_WINDOW_HEIGHT)
			{
				shapes.at(i)->posy = TK_WINDOW_HEIGHT - shapes.at(i)->height;
			}

			if (i + 1 == shapes.size())
			{
				shapes.front()->shape::drawShape(re, ac, shapes.at(i)); // draw current shape into renderer
			}
			else
			{
				shapes.front()->shape::drawShape(re, pc, shapes.at(i)); // draw current shape into renderer
			}
		}
	}

}


void ClearAll(SDL_Renderer* re, color* pc, color* sc, color* ac, std::vector<shape*> shapes)
{
	SDL_SetRenderDrawColor(re, 255, 255, 255, 255);
	SDL_RenderClear(re);

}

int main()
{



#pragma region SDL Setup
	SDL_Renderer* r = NULL;
	SDL_Surface* s = NULL;
	SDL_Window* w = NULL;
	SDL_Event e;
	std::vector<shape*> sh;
	color* pc = new color(0, 0, 0, 255);
	color* sc = new color(255, 255, 255, 255);
	color* ac = new color(200, 20, 20, 255);
	TKSCENE *scene = new TKSCENE(r,  s,  w,  &e, sh, pc, sc);
	
#pragma endregion
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	SDL_RenderClear(r);
	ClearAll(scene->rr, pc, sc, ac, scene->shapes);
	SetShapes(scene->rr, scene->PrimaryColor, scene->SecondaryColor, ac, scene->shapes);
	scene->UpdateScreen(scene->rr, scene->ss); // first display
	
	while (!TK_QUIT)
	{
		int response = GetAllEvents(scene);
		TK_QUIT = (response == 20) ? true : false;
		

		// consider making all re-render events return odd, and all no-render events return even, then check event response
		if (response != 0) 
		{
			ClearAll(scene->rr, pc, sc, ac, scene->shapes);
			SetShapes(scene->rr, scene->PrimaryColor, scene->SecondaryColor, ac, scene->shapes);
			scene->UpdateScreen(scene->rr, scene->ss); // first display
			//SDL_Delay(5); // just a small thread delay, remove if it gets slow
		}

	}
	SDL_Delay(500);
	SDL_FreeSurface(scene->ss);
	SDL_Quit();


    return 0;
}


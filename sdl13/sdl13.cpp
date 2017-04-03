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


void SetShapes(SDL_Renderer* re, std::vector<shape*> shapes) // Simple method to render all shapes in a non-empty list
{
	SDL_SetRenderDrawColor(re, 0, 0, 0, 255); // object, r,g,b, alpha
	if (!(shapes.empty()))
	{
		for (unsigned int i = 0; i < shapes.size(); ++i)
		{
			// look for shapes that escape our bounds

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


			shapes.front()->shape::drawShape(re, shapes.at(i)); // draw current shape into renderer
		}
	}

}

void SetMenus(SDL_Renderer* re, std::vector<menu*> menus)
{
	if (!menus.empty())
	{
		menus.front()->drawDropDown(re, menus.front()->posx, menus.front()->posy, menus.front()->width, menus.front()->height);
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
	std::vector<shape*> sh;
	TKSCENE *scene = new TKSCENE(r,  s,  w,  &e, sh);
	
#pragma endregion

	
	ClearAll(scene->rr);
	SetShapes(scene->rr, scene->shapes);
	scene->UpdateScreen(scene->rr, scene->ss); // first display
	
	while (!TK_QUIT)
	{
		int response = GetAllEvents(scene);
		TK_QUIT = (response == 20) ? true : false;
		

		// consider making all re-render events return odd, and all no-render events return even, then check event response
		if (response != 0) 
		{
			ClearAll(scene->rr);
			SetShapes(scene->rr, scene->shapes);
			SetMenus(scene->rr, scene->menus);
			scene->UpdateScreen(scene->rr, scene->ss); // we should only call if something changed
			SDL_Delay(5); // just a small thread delay, remove if it gets slow
		}

	}
	SDL_Delay(500);
	SDL_FreeSurface(scene->ss);
	SDL_Quit();


    return 0;
}


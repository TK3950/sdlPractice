// sdl13.cpp : Defines the entry point for the console application.
// 

// TODO: search for non-hypotenuse paths
// source and destination nodes should not be stuck on the top of the shape
// manually movable paths? by selecting intermediate nodes
// nodes should be more visisble?
// can you move pathfinding into a new thread?
// we might still be able to make a context menu
// add text processing

/*
Create multiple rects to serve as menu lines and build your context menu from there.
*/


#include <vector>
#include <SDL/SDL.h>
#include "tksdl.h"
//#include "paths.h"
#include <sdlttf/SDL_ttf.h>
#include <windows.h>
#undef main


#define TK_WINDOW_WIDTH 1000
#define TK_WINDOW_HEIGHT 680

extern bool TK_QUIT = false; // TODO: this should be moved

void SetShapes(SDL_Renderer* re, color* pc, color* sc, color* ac, std::vector<shape*> shapes) // Simple method to render all shapes in a non-empty list
{
	
	if (!(shapes.empty()))
	{
		for (unsigned int i = 0; i <= shapes.size()-1; ++i)
		{
			// look for shapes that escape our bounds
			// and return them to within the bounds
			if (shapes.at(i)->GetPosX() < 0)
			{
				shapes.at(i)->SetPos(0, shapes.at(i)->GetPosY());
			}
			if (shapes.at(i)->GetPosX()+shapes.at(i)->GetWidth() > TK_WINDOW_WIDTH)
			{
				shapes.at(i)->SetPos(TK_WINDOW_WIDTH - shapes.at(i)->GetWidth(), shapes.at(i)->GetPosY());
			}

			if (shapes.at(i)->GetPosY() < 0)
			{
				shapes.at(i)->SetPos(shapes.at(i)->GetPosX(), 0);
			}
			if (shapes.at(i)->GetPosY() + shapes.at(i)->GetHeight() > TK_WINDOW_HEIGHT)
			{
				shapes.at(i)->SetPos(shapes.at(i)->GetPosX(), TK_WINDOW_HEIGHT - shapes.at(i)->GetHeight());
			}

			if (i == shapes.size()-1) // back of vector
			{
				shapes.front()->shape::drawShape(re, ac, shapes.at(i)); // draw active shape into renderer
			}
			else
			{
				shapes.front()->shape::drawShape(re, pc, shapes.at(i)); // draw other shape into renderer
			}
		}
	}

}

void SetPaths(SDL_Renderer* re, color* pc, color* sc, color* ac, std::vector<path*> paths) // Simple method to render all paths in a non-empty list
{

	if (!(paths.empty()))
	{
		//
		for (unsigned int i = 0; i < paths.size(); ++i) 
		{
			paths.front()->path::drawPath(re, pc, paths.at(i)); // draw current path into renderer
#ifdef _DEBUG2
			for (unsigned int j = 0; j < paths.at(i)->nodes.size(); j++)
			{
				paths.at(i)->nodes.at(j)->drawNodes(re, ac, paths.at(i)->nodes.at(j));
			}
#endif
		}
	}
}

void SetNodes(SDL_Renderer* re, color* pc, color* sc, color* ac, std::vector<node*> nodes)
{
	if (!(nodes.empty()))
	{
		//
		for (unsigned int i = 0; i < nodes.size(); ++i)
		{
			nodes.front()->node::drawNodes(re, ac, nodes.at(i)); // draw current path into renderer
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
	std::vector<path*> pa;
	color* pc = new color(0, 0, 0, 255); // primary color
	color* sc = new color(255, 255, 255, 255); // secondary color
	color* ac = new color(200, 20, 20, 255); // accent/active color
	TKSCENE *scene = new TKSCENE(r,  s,  w,  &e, sh, pa, pc, sc);
	
#pragma endregion

	ClearAll(scene->rr, pc, sc, ac, scene->shapes);
	SetShapes(scene->rr, scene->PrimaryColor, scene->SecondaryColor, ac, scene->shapes);
	scene->UpdateScreen(); // first display
	
	while (!TK_QUIT)
	{
		int response = scene->GetAllEvents();
		TK_QUIT = (response == TK_CODE_QUITTING) ? true : false;

		// all re-render events return odd, and all no-render events return even, then check event response
		if (response % 2 == 1)
		{
			ClearAll(scene->rr, pc, sc, ac, scene->shapes);
			if (response == TK_CODE_DRAG || response == TK_CODE_RESIZE)
			{
				scene->RefreshPaths();
			}
			SetShapes(scene->rr, scene->PrimaryColor, scene->SecondaryColor, ac, scene->shapes);
			SetPaths(scene->rr, scene->PrimaryColor, scene->SecondaryColor, ac, scene->paths);
			if (scene->context->active)
			{
				scene->context->drawDropDown(scene->rr);
			}
			scene->UpdateScreen();
		}

	}
	SDL_Delay(500);
	SDL_FreeSurface(scene->ss);
	SDL_Quit();


    return 0;
}


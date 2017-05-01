#ifndef _TKSDL_H
#define _TKSDL_H 1
#include <list>
#include <vector>
#include "paths.h"
#include "stdafx.h"
#include "tkcodes.h"
#include <SDL/SDL.h>



class TKSCENE {
public:
	TKSCENE(SDL_Renderer* r, SDL_Surface* s, SDL_Window* w, SDL_Event* e, std::vector<shape*> sh, std::vector<path*> pa, color* pc, color* sc);
	
	
	
	SDL_Renderer*			rr;
	SDL_Surface*			ss;
	SDL_Window*				ww;
	SDL_Event*				ee;
	SDL_Texture*			tt;
	std::vector<shape*>		shapes;
	std::vector<path*>		paths;
	color*					PrimaryColor;
	color*					SecondaryColor;

	void UpdateScreen();
	int GetAllEvents();
	int PathFind(path* pa);

};

bool isInsideBox(int x, int y, shape sh);

#endif
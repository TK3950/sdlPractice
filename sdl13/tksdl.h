#pragma once
#include <list>
#include "stdafx.h"
#include <SDL/SDL.h>



class TKSCENE {
public:
	TKSCENE(SDL_Renderer* r, SDL_Surface* s, SDL_Window* w, SDL_Event* e, std::list<shape*> sh);
	
	void UpdateScreen(SDL_Renderer* , SDL_Surface*);
	
	SDL_Renderer*	rr;
	SDL_Surface*	ss;
	SDL_Window*		ww;
	SDL_Event*		ee;
	std::list<shape*> shapes;
};

int GetAllEvents(TKSCENE* scene);
#ifndef _TKSDL_H
#define _TKSDL_H 1
#include <list>
#include <vector>
#include "stdafx.h"
#include <SDL/SDL.h>



class TKSCENE {
public:
	TKSCENE(SDL_Renderer* r, SDL_Surface* s, SDL_Window* w, SDL_Event* e, std::vector<shape*> sh);
	
	void UpdateScreen(SDL_Renderer* , SDL_Surface*);
	
	SDL_Renderer*	rr;
	SDL_Surface*	ss;
	SDL_Window*		ww;
	SDL_Event*		ee;
	std::vector<shape*> shapes;
};

int GetAllEvents(TKSCENE* scene);

#endif
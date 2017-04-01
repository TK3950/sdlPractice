#include "tksdl.h"


TKSCENE::TKSCENE(SDL_Renderer* r, SDL_Surface* s, SDL_Window* w, SDL_Event* e, std::list<shape*> sh)
{
	SDL_Init(SDL_INIT_EVERYTHING); // initialize all SDL layers
	w = SDL_CreateWindow("SDL Demo", // create our window objecdt reference by pointer, with Title
		SDL_WINDOWPOS_UNDEFINED, // x position
		SDL_WINDOWPOS_UNDEFINED, // y position
		TK_WINDOW_WIDTH, TK_WINDOW_HEIGHT, // width , height
		SDL_WINDOW_OPENGL); // window flags

	s = SDL_LoadBMP(""); // empty path means we don't load an image, we get a clean slate. also returns null
	r = SDL_CreateRenderer(w, -1, 0); // make renderer-type object from screen, assign to renderer object
	rr = r;
	ss = s;
	ww = w;
	ee = e;
	shapes = sh;

}

void TKSCENE::UpdateScreen(SDL_Renderer* re, SDL_Surface* surf)
{
	SDL_BlitSurface(surf, NULL, surf, NULL);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(re, surf);
	SDL_RenderCopy(re, texture, NULL, NULL);
	SDL_RenderPresent(re); // show
	SDL_Delay(5);
}

int GetAllEvents(TKSCENE* scene)
{
	while (SDL_PollEvent(scene->ee))
	{
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_1)
		{
			scene->shapes.push_front(new shape(shape::TK_RHOMBUS, 0, 0, 100, 50));
			return SDL_SCANCODE_1;
		}

		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_2)
		{
			scene->shapes.push_front(new shape(shape::TK_RECTANGLE, 0, 0, 100, 50));
			return SDL_SCANCODE_2;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_3)
		{
			scene->shapes.push_front(new shape(shape::TK_ELLIPSE, 0, 0, 100, 50));
			return SDL_SCANCODE_2;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_Q)
		{
			return SDL_SCANCODE_Q;
		}
	}
	return 0;
}

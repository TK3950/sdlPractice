#pragma once
#include "tksdl.h"
#include "events.h"

TKSCENE::TKSCENE(SDL_Renderer* r, SDL_Surface* s, SDL_Window* w, SDL_Event* e, std::list<shape*> sh)
{
	SDL_Init(SDL_INIT_EVERYTHING); // initialize all SDL layers
	w = SDL_CreateWindow("SDL Demo", // create our window objecdt reference by pointer, with Title
		SDL_WINDOWPOS_UNDEFINED, // x position
		SDL_WINDOWPOS_UNDEFINED, // y position
		TK_WINDOW_WIDTH, TK_WINDOW_HEIGHT, // width , height
		SDL_WINDOW_OPENGL); // window flags

	//s = SDL_LoadBMP(""); // empty path means we don't load an image, we get a clean slate. also returns null, so functionally useless.
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
}





int GetAllEvents(TKSCENE* scene)
{
	while (SDL_PollEvent(scene->ee) != 0)
	{
#ifdef _DEBUG
		if (scene->ee->key.state == SDL_PRESSED)
		{
			printf("Pressed on %d\n", scene->ee->key.keysym.scancode);
		}
		if (scene->ee->button.state == SDL_PRESSED)
		{
			
			if (scene->ee->button.button == SDLK_RIGHT) printf("Right click pressed\n");
			else if(scene->ee->button.button == SDLK_LEFT) printf("Left click pressed\n");
		}
		printf("Motion Type = %d\tX = %d, Y = %d\n", scene->ee->motion.type, scene->ee->motion.x, scene->ee->motion.y);
#endif

		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_1 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_front(new shape(shape::TK_RHOMBUS, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_2 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_front(new shape(shape::TK_RECTANGLE, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_3 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_front(new shape(shape::TK_ELLIPSE, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_Q && scene->ee->key.state == SDL_PRESSED)
		{
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_W && scene->ee->key.state == SDL_PRESSED)
		{
			if (scene->shapes.front()->posy > 0)
			{
				scene->shapes.front()->posy = scene->shapes.front()->posy - 1;
			}
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_S && scene->ee->key.state == SDL_PRESSED)
		{
			if (scene->shapes.front()->posy < TK_WINDOW_HEIGHT)
			{
				scene->shapes.front()->posy = scene->shapes.front()->posy + 1;
			}
			return scene->ee->key.keysym.scancode;
		}

		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_A && scene->ee->key.state == SDL_PRESSED)
		{
			if (scene->shapes.front()->posx > 0)
			{
				scene->shapes.front()->posx = scene->shapes.front()->posx - 1;
			}
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_D && scene->ee->key.state == SDL_PRESSED)
		{
			if (scene->shapes.front()->posx < TK_WINDOW_WIDTH)
			{
				scene->shapes.front()->posx = scene->shapes.front()->posx + 1;
			}
			return scene->ee->key.keysym.scancode;
		}

	}
	return 0;
}

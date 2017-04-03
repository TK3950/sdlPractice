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
		int keystate = scene->ee->key.state;
		int keycode = scene->ee->key.keysym.scancode;
		int buttonstate = scene->ee->button.state;
		int button = scene->ee->button.button;
		int motiontype = scene->ee->motion.type;
		int mousex = scene->ee->motion.x;
		int mousey = scene->ee->motion.y;
		printf("=========================================================================\n");
		printf("Keystate = %d\t\t Keycode = %d\n",keystate,keycode);
		printf("Mouse state = %d\t\t Mouse button = %d\n", buttonstate, button);
		printf("Motion type = %d\t Mouse x = %d\t Mouse y = %d\n", motiontype, mousex, mousey);
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
			if (scene->shapes.front()->posy > 0 && !(scene->shapes.empty()))
			{
				scene->shapes.front()->posy = scene->shapes.front()->posy - 1;
			}
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_S && scene->ee->key.state == SDL_PRESSED)
		{
			if (scene->shapes.front()->posy < TK_WINDOW_HEIGHT && !(scene->shapes.empty()))
			{
				scene->shapes.front()->posy = scene->shapes.front()->posy + 1;
			}
			return scene->ee->key.keysym.scancode;
		}

		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_A && scene->ee->key.state == SDL_PRESSED)
		{
			if (scene->shapes.front()->posx > 0 && !(scene->shapes.empty()))
			{
				scene->shapes.front()->posx = scene->shapes.front()->posx - 1;
			}
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_D && scene->ee->key.state == SDL_PRESSED)
		{
			if (scene->shapes.front()->posx < TK_WINDOW_WIDTH && !(scene->shapes.empty()))
			{
				scene->shapes.front()->posx = scene->shapes.front()->posx + 1;
			}
			return scene->ee->key.keysym.scancode;
		}

		if (scene->ee->button.button == SDL_BUTTON_LEFT && scene->ee->button.state == SDL_PRESSED)
		{
			if (scene->ee->motion.x < scene->shapes.front()->posx + scene->shapes.front()->width)
			{
				if (scene->ee->motion.x > scene->shapes.front()->posx)
				{
					if (scene->ee->motion.x > scene->shapes.front()->posy + scene->shapes.front()->height)
					{
						if (scene->ee->motion.x > scene->shapes.front()->posy)
						{
							// fix this for more than just the top shape
							// we want the top shape whose bounding box we are in
						}
					}
				}

			}
		}

	}
	return 0;
}

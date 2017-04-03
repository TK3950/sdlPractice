#pragma once
#include "tksdl.h"
#include "events.h"

bool dragMode;
int selectedShape;

TKSCENE::TKSCENE(SDL_Renderer* r, SDL_Surface* s, SDL_Window* w, SDL_Event* e, std::vector<shape*> sh)
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
		int mousex = scene->ee->motion.xrel;
		int mousey = scene->ee->motion.yrel;
		printf("=========================================================================\n");
		printf("Keystate = %d\t\t Keycode = %d\n",keystate,keycode);
		printf("Mouse state = %d\t\t Mouse button = %d\n", buttonstate, button);
		printf("Motion type = %d\t Mouse x = %d\t Mouse y = %d\n", motiontype, mousex, mousey);
#endif

		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_1 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_back(new shape(shape::TK_RHOMBUS, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_2 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_back(new shape(shape::TK_RECTANGLE, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_3 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_back(new shape(shape::TK_ELLIPSE, 0, 0, 100, 50));
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

		if (scene->ee->button.button == SDL_BUTTON_LEFT)
		{
			if (scene->ee->button.state == SDL_PRESSED)
			{
				for (unsigned int i = 0; i < scene->shapes.size(); ++i)
				{
					if (scene->ee->motion.x < scene->shapes.at(i)->posx + scene->shapes.at(i)->width && !scene->shapes.empty())
					{
						if (scene->ee->motion.x > scene->shapes.at(i)->posx)
						{
							if (scene->ee->motion.y < scene->shapes.at(i)->posy + scene->shapes.at(i)->height)
							{
								if (scene->ee->motion.y > scene->shapes.at(i)->posy)
								{
									dragMode = true;
									// the cursor clicked inside the bounds of the shape
									
									selectedShape = i; // last shape within bounds
									printf("START DRAG\n");
									
								}
							}
						}
					}
				}
			}
			printf("----%d,%d,%d,%d\n",dragMode,selectedShape, scene->ee->motion.xrel, scene->ee->motion.yrel);
			if (dragMode && selectedShape >= 0 &&  abs(scene->ee->motion.xrel) < TK_WINDOW_WIDTH && abs(scene->ee->motion.yrel) < TK_WINDOW_WIDTH)
			{
				printf("DRAGGING\n");
				scene->shapes.at(selectedShape)->posx += scene->ee->motion.xrel;
				scene->shapes.at(selectedShape)->posy += scene->ee->motion.yrel;
			}
			return 418;
		}
		else
		{
			printf("NOT DRAGGING\n");
			dragMode = false;
			return 418;
		}


	}
	return 0;
}

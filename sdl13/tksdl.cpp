#pragma once
#include "tksdl.h"
#include "events.h"

bool dragMode;
bool editMode;
int selectedShape;

TKSCENE::TKSCENE(SDL_Renderer* r, SDL_Surface* s, SDL_Window* w, SDL_Event* e, std::vector<shape*> sh, color* pc, color* sc)
{
	SDL_Init(SDL_INIT_EVERYTHING); // initialize all SDL layers
	w = SDL_CreateWindow("SDL Demo", // create our window objecdt reference by pointer, with Title
		SDL_WINDOWPOS_UNDEFINED, // x position
		SDL_WINDOWPOS_UNDEFINED, // y position
		TK_WINDOW_WIDTH, TK_WINDOW_HEIGHT, // width, height
		SDL_WINDOW_OPENGL); // window flags

	//s = SDL_LoadBMP(""); // empty path means we don't load an image, we get a clean slate. also returns null, so functionally useless.
	r = SDL_CreateRenderer(w, -1, 0); // make renderer-type object from screen, assign to renderer object
	rr = r;
	ss = s;
	ww = w;
	ee = e;
	shapes = sh;
	PrimaryColor = pc;
	SecondaryColor = sc;
	SDL_BlitSurface(ss, NULL, ss, NULL);
	tt = SDL_CreateTextureFromSurface(rr, ss);

}

void UpdateScreen(TKSCENE* sc)
{
	
	SDL_RenderCopy(sc->rr, sc->tt, NULL, NULL);
	SDL_RenderPresent(sc->rr); // show
}

int GetAllEvents(TKSCENE* scene)
{
	while (SDL_PollEvent(scene->ee) != 0)
	{
		int mousex = scene->ee->motion.x;
		int mousey = scene->ee->motion.y;
#ifdef _DEBUG
		int keystate = scene->ee->key.state;
		int keycode = scene->ee->key.keysym.scancode;
		int buttonstate = scene->ee->button.state;
		int button = scene->ee->button.button;
		int motiontype = scene->ee->motion.type;

		printf("=========================================================================\n");
		printf("Keystate = %d\t\t Keycode = %d\t\tPRESSED = %d\n",keystate,keycode,scene->ee->button.state);
		printf("Mouse state = %d\t\t Mouse button = %d\n", buttonstate, button);
		printf("Motion type = %d\t Mouse x = %d\t Mouse y = %d\n", motiontype, mousex, mousey);
#endif

		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_1 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_back(new shape(shape::TK_RHOMBUS, scene->PrimaryColor, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_2 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_back(new shape(shape::TK_RECTANGLE, scene->PrimaryColor, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_3 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_back(new shape(shape::TK_ELLIPSE, scene->PrimaryColor, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}

		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_Q && scene->ee->key.state == SDL_PRESSED)
		{
			return scene->ee->key.keysym.scancode;
		}
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_DELETE && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.pop_back();
			return scene->ee->key.keysym.scancode;
		}

		if (scene->ee->button.button == SDL_BUTTON_LEFT)
		{
			if (scene->ee->button.state == SDL_PRESSED)
			{
				for (unsigned int i = 0; i < scene->shapes.size(); ++i)
				{
					if (!scene->shapes.empty())
					{
							if (scene->ee->motion.x < scene->shapes.at(i)->GetPosX() + scene->shapes.at(i)->GetWidth())
							{
								if (scene->ee->motion.x > scene->shapes.at(i)->GetPosX())
								{
									if (scene->ee->motion.y < scene->shapes.at(i)->GetPosY() + scene->shapes.at(i)->GetHeight())
									{
										if (scene->ee->motion.y > scene->shapes.at(i)->GetPosY())
										{
											dragMode = true;	// the cursor clicked inside the bounds of the shape
											selectedShape = i;	// last shape within bounds
											if (selectedShape != scene->shapes.size() - 1) // if our shape is not at the back of our vector
											{
												scene->shapes.push_back(scene->shapes.at(selectedShape));
												scene->shapes.erase(scene->shapes.begin() + selectedShape);
											}
										}
									}
								}
							}
					}
				}
			}
			if (dragMode && !scene->shapes.empty() ) 
			{
				if (selectedShape != scene->shapes.size() - 1)
				{
					scene->shapes.push_back(scene->shapes.at(selectedShape));
					scene->shapes.erase(scene->shapes.begin() + selectedShape);
				}

				if (abs(scene->ee->motion.xrel) < TK_WINDOW_WIDTH && abs(scene->ee->motion.yrel) < TK_WINDOW_WIDTH)
				{
					// DRAGGING!
					scene->shapes.back()->SetPos(scene->shapes.back()->GetPosX() + scene->ee->motion.xrel, scene->shapes.back()->GetPosY() + scene->ee->motion.yrel);
				}
			}
			return 418;
		}
		else
		{
			dragMode = false;
		}

		if (scene->ee->button.button == SDL_BUTTON_RIGHT)
		{
			if (scene->ee->button.state == SDL_PRESSED)
			{
				for (unsigned int i = 0; i < scene->shapes.size(); ++i)
				{
					if (!scene->shapes.empty())
					{
							if (scene->ee->motion.x < scene->shapes.at(i)->GetPosX() + scene->shapes.at(i)->GetWidth())
							{
								if (scene->ee->motion.x > scene->shapes.at(i)->GetPosX())
								{
									if (scene->ee->motion.y < scene->shapes.at(i)->GetPosY() + scene->shapes.at(i)->GetHeight())
									{
										if (scene->ee->motion.y > scene->shapes.at(i)->GetPosY())
										{
											editMode = true;	// the cursor clicked inside the bounds of the shape
											selectedShape = i;	// index last shape within bounds is stored here
											if (selectedShape != scene->shapes.size() - 1) // if our shape is not at the back of our vector
											{
												scene->shapes.push_back(scene->shapes.at(selectedShape));
												scene->shapes.erase(scene->shapes.begin() + selectedShape);
											}

										}
									}
								}
							}
					}
				}
			}
			return 418;
		}
																				// consider #define'ing
		if (scene->ee->button.button == 4 && editMode && !scene->shapes.empty()) // right click held + drag is 4 instead of 3
		{

			if (abs(scene->ee->motion.xrel) < 1000)
			{

				// resizing!
				scene->shapes.back()->SetWidth(scene->shapes.back()->GetWidth() + scene->ee->motion.xrel);
				scene->shapes.back()->SetHeight(scene->shapes.back()->GetHeight() + scene->ee->motion.yrel);


				// unfortunately, we need to protect against negatives
				if (scene->shapes.back()->GetWidth() < 10)
				{
					scene->shapes.back()->SetWidth(10);
				}
				if (scene->shapes.back()->GetHeight() < 10)
				{
					scene->shapes.back()->SetHeight(10);
				}
				return 422;
			}
			
		}
		
		
		if (scene->ee->button.button != SDL_BUTTON_RIGHT && scene->ee->button.button != 4)
		{
			editMode = false;
		}



	}



	return 0; 
}

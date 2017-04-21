#pragma once
#include "tksdl.h"

bool dragMode;
bool editMode;
bool lineMode;
bool lineGood;
int selectedShape;
// these variables are defined here to maintain persistence. Look for a better way to achieve this
// such as in a status class.

TKSCENE::TKSCENE(SDL_Renderer* r, SDL_Surface* s, SDL_Window* w, SDL_Event* e, std::vector<shape*> sh, std::vector<path*> pa, color* pc, color* sc)
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
	paths = pa;
	PrimaryColor = pc;
	SecondaryColor = sc;
	SDL_BlitSurface(ss, NULL, ss, NULL);
	tt = SDL_CreateTextureFromSurface(rr, ss);

}

bool isInsideBox(int x, int y, shape sh)
{
	if (x > sh.GetPosX() && x < sh.GetPosX() + sh.GetWidth())
	{
		if (y > sh.GetPosY() && y < sh.GetPosY() + sh.GetHeight())
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool hasUpperPath(int originx, int originy, int candX, int candY, std::vector<shape*> shapes)
{
	for (int x = originx; x <= candX; x++)
	{
		for (unsigned int i = 0; i < shapes.size(); ++i)
		{
			if (isInsideBox(x, originy, *shapes.at(i)))
			{
				return true;
			}
		}
	}
	for (int y = originy; y <= candY; y++)
	{
		for (unsigned int i = 0; i < shapes.size(); ++i)
		{
			if (isInsideBox(candX, y, *shapes.at(i)))
			{
				return true;
			}
		}
	}
	return false;
}

bool hasLowerPath(int originx, int originy, int candX, int candY, std::vector<shape*> shapes)
{
	for (int y = originy; y <= candY; y++)
	{
		for (unsigned int i = 0; i < shapes.size(); ++i)
		{
			if (isInsideBox(originx, y, *shapes.at(i)))
			{
				return true;
			}
		}
	}
	for (int x = originx; x <= candX; x++)
	{
		for (unsigned int i = 0; i < shapes.size(); ++i)
		{
			if (isInsideBox(x, candY, *shapes.at(i)))
			{
				return true;
			}
		}
	}
	return false;
}

int PathFind(TKSCENE* scene, path pa)
{
	// source shape = scene->shapes.at(pa.source);
	pa.nodex[0] = scene->shapes.at(pa.source)->nodex[shape::TOP];
	pa.nodey[0] = scene->shapes.at(pa.source)->nodey[shape::TOP];
	
	// candidate node methods.

	int candidatex = ((scene->shapes.at(pa.source)->nodex[shape::TOP] - pa.nodex[0])/2)+pa.nodex[0];
	int candidatey = ((scene->shapes.at(pa.source)->nodey[shape::TOP] - pa.nodey[0])/2)+pa.nodey[0];
	bool upperFails = false;
	bool lowerFails = false;
	int originx = pa.nodex[0];
	int originy = pa.nodey[0];
	// check upper path
	upperFails = hasUpperPath(originx, originy, candidatex, candidatey, scene->shapes);
	lowerFails = hasLowerPath(originx, originy, candidatex, candidatey, scene->shapes);
	// end check upper path.
	// check lower path


	// end check lower path

	//	>> first intermediate node = halfway on hypot.
	//		>> check for empty spot, verify one or more paths is unobstructed
	//			>> select inter. node and path (Lower has priority) (later we can set priority by chosen node.
	//		>> else, move inter. node backward on hypot.
	//
	//		:xy
	//
	//		>> check for clear path to desired node, write
	//		
	//			>> next node = halfway on remaining hypot.
	//				>> check uppper and lower path
	//					>> select next node
	//				>> else move node backwards
	//
	//		>> goto xy
	



}

void UpdateScreen(TKSCENE* scene)
{
	SDL_RenderCopy(scene->rr, scene->tt, NULL, NULL);
	SDL_RenderPresent(scene->rr); // show
}

int GetAllEvents(TKSCENE* scene)
{
	lineGood = false;
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
		printf("Keystate = %d\t\t Keycode = %d\t\tPRESSED = %d\n", keystate, keycode, scene->ee->button.state);
		printf("Mouse state = %d\t\t Mouse button = %d\n", buttonstate, button);
		printf("Motion type = %d\t Mouse x = %d\t Mouse y = %d\n", motiontype, mousex, mousey);
		if (lineMode)
		{
			printf("LINE ADD MODE\n");
		}
		if (editMode)
		{
			printf("SHAPE EDIT MODE\n");
		}
		if (dragMode)
		{
			printf("SHAPE DRAG MODE\n");
		}
#endif

		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_1 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_back(new shape(shape::TK_RHOMBUS, scene->PrimaryColor, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}
		// KEYPRESS: 1
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_2 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_back(new shape(shape::TK_RECTANGLE, scene->PrimaryColor, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}
		// KEYPRESS: 2
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_3 && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.push_back(new shape(shape::TK_ELLIPSE, scene->PrimaryColor, 0, 0, 100, 50));
			return scene->ee->key.keysym.scancode;
		}
		// KEYPRESS: 3
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_Q && scene->ee->key.state == SDL_PRESSED)
		{
			return scene->ee->key.keysym.scancode;
		}
		// KEYPRESS: Q
		if (scene->ee->key.keysym.scancode == SDL_SCANCODE_DELETE && scene->ee->key.state == SDL_PRESSED)
		{
			scene->shapes.pop_back();
			return scene->ee->key.keysym.scancode;
		}
		// KEYPRESS: DEL

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
			if (dragMode && !scene->shapes.empty())
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
			return TK_CODE_DRAG;
		}
		// CLICKED: LEFT
		else
		{
			dragMode = false;
		}
		// NOT-CLICKED && NOT-HELD: LEFT

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
			return TK_CODE_RESIZE;
		}
		// CLICKED: RIGHT
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
				return TK_CODE_RESIZE;
			}

		}
		// HOLD-CLICK: RIGHT


		if (scene->ee->button.button != SDL_BUTTON_RIGHT && scene->ee->button.button != 4)
		{
			editMode = false;
		}
		// NOT-CLICKED && NOT-HELD: RIGHT




		if (scene->ee->button.button == SDL_BUTTON_MIDDLE)
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
										lineMode = true;	// the cursor clicked inside the bounds of the shape
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

			else if (scene->ee->motion.type == 1024 && scene->ee->button.state != SDL_PRESSED)
			{
				// middle and drag

			}

			else if (scene->ee->motion.type == 1026 && scene->ee->button.state != SDL_PRESSED)
			{
				// middle and released
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
										selectedShape = i;	// last shape within bounds
										if (selectedShape != scene->shapes.size() - 1) // if our shape is not at the back of our vector
										{
											scene->shapes.push_back(scene->shapes.at(selectedShape));
											scene->shapes.erase(scene->shapes.begin() + selectedShape);
											lineGood = true; // source shape is not destination shape
										}
									}
								}
							}
						}
					}
				}

				// now we make the line
				if (lineGood)
				{
					// draw with shapes at last and second to last position
					scene->paths.push_back(new path(scene->shapes.size(), scene->shapes.size() - 1, 3));
					PathFind(scene, *scene->paths.back());
					
					printf("\n====Line added successfully====\n");
				}
				
			}
			return TK_CODE_ADDLINE;
		}
		// CLICKED: MIDDLE
		else
		{
			lineMode = false;
		}
		// NOT-CLICKED && NOT-HELD: MIDDLE
	}
	return 0; 
}

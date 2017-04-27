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
// check if a point is within the bounding box of a shape

bool hasUpperPath(int originx, int originy, int candX, int candY, std::vector<shape*> shapes)
{

	if (originx < candX && originy < candY)
	{ // source is above and left
		for (int x = originx; x <= candX; x++)
		{ // horizontal sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(x, originy, *shapes.at(i)))
				{
					return true;
				}
			}
		}

		for (int y = originy; y <= candY; y++)
		{ // vertical sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(candX, y, *shapes.at(i)))
				{
					return true;
				}
			}
		}


	}
	if (originx < candX && originy >= candY)
	{ // source is below or = and left

		for (int x = originx; x <= candX; x++)
		{ // horizontal sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(x, candY, *shapes.at(i)))
				{
					return true;
				}
			}
		}

		for (int y = candY; y <= originy ; y++)
		{ // vertical sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(originx, y, *shapes.at(i)))
				{
					return true;
				}
			}
		}

	}

	if (originx >= candX && originy < candY)
	{ // source right or = and above
		for (int x = candX; x <= originx; x++)
		{ // horizontal sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(x, originy, *shapes.at(i)))
				{
					return true;
				}
			}
		}

		for (int y = originy; y <= candY; y++)
		{ // vertical sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(candX, y, *shapes.at(i)))
				{
					return true;
				}
			}
		}
	}
	if (originx >= candX && originy >= candY)
	{ // source is right or = and below or =
		for (int x = candX; x <= originx; x++)
		{ // horizontal sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(x, candY, *shapes.at(i)))
				{
					return true;
				}
			}
		}

		for (int y = candY; y <= originy; y++)
		{ // vertical sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(originx, y, *shapes.at(i)))
				{
					return true;
				}
			}
		}
	}

	return false;
}
// an unobstructed upper-right-angle-path between two points exists

bool hasLowerPath(int originx, int originy, int candX, int candY, std::vector<shape*> shapes)
{
	
	if (originx < candX && originy < candY)
	{ // source is above and left
		for (int x = originx; x <= candX; x++)
		{ // horizontal sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(x, candY, *shapes.at(i)))
				{
					return true;
				}
			}
		}
		for (int y = originy; y <= candY; y++)
		{ // vertical sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(originx, y, *shapes.at(i)))
				{
					return true;
				}
			}
		}
	}
	if (originx < candX && originy >= candY)
	{ // source is below or = and left

		for (int x = originx; x <= candX; x++)
		{ // horizontal sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(x, originy, *shapes.at(i)))
				{
					return true;
				}
			}
		}

		for (int y = candY; y <= originy; y++)
		{ // vertical sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(candX, y, *shapes.at(i)))
				{
					return true;
				}
			}
		}

	}

	if (originx >= candX && originy < candY)
	{ // source right or = and above
		for (int x = candX; x <= originx; x++)
		{ // horizontal sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(x, candY, *shapes.at(i)))
				{
					return true;
				}
			}
		}

		for (int y = originy; y <= candY; y++)
		{ // vertical sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(originx, y, *shapes.at(i)))
				{
					return true;
				}
			}
		}
	}
	if (originx >= candX && originy >= candY)
	{ // source is right or = and below or =
		for (int x = candX; x <= originx; x++)
		{ // horizontal sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(x, originy, *shapes.at(i)))
				{
					return true;
				}
			}
		}

		for (int y = candY; y <= originy; y++)
		{ // vertical sweep
			for (unsigned int i = 0; i < shapes.size() - 2; ++i)
			{
				if (isInsideBox(candX, y, *shapes.at(i)))
				{
					return true;
				}
			}
		}
	}

	return false;
}
// an unobstructed lower-right-angle-path between two points exists

int PathFind(TKSCENE* scene, path* pa)
{
	// should not be called while dragging a shape.

	int exitCode = 0;
	/* THIS IS DRAFT CODE. CLEAN IT BEFORE PUSHING TO BRANCH*/

	scene->shapes.at(pa->source)->UpdateNodes();
	scene->shapes.at(pa->destination)->UpdateNodes();
	
	if ((pa->nodes.empty())) // vector is empty
	{
		// add first node
		pa->nodes.push_back(new node(scene->shapes.at(pa->source)->nodex[shape::TOP], scene->shapes.at(pa->source)->nodey[shape::TOP], node::NONE));
	}



	// candidate node methods.
	
	int destinationx = scene->shapes.at(pa->destination)->nodex[shape::TOP]; // the final x destination of the path
	int destinationy = scene->shapes.at(pa->destination)->nodey[shape::TOP]; // the final y destination of the path
	
	int zerox = pa->nodes.at(0)->posx; // the starting x point of the path
	int zeroy = pa->nodes.at(0)->posy; // the starting y point of the path

	bool upperFails = false; 
	bool lowerFails = false;

	int hyp_offsetx = 0;
	int hyp_offsety = 0;

	
	int hypx_scale = 10;
	if (destinationx < zerox)
	{
		hypx_scale = -hypx_scale; // move the other way if we're on the other side
	}
	float dx = (float)destinationx - (float)zerox;
	float dy = (float)destinationy - (float)zeroy;
	int hypy_scale = (float)(dy / dx)*hypx_scale;


	int count = 1;
	
	while (hyp_offsetx < abs(destinationx - zerox) && hyp_offsety < abs(destinationy - zeroy) && exitCode != TK_CODE_GOOD_PATH) // this check must be revised.
	{		// offset is less than distance between source point and candidate point
			// 
		
		{ // block added for future editing

			upperFails = hasUpperPath(zerox, zeroy, destinationx - hyp_offsetx, destinationy - hyp_offsety, scene->shapes);
			lowerFails = hasLowerPath(zerox, zeroy, destinationx - hyp_offsetx, destinationy - hyp_offsety, scene->shapes);
			if (upperFails)
			{
				if (lowerFails)
				{
					hyp_offsetx += hypx_scale;
					hyp_offsety += hypy_scale;
					exitCode = TK_CODE_BAD_PATH;
				}
				else
				{
					++count;
					pa->nodes.push_back(new node(destinationx - hyp_offsetx, destinationy - hyp_offsety, node::LOWER)); // select lower
					
					zerox = destinationx - hyp_offsetx;
					zeroy = destinationy - hyp_offsety;

					hyp_offsetx = 0;
					hyp_offsety = 0;


				}

			}
			else
			{
				++count;

				pa->nodes.push_back(new node(destinationx - hyp_offsetx, destinationy - hyp_offsety, node::UPPER)); // select upper

				zerox = destinationx - hyp_offsetx;
				zeroy = destinationy - hyp_offsety;

				hyp_offsetx = 0;
				hyp_offsety = 0;


			}

			if (destinationx == zerox && destinationy == zeroy)
			{
				printf("=====PATH FOUND=====\n");
				exitCode = TK_CODE_GOOD_PATH;
			}

		}
	}

	if (exitCode != TK_CODE_GOOD_PATH)
	{
		// suitable path was not found with this method
		return TK_CODE_PATH_NOT_FOUND;
	}

	else
	{
		return TK_CODE_PATH_FOUND;
	}

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
#ifdef _DEBUG2
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
					scene->paths.push_back(new path(scene->shapes.size()-1, scene->shapes.size() - 2, 3));
					PathFind(scene, scene->paths.back());
					
					printf("\n====Line added successfully====\n");
				}
				
			}
			return TK_CODE_ADD_LINE;
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

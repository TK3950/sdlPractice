#pragma once
#include "tksdl.h"

bool dragMode;
bool editMode;
bool lineMode;
bool sourceIsNotDestination;
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


int TKSCENE::PathFindHypotenuse(path* pa)
{
	// should not be called while dragging a shape.
	pa->validPath = false;
	int exitCode = 0;

	unsigned int source, destination;

	for (unsigned int i = 0; i < shapes.size(); ++i)
	{
		if (shapes.at(i)->id == pa->sourceId)
		{
			source = i;
		}
	}

	for (unsigned int i = 0; i < shapes.size(); ++i)
	{
		if (shapes.at(i)->id == pa->destinationId)
		{
			destination = i;
		}
	}


	shapes.at(source)->UpdateNodes();
	shapes.at(destination)->UpdateNodes();

	pa->nodes.clear();

	pa->nodes.push_back(new node(shapes.at(source)->nodex[shape::TOP], shapes.at(source)->nodey[shape::TOP], node::NONE));
	int destinationx = shapes.at(destination)->nodex[shape::TOP]; // the final x destination of the path
	int destinationy = shapes.at(destination)->nodey[shape::TOP]; // the final y destination of the path
	int zerox = pa->nodes.at(0)->posx; // the starting x point of the path
	int zeroy = pa->nodes.at(0)->posy; // the starting y point of the path
	bool upperFails = false;
	bool lowerFails = false;
	int hyp_offsetx = 0;
	int hyp_offsety = 0;
	int hypx_scale = 10;
	if (destinationx < zerox)
	{
		hypx_scale = -hypx_scale;
	}
	float dx = (float)destinationx - (float)zerox;
	float dy = (float)destinationy - (float)zeroy;
	int hypy_scale = (int)((dy / dx)*hypx_scale);
	int count = 1;

	while (hyp_offsetx < abs(destinationx - zerox) && hyp_offsety < abs(destinationy - zeroy) && exitCode != TK_CODE_GOOD_PATH) // this check must be revised.
	{
		upperFails = hasUpperPath(zerox, zeroy, destinationx - hyp_offsetx, destinationy - hyp_offsety, shapes);
		lowerFails = hasLowerPath(zerox, zeroy, destinationx - hyp_offsetx, destinationy - hyp_offsety, shapes);
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
#ifdef _DEBUG
			printf("=====PATH FOUND=====\n");
#endif
			exitCode = TK_CODE_GOOD_PATH;
		}

	}

	if (exitCode != TK_CODE_GOOD_PATH)
	{
		// suitable path was not found with this method
		return TK_CODE_PATH_NOT_FOUND;
	}

	else
	{
		pa->validPath = true;
		return TK_CODE_PATH_FOUND;
	}

}


void TKSCENE::UpdateScreen()
{
	SDL_RenderCopy(rr, tt, NULL, NULL);
	SDL_RenderPresent(rr); // show
}

int TKSCENE::GetAllEvents()
{
	sourceIsNotDestination = false;
	while (SDL_PollEvent(ee) != 0)
	{
		int mousex = ee->motion.x;
		int mousey = ee->motion.y;
#ifdef _DEBUG2
		int keystate = ee->key.state;
		int keycode = ee->key.keysym.scancode;
		int buttonstate = ee->button.state;
		int button = ee->button.button;
		int motiontype = ee->motion.type;

		printf("=========================================================================\n");
		printf("Keystate = %d\t\t Keycode = %d\t\tPRESSED = %d\n", keystate, keycode, ee->button.state);
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

		if (ee->key.keysym.scancode == SDL_SCANCODE_1 && ee->key.state == SDL_PRESSED)
		{
			shapes.push_back(new shape(shape::TK_RHOMBUS, PrimaryColor, 0, 0, 100, 50, shapeIterator));
			shapeIterator++;
			return ee->key.keysym.scancode;
		}
		// KEYPRESS: 1
		if (ee->key.keysym.scancode == SDL_SCANCODE_2 && ee->key.state == SDL_PRESSED)
		{
			shapes.push_back(new shape(shape::TK_RECTANGLE, PrimaryColor, 0, 0, 100, 50, shapeIterator));
			shapeIterator++;
			return ee->key.keysym.scancode;
		}
		// KEYPRESS: 2
		if (ee->key.keysym.scancode == SDL_SCANCODE_3 && ee->key.state == SDL_PRESSED)
		{
			shapes.push_back(new shape(shape::TK_ELLIPSE, PrimaryColor, 0, 0, 100, 50, shapeIterator));
			shapeIterator++;
			return ee->key.keysym.scancode;
		}
		// KEYPRESS: 3
		if (ee->key.keysym.scancode == SDL_SCANCODE_Q && ee->key.state == SDL_PRESSED)
		{
			return ee->key.keysym.scancode;
		}
		// KEYPRESS: Q
		if (ee->key.keysym.scancode == SDL_SCANCODE_DELETE && ee->key.state == SDL_PRESSED)
		{
			shapes.pop_back();
			return ee->key.keysym.scancode;
		}
		// KEYPRESS: DEL
		if (ee->key.keysym.scancode == SDL_SCANCODE_F5 && ee->key.state == SDL_PRESSED)
		{
			// BOOKMARK
			// new paths are not validating paths
			for (unsigned int i = 0; i < paths.size(); ++i)
			{
				PathFindHypotenuse(paths.at(i));
			}
			return ee->key.keysym.scancode;
		}
		// KEYPRESS: F5

		if (ee->button.button == SDL_BUTTON_LEFT)
		{
			if (ee->button.state == SDL_PRESSED)
			{
				for (unsigned int i = 0; i < shapes.size(); ++i)
				{
					if (!shapes.empty())
					{
						if (ee->motion.x < shapes.at(i)->GetPosX() + shapes.at(i)->GetWidth())
						{
							if (ee->motion.x > shapes.at(i)->GetPosX())
							{
								if (ee->motion.y < shapes.at(i)->GetPosY() + shapes.at(i)->GetHeight())
								{
									if (ee->motion.y > shapes.at(i)->GetPosY())
									{
										dragMode = true;	// the cursor clicked inside the bounds of the shape
										selectedShape = i;	// last shape within bounds
										if (selectedShape != shapes.size() - 1) // if our shape is not at the back of our vector
										{
											shapes.push_back(shapes.at(selectedShape));
											shapes.erase(shapes.begin() + selectedShape);
										}
									}
								}
							}
						}
					}
				}
			}
			if (dragMode && !shapes.empty())
			{
				if (selectedShape != shapes.size() - 1)
				{
					shapes.push_back(shapes.at(selectedShape));
					shapes.erase(shapes.begin() + selectedShape);
				}

				if (abs(ee->motion.xrel) < TK_WINDOW_WIDTH && abs(ee->motion.yrel) < TK_WINDOW_WIDTH)
				{
					// DRAGGING!
					shapes.back()->SetPos(shapes.back()->GetPosX() + ee->motion.xrel, shapes.back()->GetPosY() + ee->motion.yrel);
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

		if (ee->button.button == SDL_BUTTON_RIGHT)
		{
			if (ee->button.state == SDL_PRESSED)
			{
				for (unsigned int i = 0; i < shapes.size(); ++i)
				{
					if (!shapes.empty())
					{
						if (ee->motion.x < shapes.at(i)->GetPosX() + shapes.at(i)->GetWidth())
						{
							if (ee->motion.x > shapes.at(i)->GetPosX())
							{
								if (ee->motion.y < shapes.at(i)->GetPosY() + shapes.at(i)->GetHeight())
								{
									if (ee->motion.y > shapes.at(i)->GetPosY())
									{
										editMode = true;	// the cursor clicked inside the bounds of the shape
										selectedShape = i;	// index last shape within bounds is stored here
										if (selectedShape != shapes.size() - 1) // if our shape is not at the back of our vector
										{
											shapes.push_back(shapes.at(selectedShape));
											shapes.erase(shapes.begin() + selectedShape);
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
		if (ee->button.button == 4 && editMode && !shapes.empty()) // right click held + drag is 4 instead of 3
		{

			if (abs(ee->motion.xrel) < 1000)
			{

				// resizing!
				shapes.back()->SetWidth(shapes.back()->GetWidth() + ee->motion.xrel);
				shapes.back()->SetHeight(shapes.back()->GetHeight() + ee->motion.yrel);


				// unfortunately, we need to protect against negatives
				if (shapes.back()->GetWidth() < 10)
				{
					shapes.back()->SetWidth(10);
				}
				if (shapes.back()->GetHeight() < 10)
				{
					shapes.back()->SetHeight(10);
				}

				return TK_CODE_RESIZE;
			}

		}
		// HOLD-CLICK: RIGHT

		if (ee->button.button != SDL_BUTTON_RIGHT && ee->button.button != 4)
		{
			editMode = false;
		}
		// NOT-CLICKED && NOT-HELD: RIGHT

		if (ee->button.button == SDL_BUTTON_MIDDLE)
		{
			if (ee->button.state == SDL_PRESSED)
			{
				for (unsigned int i = 0; i < shapes.size(); ++i)
				{
					if (!shapes.empty())
					{
						if (ee->motion.x < shapes.at(i)->GetPosX() + shapes.at(i)->GetWidth())
						{
							if (ee->motion.x > shapes.at(i)->GetPosX())
							{
								if (ee->motion.y < shapes.at(i)->GetPosY() + shapes.at(i)->GetHeight())
								{
									if (ee->motion.y > shapes.at(i)->GetPosY())
									{
										lineMode = true;	// the cursor clicked inside the bounds of the shape
										selectedShape = i;	// last shape within bounds
										if (selectedShape != shapes.size() - 1) // if our shape is not at the back of our vector
										{
											shapes.push_back(shapes.at(selectedShape));
											shapes.erase(shapes.begin() + selectedShape);
										}
									}
								}
							}
						}
					}
				}
			}

			else if (ee->motion.type == 1024 && ee->button.state != SDL_PRESSED)
			{
				// middle and drag

			}

			else if (ee->motion.type == 1026 && ee->button.state != SDL_PRESSED)
			{
				// middle and released
				for (unsigned int i = 0; i < shapes.size(); ++i)
				{
					if (!shapes.empty())
					{
						if (ee->motion.x < shapes.at(i)->GetPosX() + shapes.at(i)->GetWidth())
						{
							if (ee->motion.x > shapes.at(i)->GetPosX())
							{
								if (ee->motion.y < shapes.at(i)->GetPosY() + shapes.at(i)->GetHeight())
								{
									if (ee->motion.y > shapes.at(i)->GetPosY())
									{
										selectedShape = i;	// last shape within bounds
										if (selectedShape != shapes.size() - 1) // if our shape is not at the back of our vector
										{
											shapes.push_back(shapes.at(selectedShape));
											shapes.erase(shapes.begin() + selectedShape);
											sourceIsNotDestination = true; // source shape is not destination shape
										}
									}
								}
							}
						}
					}
				}

				// now we make the line
				if (sourceIsNotDestination)
				{
					// draw with shapes at last and second to last position


					paths.push_back(new path(shapes.at(shapes.size() - 1)->id, shapes.at(shapes.size() - 2)->id, 3));
					PathFindHypotenuse(paths.back());
					if (!paths.back()->validPath)
					{
						paths.pop_back();
						printf("\n====Path not valid====\n");
					}
					else
					{
#ifdef _DEBUG
						printf("\n====Line added successfully====\n");
#endif
					}
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

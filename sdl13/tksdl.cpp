#pragma once
#include "tksdl.h"

// TODO:

TKSCENE::TKSCENE(SDL_Renderer* r, SDL_Surface* s, SDL_Window* w, SDL_Event* e, std::vector<shape*> sh, std::vector<path*> pa, color* pc, color* sc)
{
	SDL_Init(SDL_INIT_EVERYTHING); // initialize all SDL layers
	w = SDL_CreateWindow("SDL Demo", // create our window object reference by pointer, with Title
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
	tt = SDL_CreateTextureFromSurface(rr, ss);
	context = new menu(0, 0, 100, 100);

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

bool hasHorizontalLine(int lowx, int y, int highx, std::vector<shape*> shapes, unsigned int src, unsigned int dest)
{
	
	for (int x = lowx; x <= highx; x++)
	{ // horizontal sweep
		for (unsigned int i = 0; i < shapes.size(); ++i)
		{
			if (i != src && i != dest)
			{
				if (isInsideBox(x, y, *shapes.at(i)))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool hasVerticalLine(int lowy, int x, int highy, std::vector<shape*> shapes, unsigned int src, unsigned int dest)
{

	for (int y = lowy; y <= highy; y++)
	{ // vertical sweep
		for (unsigned int i = 0; i < shapes.size(); ++i)
		{
			if (i != src && i != dest)
			{
				if (isInsideBox(x, y, *shapes.at(i)))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool hasUpperPath(int originx, int originy, int candX, int candY, std::vector<shape*> shapes, unsigned int src, unsigned int dest)
{
	bool horizontalFails = false;
	bool verticalFails = false;

	if (originx < candX && originy < candY)
	{ // source is above and left
		horizontalFails = hasHorizontalLine(originx, originy, candX, shapes, src, dest);
		//					lowx	y		highx
		verticalFails = hasVerticalLine(originy, candX, candY, shapes, src, dest);
		//					lowy	x		highy
	}

	else if (originx < candX && originy > candY)
	{ // source is below and left
		horizontalFails = hasHorizontalLine(originx, candY, candX, shapes, src, dest);
		//					lowx	y		highx
		verticalFails = hasVerticalLine(candY, originx, originy, shapes, src, dest);
		//					lowy	x		highy
	}

	else if (originx > candX && originy < candY)
	{ // source right and above
		horizontalFails = hasHorizontalLine(candX, originy, originx, shapes, src, dest);
		//					lowx	y		highx
		verticalFails = hasVerticalLine(originy, candX, candY, shapes, src, dest);
		//					lowy	x		highy
	}
	else if (originx >  candX && originy > candY)
	{ // source is right and below
		horizontalFails = hasHorizontalLine(candX, candY, originx, shapes, src, dest);
		//					lowx	y		highx
		verticalFails = hasVerticalLine(candY, originx, originy, shapes, src, dest);
		//					lowy	x		highy
	}

	return (verticalFails || horizontalFails);
}
// an unobstructed upper-right-angle-path between two points exists

bool hasLowerPath(int originx, int originy, int candX, int candY, std::vector<shape*> shapes, unsigned int src, unsigned int dest)
{
	bool horizontalFails = false;
	bool verticalFails = false;

	if (originx < candX && originy < candY)
	{ // source is above and left
		horizontalFails = hasHorizontalLine(originx, candY, candX, shapes, src, dest);
		//									lowx	y		highx
		verticalFails = hasVerticalLine(originy, originx, candY, shapes, src, dest);
		//									lowy	x		highy
	}
	else if (originx < candX && originy > candY)
	{ // source is below and left
		horizontalFails = hasHorizontalLine(originx, originy, candX, shapes, src, dest);
		//									lowx	y		highx
		verticalFails = hasVerticalLine(candY, candX, originy, shapes, src, dest);
		//									lowy	x		highy
	}
	else if (originx > candX && originy < candY)
	{ // source is above and right
		horizontalFails = hasHorizontalLine(candX, candY, originx, shapes, src, dest);
		//									lowx	y		highx
		verticalFails = hasVerticalLine(originy, originx, candY, shapes, src, dest);
		//									lowy	x		highy
	}
	else if (originx > candX && originy > candY)
	{ // source is below and right
		horizontalFails = hasHorizontalLine(candX, originy, originx, shapes, src, dest);
		//									lowx	y		highx
		verticalFails = hasVerticalLine(candY, candX, originy, shapes, src, dest);
		//									lowy	x		highy
	}
	return (verticalFails || horizontalFails);
}
// an unobstructed lower-right-angle-path between two points exists

bool isObstructed(unsigned int sh, std::vector<shape*> shapes)
{
	for (unsigned int i = 0; i < shapes.size(); ++i)
	{
		if (i != sh)
		{
			if (isInsideBox(shapes.at(sh)->nodex[shape::TOP], shapes.at(sh)->nodey[shape::TOP], *shapes.at(i)))
			{
				return true;
			}
		}
	}
	return false;

}


void TKSCENE::RefreshPaths()
{
	for (unsigned int i = 0; i < paths.size(); ++i)
	{
		if (PathFindHypotenuse(paths.at(i)) != TK_CODE_PATH_FOUND)
		{
			paths.erase(paths.begin() + i);
		}
	}
}



int TKSCENE::PathFindHypotenuse(path* pa)
{

	// TODO: rework this function to improve speed, or do no call when dragging
	// should not be called while dragging a shape.
	pa->validPath = false;
	int exitCode = 0;

	unsigned int source, destination;
	source = pa->source;
	destination = pa->destination;
	shapes.at(source)->UpdateNodes();
	shapes.at(destination)->UpdateNodes();

	if (isObstructed(source, shapes))
	{
		return TK_CODE_PATH_NOT_FOUND;
	}
	// source has another shape on top of it

	if (isObstructed(destination, shapes))
	{
		return TK_CODE_PATH_NOT_FOUND;
	}
	// destination has another shape on top of it

	pa->nodes.clear(); // start with a clean slate
	// this may want to be modified some other time.

	pa->nodes.push_back(new node(shapes.at(source)->nodex[shape::TOP], shapes.at(source)->nodey[shape::TOP], node::NONE));
	int destinationx = shapes.at(destination)->nodex[shape::TOP]; // the final x destination of the path
	int destinationy = shapes.at(destination)->nodey[shape::TOP]; // the final y destination of the path
	int zerox = pa->nodes.at(0)->posx; // the starting x point of the path
	int zeroy = pa->nodes.at(0)->posy; // the starting y point of the path
	bool upperFails = false;
	bool lowerFails = false;

	if (zerox == destinationx && zeroy != destinationy)
	{
		if (zeroy > destinationy)
		{
			if (!hasVerticalLine(destinationy, zerox, zeroy, shapes, source, destination))
			{
				pa->nodes.push_back(new node(destinationx,destinationy,node::VERTICAL));
				exitCode = TK_CODE_GOOD_PATH;
			}
		}
		else
		{
			if (!hasVerticalLine(zeroy, zerox, destinationy, shapes, source, destination))
			{
				pa->nodes.push_back(new node(destinationx, destinationy, node::VERTICAL));
				exitCode = TK_CODE_GOOD_PATH;
			}
		}
	}
	// special vertical path

	else if (zeroy == destinationy && zerox != destinationx)
	{
		if (zerox > destinationx)
		{
			if (!hasHorizontalLine(destinationx, zeroy, zerox, shapes, source, destination))
			{
				pa->nodes.push_back(new node(destinationx, destinationy, node::HORIZONTAL));
				exitCode = TK_CODE_GOOD_PATH;
			}
		}
		else
		{
			if (!hasHorizontalLine(zerox, zeroy, destinationx, shapes, source, destination))
			{
				pa->nodes.push_back(new node(destinationx, destinationy, node::HORIZONTAL));
				exitCode = TK_CODE_GOOD_PATH;
			}
		}
	}
	// special horizontal path.


	int hyp_offsetx = 0;
	int hyp_offsety = 0;

	int hypx_scale = 11; // just a standard pick
	if (destinationx < zerox)
	{
		hypx_scale = -hypx_scale; // make negative if need be
	}
	float dx = (float)destinationx - (float)zerox; // total delta x
	float dy = (float)destinationy - (float)zeroy; // total delta y

	if ((int)dx % hypx_scale == 0)
	{
		hypx_scale++;
	}

	int hypy_scale = (int)((dy / dx)*hypx_scale); // slope  = dy/dx
	int count = 1;

	//	using <= in the below condition is what causes our loop crashing. DO NOT USE <=
	while (hyp_offsetx < abs(destinationx - zerox) && hyp_offsety < abs(destinationy - zeroy) && exitCode != TK_CODE_GOOD_PATH) // this check must be revised.
	{
		upperFails = hasUpperPath(zerox, zeroy, destinationx - hyp_offsetx, destinationy - hyp_offsety, shapes, source, destination);
		lowerFails = hasLowerPath(zerox, zeroy, destinationx - hyp_offsetx, destinationy - hyp_offsety, shapes, source, destination);
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
		else if (zerox == destinationx - hyp_offsetx && zeroy == destinationy - hyp_offsety) // special case to break loops, only valid path is onto itself
		{
			exitCode = TK_CODE_BAD_PATH;
			zerox++;
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
// Finds right-angle paths with nodes along the hypotenuse between the source and destination.

void TKSCENE::UpdateScreen()
{
	SDL_RenderCopy(rr, tt, NULL, NULL);
	SDL_RenderPresent(rr); // show
}
// forces the renderer to update and redisplay

int TKSCENE::GetAllEvents()
{
	static bool dragMode;
	static bool editMode;
	static bool lineMode;
	static bool sourceIsNotDestination;
	static int selectedShape;
	static int pathSource, pathDest;


	sourceIsNotDestination = false;
	while (SDL_PollEvent(ee) != 0)
	{
		int mousex = ee->motion.x;
		int mousey = ee->motion.y;
		
#ifdef _DEBUG
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

#pragma region Key Presses

		if (ee->key.keysym.scancode == SDL_SCANCODE_1 && ee->key.state == SDL_PRESSED)
		{
			shapes.push_back(new shape(shape::TK_RHOMBUS, PrimaryColor, 0, 0, 100, 50, shapeIterator));
			shapeIterator++;
			return TK_CODE_ADD_SHAPE;
		}
		// KEYPRESS: 1
		if (ee->key.keysym.scancode == SDL_SCANCODE_2 && ee->key.state == SDL_PRESSED)
		{
			shapes.push_back(new shape(shape::TK_RECTANGLE, PrimaryColor, 0, 0, 100, 50, shapeIterator));
			shapeIterator++;
			return TK_CODE_ADD_SHAPE;
		}
		// KEYPRESS: 2
		if (ee->key.keysym.scancode == SDL_SCANCODE_3 && ee->key.state == SDL_PRESSED)
		{
			shapes.push_back(new shape(shape::TK_ELLIPSE, PrimaryColor, 0, 0, 100, 50, shapeIterator));
			shapeIterator++;
			return TK_CODE_ADD_SHAPE;
		}
		// KEYPRESS: 3
		if (ee->key.keysym.scancode == SDL_SCANCODE_Q && ee->key.state == SDL_PRESSED)
		{
			return TK_CODE_QUITTING;
		}
		// KEYPRESS: Q
		if (ee->key.keysym.scancode == SDL_SCANCODE_DELETE && ee->key.state == SDL_PRESSED)
		{
			shapes.pop_back();
			return TK_CODE_DELETE_SHAPE;
		}
		// KEYPRESS: DEL
		if (ee->key.keysym.scancode == SDL_SCANCODE_F5 && ee->key.state == SDL_PRESSED)
		{
			RefreshPaths();
			return TK_CODE_REFRESH_PATHS;
		}
		// KEYPRESS: F5
		if (ee->key.keysym.scancode == SDL_SCANCODE_F2 && ee->key.state == SDL_PRESSED)
		{
			color* col = new color(0, 0, 0, 0);
			shape* one = new shape(shape::TK_TEXT, col, 0, 0, 100, 100, 49);
			one->drawText(rr);
			return TK_CODE_MISC;
		}
		// KEYPRESS: F2
		if (ee->key.keysym.scancode == SDL_SCANCODE_F1 && ee->key.state == SDL_PRESSED)
		{
			return TK_CODE_MISC;
		}
		// KEYPRESS: F1

#pragma endregion

#pragma region Mouse Events
		if (ee->button.button == SDL_BUTTON_LEFT)
		{
			if (ee->button.state == SDL_PRESSED)
			{
				for (unsigned int i = 0; i < shapes.size(); ++i)
				{
					if (!shapes.empty() && ee->motion.x < shapes.at(i)->GetPosX() + shapes.at(i)->GetWidth() && ee->motion.x > shapes.at(i)->GetPosX())
					{
						if (ee->motion.y < shapes.at(i)->GetPosY() + shapes.at(i)->GetHeight() && ee->motion.y > shapes.at(i)->GetPosY())
						{
							dragMode = true;	// the cursor clicked inside the bounds of the shape
							selectedShape = i;	// last shape within bounds
						}
					}
				}
			}
			if (dragMode && !shapes.empty() && abs(ee->motion.xrel) < TK_WINDOW_WIDTH && abs(ee->motion.yrel) < TK_WINDOW_WIDTH)
			{
					// DRAGGING!
					shapes.at(selectedShape)->SetPos(shapes.at(selectedShape)->GetPosX() + ee->motion.xrel, shapes.at(selectedShape)->GetPosY() + ee->motion.yrel);
			}
			return TK_CODE_DRAG;
		}
		// CLICKED: LEFT
		else
		{
			dragMode = false;
		}
		// NOT-CLICKED && NOT-HELD: LEFT

#ifdef RESIZE
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
																				
		if (ee->button.button == 4 && editMode && !shapes.empty()) // right click held + drag is 4 instead of 3, consider #define'ing
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
#endif

#ifndef RESIZE
		if (ee->button.button == SDL_BUTTON_RIGHT && ee->button.state == SDL_PRESSED)
		{
			context->box->x = ee->motion.x;
			context->box->y = ee->motion.y;
			
			if (context->active)
			{
				context->active = false;
				return TK_CODE_MENU_OFF;
			}
			else
			{
				context->active = true;
				return TK_CODE_MENU_ON;
			}
			return TK_CODE_MISC;
		}

#endif

		if (ee->button.button == SDL_BUTTON_MIDDLE)
		{
			
			if (ee->button.state == SDL_PRESSED)
			{
				pathSource = 0;
				for (unsigned int i = 0; i < shapes.size(); ++i)
				{
					if (!shapes.empty() && ee->motion.x < shapes.at(i)->GetPosX() + shapes.at(i)->GetWidth() && ee->motion.x > shapes.at(i)->GetPosX())
					{
						if (ee->motion.y < shapes.at(i)->GetPosY() + shapes.at(i)->GetHeight() && ee->motion.y > shapes.at(i)->GetPosY())
						{
							lineMode = true;	// the cursor clicked inside the bounds of the shape
							selectedShape = i;	// last shape within bounds
							pathSource = i;
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
				pathDest = 0;
				for (unsigned int i = 0; i < shapes.size(); ++i)
				{
					if (!shapes.empty())
					{
						if (ee->motion.x < shapes.at(i)->GetPosX() + shapes.at(i)->GetWidth() && ee->motion.x > shapes.at(i)->GetPosX())
						{
							if (ee->motion.y < shapes.at(i)->GetPosY() + shapes.at(i)->GetHeight() && ee->motion.y > shapes.at(i)->GetPosY())
							{
								selectedShape = i;	// last shape within bounds
								pathDest = i;
								if (pathSource != pathDest) // if our shapes are not the same
								{
									sourceIsNotDestination = true; // source shape is not destination shape
								}
									
							}
						}
					}
				}

				// now we make the line
				if (sourceIsNotDestination)
				{
					// draw with shapes at last and second to last position
					paths.push_back(new path(pathSource, pathDest)); // send a new path to the back of our vector

					if (PathFindHypotenuse(paths.back()) != TK_CODE_PATH_FOUND) // if we don't have a hypot. path
					{
						paths.pop_back(); // delete it
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

#pragma endregion

	}
	return 0; 
}
// process events

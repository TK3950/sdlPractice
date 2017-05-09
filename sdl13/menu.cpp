#include "menu.h"

void menu::drawDropDown(SDL_Renderer *r)
{

	SDL_Rect *myMenu;
	myMenu = new SDL_Rect();
	myMenu->x = posx;
	myMenu->y = posy;
	myMenu->h = height;
	myMenu->w = width;

}
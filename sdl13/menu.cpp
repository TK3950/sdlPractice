#include "menu.h"

void menu::drawDropDown(SDL_Renderer *r)
{

	box.x = posx;
	box.y = posy;
	box.w = width;
	box.h = height;
	
	SDL_RenderDrawRect(r, &box);
}

menu::~menu()
{
	delete &posx;
	delete &posy;
	delete &width;
	delete &height;
}

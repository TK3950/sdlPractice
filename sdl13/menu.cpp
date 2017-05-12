#include "menu.h"


menu::menu(int x, int y, int w, int h) : posx(x), posy(y), width(w), height(h), active(false)
{
	boxes[0] = new SDL_Rect{ posx, posy, width, height };
	box = boxes[0];
}
void menu::drawDropDown(SDL_Renderer *r)
{
	SDL_SetRenderDrawColor(r, 140, 140, 140, 0);
	SDL_RenderFillRect(r, box);
	SDL_RenderDrawRect(r, box);
}

menu::~menu()
{
	delete &posx;
	delete &posy;
	delete &width;
	delete &height;
}

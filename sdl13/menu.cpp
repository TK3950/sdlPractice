#include "menu.h"



menu::menu(int x, int y, int w, int h) : posx(x), posy(y), width(w), height(h), active(false), visibleHeight(h/10)
{
	for (int i = 0; i <= 9; i++)
	{
		boxes[i] = new SDL_Rect{ posx, posy + (i*(height / 10)), width, height / 10 };
	}
	box = boxes[0];

	TTF_Init();
	Sans = TTF_OpenFont("Sans.ttf", 24);
	black = { 0,0,0 };

	firstMessage = TTF_RenderText_Solid(Sans, "put your text here", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

}

void menu::updateBoxes()
{
	// calculate the height of the visible box in here once that typing has been handled.
	for (int i = 0; i <= 9; i++)
	{
		boxes[i]->x = posx;
		boxes[i]->y = posy + (i*(height / 10));
	}
}

void menu::drawDropDown(SDL_Renderer *r)
{
	SDL_SetRenderDrawColor(r, 140, 140, 140, 0); // a basic grey

	for (int i = 0; i <= 9; i++)
	{
		SDL_RenderFillRect(r, box);
		SDL_RenderDrawRect(r, box);
	}


}

menu::~menu()
{
	delete &posx;
	delete &posy;
	delete &width;
	delete &height;
}

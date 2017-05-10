#include "menu.h"


menu::menu(int x, int y, int w, int h) : posx(x), posy(y), width(w), height(h), active(false)
{
	box = new SDL_Rect{ posx, posy, width, height };
}
void menu::drawDropDown(SDL_Renderer *r)
{
	SDL_SetRenderDrawColor(r, 140, 140, 140, 0);
	SDL_RenderFillRect(r, box);
	SDL_RenderDrawRect(r, box);

	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

	SDL_Color Black = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(r, surfaceMessage); //now you can convert it into a texture


}

menu::~menu()
{
	delete &posx;
	delete &posy;
	delete &width;
	delete &height;
}

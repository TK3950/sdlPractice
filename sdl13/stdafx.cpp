// stdafx.cpp : source file that includes just the standard includes
// sdl13.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <SDL\SDL.h>

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

shape::shape(form f, int x, int y, int w, int h) : width(w), height(h), posx(x), posy(y)
{
	if (f == TK_RHOMBUS)
	{
		rhombus* rh = new rhombus(x, y, w, h);
		this->posx = rh->posx;
		this->posy = rh->posy;
		this->width = rh->width;
		this->height = rh->height;
	}
	else if (f == TK_RECTANGLE)
	{
		rectangle* r = new rectangle(x, y, w, h);
		this->posx = r->posx;
		this->posy = r->posy;
		this->width = r->width;
		this->height = r->height;
	}
}

void shape::drawShape(SDL_Renderer *r, shape *s)
{
}

void rhombus::drawRhombus(SDL_Renderer *r, rhombus t) {
	SDL_RenderDrawLine(r, t.posx, t.posy + t.height/2,		t.posx + t.width/2, t.posy);
	SDL_RenderDrawLine(r, t.posx, t.posy + t.height / 2, t.posx + t.width / 2, t.posy+t.height);

	SDL_RenderDrawLine(r, t.posx + t.width, t.posy + t.height / 2, t.posx + t.width / 2, t.posy);
	SDL_RenderDrawLine(r, t.posx + t.width, t.posy + t.height / 2, t.posx + t.width / 2, t.posy + t.height);

}
void rectangle::drawRectangle(SDL_Renderer *r, rectangle t) {

	SDL_RenderDrawLine(r, t.posx, t.posy, t.posx + t.width, t.posy);
	SDL_RenderDrawLine(r, t.posx, t.posy, t.posx, t.posy+t.height);
	SDL_RenderDrawLine(r, t.posx+t.width, t.posy+t.height, t.posx+t.width, t.posy);
	SDL_RenderDrawLine(r, t.posx+t.width, t.posy+t.height, t.posx, t.posy+t.height);

}
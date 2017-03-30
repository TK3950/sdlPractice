// stdafx.cpp : source file that includes just the standard includes
// sdl13.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <SDL\SDL.h>

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file


void shape::drawShape(SDL_Renderer *r, shape *s)
{
	if (s->fo == TK_RHOMBUS)
	{
		drawRhombus(r, *s);
	}

	if (s->fo == TK_RECTANGLE)
	{
		drawRectangle(r, *s);
	}
}

void shape::drawRhombus(SDL_Renderer *r, shape t) {
	SDL_RenderDrawLine(r, t.posx, t.posy + t.height/2,		t.posx + t.width/2, t.posy);
	SDL_RenderDrawLine(r, t.posx, t.posy + t.height / 2, t.posx + t.width / 2, t.posy+t.height);

	SDL_RenderDrawLine(r, t.posx + t.width, t.posy + t.height / 2, t.posx + t.width / 2, t.posy);
	SDL_RenderDrawLine(r, t.posx + t.width, t.posy + t.height / 2, t.posx + t.width / 2, t.posy + t.height);

}
void shape::drawRectangle(SDL_Renderer *r, shape t) {

	SDL_RenderDrawLine(r, t.posx, t.posy, t.posx + t.width, t.posy);
	SDL_RenderDrawLine(r, t.posx, t.posy, t.posx, t.posy+t.height);
	SDL_RenderDrawLine(r, t.posx+t.width, t.posy+t.height, t.posx+t.width, t.posy);
	SDL_RenderDrawLine(r, t.posx+t.width, t.posy+t.height, t.posx, t.posy+t.height);

}
// stdafx.cpp : source file that includes just the standard includes
// sdl13.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information
#pragma once
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

	if (s->fo == TK_ELLIPSE)
	{
		drawEllipse(r, *s);
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

void shape::drawEllipse(SDL_Renderer *r, shape t) {
	double a = t.width / 2;
	double b = t.height / 2;
	double last_deviance = 0;
	SDL_RenderDrawPoint(r, t.posx + a, t.posy);
	SDL_RenderDrawPoint(r, t.posx + a, t.posy + (b*2));
	SDL_RenderDrawPoint(r, t.posx , t.posy + b);
	SDL_RenderDrawPoint(r, t.posx + (a * 2), t.posy +b);


	for (int x = -t.width; x <= t.width; x++)
	{
		int y = round(sqrt((b*b)*(1 - ((x*x) / (a*a)))));
		SDL_RenderDrawPoint(r, t.posx + x + a, t.posy + y + b);
		SDL_RenderDrawPoint(r, t.posx + x + a, t.posy - y + b);
	}
	for (int y = -t.height; y <= t.height; y++)
	{
		int x = round(sqrt((a*a)*(1 - ((y*y) / (b*b)))));
		SDL_RenderDrawPoint(r, t.posx + x + a, t.posy + y + b);
		SDL_RenderDrawPoint(r, t.posx - x + a, t.posy + y + b);
	}


	
	

}
// stdafx.cpp : source file that includes just the standard includes
// sdl13.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information
#pragma once
#include "stdafx.h"
#include <SDL\SDL.h>
#define BRESENHAM 1

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file


void shape::drawShape(SDL_Renderer *r, color* c, shape *s)
{
	SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);
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
#ifndef BRESENHAM

	SDL_RenderDrawPoint(r, t.posx + a, t.posy);
	SDL_RenderDrawPoint(r, t.posx + a, t.posy + (b*2));
	SDL_RenderDrawPoint(r, t.posx , t.posy + b);
	SDL_RenderDrawPoint(r, t.posx + (a * 2), t.posy +b);

	for (int x = -t.width; x <= t.width; x++)
	{
		
		{
			int y = round(sqrt((b*b)*(1 - ((x*x) / (a*a)))));
			
			SDL_RenderDrawPoint(r, t.posx + x + a, t.posy + y + b);
			SDL_RenderDrawPoint(r, t.posx + x + a, t.posy - y + b);
		}
		
	}


	for (int y = -t.height; y <= t.height; y++)
	{
		
		{

			int x = round(sqrt((a*a)*(1 - ((y*y) / (b*b)))));
			SDL_RenderDrawPoint(r, t.posx + x + a, t.posy + y + b);
			SDL_RenderDrawPoint(r, t.posx - x + a, t.posy + y + b);
		}
	}
#endif

#ifdef BRESENHAM
	int width = t.width/2;
	int height = t.height/2;
	int xc = t.posx+a;
	int yc = t.posy+b;
	{
		int a2 = width * width;
		int b2 = height * height;
		int fa2 = 4 * a2, fb2 = 4 * b2;
		int x, y, sigma;

		/* first half */
		for (x = 0, y = height, sigma = 2 * b2 + a2*(1 - 2 * height); b2*x <= a2*y; x++)
		{
			SDL_RenderDrawPoint(r, xc + x, yc + y);
			SDL_RenderDrawPoint(r, xc - x, yc + y);
			SDL_RenderDrawPoint(r, xc + x, yc - y);
			SDL_RenderDrawPoint(r, xc - x, yc - y);
			if (sigma >= 0)
			{
				sigma += fa2 * (1 - y);
				y--;
			}
			sigma += b2 * ((4 * x) + 6);
		}

		/* second half */
		for (x = width, y = 0, sigma = 2 * a2 + b2*(1 - 2 * width); a2*y <= b2*x; y++)
		{
			SDL_RenderDrawPoint(r, xc + x, yc + y);
			SDL_RenderDrawPoint(r, xc - x, yc + y);
			SDL_RenderDrawPoint(r, xc + x, yc - y);
			SDL_RenderDrawPoint(r, xc - x, yc - y);
			if (sigma >= 0)
			{
				sigma += fb2 * (1 - x);
				x--;
			}
			sigma += a2 * ((4 * y) + 6);
		}
	}
#endif
	
	a += 1;

}

void menu::drawDropDown(SDL_Renderer* r, int x, int y, int w, int h)
{
	

	SDL_RenderDrawLine(r, x, y, x + w, y);
	SDL_RenderDrawLine(r, x, y, x, y + h);
	SDL_RenderDrawLine(r, x + w, y + h, x + w, y);
	SDL_RenderDrawLine(r, x + w, y + h, x, y + h);
	for (int lx = x + 1; lx < x+w; ++lx)
	{
		for (int ly = y + 1; ly < y+h; ++ly)
		{
			SDL_SetRenderDrawColor(r, 200, 200, 200, 200);
			SDL_RenderDrawPoint(r, lx, ly );
		}
	}
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	
}
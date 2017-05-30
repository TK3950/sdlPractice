// shape.cpp : source file that includes just the standard includes
// sdl13.pch will be the pre-compiled header
// shape.obj will contain the pre-compiled type information


#include "shape.h"
#include <SDL\SDL.h>

#define BRESENHAM 1

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

int shape::GetPointX()
{
	return pointx;
}
int shape::GetPointY()
{
	return pointy;
}
void shape::SetPoints(int newX, int newY)
{
	pointx = newX;
	pointy = newY;
}

int shape::GetWidth()
{
	return width;
}
int shape::GetHeight()
{
	return height;
}
void shape::SetWidth(int newWidth)
{
	width = newWidth;
}
void shape::SetHeight(int newHeight)
{
	height = newHeight;
}

int shape::GetPosX()
{
	return posx;
}
int shape::GetPosY()
{
	return posy;
}
void shape::SetPos(int newX, int newY)
{
	posx = newX;
	posy = newY;
}


void shape::drawShape(SDL_Renderer *r, color* c)
{
	SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);
	switch (this->fo)
	{
		case TK_RHOMBUS:
			this->drawRhombus(r);
			break;
		case TK_RECTANGLE:
			this->drawRectangle(r);
			break;
		case TK_ELLIPSE:
			this->drawEllipse(r);
			break;
	}
}

void shape::drawArrow(SDL_Renderer *r)
{
	SDL_RenderDrawLine(r, this->GetPosX(), this->GetPosY(), this->GetPointX(), this->GetPointY());
}

void shape::drawLine(SDL_Renderer *r)
{
	SDL_RenderDrawLine(r, this->GetPosX(), this->GetPosY(), this->GetPointX(), this->GetPointY());
}

void shape::drawRhombus(SDL_Renderer *r) {
	SDL_RenderDrawLine(r, this->GetPosX(), this->GetPosY() + this->height/2,		this->GetPosX() + this->width/2, this->GetPosY());
	SDL_RenderDrawLine(r, this->GetPosX(), this->GetPosY() + this->height / 2, this->GetPosX() + this->width / 2, this->GetPosY()+this->height);

	SDL_RenderDrawLine(r, this->GetPosX() + this->width, this->GetPosY() + this->height / 2, this->GetPosX() + this->width / 2, this->GetPosY());
	SDL_RenderDrawLine(r, this->GetPosX() + this->width, this->GetPosY() + this->height / 2, this->GetPosX() + this->width / 2, this->GetPosY() + this->height);

}

void shape::drawRectangle(SDL_Renderer *r) {

	SDL_RenderDrawLine(r, this->GetPosX(), this->GetPosY(), this->GetPosX() + this->width, this->GetPosY());
	SDL_RenderDrawLine(r, this->GetPosX(), this->GetPosY(), this->GetPosX(), this->GetPosY()+this->height);
	SDL_RenderDrawLine(r, this->GetPosX()+this->width, this->GetPosY()+this->height, this->GetPosX()+this->width, this->GetPosY());
	SDL_RenderDrawLine(r, this->GetPosX()+this->width, this->GetPosY()+this->height, this->GetPosX(), this->GetPosY()+this->height);

}

void shape::drawEllipse(SDL_Renderer *r) {
	double a = this->width / 2;
	double b = this->height / 2;
#ifndef BRESENHAM

	SDL_RenderDrawPoint(r, this->GetPosX() + a, this->GetPosY());
	SDL_RenderDrawPoint(r, this->GetPosX() + a, this->GetPosY() + (b*2));
	SDL_RenderDrawPoint(r, this->GetPosX() , this->GetPosY() + b);
	SDL_RenderDrawPoint(r, this->GetPosX() + (a * 2), this->GetPosY() +b);

	for (int x = -this->width; x <= this->width; x++)
	{
		
		{
			int y = round(sqrt((b*b)*(1 - ((x*x) / (a*a)))));
			
			SDL_RenderDrawPoint(r, this->GetPosX() + x + a, this->GetPosY() + y + b);
			SDL_RenderDrawPoint(r, this->GetPosX() + x + a, this->GetPosY() - y + b);
		}
		
	}


	for (int y = -this->height; y <= this->height; y++)
	{
		
		{

			int x = round(sqrt((a*a)*(1 - ((y*y) / (b*b)))));
			SDL_RenderDrawPoint(r, this->GetPosX() + x + a, this->GetPosY() + y + b);
			SDL_RenderDrawPoint(r, this->GetPosX() - x + a, this->GetPosY() + y + b);
		}
	}
#endif

#ifdef BRESENHAM
	int width = this->width/2;
	int height = this->height/2;
	int xc = this->GetPosX()+(int)a;
	int yc = this->GetPosY()+(int)b;
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




}

void shape::drawText(SDL_Renderer *r, SDL_Rect *rect)
{


	

}

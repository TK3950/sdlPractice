// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef _STDAFX_H
#define _STDAFX_H
#include "targetver.h"
#include <math.h>
#include <SDL/SDL.h>
#include "color.h"
#include <stdio.h>
#include <tchar.h>
#define TK_WINDOW_WIDTH 1000
#define TK_WINDOW_HEIGHT 680

// TODO: develop path, line, and pathfinding

class menu {
public:
	menu(int x, int y, int w, int h) : posx(x), posy(y), width(w), height(h) {}
	void drawDropDown(SDL_Renderer *r, int x, int y, int w, int h);

	int posx;
	int posy;
	int width;
	int height;
};

class shape {
public:
	enum form {
		TK_RECTANGLE = 0,
		TK_RHOMBUS,
		TK_ELLIPSE,
	};

	shape(form f, color* c, int x, int y, int w, int h)
		: width(w), height(h), posx(x), posy(y), fo(f), co(c), pointx(x + w), pointy(y + h)
		{}


	void drawShape(SDL_Renderer *r, color *c, shape *s);
	void drawRhombus(SDL_Renderer *r, shape s);
	void drawRectangle(SDL_Renderer *r, shape s);
	void drawEllipse(SDL_Renderer *r, shape s);
	void drawLine(SDL_Renderer *r, shape s);
	void drawArrow(SDL_Renderer *r, shape s);
	
	int GetPosX();
	int GetPosY();
	void SetPos(int newX, int newY);

	int GetPointX();
	int GetPointY();
	void SetPoints(int newX, int newY);
	
	int GetWidth();
	int GetHeight();
	void SetWidth(int newWidth);
	void SetHeight(int newHeight);

	color* co;
	form fo;

private:
	int posx, posy, pointx, pointy, width, height;
	
};



#endif
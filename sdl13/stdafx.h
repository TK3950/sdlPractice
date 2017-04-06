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
#include <stdio.h>
#include <tchar.h>
#define TK_WINDOW_WIDTH 1000
#define TK_WINDOW_HEIGHT 680

// TODO: create addition shape definitions

class menu {
public:
	menu(int x, int y, int w, int h) : posx(x), posy(y), width(w), height(h) {}
	void drawDropDown(SDL_Renderer *r, int x, int y, int w, int h);

	int posx;
	int posy;
	int width;
	int height;
};

class color {
public:
	color(int red, int green, int blue, int alpha) : r(red), g(green), b(blue), a(alpha) {}
	int r;
	int g;
	int b;
	int a;
};

class shape {
public:
	enum form {
		TK_RECTANGLE = 0,
		TK_RHOMBUS,
		TK_ELLIPSE,
		TK_TEXT,
		TK_LINE,
		TK_ARROW,
		TK_MENU
	};

	shape(form f, color* c, int x, int y, int w, int h) : width(w), height(h), posx(x), posy(y), fo(f), co(c){}


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
	
	int width, height;
	color* co;
	form fo;

private:
	int posx, posy, pointx, pointy;
	
};



#endif
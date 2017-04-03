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

class shape {
public:
	enum form { // bring into lower header
		TK_RECTANGLE = 0,
		TK_RHOMBUS,
		TK_ELLIPSE,
		TK_TEXT,
		TK_LINE,
		TK_ARROW,
		TK_MENU
	};

	shape(form f, int x, int y, int w, int h) : width(w), height(h), posx(x), posy(y), fo(f){}


	void drawShape(SDL_Renderer *r, shape *s);
	void drawRhombus(SDL_Renderer *r, shape s);
	void drawRectangle(SDL_Renderer *r, shape s);
	void drawEllipse(SDL_Renderer *r, shape s);
	

	
	int width, height, posx, posy;

	form fo;
};

#endif
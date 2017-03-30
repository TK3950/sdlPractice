// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <tchar.h>


// TODO: rework, use a general shape class, create a type enum



class rhombus {
public:
	rhombus(int x, int y, int w, int h)
		: width(w), height(h), posx(x), posy(y) {}

	void drawRhombus(SDL_Renderer *r, rhombus t);

	int width, height, posx, posy;

	//~rhombus();
};

class rectangle {
public:
	rectangle(int x, int y, int w, int h)
		: width(w), height(h), posx(x), posy(y) {}

	void drawRectangle(SDL_Renderer *r, rectangle t);
	

	int width, height, posx, posy;
	//~rectangle();
};

class shape {

	enum form { // bring into lower header
		TK_RECTANGLE = 0,
		TK_RHOMBUS,
		TK_ELLIPSE,
		TK_TEXT,
		TK_LINE,
		TK_ARROW
	};

	shape(form f, int x, int y, int w, int h) : width(w), height(h), posx(x), posy(y), fo(f) {}


public:
	void drawShape(SDL_Renderer *r, shape *s);
	int width, height, posx, posy;

	form fo;
};
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
class shape {
	
};


class rhombus : shape {
public:
	rhombus(int x, int y, int w, int h)
		: width(w), height(h), posx(x), posy(y) {}

	void drawRhombus(SDL_Renderer *r, rhombus t);

	int width, height, posx, posy;

	//rhombus();
};

class rectangle : shape {
public:
	rectangle(int x, int y, int w, int h)
		: width(w), height(h), posx(x), posy(y) {}

	void drawRectangle(SDL_Renderer *r, rectangle t);
	

	int width, height, posx, posy;
	//~rectangle();
};
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
class rhombus {
public:
	rhombus(int x, int y, int w, int h)
		: width(w), height(h), posx(x), posy(y) {}

	void drawRhombus(SDL_Renderer *r, rhombus t);

	int width, height, posx, posy;


};
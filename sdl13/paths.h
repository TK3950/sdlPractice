#pragma once
#ifndef _PATHS_H
#define _PATHS_H 1
#include <SDL/SDL.h>
#include "color.h"

class path {
public:
	path(int srcX, int srcY, int destX, int destY) : startx(srcX), starty(srcY), endx(destX), endy(destY) {}
	void NewPath();
	void path::drawPath(SDL_Renderer *r, color* c, path *s);

private:
	unsigned int nodes;
	int startx, starty;
	int endx, endy;

};

class line {
public:
	line(int x, int y, int x2, int y2) : posx(x), posy(y), pointx(x2), pointy(y2) {}

private:
	int posx, posy, pointx, pointy;
	bool isVertical, isHorizontal;
};

#endif
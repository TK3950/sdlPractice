#pragma once
#ifndef _PATHS_H
#define _PATHS_H 1
#include <SDL/SDL.h>
#include "color.h"

class path {
public:
	path(unsigned int shape1, unsigned int shape2, unsigned int node_count) : source(shape1), destination(shape2), nodes(node_count) {
		nodex = new int[node_count];
		nodey = new int[node_count];
		NewPath();
	}
	void NewPath();
	void drawPath(SDL_Renderer *r, color* c, path *s);

	unsigned int source;
	unsigned int destination;

	unsigned int nodes;
	int * nodex;
	int * nodey;
};

class line {
public:
	line(int x, int y, int x2, int y2) : posx(x), posy(y), pointx(x2), pointy(y2) {}

private:
	int posx, posy, pointx, pointy;
	bool isVertical, isHorizontal;
};

#endif
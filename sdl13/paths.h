#pragma once
#ifndef _PATHS_H
#define _PATHS_H 1
#include <SDL/SDL.h>
#include "color.h"
#include <vector>

class node{
public:
	enum branchType {
		NONE = 0,
		UPPER = 1,
		LOWER = 2
	};

	node(int x, int y, branchType b) : posx(x), posy(y), branch(b) {}
	int posx;
	int posy;



	branchType branch;


};


class path {
public:
	path(unsigned int shape1, unsigned int shape2, unsigned int node_count) : source(shape2), destination(shape1) {
		
	}



	void drawPath(SDL_Renderer *r, color* c, path *s);

	unsigned int source;
	unsigned int destination;

	std::vector<node*> nodes;

	

};

class line {
public:
	line(int x, int y, int x2, int y2) : posx(x), posy(y), pointx(x2), pointy(y2) {}

private:
	int posx, posy, pointx, pointy;
	bool isVertical, isHorizontal;
};

#endif
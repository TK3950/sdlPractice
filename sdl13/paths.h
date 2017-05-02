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
	path(unsigned int shape1Id, unsigned int shape2Id, unsigned int node_count) : sourceId(shape2Id), destinationId(shape1Id), validPath(false) {
		
	}
	/*
	Each path might be better classified as a link. 
	When selecting two shapes for a path, it links these two shapes in memory
	from source to destination. PathFind() should try to create a complete path from source to destination.
	*/


	void drawPath(SDL_Renderer *r, color* c, path *s);
	unsigned int sourceId;
	unsigned int destinationId;

	std::vector<node*> nodes;
	bool validPath;
	

};

class line {
public:
	line(int x, int y, int x2, int y2) : posx(x), posy(y), pointx(x2), pointy(y2) {}

private:
	int posx, posy, pointx, pointy;
	bool isVertical, isHorizontal;
};

#endif
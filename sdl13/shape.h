// shape.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef _SHAPE_H
#define _SHAPE_H
#include "targetver.h"
#include <math.h>
#include <SDL/SDL.h>
#include "color.h"
#include <stdio.h>
#include <tchar.h>
#define TK_WINDOW_WIDTH 1000
#define TK_WINDOW_HEIGHT 680

class shape {
public:
	enum form {
		TK_RECTANGLE = 0,
		TK_RHOMBUS,
		TK_ELLIPSE,
	};

	enum node {
		TOP = 0,
		RIGHT,
		BOTTOM,
		LEFT,
	};

	shape(form f, color* c, int x, int y, int w, int h, unsigned int identifier)
		: width(w), height(h), posx(x), posy(y), fo(f), co(c), pointx(x + w), pointy(y + h), id(identifier)
		{
			
		}


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

	void UpdateNodes()
	{
		nodex[node::TOP] = posx + width / 2;
		nodey[node::TOP] = posy;

		nodex[node::RIGHT] = posx + width;
		nodey[node::RIGHT] = posy + height / 2;

		nodex[node::BOTTOM] = posx + width / 2;
		nodey[node::BOTTOM] = posy + height;

		nodex[node::LEFT] = posx;
		nodey[node::LEFT] = posy + height / 2;
	}
	color* co;
	form fo;

	int nodex[4];
	int nodey[4];

	unsigned int id;


private:
	int posx, posy, pointx, pointy, width, height;

	
};



#endif
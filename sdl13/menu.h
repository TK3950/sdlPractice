#pragma once
#ifndef _MENU_H
#define _MENU_H true
#include <SDL\SDL.h>
#include <SDL_ttf.h>

/* We may want to re-examine our blitting process in tksdl.cpp
 * We're going to see about using a .bmp resource file and some text
 * to add a context menu functionality to this program. This will require
 * a lot of restructuring in other portions of the program, but since
 * so many functions are working properly, we can afford to spend a
 * little time cleaning and improving our organization.
 *
 *
 * We may want to make shape objects map directly into SDL_Rect's
 * It might improve render-time, if we're lucky.
 * Either way, if we're going to use .bmp resources, we'll need
 * to look deeper into the blitting process, which we should be
 * able to improve if we use our SDL_Rect's there.
 */


class menu
{
	public:
		menu(int x, int y, int w, int h);
		~menu();
		void drawDropDown(SDL_Renderer *r);
		void updateBoxes();

		enum type {
			SHAPE_CONTEXT = 0,
			PATH_CONTEXT = 1,
			SPACE_CONTEXT = 2,

		};

		SDL_Rect* boxes[10];

		SDL_Rect* box;
	int posx;
	int posy;
	int width;
	int height;
	int visibleHeight;

	bool active;

	TTF_Font* Sans;
	SDL_Color black;
	SDL_Surface* firstMessage;
	SDL_Texture* firstTexture;

};





#endif
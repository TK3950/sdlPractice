#pragma once
#ifndef COLOR_H
#define COLOR_H 1
class color {
public:
	color(int red, int green, int blue, int alpha) : r(red), g(green), b(blue), a(alpha) {}
	int r;
	int g;
	int b;
	int a;
};

color TK_RED	(255,	0,		0,		255);
color TK_GREEN	(0,		255,	0,		255);
color TK_BLUE	(0,		0,		255,	255);

color TK_CYAN	(0,		 255,	255,	255);


#endif
#pragma once
#ifndef _COLOR_H
#define _COLOR_H 1
class color {
public:
	color(int red, int green, int blue, int alpha) : r(red), g(green), b(blue), a(alpha) {}
	int r;
	int g;
	int b;
	int a;
};
#endif
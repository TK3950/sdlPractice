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
#endif
#include "paths.h"

void path::NewPath()
{

}


void path::drawPath(SDL_Renderer *r, color* c, path *p)
{
	SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);

}

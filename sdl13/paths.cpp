#include "paths.h"

void path::NewPath()
{
	// this is where we try to find a path.
}


void path::drawPath(SDL_Renderer *r, color* c, path *p)
{
	SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);

}

#include "paths.h"


void path::drawPath(SDL_Renderer *r, color* c, path *p)
{
	SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);
	
	if(!(p->nodes.empty()))
	{
		for (unsigned int i = 1; i < p->nodes.size(); ++i)
		{
			if (i != p->nodes.size())
			{
				if (p->nodes.at(i)->branch == node::UPPER)
				{
					SDL_RenderDrawLine(r, p->nodes.at(i-1)->posx, p->nodes.at(i-1)->posy, p->nodes.at(i)->posx, p->nodes.at(i-1)->posy);
					SDL_RenderDrawLine(r, p->nodes.at(i)->posx, p->nodes.at(i-1)->posy, p->nodes.at(i)->posx, p->nodes.at(i)->posy);
				}
				else if (p->nodes.at(i)->branch == node::LOWER)
				{
					SDL_RenderDrawLine(r, p->nodes.at(i - 1)->posx, p->nodes.at(i - 1)->posy, p->nodes.at(i-1)->posx, p->nodes.at(i)->posy);
					SDL_RenderDrawLine(r, p->nodes.at(i - 1)->posx, p->nodes.at(i)->posy, p->nodes.at(i)->posx, p->nodes.at(i)->posy);
				}
				else
				{

				}
			}
			else
			{
				
			}
		}
	}

}

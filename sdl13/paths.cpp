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
					if (p->nodes.at(i - 1)->posy <= p->nodes.at(i)->posy)
					{
						SDL_RenderDrawLine(r, p->nodes.at(i - 1)->posx, p->nodes.at(i - 1)->posy, p->nodes.at(i)->posx, p->nodes.at(i - 1)->posy);
						SDL_RenderDrawLine(r, p->nodes.at(i)->posx, p->nodes.at(i - 1)->posy, p->nodes.at(i)->posx, p->nodes.at(i)->posy);
					}
					else if (p->nodes.at(i - 1)->posy > p->nodes.at(i)->posy)
					{
						SDL_RenderDrawLine(r, p->nodes.at(i - 1)->posx, p->nodes.at(i - 1)->posy, p->nodes.at(i - 1)->posx, p->nodes.at(i)->posy);
						SDL_RenderDrawLine(r, p->nodes.at(i - 1)->posx, p->nodes.at(i)->posy, p->nodes.at(i)->posx, p->nodes.at(i)->posy);
					}
				}
				else if (p->nodes.at(i)->branch == node::LOWER)
				{
					if (p->nodes.at(i - 1)->posy <= p->nodes.at(i)->posy)
					{
						SDL_RenderDrawLine(r, p->nodes.at(i - 1)->posx, p->nodes.at(i - 1)->posy, p->nodes.at(i - 1)->posx, p->nodes.at(i)->posy);
						SDL_RenderDrawLine(r, p->nodes.at(i - 1)->posx, p->nodes.at(i)->posy, p->nodes.at(i)->posx, p->nodes.at(i)->posy);

					}
					else if (p->nodes.at(i - 1)->posy > p->nodes.at(i)->posy)
					{
						SDL_RenderDrawLine(r, p->nodes.at(i - 1)->posx, p->nodes.at(i - 1)->posy, p->nodes.at(i)->posx, p->nodes.at(i - 1)->posy);
						SDL_RenderDrawLine(r, p->nodes.at(i)->posx, p->nodes.at(i - 1)->posy, p->nodes.at(i)->posx, p->nodes.at(i)->posy);
					}
				}

				else if (p->nodes.at(i)->branch == node::VERTICAL || p->nodes.at(i)->branch == node::HORIZONTAL)
				{
					SDL_RenderDrawLine(r, p->nodes.at(i - 1)->posx, p->nodes.at(i - 1)->posy, p->nodes.at(i)->posx, p->nodes.at(i)->posy);
				}


			}

		}
	}

}



void node::drawNodes(SDL_Renderer *r, color* c, node* n)
{

	SDL_RenderDrawLine(r, n->posx, n->posy, n->posx + 10, n->posy + 10);

}
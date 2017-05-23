#include "paths.h"


void path::drawPath(SDL_Renderer *r, color* c) 
{
	SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);
	
	if(!(this->nodes.empty()))
	{
		for (unsigned int i = 1; i < this->nodes.size(); ++i)
		{
			if (i != this->nodes.size())
			{
				if (this->nodes.at(i)->branch == node::UPPER)
				{
					if (this->nodes.at(i - 1)->posy <= this->nodes.at(i)->posy)
					{
						SDL_RenderDrawLine(r, this->nodes.at(i - 1)->posx, this->nodes.at(i - 1)->posy, this->nodes.at(i)->posx, this->nodes.at(i - 1)->posy);
						SDL_RenderDrawLine(r, this->nodes.at(i)->posx, this->nodes.at(i - 1)->posy, this->nodes.at(i)->posx, this->nodes.at(i)->posy);
					}
					else if (this->nodes.at(i - 1)->posy > this->nodes.at(i)->posy)
					{
						SDL_RenderDrawLine(r, this->nodes.at(i - 1)->posx, this->nodes.at(i - 1)->posy, this->nodes.at(i - 1)->posx, this->nodes.at(i)->posy);
						SDL_RenderDrawLine(r, this->nodes.at(i - 1)->posx, this->nodes.at(i)->posy, this->nodes.at(i)->posx, this->nodes.at(i)->posy);
					}
				}
				else if (this->nodes.at(i)->branch == node::LOWER)
				{
					if (this->nodes.at(i - 1)->posy <= this->nodes.at(i)->posy)
					{
						SDL_RenderDrawLine(r, this->nodes.at(i - 1)->posx, this->nodes.at(i - 1)->posy, this->nodes.at(i - 1)->posx, this->nodes.at(i)->posy);
						SDL_RenderDrawLine(r, this->nodes.at(i - 1)->posx, this->nodes.at(i)->posy, this->nodes.at(i)->posx, this->nodes.at(i)->posy);

					}
					else if (this->nodes.at(i - 1)->posy > this->nodes.at(i)->posy)
					{
						SDL_RenderDrawLine(r, this->nodes.at(i - 1)->posx, this->nodes.at(i - 1)->posy, this->nodes.at(i)->posx, this->nodes.at(i - 1)->posy);
						SDL_RenderDrawLine(r, this->nodes.at(i)->posx, this->nodes.at(i - 1)->posy, this->nodes.at(i)->posx, this->nodes.at(i)->posy);
					}
				}

				else if (this->nodes.at(i)->branch == node::VERTICAL || this->nodes.at(i)->branch == node::HORIZONTAL)
				{
					SDL_RenderDrawLine(r, this->nodes.at(i - 1)->posx, this->nodes.at(i - 1)->posy, this->nodes.at(i)->posx, this->nodes.at(i)->posy);
				}


			}

		}
	}

}



void node::drawNodes(SDL_Renderer *r, color* c, node* n)
{

	SDL_RenderDrawLine(r, n->posx, n->posy, n->posx + 10, n->posy + 10);

}
#include "Dot.h"



Dot::Dot()
{
	for (int p = 0; p < TOTAL_PARTICLES; p++)
	{
		particles[p] = new Particle(x, y);
	}
}


Dot::~Dot()
{
	delete[] particles;
}

void Dot::move(SDL_Event &e,int mode)
{
	switch (mode) 
	{
	case 0:
		x = e.motion.x;
		y = e.motion.y;
		break;
	case 1:
		x = e.motion.x;
		y = e.motion.y;
		break;
		
	}
 	
}

void Dot::showParticles(SDL_Renderer* gRenderer,int mode)
{
	switch (mode) 
	{
	case 1:
		for (int i = 0; i < TOTAL_PARTICLES; i++)
		{
			x = x - 15 + rand() % 30;
			y = y - 15 + rand() % 30;
			if (particles[i]->is_dead())
			{
				delete particles[i];
				particles[i] = new Particle(x, y);
			}
		}
		for (int i = 0; i < TOTAL_PARTICLES; i++)
		{
			particles[i]->setText(par[rand() % 3 + 1]);
			particles[i]->show(gRenderer);
		}
		break;
	case 0:
		
		for (int i = 0; i < TOTAL_PARTICLES; i++)
		{

			if (particles[i]->is_dead())
			{
				delete particles[i];
				particles[i] = new Particle(x, y);
			}
		}
		for (int i = 0; i < TOTAL_PARTICLES; i++)
		{
			particles[i]->setText(par[rand()%3+1]);
			particles[i]->show(gRenderer);
		}
		break;
	}
	
}

void Dot::show(SDL_Renderer * gRenderer,int mode)
{
	//apply_surface(x, y, dot, screen);
	showParticles(gRenderer,mode);
}

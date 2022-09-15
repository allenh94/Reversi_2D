#include "Particle.h"



Particle::Particle()
{
}


Particle::Particle(int x, int y)
{
	this->x = x -7+ rand() % 15;
	this->y = y -7+ rand() % 15;
	frame = rand() % 30;

}

Particle::~Particle()
{
}

void Particle::show(SDL_Renderer *gRenderer)
{
	type.render(x-(type.getWidth()/2), y-(type.getHeight()/2), gRenderer);
	if (frame %( (rand() % 3+1)) == 0) 
	{

	}
	frame++;
}

bool Particle::is_dead()
{
	if (frame > 30)
		return true;
	return false;
}

void Particle::setText(LTexture a)
{
	type = a;
}

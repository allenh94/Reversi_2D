#pragma once
#include "Particle.h"
#define TOTAL_PARTICLES 50
class Dot
{
public:
	Dot();
	~Dot();
	void move(SDL_Event &e,int mode);
	void showParticles(SDL_Renderer* gRenderer,int mode);
	void show(SDL_Renderer* gRenderer, int mode);
	LTexture par[10];
private:
	int x, y;
	int xVel, yVel;
	Particle *particles[TOTAL_PARTICLES];
};


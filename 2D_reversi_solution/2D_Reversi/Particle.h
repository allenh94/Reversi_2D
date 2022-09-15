#pragma once
#include<SDL.h>
#include"LTexture.h"
class Particle
{
public:
	Particle();

	Particle(int x,int y);
	~Particle();
	void show(SDL_Renderer *gRenderer);
	bool is_dead();
	void setText(LTexture a);
	LTexture type;
private: 
	int x, y;
	int frame;
	                                     
};

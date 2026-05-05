#pragma once
#include <SDL.h>
#include <iostream>
#include "string.h"
#include "LTexture.h"


class Button
{
public:
	Button();

	~Button();
	int x;
	int y;
	bool isOn;
	LTexture text[2];
	void show(SDL_Renderer *gRenderer);
	void setPos(int x, int y);
	bool checkClick(SDL_Event* e);
	
};


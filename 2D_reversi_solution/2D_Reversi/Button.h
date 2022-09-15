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
	bool checkClick(SDL_Event* e);
	bool isOn;
	void show(SDL_Renderer *gRenderer);
	LTexture text[2];
	void setPos(int x, int y);
	int x;
	int y;
	
};


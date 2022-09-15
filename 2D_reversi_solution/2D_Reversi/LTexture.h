#pragma once
#include <SDL.h>
#include<iostream>
#include <SDL_image.h>
#include <stdio.h>
#include "string.h"
using namespace std;
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();
	LTexture& operator = (const LTexture& t);
	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y,SDL_Renderer* gRenderer);

	//Gets image dimensions
	int getWidth();
	int getHeight();
	void setWidth(int w);
	void setHeight(int h);

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};


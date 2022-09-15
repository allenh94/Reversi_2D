#include "Button.h"


Button::Button()
{

}



Button::~Button()
{
}

bool Button::checkClick(SDL_Event *e)
{
	if (e->button.x >= x && e->button.x <= x + text[isOn].getWidth() && e->button.y >= y && e->button.y <= y + text[isOn].getHeight())
	{
		isOn = true;
		if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			return  true;
		}

	}
	else
	{
		isOn = false;
	}

	return false;
}

void Button::show(SDL_Renderer *gRenderer)
{
	double offsetX = (text[1].getWidth() - text[0].getWidth()) / 2;
	double offsetY = (text[1].getHeight() - text[0].getHeight()) / 2;
	int buttonUp = 5;
	if (isOn)
	{
		text[1].render(x - offsetX+buttonUp, y - offsetY+buttonUp, gRenderer);
	}
	else
	{
		text[0].render(x , y, gRenderer);
	}
}

void Button::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}



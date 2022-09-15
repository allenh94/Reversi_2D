#include "CheckerBoard.h"



void CheckerBoard::setup(void)
{
	int x = Xsize / 2 - 1;
	int y = Ysize / 2 - 1;
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			p[i][j].state = null;
		}
	}
	p[x][y].state = dark;
	p[x + 1][y].state = light;
	p[x][y + 1].state = light;
	p[x + 1][y + 1].state = dark;
	darkCount = 2;
	lightCount = 2;

	mover = dark;
	for (int i = 0; i < Xsize; i++)
	{
		keyrow[i] = 0;
		keycol[i] = 0;
	}
	checkpoint();
}

int CheckerBoard::move(bool isBot, int mousex, int mousey, SDL_Renderer *gRenderer)
{
	int posX = mousex - x - X_offset;
	int posY = mousey - y - Y_offset;

	int xbuf = -1;
	int ybuf = -1;
	if (isBot&&mover == light)
	{
		ybuf = checkpoint() % 10;
		xbuf = checkpoint() / 10;
	}
	else
	{
		double delta = ((833.0 - 202.0) / 8.0);
		xbuf = posX / delta;
		ybuf = posY / delta;

	}
	if (xbuf >= 0 && ybuf >= 0)
	{
		if (p[ybuf][xbuf].state == hint)
		{
			p[ybuf][xbuf].state = mover;
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (i == 0 && j == 0)
					{
						continue;
					}
					flippieces(xbuf + i, ybuf + j, i, j);
				}
			}
			changeMover();
			checkpoint();
			return 1;
		}

	}
	return 0;
}

void CheckerBoard::setHint(void)
{
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			if (p[i][j].state == null)
			{
				/*if (checkpoint(i, j))
				{
					p[i][j].state = hint;
				}*/
			}
		}
	}
}

void CheckerBoard::showBoard(bool isBot, SDL_Renderer *gRenderer)
{
	lightCount = 0;
	darkCount = 0;
	checkpoint();

	//count space 

	double delta = ((833.0 - 202.0) / 8.0);

	text.render(x, y, gRenderer);
	for (int i = 0; i < Ysize; i++)
	{
		for (int j = 0; j < Xsize; j++)
		{
			double posX = delta * j;
			double posY = delta * i;
			if (p[i][j].state == dark)
			{
				darkText.render(posX + x + X_offset, posY + y + Y_offset, gRenderer);
				darkCount++;
			}
			else if (p[i][j].state == light)
			{
				lightText.render(posX + x + X_offset, posY + y + Y_offset, gRenderer);
				lightCount++;
			}
			else if (p[i][j].state == hint)
			{
				if (!(isBot&&mover == light))
					hintT.render(posX + x + delta / 2 - 15, posY + y + delta / 2 - 15, gRenderer);
			}
			else
			{
				//cout << "¡Å";
			}
		}

	}

	showUI(isBot, gRenderer);
}

CheckerBoard::CheckerBoard()
{
}


CheckerBoard::~CheckerBoard()
{
}

CheckerBoard & CheckerBoard::operator=(const CheckerBoard&  a)
{

	checkflag = a.checkflag;
	darkCount = a.darkCount;
	lightCount = a.lightCount;
	text = a.text;
	darkText = a.darkText;
	lightText = a.lightText;
	x = a.x;
	y = a.y;
	X_offset = a.X_offset;
	Y_offset = a.Y_offset;
	mover = a.mover;
	now = a.now;
	dwin = a.dwin;
	lwin = a.lwin;
	hintT = a.hintT;
	draw = a.draw;
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			p[i][j] = a.p[i][j];
		}
	}
	for (int i = 0; i < 10; i++)
	{
		nums[i] = a.nums[i];
		num2[i] = a.num2[i];
	}
	return *this;

}

void CheckerBoard::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void CheckerBoard::showUI(bool isBot, SDL_Renderer *gRenderer)
{
	//cout << endl;
	//cout << "now : " << (mover == light ? "¡´" : "¡³") << endl << endl;
	now.render(0, 415, gRenderer);
	mover == light ? lightText.render(180, 430, gRenderer) : darkText.render(180, 430, gRenderer);
	if (darkHint == false && lightHint == false)
	{
		if (darkCount < lightCount)
		{
			lwin.render(x + text.getWidth() / 2 - (lwin.getWidth() / 2), y + text.getHeight() / 2 - lwin.getHeight() / 2, gRenderer);
		}
		else if (darkCount > lightCount)
		{
			dwin.render(x + text.getWidth() / 2 - (dwin.getWidth() / 2), y + text.getHeight() / 2 - dwin.getHeight() / 2, gRenderer);
		}
		else
		{
			draw.render(x + text.getWidth() / 2 - (draw.getWidth() / 2), y + text.getHeight() / 2 - draw.getHeight() / 2, gRenderer);
		}
	}
	int count_pos_x = 50;
	int count_pos_y = 550;
	darkText.render(count_pos_x, count_pos_y, gRenderer);
	num2[(darkCount / 10)].render(count_pos_x + 100, count_pos_y, gRenderer);
	nums[darkCount % 10].render(count_pos_x + 130, count_pos_y, gRenderer);
	lightText.render(count_pos_x, count_pos_y + 100, gRenderer);
	num2[(lightCount / 10)].render(count_pos_x + 100, count_pos_y + 100, gRenderer);
	nums[lightCount % 10].render(count_pos_x + 130, count_pos_y + 100, gRenderer);

	//cout << "Player ¡³ : " << darkCount << "\t " << (isBot ? "Bot" : "Player") << " ¡´ : " << lightCount << endl << endl;
	//cout << "UNDO: BACK" << endl;
	//cout << "REDO: TAB" << endl;
	//cout << "RESTART: ENTER" << endl;
}


int CheckerBoard::checkpoint()
{
	int hashint = 0;
	int bestPos = 0;
	int bigPoint = 0;
	for (int x = 0; x < Xsize; x++)
	{
		for (int y = 0; y < Ysize; y++)
		{
			int countpoint = 0;
			if (p[y][x].state == light || p[y][x].state == dark)
			{
				continue;
			}
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (i == 0 && j == 0)
					{
						continue;
					}

					countpoint += checkside(x + i, y + j, i, j, 0, false);
				}
			}
			if (countpoint != 0)
			{
				p[y][x].state = hint;
				hashint = 1;
				if (countpoint > bigPoint)
				{
					bigPoint = countpoint;
					bestPos = x * 10 + y;
				}
			}
			else
			{
				p[y][x].state = null;
			}
		}
	}

	if (!hashint)
	{
		if (mover == dark)
		{
			darkHint = false;
		}
		else
		{
			lightHint = false;
		}
		if (darkHint || lightHint)
			changeMover();
	}
	else
	{
		if (mover == dark)
		{
			darkHint = true;
		}
		else
		{
			lightHint = true;
		}
	}

	return bestPos;


}



int CheckerBoard::checkside(int x, int y, int i, int j, int count, bool checkflag)
{
	if (x == -1 || x == Xsize || y == -1 || y == Ysize || p[y][x].state == null || p[y][x].state == hint)
	{
		return 0;
	}
	if (mover == p[y][x].state)
	{
		return count;
	}
	return (checkside(x + i, y + j, i, j, count + 1, checkflag));
}

int CheckerBoard::flippieces(int x, int y, int i, int j)
{
	if (x == -1 || x == Xsize || y == -1 || y == Ysize || p[y][x].state == null || p[y][x].state == hint)
	{
		return 0;
	}
	if (p[y][x].state == mover)
	{
		return 1;
	}
	else
	{
		if (flippieces(x + i, y + j, i, j))
		{
			p[y][x].flip();
			return 1;
		}
	}
}

void CheckerBoard::changeMover()
{
	if (mover == light)
	{
		mover = dark;
	}
	else
	{
		mover = light;
	}
}

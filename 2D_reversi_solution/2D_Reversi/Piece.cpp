#include "Piece.h"



Piece::Piece()
{
}


Piece::~Piece()
{
}

void Piece::flip()
{
	if (state == dark) 
	{
		state = light;
	}
	else if (state == light) 
	{
		state = dark;
	}
}

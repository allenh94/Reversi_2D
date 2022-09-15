#pragma once
#include<iostream>
#include"LTexture.h"
using namespace std;
enum Condition {null,hint,dark,light};
class Piece
{
public:
	Piece();
	~Piece();
	Condition state;
	void flip();
};

   
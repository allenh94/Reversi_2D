#pragma once
#include<iostream>
#include"Piece.h"
#include<string.h>
#include"LTexture.h"
#define Xsize 8
#define Ysize 8
using namespace std;
class CheckerBoard
{
public:
	//��l�ƴѽL
	void setup(void);

	// �U��
	int move(bool isBot,int mousex,int mousey,SDL_Renderer *gRenderer);

	// �p��X�i�H�U����m
	void setHint(void);

	// ��ܵe��
	void showBoard(bool isBot,SDL_Renderer *gRenderer);
	CheckerBoard();
	~CheckerBoard();
	bool keycol[Xsize];
	bool keyrow[Ysize];
	CheckerBoard& operator = (const CheckerBoard& a);
	LTexture text;
	LTexture darkText;
	LTexture lightText;
	LTexture now;
	LTexture dwin;
	LTexture lwin;
	LTexture draw;
	LTexture hintT;
	LTexture nums[10];
	LTexture num2[10];
	void setPos(int x, int y);
private:
	
	Piece p[Xsize][Ysize];

	bool darkHint;
	bool lightHint;
	void showUI(bool isBot,SDL_Renderer *gRenderer);
	int checkpoint();
	int checkside(int x,int y ,int i, int j, int count,bool checkflag);
	int flippieces(int x,int y,int i ,int j);
	bool checkflag;
	Condition mover;
	void changeMover();
	int darkCount;
	int lightCount;
	int x;
	int y;
	int X_offset = 25;
	int Y_offset = 25;
};


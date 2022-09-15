#include <iostream>
#include <SDL.h>
#include <vector>
#include "string.h"
#include "SDL_image.h"
#include "LTexture.h"
#include "Button.h"
#include "CheckerBoard.h"
#include "Piece.h"
#include"Dot.h"
#include"Particle.h"
#include <SDL_mixer.h>
using namespace std;




const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHomeScreen = NULL;
SDL_Surface* gStar = NULL;
SDL_Event events;

//The window renderer

//Scene textures
LTexture gBackgroundTexture;
LTexture scene1;
LTexture scene2;



SDL_Renderer* gRenderer1 = NULL;
//Button test;
Button pvp;
Button pvc;
Button redo;
Button undo;
Button restart;
Button back;
//Particle
Dot mouse;
Dot mouseClick;
//music
Mix_Music *bgm;
Mix_Chunk *buttonS;
Mix_Chunk *moveS;

//object
CheckerBoard game;
vector<CheckerBoard> games;
int rounds = 0;

bool isBot;
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("2D Reversi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer1 = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer1 == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer1, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;


	//Load background texture
	if (!scene1.loadFromFile("media\\scene1_backgournd.png", gRenderer1))
	{
		printf("Failed to load scene texture image!\n");
		success = false;
	}
	if (!pvp.text[0].loadFromFile("media\\pvp_button.png", gRenderer1))
	{
		cout << "Failed to load pvp_botton image!" << endl;
		success = false;
	}
	if (!pvp.text[1].loadFromFile("media\\pvp_button2.png", gRenderer1))
	{
		cout << "Failed to load pvp_button2 image!" << endl;
		success = false;
	}
	if (!scene2.loadFromFile("media\\scene2_background.png", gRenderer1))
	{
		cout << "Failed to load  scene2_background image!" << endl;
		success = false;
	}
	if (!game.text.loadFromFile("media\\CheckerBoard.png", gRenderer1))
	{
		cout << "Failed to load CheckerBoard image!" << endl;
		success = false;
	}
	if (!game.darkText.loadFromFile("media\\darkPiece.png", gRenderer1))
	{
		cout << "Failed to load darkPiece image!" << endl;
		success = false;
	}
	if (!game.lightText.loadFromFile("media\\lightPiece.png", gRenderer1))
	{
		cout << "Failed to load darkPiece image!" << endl;
		success = false;
	}
	if (!game.hintT.loadFromFile("media\\hint1.png", gRenderer1))
	{
		cout << "Failed to load hint image!" << endl;
		success = false;
	}
	if (!redo.text[0].loadFromFile("media\\redo_button1.png", gRenderer1))
	{
		cout << "Failed to load redo_button1 image!" << endl;
		success = false;

	}
	if (!redo.text[1].loadFromFile("media\\redo_button2.png", gRenderer1))
	{
		cout << "Failed to load redo_button2 image!" << endl;
		success = false;
	}
	if (!undo.text[0].loadFromFile("media\\undo_button1.png", gRenderer1))
	{
		cout << "Failed to load undo_button1 image!" << endl;
		success = false;
	}
	if (!undo.text[1].loadFromFile("media\\undo_button2.png", gRenderer1))
	{
		cout << "Failed to load undo_button2 image!" << endl;
		success = false;
	}
	if (!restart.text[0].loadFromFile("media\\restart_button1.png", gRenderer1))
	{
		cout << "Failed to load restart_button1 image!" << endl;
		success = false;
	}
	if (!restart.text[1].loadFromFile("media\\restart_button2.png", gRenderer1))
	{
		cout << "Failed to load restart_button2 image!" << endl;
		success = false;
	}
	if (!pvc.text[0].loadFromFile("media\\pvc_button1.png", gRenderer1))
	{
		cout << "Failed to load pvc_button1 image!" << endl;
		success = false;
	}
	if (!pvc.text[1].loadFromFile("media\\pvc_button2.png", gRenderer1))
	{
		cout << "Failed to load pvc_button1 image!" << endl;
		success = false;
	}
	if (!game.now.loadFromFile(("media\\now.png"),gRenderer1) )
	{
		cout<< "Failed to load now image!"<<endl;
		success = false;
	}
	if(!game.dwin.loadFromFile("media\\dwin.png", gRenderer1)) 
	{
		cout << "Failed to load dwin image!" << endl;
		success = false;
	}
	if (!game.lwin.loadFromFile("media\\lwin.png", gRenderer1))
	{
		cout << "Failed to load lwin image!" << endl;
		success = false;
	}
	if (!game.draw.loadFromFile("media\\draw.png", gRenderer1))
	{
		cout << "Failed to load draw image!" << endl;
		success = false;
	}
	if (!back.text[0].loadFromFile("media\\back_button1.png", gRenderer1))
	{
		cout << "Failed to load back_button1 image!" << endl;
		success = false;
	}
	if (!back.text[1].loadFromFile("media\\back_button2.png", gRenderer1))
	{
		cout << "Failed to load back_button2 image!" << endl;
		success = false;
	}
	for (int i = 0; i < 10; i++) 
	{
		string a[10] = { "0","1","2","3","4","5","6","7","8","9" };
		if  (!game.nums[i].loadFromFile(("media\\" + a[i] + ".png"), gRenderer1))
		{
			cout << "Failed to load "<<i<<" image!" << endl;
			success = false;
		}
		if (!game.num2[i].loadFromFile(("media\\" + a[i] + ".png"), gRenderer1)) 
		{
			cout << "Failed to load " << i << " image!" << endl;
			success = false;
		}
	}
	for (int i = 0; i < 4; i++) 
	{
		string a[10] = { "0","1","2","3","4","5","6","7","8","9" };
		if (!mouse.par[i].loadFromFile("media\\par"+ a[i]+ ".png", gRenderer1))
		{
			cout << "Failed to load par"<<i<<".png" << endl;
			success = false;
		}
		
	}
	bgm = Mix_LoadMUS("media\\bgm.mp3");
	if (bgm == NULL) 
	{
		cout << "Failed to load bgm.mp3 !" << endl;
		success = false;
	}
	buttonS = Mix_LoadWAV("media\\bgm.mp3");
	if (buttonS == NULL)
	{
		cout << "Failed to load bgm.mp3 !" << endl;
		success = false;
	}
	moveS = Mix_LoadWAV("media\\move.wav");
	if (buttonS == NULL)
	{
		cout << "Failed to load move.wav !" << endl;
		success = false;
	}
	return success;
}

void close()
{
	//Free loaded images
	gBackgroundTexture.free();
	//Destroy window	
	SDL_DestroyRenderer(gRenderer1);
	SDL_DestroyWindow(gWindow);
	gBackgroundTexture.free();
	scene1.free();
	scene2.free();
	gWindow = NULL;
	gRenderer1 = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();

}


int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;
			int move = 0;
			rounds = 0;
			game.setup();
			game.setPos(300, 74);
			games.push_back(game);
			pvp.setPos((1024/2)-(pvp.text[0].getWidth()/2), 400);
			pvc.setPos((1024 / 2) - (pvc.text[0].getWidth() / 2), 550);
			undo.setPos(60, 150);
			redo.setPos(60, 230);
			restart.setPos(40, 310);
			back.setPos(10, 10);
			int botDelay =0 ;
			// scenes change
			int scenes = 1;
			//Event handler
			SDL_Event e;
			if (Mix_PlayingMusic() == 0)
			{
				//Play the music
				Mix_PlayMusic(bgm, -1);
			}
		
			gBackgroundTexture = scene1;
			//While application is running
			while (!quit)
			{

				
				SDL_RenderClear(gRenderer1);
				//Handle events on queue
				if (isBot&&scenes == 2)
				{
					botDelay++;
					if (botDelay == 30)
					{
						if (game.move(isBot, -1, -1, gRenderer1) == 1)
						{
							Mix_PlayChannel(-1, moveS, 0);

							games.erase(games.begin() + rounds + 1, games.end());
							games.push_back(game);
							rounds++;
							game = games[rounds];
						}
						botDelay = 0;
					}
				}
				while (SDL_PollEvent(&e) != 0)
				{
					mouse.move(e,0);
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					
					if (scenes == 1) //  scene1
					{
						if (e.type == SDL_MOUSEBUTTONDOWN)
							mouse.move(e, 1);
						if (pvp.checkClick(&e))
						{
							gBackgroundTexture = scene2;
							scenes = 2;
							isBot = false;
							rounds = 0;
							games.erase(games.begin(), games.end());
							game.setup();
							games.push_back(game);
						}
						//render scene1's buttons to screen
						if (pvc.checkClick(&e))
						{
							gBackgroundTexture = scene2;
							scenes = 2;
							isBot = true;
							rounds = 0;
							games.erase(games.begin(), games.end());
							game.setup();
							games.push_back(game);
						}
						
					}
					else  // scene2
					{
						if (back.checkClick(&e))
						{
							gBackgroundTexture = scene1;
							scenes = 1;
						}
						if (redo.checkClick(&e))
						{
							if (isBot)
							{
								if (rounds < games.size() - 1)
								{
									rounds += 1;
									game = games[rounds];
								}
							}
							if (rounds < games.size() - 1)
							{
								rounds += 1;
								game = games[rounds];
							}
						}
						else if (undo.checkClick(&e))
						{
							if (isBot)
							{
								if (rounds > 0)
								{
									rounds -= 1;
									game = games[rounds];
								}
							}
							if (rounds > 0)
							{
								rounds -= 1;
								game = games[rounds];
							}
						}
						else if (restart.checkClick(&e))
						{
							rounds = 0;
							games.erase(games.begin(), games.end());
							game.setup();
							games.push_back(game);
						}
						
						if (e.type == SDL_MOUSEBUTTONDOWN)
						{

							if (game.move(isBot, e.button.x, e.button.y, gRenderer1) == 1)
							{
								Mix_PlayChannel(-1, moveS, 0);
								games.erase(games.begin() + rounds + 1, games.end());
								games.push_back(game);
								rounds++;
								game = games[rounds];
								botDelay = 0;
							}
						}
					
					
						//SDL_RenderPresent(gRenderer1);
					}

					//Update screen
					
				}
				gBackgroundTexture.render(0, 0, gRenderer1);
				if (scenes == 1)
				{
					pvp.show(gRenderer1);
					pvc.show(gRenderer1);
				}
				else
				{
					back.show(gRenderer1);
					game.showBoard(isBot, gRenderer1);
					undo.show(gRenderer1);
					redo.show(gRenderer1);
					restart.show(gRenderer1);
				}
				
				mouse.show(gRenderer1,0);
				SDL_RenderPresent(gRenderer1);
				SDL_Delay(16);//60fps
			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}


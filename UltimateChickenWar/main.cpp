#include "UCW.h"
#include <iostream>
#include <SDL_ttf.h>
#include "Menu.h"
UCW *game = nullptr;	

int main(int argc, char *args[]) {

	const int FPS = 60;	//fps of the game
	const int frameDelay = 1000 / FPS;	//the delay fps time in case it runs too slow
reset:
	Uint32 frameStart;	//time to restart frame
	int frameTime;	//display time of each frame
	
	game = new UCW();	//create a  game
	game->init("ULITMATE CHICKEN WAR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1152, 600, false);	//init the game

	while (game->running()) {

		frameStart = SDL_GetTicks();	//get the start time

		game->handleEvents();	//handle all the events in the game
		game->update();	//update the game
		game->render();	//render the game

		frameTime = SDL_GetTicks() - frameStart;	
		//if frametime is too short
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	//if game is quitted
	bool restart = game->restart;	//check the restart status
	game->clean();	//clean everything in game
	
	delete game;	//release the dynamic memory
	if (restart == true) goto reset;//restart the game
	
	return 0;

}
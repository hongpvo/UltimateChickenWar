#include "UCW.h"
#include <iostream>
#include <SDL_ttf.h>
#include "Menu.h"
UCW *game = nullptr;



int main(int argc, char *args[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
reset:
	Uint32 frameStart;
	int frameTime;
	
	game = new UCW();
	game->init("ULITMATE CHICKEN WAR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1728, 900, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	bool restart = game->restart;
	game->clean();
	
	delete game;
	if (restart == true) goto reset;
	
	

	return 0;

}
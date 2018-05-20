#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <vector>

class UCW
{
public:
	UCW();
	~UCW();
	

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents(); 
	void update();
	void render();
	void clean();

	//Globally used font
	static TTF_Font *gFont;
	static SDL_Renderer* renderer;
	static SDL_Event event;

	bool restart = false;
	
	bool running() { return isRunning; };



private:
	bool isRunning;
	int cnt = 0;
	SDL_Window *window;
	bool checkmenu = false;
	bool endgame = false;
	int j1 = 0;
	int j2 = 0;
	std::string playerwin1, playerwin2;
	

};
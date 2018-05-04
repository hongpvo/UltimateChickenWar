#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <iostream>

//class ColliderComponent;

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

	static SDL_Renderer* renderer;
	static SDL_Event event;
	
	//static std::vector<ColliderComponent*> colliders;

	bool running() { return isRunning; };
private:
	bool isRunning;
	int cnt = 0;
	SDL_Window *window;

};
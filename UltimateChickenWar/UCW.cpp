#include "UCW.h"
#include "Map.h"
#include "Component.h"
#include "TextureManager.h"
#include "Vector2D.h"



Map* map;

SDL_Renderer* UCW::renderer = nullptr;
SDL_Event UCW::event;
SDL_Rect position[9][16];

//test manager
Manager manager;
auto& player(manager.addEntity());

UCW::UCW()
{
}


UCW::~UCW()
{
}

void UCW::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised!..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;

	}

	
	map = new Map();
	//getPosition
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			position[row][column].h = 100;
			position[row][column].w = 108;
			if (row % 2 == 0) {
				position[row][column].x = (column * 108)/2;
				position[row][column].y = (row * 100 - 32 * row)/2;
			}
			else {
				position[row][column].x = (column * 108 + 54)/2;
				position[row][column].y = (row * 100 - 32 * row)/2;
			}

		}
	}
	//test ECS
	player.addComponent<TransformComponent>(position[5][5], 2);
	player.addComponent<SpriteComponent>("assets/chicken.png");
	player.addComponent<Keyboard_Controller>();
	//player.addComponent<ColliderComponent>("player");
}

void UCW::handleEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
};
void UCW::update() {
	manager.refresh();
	manager.update();
	
};

void UCW::render() {
	SDL_RenderClear(renderer);
	//this add stuffs to render
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);

};
void UCW::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;

};


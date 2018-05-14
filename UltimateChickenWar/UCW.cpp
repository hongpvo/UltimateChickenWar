#include "UCW.h"
#include "Map.h"
#include "Component.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "LoadTextureFromText.h"
#include "Popup.h"


Map* map;
int map_test[9][16]= 
{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,
2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,
5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,
5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,
5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0
};

SDL_Renderer* UCW::renderer = nullptr;
SDL_Event UCW::event;
SDL_Rect position[9][16];
SDL_Rect position_ini[6];
SDL_Rect center_position[9][16];

TTF_Font* UCW::gFont=nullptr;
//render texture
//LoadTextureFromText gTextTexture;
Popup attack("attack or not?",1500, 1728);
Popup final1("Player 1 wins", 1500, 1728);
Popup final2("Player 2 wins", 1500, 1728);


//test manager
Manager manager;
//auto& player1(manager.addEntity());
//auto& player2(manager.addEntity());

Entity* player[6];
char* image[6] = { "assets/chicken.png", "assets/chicken1.png","assets/chicken.png", "assets/chicken1.png","assets/chicken.png", "assets/chicken1.png" };
char* turn_indicator = { "assets/lowsnow.png" };
//int position_ini[6][6] = { {1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6} };
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
				position[row][column].x = column * 104 ;
				position[row][column].y = row * 100 - 32 * row ;
			}
			else {
				position[row][column].x = column * 104 + 52 ;
				position[row][column].y = row * 100 - 32 * row;
			}

		}
	}

	position_ini[0] = position[0][0];
	position_ini[1] = position[0][15];
	position_ini[2] = position[1][0];
	position_ini[3] = position[1][15];
	position_ini[4] = position[2][0];
	position_ini[5] = position[2][15];

	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			center_position[row][column].h = 100;
			center_position[row][column].w = 104;
			if (row == 0) {
				center_position[row][column].x = 52 + 104 * column;
				center_position[row][column].y = 50;
			}
			else if (row % 2 == 0) {
				center_position[row][column].x = 52 + 104 * column;
				center_position[row][column].y = 50 + 68 * row;
			}
			else {
				center_position[row][column].x = 104 + 104 * column;
				center_position[row][column].y = 50 + 68 * row;
			}
		}
	}
	
	for (int i = 0; i <= 5; i++) {
		player[i] = &manager.addEntity();
		player[i]->addComponent<TransformComponent>(position_ini[i], 1);
		player[i]->addComponent<SpriteComponent>(image[i], turn_indicator);
		player[i]->addComponent<Keyboard_Controller>();
		player[i]->addComponent<StatsComponent>(i, i%2);
	}
	player[0]->getComponent<StatsComponent>().myturn = true;
	/*
	//test ECS
	player1.addComponent<TransformComponent>(position[1][1], 1);
	player1.addComponent<SpriteComponent>("assets/chicken.png");
	player1.addComponent<Keyboard_Controller>();
	player1.addComponent<StatsComponent>(1);
	
	//player.addComponent<ColliderComponent>("player");

	//player2.addComponent<Mouse_Controller>(2, manager);
	//player1.addComponent<Mouse_Controller>(1, manager);
	*/
	//Debugfont
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

}

void UCW::handleEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		Mouse_Controller(&manager, center_position, map_test, &attack);
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
	attack.clean();
	SDL_RenderClear(renderer);
	//cout << "length: " << manager.returnlength() << endl;
	//this add stuffs to render
	map->DrawMap();
	manager.draw();
	
	bool draw_allowing = false;
	for (int i = 0; i < manager.returnlength(); i++) {
		if (player[i]->getComponent<StatsComponent>().choosing) {
			draw_allowing = true;
			break;
		}
	}
	int numPlayerAlive =0;
	int numPlayer1 = 0;
	int numPlayer2 = 0;
	for (int i = 0; i < manager.returnlength(); i++) {
		if (player[i]->getComponent<StatsComponent>().isAlive) {
			if (player[i]->getComponent<StatsComponent>().side == 0) numPlayer1++;
			else numPlayer2++;
		}
	}
	if (numPlayer2 == 0) final1.draw();
	if (numPlayer1 == 0) final2.draw();
	final1.clean();
	final2.clean();
	
	for (int i = 0; i < manager.returnlength(); i++) {
		if (player[i]->getComponent<StatsComponent>().choosing) {
			draw_allowing = true;
			break;
		}
	}
	static bool running = false;
	//if (draw_allowing && !running) {
		if (draw_allowing){
		attack.draw();
		//cout << "drawing" << endl;
		running = true;
	}
		attack.clean();
	
	//if (player1.getComponent<StatsComponent>().attacking || player2.getComponent<StatsComponent>().attacking) {
	//	attack.draw();
	//}
	
	SDL_RenderPresent(renderer);

};
void UCW::clean() {
	//attack.clean();
	attack.clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

	std::cout << "Game Cleaned" << std::endl;

};


#include "UCW.h"
#include "Map.h"
#include "Component.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "LoadTextureFromText.h"
#include "Popup.h"
#include "Menu.h"
#include <string>
#include "playerstats.h"
#include "NameInput.h"

extern int lv1[9][16];
extern int lv2[9][16];
Map* map;
int map_test[9][16]= 
{	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
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

NameInput player1("player 1");
NameInput player2("player 2");

//test manager
Manager manager;
//auto& player1(manager.addEntity());
//auto& player2(manager.addEntity());

Entity* player[6];

char* image[6] = { "assets/character/chicken_warrior.png", "assets/character/chicken_warrior2.png","assets/character/chicken_acher.png", "assets/character/chicken_acher2.png","assets/character/chicken_tank.png", "assets/character/chicken_tank2.png" };
char* turn_indicator = { "assets/turn_indicator.png" };
char* range_indicator = { "assets/range_indicator.png" };
//int position_ini[6][6] = { {1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6} };


Menu menu;
std::string labels[2] = { "Start","Exit" };
std::string labels2[2] = { "Restart","Exit" };
playerstats statsmenu;
SDL_Texture* background;

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
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;

	}
	// draw background
	
	for (int i = 0; i < manager.returnlength(); i++) {
		player[i]->destroy();
	}
	manager.index = 0;
	manager.refresh();
	cout << "run to here " << endl;
	manager.update();
	first_time = true;
	map = new Map();
	//getPosition
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			position[row][column].h = 100;
			position[row][column].w = 104;
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
	/*
	position_ini[0] = position[0][0];
	position_ini[1] = position[0][15];
	position_ini[2] = position[1][0];
	position_ini[3] = position[1][15];
	position_ini[4] = position[2][0];
	position_ini[5] = position[2][15];
	*/

	//test 
	position_ini[0] = position[0][0];
	position_ini[1] = position[0][1];
	position_ini[2] = position[1][0];
	position_ini[3] = position[1][1];
	position_ini[4] = position[2][0];
	position_ini[5] = position[2][1];


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
		player[i]->addComponent<SpriteComponent>(image[i], turn_indicator, range_indicator);
		player[i]->addComponent<StatsComponent>(i, i%2);
		
	}
	player[0]->getComponent<StatsComponent>().myturn = true;
	
	//Debugfont
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}
	std::cout<<"init passed"<<std::endl;
}

void UCW::handleEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		Mouse_Controller(&manager, map_test, &attack);
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
	background = TextureManager::LoadTexture("assets/island/background.png"); //3d - Dot - Heroes4
	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = 1728;
	src.h = 900;
	dest.x = 0;
	dest.y = 0;
	dest.w = 1728;
	dest.h = 900;
	SDL_RenderClear(renderer);
	TextureManager::Draw(background, src, dest);
	//cout << "length: " << manager.returnlength() << endl;
	//this add stuffs to render
	int i;
	if (checkmenu == false) { 
		if (endgame == false) i = menu.show(labels);
		else i = menu.show(labels2);
		if (i == 0 && endgame == false) {
			checkmenu = true;
		}
		else if (i == 0 && endgame == true) {
			checkmenu = true;
			//restart
			restart = true;
			checkmenu = false;
			isRunning = false;
		}
		else if (i == 2) {
			isRunning = false;
		}
	}

	if (checkmenu == true) {
		if (j1 == 0) {
			j1 = player1.handle_input();
			playerwin1 = player1.getName();
			player1.clean();
			//SDL_RenderClear(renderer);
		}
		else if (j2 == 0){
			j2 = player2.handle_input();
			playerwin2 = player2.getName();
			player2.clean();
			//SDL_RenderClear(renderer);
		}
		if (j2 == 1) {
			attack.clean();
			map->LoadMap(lv1, lv2);
			map->DrawMap();
			manager.draw();
			statsmenu.draw(&manager);

			bool draw_allowing = false;
			for (int i = 0; i < manager.returnlength(); i++) {
				if (player[i]->getComponent<StatsComponent>().choosing) {
					draw_allowing = true;

					break;
				}
			}
			int numPlayerAlive = 0;
			int numPlayer1 = 0;
			int numPlayer2 = 0;
			for (int i = 0; i < manager.returnlength(); i++) {
				if (player[i]->getComponent<StatsComponent>().isAlive) {
					if (player[i]->getComponent<StatsComponent>().side == 0) numPlayer1++;
					else numPlayer2++;

				}
			}

			if (numPlayer2 == 0) {
				playerwin1 = playerwin1 + " win!";
				Popup final1(playerwin1, 1500, 1728);
				final1.draw();
				checkmenu = false;
				endgame = true;
			}
			if (numPlayer1 == 0) {
				playerwin2 = playerwin2 + " win!";
				Popup final2(playerwin2, 1500, 1728);
				final2.draw();
				checkmenu = false;
				endgame = true;
			}
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
			if (draw_allowing) {
				attack.draw();
				//cout << "drawing" << endl;
				running = true;
			}
			attack.clean();
			statsmenu.clean();

			//if (player1.getComponent<StatsComponent>().attacking || player2.getComponent<StatsComponent>().attacking) {
			//	attack.draw();
			//}
			SDL_RenderPresent(renderer);
			if (endgame == true) {
				SDL_Delay(1000);
			}
		}
	}
	SDL_DestroyTexture(background);

};
void UCW::clean() {
	statsmenu.clean();
	attack.clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(background);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

	std::cout << "Game Cleaned" << std::endl;

};


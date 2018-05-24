#include "UCW.h"
#include "Map.h"
#include "Component.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "LoadTextureFromText.h"
#include "Popup.h"
#include "Menu.h"
#include <string>
#include "stats_table.h"
#include "NameInput.h"

Map* GameMap;
Chicken* Player::allChickens[6];
SDL_Renderer* UCW::renderer = nullptr;
SDL_Event UCW::event;
SDL_Rect position[9][16];
SDL_Rect position_ini[6];
SDL_Rect center_position[9][16];

TTF_Font* UCW::gFont=nullptr;

Popup attack("attack or not?",1500, 1728);
Popup final1("Player 1 wins", 1500, 1728);
Popup final2("Player 2 wins", 1500, 1728);

NameInput name_input1("player 1");
NameInput name_input2("player 2");

Player manager1;
Player manager2;
Chicken* player1[3];
Chicken* player2[3];

char* image[6] = { "assets/character/chicken_warrior.png", "assets/character/chicken_warrior2.png","assets/character/chicken_acher.png", "assets/character/chicken_acher2.png","assets/character/chicken_tank.png", "assets/character/chicken_tank2.png" };
char* turn_indicator = { "assets/indicator/turn_indicator.png" };
char* range_indicator = { "assets/indicator/range_indicator.png" };

Menu menu;
std::string labels[2] = { "Start","Exit" };
std::string labels2[2] = { "Restart","Exit" };
stats_table statsmenu;
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
	
	for (int i = 0; i < manager1.returnlength(); i++) {
		player1[i]->destroy();
	}
	manager1.index = 0;
	manager1.refresh();
	manager1.update();
	for (int i = 0; i < manager2.returnlength(); i++) {
		player2[i]->destroy();
	}
	
	Player::initialiser();
	manager2.index = 0;
	manager2.refresh();
	manager2.update();
	first_time = true;
	GameMap = new Map();
	//Calculating render box coordinate drawn from top left corner or center
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			position[row][column].h = 100;
			position[row][column].w = 104;
			if (row % 2 == 0) {
				position[row][column].x = column * 104 ;
				position[row][column].y = row * 100 - 32 * row ;
				center_position[row][column].x = 52 + 104 * column;
				center_position[row][column].y = 50 + 68 * row;
			}
			else {
				position[row][column].x = column * 104 + 52 ;
				position[row][column].y = row * 100 - 32 * row;
				center_position[row][column].x = 104 + 104 * column;
				center_position[row][column].y = 50 + 68 * row;
			}

		}
	}
	
	position_ini[0] = position[0][0];
	position_ini[1] = position[6][15];
	position_ini[2] = position[1][0];
	position_ini[3] = position[7][15];
	position_ini[4] = position[2][0];
	position_ini[5] = position[8][15];
	

	/* 
	position_ini[0] = position[0][0];
	position_ini[1] = position[0][1];
	position_ini[2] = position[1][0];
	position_ini[3] = position[1][1];
	position_ini[4] = position[2][0];
	position_ini[5] = position[2][1];
	*/

	for (int i = 0; i <= 2; i++) {
		player1[i] = &manager1.addChicken(2*i);
		player1[i]->addComponent<TransformComponent>(position_ini[2*i], 1);
		player1[i]->addComponent<SpriteComponent>(image[2*i], turn_indicator, range_indicator);
		player1[i]->addComponent<StatsComponent>(2*i);

		player2[i] = &manager2.addChicken(2*i+1);
		player2[i]->addComponent<TransformComponent>(position_ini[2*i+1], 1);
		player2[i]->addComponent<SpriteComponent>(image[2*i+1], turn_indicator, range_indicator);
		player2[i]->addComponent<StatsComponent>(2*i+1);
		
	}
	player1[0]->getComponent<StatsComponent>().myturn = true;
	
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
		Mouse_Controller( GameMap->map,GameMap->itemMap, &attack);
		break;
	default:
		break;
	}
};
void UCW::update() {
	manager1.refresh();
	manager1.update();
	manager2.refresh();
	manager2.update();
	
};

void UCW::render() {
	background = TextureManager::LoadTexture("assets/background/background.png"); //3d - Dot - Heroes4
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
	//this add stuffs to render
	int i;
	if (menu_checked == false) { 
		if (endgame == false) i = menu.draw(labels);
		else i = menu.draw(labels2);
		if (i == 0 && endgame == false) {
			menu_checked = true;
		}
		else if (i == 0 && endgame == true) {
			//restart
			restart = true;
			menu_checked = false;
			isRunning = false;
		}
		else if (i == 2) {
			isRunning = false;
		}
	}

	if (menu_checked == true) {
		if (player1nameInput == 0) {
			player1nameInput = name_input1.draw();
			if (player1nameInput == 2) isRunning = false;
			player1name = name_input1.getName();
			name_input1.clean();
		}
		else if (player2nameInput == 0){
			player2nameInput = name_input2.draw();
			if (player2nameInput == 2) isRunning = false;
			player2name = name_input2.getName();
			name_input2.clean();
		}
		if (player2nameInput == true) {
			attack.clean();
			GameMap->draw();
			manager1.draw();
			manager2.draw();
			statsmenu.draw();

			bool draw_allowing = false;
			for (int i = 0; i < 6; i++) {
				if ((Player::allChickens[i])->getComponent<StatsComponent>().choosing) {
					draw_allowing = true;
					break;
				}
			}
			int numPlayer1 = 0;
			int numPlayer2 = 0;
			for (int i = 0; i < manager1.returnlength(); i++) {
				if (player1[i]->getComponent<StatsComponent>().isAlive) numPlayer1++;
				if (player2[i]->getComponent<StatsComponent>().isAlive) numPlayer2++;
			}

			if (numPlayer2 == 0) {
				player1name = player1name + " win!";
				Popup final1(player1name, 1500, 1728);
				final1.draw();
				menu_checked = false;
				endgame = true;
			}
			if (numPlayer1 == 0) {
				player2name = player2name + " win!";
				Popup final2(player2name, 1500, 1728);
				final2.draw();
				menu_checked = false;
				endgame = true;
			}
			final1.clean();
			final2.clean();

			static bool running = false;
			if (draw_allowing) {
				attack.draw();
				running = true;
			}
			attack.clean();
			statsmenu.clean();

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


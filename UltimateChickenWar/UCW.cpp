#include "UCW.h"
#include "Map.h"
#include "Player_system.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Mouse_Controller.h"
#include "StatsComponent.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "LoadTextureFromText.h"
#include "Popup.h"
#include "Menu.h"
#include <string>
#include "stats_table.h"
#include "NameInput.h"

//Game Map
Map* GameMap;
Chicken* Player::allChickens[6];	//foward declaration of static variable in class Player
SDL_Renderer* UCW::renderer = nullptr;	//definition of static variable in UCW class 
SDL_Event UCW::event;	//foward declaration of static variable in class UCW
SDL_Rect position[9][16];	//rendering rectangles of map tiles drawn from top left corner 
SDL_Rect position_ini[6];	//intial rendering position for 6 chickens
SDL_Rect center_position[9][16];		//center of rendering rectangles of map tiles 
TTF_Font* UCW::gFont=nullptr;	//font is null
bool temp_endgame = false;
//creating instances of class popup (constructor ("string to display", location of text))
Popup attack("attack or not?",1500, 1728);	//Popup when you attack opponent
Popup final1("Player 1 wins", 1500, 1728);	//Popup when player1 wins
Popup final2("Player 2 wins", 1500, 1728);	//Popup  when player2 wins

//creating instances of class popup (constructor (default name of the player))
NameInput name_input1("player 1");
NameInput name_input2("player 2");

//create instances of Player class
Player manager1;	//Player1
Player manager2;	//Player2
Chicken* player1[3];	//3 chicken of player 1 
Chicken* player2[3];	//3 chicken of player 2

//chicken's image path
char* image[6] = { "assets/character/chicken_warrior.png", "assets/character/chicken_warrior2.png","assets/character/chicken_acher.png", "assets/character/chicken_acher2.png","assets/character/chicken_tank.png", "assets/character/chicken_tank2.png" };
//turn indicator's path
char* turn_indicator = { "assets/indicator/turn_indicator.png" };
//range indicator's path
char* range_indicator = { "assets/indicator/range_indicator.png" };
//2d array of stats of each chicken {hp, atk, def, range}
int stats_array[3][4] = { {3,2,1,1},{3,1,0,2},{3,1,2,1} };

//create menu instance
Menu menu;
std::string labels[2] = { "Start","Exit" };	//string for 1st menu (beginning of the game)
std::string labels2[2] = { "Restart","Exit" };	//string for last menu (end game)
stats_table statsmenu;	//stats table to display stats
SDL_Texture* background;	//background image of the game

void UCW::init(const char* title, int xpos, int ypos, int width, int height) {
	//create game window
	int flags = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised!..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);	//create window and enable it to resize
		if (window) {
			std::cout << "Window created!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);	//create renderer
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);	//background color of the window to be white
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;

	}
	//Set logical size to be 1728x900 so that you can change the resolution of the game without affecting it (especially mouse location)  
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	SDL_RenderSetLogicalSize(renderer, 1728, 900);
	
	for (int i = 0; i < manager1.returnlength(); i++) {
		player1[i]->destroy();	//deactivate all the chicken of player1
	}
	manager1.index = 0;	//bring the index of the chicken list back to 0
	manager1.refresh();	//refresh the chicken list of player1
	manager1.update();	//refresh the chicken list of player1
	for (int i = 0; i < manager2.returnlength(); i++) {
		player2[i]->destroy();	//deactivate all the chicken of player1
	}
	
	Player::initialiser();	//initalize the static variable allChickens of class Player
	manager2.index = 0;		//bring the index of the chicken list back to 0
	manager2.refresh();		//refresh the chicken list of player2
	manager2.update();		//refresh the chicken list of player2
	first_time = true;		//next mouse-click is going to be the first time
	GameMap = new Map();
	//Calculating rendering box coordinate drawn from top left corner or center
	//there are 9 rows, 16 columns on the map, and we are going to iterate through all of them
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			//calculale rendering position of each rectangle:
			position[row][column].h = 100;		
			position[row][column].w = 104;
			if (row % 2 == 0) { //even row
				position[row][column].x = column * 104 ;	
				position[row][column].y = row * 100 - 32 * row ;
				center_position[row][column].x = 52 + 104 * column;
				center_position[row][column].y = 50 + 68 * row;
			}
			else {	//odd row
				position[row][column].x = column * 104 + 52 ;
				position[row][column].y = row * 100 - 32 * row;
				center_position[row][column].x = 104 + 104 * column;
				center_position[row][column].y = 50 + 68 * row;
			}
		}
	}

	//starting position of each chicken
	
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
		player1[i] = manager1.addChicken(2*i); // add the chickens in player1 to chickens list of player1
		player1[i]->addComponent<TransformComponent>(position_ini[2*i], 1);	//position_ini[0,2,4], 1 is scale
		player1[i]->addComponent<SpriteComponent>(image[2*i], turn_indicator, range_indicator,GameMap->map); //image[0,2,4]
		player1[i]->addComponent<StatsComponent>(2*i, stats_array[i][0], stats_array[i][1], stats_array[i][2], stats_array[i][3]);	//2*i is turn

		//same as player1
		player2[i] = manager2.addChicken(2*i+1);
		player2[i]->addComponent<TransformComponent>(position_ini[2*i+1], 1);	//position_ini[1,3,5]
		player2[i]->addComponent<SpriteComponent>(image[2*i+1], turn_indicator, range_indicator,GameMap->map);
		player2[i]->addComponent<StatsComponent>(2*i+1, stats_array[i][0], stats_array[i][1], stats_array[i][2], stats_array[i][3]);
		
	}
	player1[0]->getComponent<StatsComponent>()->myturn = true;	//first chicken of player 1 will get the first turn
	
	//initialize font
	TTF_Init();
	std::cout<<"init passed"<<std::endl;
}

//handle quit & mouse click event
void UCW::handleEvents() {
	SDL_PollEvent(&event);	//waiting for event
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;	//close game
		break;
	case SDL_MOUSEBUTTONDOWN:
		Mouse_Controller( GameMap->map,GameMap->itemMap, &attack, temp_endgame);	//call mouse_controller to handle mouse click
		break;
	default:
		break;
	}
};
//update both player
void UCW::update() {
	manager1.refresh();
	manager1.update();
	manager2.refresh();
	manager2.update();
	
};
//render the texture on the window
void UCW::render() {
	background = TextureManager::LoadTexture("assets/background/background.png");	//load the background from the specified path
	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = 1728;
	src.h = 900;
	dest.x = 0;
	dest.y = 0;
	dest.w = 1728;
	dest.h = 900;
	SDL_RenderClear(renderer);	//empty the renderer before rendering anything new
	TextureManager::Draw(background, src, dest);	//draw the background
	//this add stuffs to render
	int i;	//return value of draw() (0 : restart/start, 1 : exit)
	if (menu_checked == false) {	//if menu hasn't been checked
		if (endgame == false) i = menu.draw(labels);	//if game hasn't ended then draw the "start,exit" menu
		else i = menu.draw(labels2);	//if game has ended, draw "restart,exit" menu
		if (i == 0 && endgame == false) {	//if player pressed "start"
			menu_checked = true;	//menu is now checked
		}
		else if (i == 0 && endgame == true) {	//if player pressed "restart"
			//restart
			restart = true;		//restart the game
			menu_checked = false;	//menu has again not been checked
			isRunning = false;		//stop the game to run the game a gain in main loop
		}
		else if (i == 2) {
			isRunning = false;	//if player presses "exit" then quit game
		}
	}

	if (menu_checked == true) {	//if menu has been selected
		if (player1nameInput == 0) {	//if player1 hasn't input name 
			player1nameInput = name_input1.draw(&manager1);	//draw() return (2 : player press "Esc", 1: player finished inputting name)
			if (player1nameInput == 2) isRunning = false;	//if player1 pressed "Esc" then quit game
			name_input1.clean();	//clean the popup
		}
		else if (player2nameInput == 0){	//if player1 has input but player2 has not input name
			player2nameInput = name_input2.draw(&manager2);	
			if (player2nameInput == 2) isRunning = false;
			name_input2.clean();
		}
		if (player2nameInput == true) {	//if player2 has finisjed inputting name
			attack.clean();		//clean the attack popup first
			GameMap->draw();	//draw the map
			manager1.draw();	//draw the chickens1
			manager2.draw();	//draw the chickens2
			statsmenu.draw(manager1.name,manager2.name);	//draw the stats table

			bool draw_allowing = false;		//this variable is used to check whether there is a player attacking
			for (int i = 0; i < 6; i++) {
				if ((Player::allChickens[i])->getComponent<StatsComponent>()->choosing) {	//check if there is a chicken attacking
					draw_allowing = true;
					break;
				}
			}
			//counting the number of alive chickens
			int numPlayer1 = 0;
			int numPlayer2 = 0;
			for (int i = 0; i < manager1.returnlength(); i++) {
				if (player1[i]->getComponent<StatsComponent>()->isAlive) numPlayer1++;
				if (player2[i]->getComponent<StatsComponent>()->isAlive) numPlayer2++;
			}

			//if player 2 loses
			if (numPlayer2 == 0) {
				player1name = manager1.name + " win!";
				Popup final1(player1name, 1500, 1728);
				final1.draw();	//draw the final result
				menu_checked = false;	//draw the restart menu
				endgame = true;		//game has ended
			}

			//if player 1 loses
			if (numPlayer1 == 0) {
				player2name = manager2.name + " win!";
				Popup final2(player2name, 1500, 1728);
				final2.draw();
				menu_checked = false;
				endgame = true;
			}
			//clean both final popup
			final1.clean();	
			final2.clean();

			//when attacking
			if (draw_allowing) {	
				attack.draw();	//draw the attack popup
			}
			attack.clean();		//clean the attack popup
			statsmenu.clean();	//clean the stats table

			SDL_RenderPresent(renderer);	//present the renderer on the window
			if (endgame == true) {	//if game has ended
				SDL_Delay(1000);//delay 1s before displaying restart menu
				temp_endgame = endgame;
			}
		}
	}
	SDL_DestroyTexture(background);		//destroy the background

};
//clean the game
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


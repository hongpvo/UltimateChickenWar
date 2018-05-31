#pragma once
#include "UCW.h"
#include "UI.h"
#include "Player_system.h"

//This class is used to represent Map
//Derived from UI
class Map : public UI {
public:
	//Constructors and destructors
	Map();
	~Map();
	//Load random Map and Item from *.txt file 
	void LoadMap();
	//To display Map and Item list - override draw of UI
	int draw();
	//Friend function allows these classes to acess private instances such as map and item
	friend class UCW;
	friend class SpriteComponent;
private:
	//Initializes items' textures
	SDL_Texture* sword;
	SDL_Texture* shield;
	SDL_Texture* heart;
	//Initializes map terrain tiles' textures
	SDL_Texture* grass1;
	SDL_Texture* grass2;
	SDL_Texture* grass3;
	SDL_Texture* grass4;
	SDL_Texture* sand1;
	SDL_Texture* sand2;
	SDL_Texture* water1;
	SDL_Texture* water2;
	SDL_Texture* water3;
	SDL_Texture* water4;
	//Declare 2D array displaying Map tiles based on terrain tiles
	int map[9][16];
	//Declare 2D array displaying Item location on Map
	int itemMap[9][16];
	//Our redefined map and item list for randomization purpose
	std::string map_list[5] = { "map/map1.txt","map/map2.txt","map/map3.txt","map/map4.txt","map/map5.txt" };
	std::string item_list[5] = { "map/item1.txt","map/item2.txt","map/item3.txt","map/item4.txt","map/item5.txt" };
	//Random variable
	int map_rand;

};
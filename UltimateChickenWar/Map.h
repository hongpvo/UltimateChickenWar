#pragma once
#include "UCW.h"
#include "UI.h"
#include "Player_system.h"

class Map : public UI {
public:
	Map();
	~Map();

	void LoadMap();
	int draw();
	friend void UCW::handleEvents();
	friend class SpriteComponent;
	//friend void SpriteComponent::draw();
private:


	SDL_Texture* sword;
	SDL_Texture* shield;
	SDL_Texture* heart;

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
	//SDL_Texture* background;

	int map[9][16];
	int itemMap[9][16];

	std::string map_list[5] = { "map/map1.txt","map/map2.txt","map/map3.txt","map/map4.txt","map/map5.txt" };
	std::string item_list[5] = { "map/item1.txt","map/item2.txt","map/item3.txt","map/item4.txt","map/item5.txt" };

	int map_rand, item_rand;

};
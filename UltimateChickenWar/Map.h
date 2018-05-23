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


	SDL_Texture* flow;
	SDL_Texture* lowsnow;
	SDL_Texture* yeltree;
	SDL_Texture* water;
	SDL_Texture* mount;
	SDL_Texture* pyah;
	SDL_Texture* sword;
	SDL_Texture* shield;
	//SDL_Texture* background;

	int map[9][16];
	int itemMap[9][16];

};
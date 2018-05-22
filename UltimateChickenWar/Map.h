#pragma once
#include "UCW.h"
#include "UI.h"

class Map : public UI {
public:
	Map();
	~Map();

	void LoadMap(int arr[9][16], int arr2[9][16]);
	void LoadMap(int arr[9][16]);
	void LoadItem(int arr[9][16]);
	int draw();
	friend void UCW::handleEvents();

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
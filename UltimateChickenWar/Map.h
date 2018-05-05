#pragma once
#include "UCW.h"

class Map {
public:
	Map();
	~Map();

	void LoadMap(int arr[9][16]);
	void DrawMap();

private:

	SDL_Rect src, dest;

	SDL_Texture* flow;
	SDL_Texture* lowsnow;
	SDL_Texture* yeltree;
	SDL_Texture* water;
	SDL_Texture* mount;
	SDL_Texture* pyah;

	int map[9][16];
};
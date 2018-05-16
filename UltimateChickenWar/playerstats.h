#pragma once
#//include"UCW.h"
#include "LoadTextureFromText.h"
#include <string>
#include "TextureManager.h"
#include "ECS.h"
#include "StatsComponent.h"

class playerstats {
public:
	playerstats();
	~playerstats();
	void draw(Manager* all_player_manager);
	void clean();
private:
	int x, y;
	SDL_Color color = { 0,0,0 };
	LoadTextureFromText playertext[6];
	SDL_Texture* chicken[6];
	char* image[6] = { "assets/chicken.png", "assets/chicken1.png","assets/chicken.png", "assets/chicken1.png","assets/chicken.png", "assets/chicken1.png" };
	Entity* player[6];
	StatsComponent* stats_player;
	SDL_Rect src[6];
	SDL_Rect dest[6];
	int w[6] = { 576,2880,576,2880,576,2880 };
	int h[6] = { 1500,1500,1600,1600,1700,1700};
};

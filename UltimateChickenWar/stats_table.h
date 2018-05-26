#pragma once
#include "LoadTextureFromText.h"
#include <string>
#include "TextureManager.h"
#include "StatsComponent.h"
#include "UI.h"

//This class is used to represent both player's chickens stats such as hp, def and atk
//Derived from UI
class stats_table : public UI {
public:
	//constructor and destructor
	stats_table();
	~stats_table();
	//Override UI draw and get name of player from UCW (from NameInput::getName())
	int draw(std::string name_player1, std::string name_player2);
	//Override UI clean
	void clean();
private:
	//Define color 
	SDL_Color color = { 255,0,0 };			//red	(color for dead chicken or selected chicken)
	SDL_Color textColor = { 0, 0, 0 };		//black	(stats info color)
	SDL_Color player_color = { 0,0,255 };	//blue (player name color)
	//instances  to render player name and chicken stats to the screen
	LoadTextureFromText playertext[6];
	LoadTextureFromText player1, player2;
	//Declare chicken texture, box, and image list 
	SDL_Texture* chicken[6];
	SDL_Texture* sbox;
	char* image[6] = { "assets/character/chicken_warrior.png", "assets/character/chicken_acher.png","assets/character/chicken_tank.png", "assets/character/chicken_warrior2.png","assets/character/chicken_acher2.png", "assets/character/chicken_tank2.png" };
	Chicken* player[6];
	//stats component instance to get stats of chicken and render it
	StatsComponent* stats_player;
	//left and right box rectangle and chicken images render rectangle
	SDL_Rect src[6];
	SDL_Rect dest[6];
	SDL_Rect lboxsrc, lboxdes, rboxsrc, rboxdes;
	// width and height of text location for stats of 6 chickens
	int w[6] = { 530, 3000,530,3000,530,3000 };
	int h[6] = { 1500,1500,1600,1600,1700,1700 };
};

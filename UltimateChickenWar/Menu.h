#pragma once
#include"UCW.h"
#include "LoadTextureFromText.h"
#include <string>
#include "TextureManager.h"
#include "UI.h"
//This class is used to display Menu when the game start and when the game end
//Derived from UI
class Menu : public UI {
public:
	//Constructors and destructors
	Menu();
	~Menu();
	//To display Map and Item list - override draw of UI
	int draw(std::string labels[2]);
private:
	//event motion variable of x and y
	int x, y;
	//boolean variable to check if you select button 1 or 2
	bool selected[2] = { 0,0 };
	//Instances array of LoadTextureFromText to display Menu button and Game title
	LoadTextureFromText menus[2];
	LoadTextureFromText Game_title[2];
	//Set color of title
	SDL_Color title_color = { 255,0,255 }; //purple	(based on RGB)
};

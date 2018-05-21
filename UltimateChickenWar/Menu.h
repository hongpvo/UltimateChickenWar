#pragma once
#include"UCW.h"
#include "LoadTextureFromText.h"
#include <string>
#include "TextureManager.h"
#include "UI.h"

class Menu : public UI {
public:
	Menu();
	~Menu();
	int draw(std::string labels[2]);
private:
	Uint32 time;
	int x, y;
	bool selected[2] = { 0,0 };
	SDL_Color color[2] = { { 0,0,0 },{ 255,0,0 } };
	LoadTextureFromText menus[2];

};

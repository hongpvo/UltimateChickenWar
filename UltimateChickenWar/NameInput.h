#pragma once
#include"UCW.h"
#include "LoadTextureFromText.h"
#include <string>
#include "TextureManager.h"
#include "Popup.h"
#include "UI.h"

class NameInput: public UI{
public:
	NameInput(std::string str);
	~NameInput();
	int draw();
	std::string getName();
	void clean();

private:
	std::string name, player;
	SDL_Event event;
	LoadTextureFromText gInput, title;
	SDL_Texture* box,*background;
	SDL_Color color = { 0,0,0 };
	SDL_Rect src, dest,bsrc,bdest;
	bool renderText = false;
	bool end = false;
};
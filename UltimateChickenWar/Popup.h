#pragma once
#include"UCW.h"
#include "LoadTextureFromText.h"
#include <string>
#include "TextureManager.h"

class Popup {
public:
	Popup(std::string str,int h,int w);
	~Popup();
	void draw();
	void clean();

private:
	LoadTextureFromText gTextTexture;
	std::string text;
	SDL_Texture* box;
	SDL_Rect src, dest;
	int height;
	int width;
};
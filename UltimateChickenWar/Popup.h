#pragma once
#include"UCW.h"
#include "LoadTextureFromText.h"
#include <string>
#include "TextureManager.h"
#include "UI.h"

class Popup: public UI {
public:
	Popup(std::string str,int h,int w);
	~Popup();
	int draw();
	void clean();

private:
	LoadTextureFromText gTextTexture;
	std::string text;
	int height;
	int width;
};
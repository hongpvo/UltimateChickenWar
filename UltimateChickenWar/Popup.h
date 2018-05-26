#pragma once
#include"UCW.h"
#include "LoadTextureFromText.h"
#include <string>
#include "TextureManager.h"
#include "UI.h"
//This class is used to represent Popup box and info that you want to display
//Derived from UI
class Popup: public UI {
public:
	// Popup constructor with input location of the text and text to render
	Popup(std::string str,int h,int w);
	~Popup();
	// Override draw function of UI
	int draw();
	// Override clean function of UI
	void clean();

private:
	// instance to render the text
	LoadTextureFromText gTextTexture;
	// variable to store the text
	std::string text;
	// height and width show the location of the text
	int height;
	int width;
};
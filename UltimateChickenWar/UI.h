#pragma once
#include <iostream>
//base class of Map, Menu, NameInput, Popup, and stats_table
class UI {
public:
	//default function draw
	virtual int draw() {
		std::cout << "Default Draw Nothing" << std::endl;
		return 0;
	};
	//default function clean
	virtual void clean() {
		std::cout << "Default Clean Nothing" << std::endl;
	};
protected:
	// Rectangle to draw box or background
	SDL_Rect src, dest;
	SDL_Rect bsrc, bdest;
	// Texture box and background (basic elements of UI)
	SDL_Texture* box, *background;
	// Color of text (if any)
	SDL_Color color[2];
};
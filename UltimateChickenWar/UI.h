#pragma once
#include <iostream>
class UI {
public:
	virtual int draw() {
		std::cout << "Default Draw Nothing" << std::endl;
		return 0;
	};
	virtual void clean() {
		std::cout << "Default Clean Nothing" << std::endl;
	};
protected:
	SDL_Rect src, dest;
	SDL_Rect bsrc, bdest;
	SDL_Texture* box, *background;
	SDL_Color color[2];
};
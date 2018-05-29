#pragma once

#include "UCW.h"
//handle all texture-relating events
class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName);	//load the texture from the path
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);	//take the texure at "src" and draw at "dest"

};

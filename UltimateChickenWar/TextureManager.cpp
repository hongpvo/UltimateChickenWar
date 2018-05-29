#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);	//create temporary surface
	SDL_Texture* tex = SDL_CreateTextureFromSurface(UCW::renderer, tempSurface);	//create texture from surface
	SDL_FreeSurface(tempSurface);	//free the temporary surface

	return tex;		//return the texture
}
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(UCW::renderer, tex, &src, &dest);	//copy the texture from "src" to "dest"
}
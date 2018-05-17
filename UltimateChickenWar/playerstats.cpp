#include "playerstats.h"

playerstats::playerstats() {
	for (int i = 0; i < 6; i++) {
		src[i].x = 0;
		src[i].y = 0;
		src[i].w = 108/1.5;
		src[i].h = 100/1.5;

		if(i<3) dest[i].x = 0 ;
		else dest[i].x = 1235;
		dest[i].y = 710 + (i%3)* 50;
		dest[i].w = 108/1.5;
		dest[i].h = 100/1.5;
	}
}
playerstats::~playerstats() {

}
void playerstats::draw(Manager* all_player_manager) {
	for (int i = 0; i < 6; i++) {
		player[i] = all_player_manager->getEntityList().at(i);
		chicken[i] = TextureManager::LoadTexture(image[i]);
		TextureManager::Draw(chicken[i], src[i], dest[i]);
		//Open the font
		UCW::gFont = TTF_OpenFont("pixelFJ8pt1__.ttf", 30);
		//Render text
		
		stats_player = &player[i]->getComponent<StatsComponent>();
		std::string atk = std::to_string(stats_player->atk);
		std::string hp = std::to_string(stats_player->hp);
		std::string def = std::to_string(stats_player->def);
		std::string str;
		if (stats_player->isAlive == 0) {
			str = "DEAD";
			playertext[i].loadFromRenderedText(str, color);
		}
		else {
			str = "HP: " + hp + "   " + "ATK: " + atk + "   " + "DEF: " + def;
			playertext[i].loadFromRenderedText(str, textColor);
		}
		playertext[i].render((w[i] - playertext[i].getWidth()) / 2, (h[i] - playertext[i].getHeight()) / 2);
	}
	
}
void playerstats::clean() {
	for (int i = 0; i < 6; i++) {
		playertext[i].free();
		SDL_DestroyTexture(chicken[i]);
	}
	TTF_CloseFont(UCW::gFont);
	UCW::gFont = NULL;
}
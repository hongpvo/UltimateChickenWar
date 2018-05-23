#include "stats_table.h"


stats_table::stats_table() {
	for (int i = 0; i < 6; i++) {
		src[i].x = 0;
		src[i].y = 0;
		src[i].w = 108/1.5;
		src[i].h = 100/1.5;

		if(i<3) dest[i].x = -10 ;
		else dest[i].x = 1225;
		dest[i].y = 710 + (i%3)* 50;
		dest[i].w = 108/1.5;
		dest[i].h = 100/1.5;
	}
	//left stats box of player 1
	lboxsrc.x = 0;
	lboxsrc.y = 0;
	lboxsrc.w = 500;
	lboxsrc.h = 400;
	
	lboxdes.x = 0;
	lboxdes.y = 700;
	lboxdes.w = 500;
	lboxdes.h = 400;
	//right stats box of player 2
	rboxsrc.x = 0;
	rboxsrc.y = 0;
	rboxsrc.w = 500;
	rboxsrc.h = 400;

	rboxdes.x = 1225;
	rboxdes.y = 700;
	rboxdes.w = 500;
	rboxdes.h = 400;

}
stats_table::~stats_table() {

}
int stats_table::draw() {
	sbox = TextureManager::LoadTexture("assets/sbox.png");
	TextureManager::Draw(sbox,lboxsrc,lboxdes);
	TextureManager::Draw(sbox,rboxsrc,rboxdes);
	//Open the font
	UCW::gFont = TTF_OpenFont("pixelFJ8pt1__.ttf", 30);
	for (int i = 0; i < 6; i++) {
		player[i] = Player::allChickens[i];
		chicken[i] = TextureManager::LoadTexture(image[i]);
		TextureManager::Draw(chicken[i], src[i], dest[i]);
		//Render text
		stats_player = &player[i]->getComponent<StatsComponent>();
		std::string atk = std::to_string(stats_player->atk);
		std::string hp = std::to_string(stats_player->hp);
		std::string def = std::to_string(stats_player->def);
		bool myturn = stats_player->myturn;
		std::string str;
		if (stats_player->isAlive == 0) {
			str = "DEAD";
			playertext[i].loadFromRenderedText(str, color);
		}
		else {
			str = "HP: " + hp + "   " + "ATK: " + atk + "   " + "DEF: " + def;
			if (myturn == false)
			playertext[i].loadFromRenderedText(str, textColor);
			else 
			playertext[i].loadFromRenderedText(str, color);
		}
		playertext[i].render((w[i] - playertext[i].getWidth()) / 2, (h[i] - playertext[i].getHeight()) / 2);
	}
	return 0;
	
}
void stats_table::clean() {
	for (int i = 0; i < 6; i++) {
		playertext[i].free();
		SDL_DestroyTexture(chicken[i]);
	}
	TTF_CloseFont(UCW::gFont);
	SDL_DestroyTexture(sbox);
	UCW::gFont = NULL;
}
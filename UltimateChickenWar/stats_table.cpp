#include "stats_table.h"


stats_table::stats_table() {
	//calculate chicken image location and scale of it
	for (int i = 0; i < 6; i++) {
		src[i].x = 0;
		src[i].y = 0;
		src[i].w = 108/1.5; //scale 2/3
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
	lboxdes.y = 650;
	lboxdes.w = 500;
	lboxdes.h = 400;
	//right stats box of player 2
	rboxsrc.x = 0;
	rboxsrc.y = 0;
	rboxsrc.w = 500;
	rboxsrc.h = 400;

	rboxdes.x = 1225;
	rboxdes.y = 650;
	rboxdes.w = 500;
	rboxdes.h = 400;

}
stats_table::~stats_table() {

}
int stats_table::draw(std::string name_player1, std::string name_player2) {
	//Load and Render 2 box from *.PNG
	sbox = TextureManager::LoadTexture("assets/box/sbox.png");
	TextureManager::Draw(sbox,lboxsrc,lboxdes);
	TextureManager::Draw(sbox,rboxsrc,rboxdes);
	//Open the font
	UCW::gFont = TTF_OpenFont("pixelFJ8pt1__.ttf", 30);
	//Render name of player 1 and player 2 with blue color
	player1.loadFromRenderedText(name_player1, player_color);
	player2.loadFromRenderedText(name_player2, player_color);
	player1.render((500 - player2.getWidth()) / 2, (1370 - player2.getHeight()) / 2);
	player2.render((2950 - player2.getWidth()) / 2, (1370 - player2.getHeight()) / 2);
	//Render stats of chickens
	for (int i = 0; i < 6; i++) {
		//get stats of all chickens from UCW
		player[i] = Player::allChickens[i];
		//Draw image of 6 chickens
		chicken[i] = TextureManager::LoadTexture(image[i]);
		TextureManager::Draw(chicken[i], src[i], dest[i]);
		//Render text
		stats_player = player[i]->getComponent<StatsComponent>();
		std::string atk = std::to_string(stats_player->atk);		//attack
		std::string hp = std::to_string(stats_player->hp);			//health point
		std::string def = std::to_string(stats_player->def);		//defend
		bool myturn = stats_player->myturn;							//get turn of which chicken 
		std::string str;
		//if chicken is not alive, instead of displaying stats, we will display a red colored "DEAD"
		if (stats_player->isAlive == 0) {		
			str = "DEAD";
			playertext[i].loadFromRenderedText(str, color);
		}
		//if chicken is alive we will display its stats (which gets from StatsComponent of player)
		else {
			str = "HP: " + hp + "   " + "ATK: " + atk + "   " + "DEF: " + def;
			if (myturn == false)
			playertext[i].loadFromRenderedText(str, textColor); //if not its turn, text color will be black
			else 
			playertext[i].loadFromRenderedText(str, color);		//if its turn, text color will be red to distinguish with others
		}
		playertext[i].render((w[i] - playertext[i].getWidth()) / 2, (h[i] - playertext[i].getHeight()) / 2);
	}
	return 0;
	
}
void stats_table::clean() {
	//clean chicken image, font, box and text
	for (int i = 0; i < 6; i++) {
		playertext[i].free();
		SDL_DestroyTexture(chicken[i]);
	}
	TTF_CloseFont(UCW::gFont);
	SDL_DestroyTexture(sbox);
	UCW::gFont = NULL;
}
#include "Map.h"
#include "TextureManager.h"
#include <fstream>
#include <stdlib.h>
#include <time.h>

SDL_Rect pos[9][16];

Map::Map() {
	grass1 = TextureManager::LoadTexture("assets/tiles/grass1.png");
	grass2 = TextureManager::LoadTexture("assets/tiles/grass2.png");
	grass3 = TextureManager::LoadTexture("assets/tiles/grass3.png");
	grass4 = TextureManager::LoadTexture("assets/tiles/grass4.png");
	sand1 = TextureManager::LoadTexture("assets/tiles/sand1.png");
	sand2 = TextureManager::LoadTexture("assets/tiles/sand2.png");
	water1 = TextureManager::LoadTexture("assets/tiles/water1.png");
	water2 = TextureManager::LoadTexture("assets/tiles/water2.png");
	water3 = TextureManager::LoadTexture("assets/tiles/water3.png");
	water4 = TextureManager::LoadTexture("assets/tiles/water4.png");

	sword = TextureManager::LoadTexture("assets/item/sword.png");
	shield = TextureManager::LoadTexture("assets/item/shield.png");
	heart = TextureManager::LoadTexture("assets/item/heart.png");

	srand(time(NULL));
	map_rand = rand() % 5;

	LoadMap();
	src.x = 0;
	src.y = 0;
	src.h = 100;
	src.w = 108;

	dest.h = 100;
	dest.w = 108;
	dest.x = 0;
	dest.y = 0;
}

Map::~Map() {
	SDL_DestroyTexture(grass1);
	SDL_DestroyTexture(grass2);
	SDL_DestroyTexture(grass3);
	SDL_DestroyTexture(grass4);
	SDL_DestroyTexture(sand1);
	SDL_DestroyTexture(sand2);
	SDL_DestroyTexture(water1);
	SDL_DestroyTexture(water2);
	SDL_DestroyTexture(water3);
	SDL_DestroyTexture(water4);

	SDL_DestroyTexture(sword);
	SDL_DestroyTexture(heart);
	SDL_DestroyTexture(shield);

}
void Map::LoadMap() {

	std::ifstream input_map ,input_item;

	input_map.open(map_list[map_rand]);
	input_item.open(item_list[map_rand]);

	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			input_map>>map[row][column];
			
		}
	}
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			input_item>>itemMap[row][column];
		}
	}
	input_map.close();
	input_item.close();
}


int Map::draw() {
	int type = 0;
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			type = map[row][column];
			if (row % 2 == 0) {
				dest.x = column * 104 ;
				dest.y = row * 100 - 32 * row ;
				dest.w = 108 ;
				dest.h = 100 ;
			}
			else {
				dest.x = column * 104 + 52;
				dest.y = row * 100 - 32 * row ;
				dest.w = 108;
				dest.h = 100;
			}
			switch (type) {
			case 0:
				TextureManager::Draw(grass1, src, dest);
				break;
			case 1:
				TextureManager::Draw(grass2, src, dest);
				break;
			case 2:
				TextureManager::Draw(grass3, src, dest);
				break;
			case 3:
				TextureManager::Draw(grass4, src, dest);
				break;
			case 4:
				TextureManager::Draw(sand1, src, dest);
				break;
			case 5:
				TextureManager::Draw(sand2, src, dest);
				break;
			case 6:
				TextureManager::Draw(water1, src, dest);
				break;
			case 7:
				TextureManager::Draw(water2, src, dest);
				break;
			case 8:
				TextureManager::Draw(water3, src, dest);
				break;
			case 9:
				TextureManager::Draw(water4, src, dest);
				break;
			default:
				break;
			}
		}
	}
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			type = itemMap[row][column];
			if (row % 2 == 0) {
				dest.x = column * 104 + 10;
				dest.y = row * 100 - 32 * row + 20;
				dest.w = 108/1.5;
				dest.h = 100/1.5;
			}
			else {
				dest.x = column * 104 + 52 + 10;
				dest.y = row * 100 - 32 * row + 20;
				dest.w = 108 / 1.5;
				dest.h = 100 / 1.5;
			}
			switch (type) {
			case 1:
				TextureManager::Draw(sword, src, dest);
				break;
			case 2:
				TextureManager::Draw(shield, src, dest);
				break;
			case 3:
				TextureManager::Draw(heart, src, dest);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}


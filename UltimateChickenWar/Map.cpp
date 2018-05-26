#include "Map.h"
#include "TextureManager.h"
#include <fstream> //for input purpose
#include <stdlib.h> //for randomization purpose
#include <time.h> 

Map::Map() {
	//Load terrain's textures from *.PNG that we have made by PISKEL
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
	//Load item's textures from *.PNG that we have made by PISKEL
	sword = TextureManager::LoadTexture("assets/item/sword.png");
	shield = TextureManager::LoadTexture("assets/item/shield.png");
	heart = TextureManager::LoadTexture("assets/item/heart.png");
	//random a number from 0 to 4 which is the index of map and item in its list
	srand(time(NULL));
	map_rand = rand() % 5;
	//Call LoadMap function to input map and item from *.txt to 2D array map and itemMap
	LoadMap();
	//Create a rectangle region to render textures 108x100 pixels
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
	//Clear defined textures from memory
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
	//input map from file *.txt
	std::ifstream input_map ,input_item;
	//input random map from list (the index of map and item is the same)
	input_map.open(map_list[map_rand]);
	input_item.open(item_list[map_rand]);
	// for loop to input map to 2D map array 
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			input_map>>map[row][column];
		}
	}
	//for loop to input item location to 2D item array
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			input_item>>itemMap[row][column];
		}
	}
	//close input stream
	input_map.close();
	input_item.close();
}


int Map::draw() {
	//type variable which values defined which type of terrain to display
	int type = 0;
	//loop to display terrain 
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			type = map[row][column];
			if (row % 2 == 0) {							// even rows
				dest.x = column * 104 ;					// 104 instead of 108 because we want to overlap 2 vertical border
				dest.y = row * 100 - 32 * row ;			// shift row up 32 pixel because of hexagon (~=1/3 of 100)
				dest.w = 108 ;
				dest.h = 100 ;
			}
			else {										// odd rows
				dest.x = column * 104 + 52;				//shift column to the right 52 pixel (1/2 of 104)
				dest.y = row * 100 - 32 * row ;			//shift row up 32 pixel 
				dest.w = 108;
				dest.h = 100;
			}
			switch (type) {								//type of terrain based on value in input array 
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
	//similar to upper section
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


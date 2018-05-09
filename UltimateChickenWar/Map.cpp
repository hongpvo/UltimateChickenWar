#include "Map.h"
#include "TextureManager.h"
#include <fstream>

std::fstream input;
int lv1[9][16] =
{	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,
	2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,
	5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,
	5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,
	5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0
};



SDL_Rect pos[9][16];

Map::Map() {
	flow = TextureManager::LoadTexture("assets/grass/grass1.png");
	lowsnow = TextureManager::LoadTexture("assets/grass/grass4.png");
	yeltree = TextureManager::LoadTexture("assets/sand/sand1.png");
	water = TextureManager::LoadTexture("assets/water.png");
	mount = TextureManager::LoadTexture("assets/mout.png");
	pyah = TextureManager::LoadTexture("assets/water/water1.png");

	LoadMap(lv1);
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
	SDL_DestroyTexture(flow);
	SDL_DestroyTexture(lowsnow);
	SDL_DestroyTexture(yeltree);
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(mount);
	SDL_DestroyTexture(pyah);
}
void Map::LoadMap(int arr[9][16]) {
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			map[row][column] = arr[row][column];
		}
	}
}
void Map::GetMap(int arr[9][16]) {
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			arr[row][column] = lv1[row][column];
		}
	}
}
void Map::DrawMap() {
	int type = 0;
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			type = map[row][column];
			if (row % 2 == 0) {
				dest.x = column * 104 ;
				dest.y = row * 100 - 32 * row ;
			}
			else {
				dest.x = column * 104 + 52;
				dest.y = row * 100 - 32 * row  ;
			}
			switch (type) {
			case 0:
				TextureManager::Draw(flow, src, dest);
				break;
			case 1:
				TextureManager::Draw(lowsnow, src, dest);
				break;
			case 2:
				TextureManager::Draw(yeltree, src, dest);
				break;
			case 3:
				TextureManager::Draw(water, src, dest);
				break;
			case 4:
				TextureManager::Draw(mount, src, dest);
				break;
			case 5:
				TextureManager::Draw(pyah, src, dest);
				
				break;
			default:
				break;
			}
		}
	}
}


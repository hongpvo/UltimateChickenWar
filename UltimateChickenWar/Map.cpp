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
SDL_Rect pos[25][25];
Map::Map() {
	flow = TextureManager::LoadTexture("assets/flow.png");
	lowsnow = TextureManager::LoadTexture("assets/lowsnow.png");
	yeltree = TextureManager::LoadTexture("assets/yeltree.png");
	water = TextureManager::LoadTexture("assets/water.png");
	mount = TextureManager::LoadTexture("assets/mout.png");
	pyah = TextureManager::LoadTexture("assets/pyah.png");

	LoadMap(lv1);
	src.x = 0;
	src.y = 0;
	src.h = 64;
	src.w = 64;

	dest.h = 64;
	dest.w = 64;
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

void Map::DrawMap() {
	int type = 0;
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			type = map[row][column];
			if (row % 2 == 0) {
				dest.x = column * 64;
				dest.y = row * 64 - 16 * row;

			}
			else {
				dest.x = column * 64 + 32;
				dest.y = row * 64 - 16 * row;


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
			default:
				break;
			}

		}

	}


}


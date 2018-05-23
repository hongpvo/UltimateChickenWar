#pragma once
#include "Component.h"
//#include "ECS.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Mouse_Controller.h"
#include "Map.h"
#include <iostream>
using namespace std;
Map* loadmap = NULL;
int checkmap[9][16];
extern SDL_Rect position[9][16];
extern SDL_Rect center_position[9][16];
class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	StatsComponent* stats;
	SDL_Texture *texture;
	SDL_Texture *turn_indicator;
	SDL_Texture *range_indicator;
	SDL_Rect srcRect, destRect, destRect1;
	bool indicator_allowing;
	
	int mouse_x, mouse_y, mouse_row, mouse_col;
	int mouse_center_x, mouse_center_y;
	int player_x, player_y, player_range;
	
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path, char* background, char* moving_background)
	{
		setTex(path,background, moving_background);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(turn_indicator);
		SDL_DestroyTexture(range_indicator);
		delete loadmap;
	}
	void setTex(const char* path, char* background, char* range_background) {
		texture = TextureManager::LoadTexture(path);
		turn_indicator = TextureManager::LoadTexture(background);
		range_indicator = TextureManager::LoadTexture(range_background);
	}
	void init() override {
		transform = &chicken->getComponent<TransformComponent>();
		loadmap = new Map();
		srcRect.x = srcRect.y = 0;
		srcRect.w = 108;
		srcRect.h = 100;

	}
	void update() override {
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = 108;
		destRect.h = 100;
		destRect1.h = 100;
		destRect1.w = 108;
	}
	void draw() override {
		SDL_GetMouseState(&mouse_x, &mouse_y);
		int mouse_row_col[2];
		find_mouseCenter(mouse_x, mouse_y, mouse_col, mouse_row, mouse_center_x, mouse_center_y);
		if (indicator_allowing) {
			TextureManager::Draw(turn_indicator, srcRect, destRect);
			player_x = transform->position.x + 52;
			player_y = transform->position.y + 50;
			if (sqrt(pow(player_x - mouse_center_x, 2) + pow(player_y - mouse_center_y, 2)) <= (chicken->getComponent<StatsComponent>()).range * 104 && (loadmap->map)[mouse_row][mouse_col]!=5) {
				if (mouse_row % 2 == 0) {
					destRect1.x = mouse_col * 104;
					destRect1.y = mouse_row * 68;
				}
				else {
					destRect1.x = mouse_col * 104 + 52;
					destRect1.y = mouse_row * 68;
				}
				TextureManager::Draw(range_indicator, srcRect, destRect1);
			}

		}
		TextureManager::Draw(texture, srcRect, destRect);
		//to update indicator_allowing
		indicator_allowing = (chicken->getComponent<StatsComponent>()).myturn;
		
	}
};
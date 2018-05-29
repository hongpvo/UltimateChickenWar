#pragma once
#include "Player_system.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Mouse_Controller.h"
#include "StatsComponent.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Map.h"
#include <iostream>
using namespace std;
Map* loadmap = NULL;
//these are variables used in UCW.cpp, so we use extern to use them
extern SDL_Rect position[9][16];
extern SDL_Rect center_position[9][16];

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;	//position of the this chicken
	StatsComponent* stats;		//stats of this chicken
	SDL_Texture *texture;		//image of this chicken
	SDL_Texture *turn_indicator;	//the hexagon displaying the turn
	SDL_Texture *range_indicator;	//the hexagon displaying the range - the range that you are allowed to move or attack there
	SDL_Rect srcRect, destRect, destRect1;	//these are rectangles to render the range indicator and turn indicator
	
	bool indicator_allowing;	//indicating whether the indicator can be displayed, meaning if this is your turn 
	//coordinate of the mouse and this chicken
	int mouse_x, mouse_y, mouse_row, mouse_col;
	int mouse_center_x, mouse_center_y;
	int player_x, player_y, player_range;
	
public:
	//SpriteComponent() = default;
	//constructor
	SpriteComponent(const char* path, char* background, char* moving_background)
	{
		setTex(path,background, moving_background);	//load the texture by the specified path
	}
	//destructor
	~SpriteComponent() {
		//destroy all the loaded texture
		SDL_DestroyTexture(texture);	
		SDL_DestroyTexture(turn_indicator);
		SDL_DestroyTexture(range_indicator);
		delete loadmap;	//release the dynamic memory
	}
	//load the texture
	void setTex(const char* path, char* background, char* range_background) {
		texture = TextureManager::LoadTexture(path);
		turn_indicator = TextureManager::LoadTexture(background);
		range_indicator = TextureManager::LoadTexture(range_background);
	}
	void init() override {	//init the transform component
		transform = chicken->getComponent<TransformComponent>();	//get the transform component of this chicken
		loadmap = new Map();	//get the map
		srcRect.x = srcRect.y = 0;
		srcRect.w = 108;
		srcRect.h = 100;

	}
	//overriding base class virtual function
	void update() override {
		//we will render the turn indicator at the position of the chicken
		destRect.x = (int)(transform->position.x);	//casting from float to int. 
		destRect.y = (int)(transform->position.y);
		destRect.w = 108;
		destRect.h = 100;
		destRect1.h = 100;
		destRect1.w = 108;
	}
	//overriding base class virtual function
	void draw() override {
		mouse_x = UCW::event.button.x;
		mouse_y = UCW::event.button.y;	//get current position of the mouse
		int mouse_row_col[2];
		find_mouseCenter(mouse_x, mouse_y, mouse_col, mouse_row, mouse_center_x, mouse_center_y);	//use functions from Mouse_controller.h
		if (indicator_allowing) {	//if this is the chicken's turn
			TextureManager::Draw(turn_indicator, srcRect, destRect);	//draw the turn indicator
			player_x = transform->position.x + 52;
			player_y = transform->position.y + 50;
			player_range = (chicken->getComponent<StatsComponent>())->range * 104;	//104 is a circle with radius 104 pixels at the origin of the player
			//check if mouse within range and not on water tiles
			if (sqrt(pow(player_x - mouse_center_x, 2) + pow(player_y - mouse_center_y, 2)) <= player_range && ((loadmap->map)[mouse_row][mouse_col] != 6
				 && (loadmap->map)[mouse_row][mouse_col] != 7 && (loadmap->map)[mouse_row][mouse_col] != 8 && (loadmap->map)[mouse_row][mouse_col] != 9)) {
				if (mouse_row % 2 == 0) {	//if row is even
					destRect1.x = mouse_col * 104;	//position to render the range_indicator
					destRect1.y = mouse_row * 68;
				}
				else {	//if row is now odd
					destRect1.x = mouse_col * 104 + 52;
					destRect1.y = mouse_row * 68;
				}
				TextureManager::Draw(range_indicator, srcRect, destRect1);	//draw the range_indicator
			}

		}
		TextureManager::Draw(texture, srcRect, destRect);	//draw the image of the chicken
		//to update indicator_allowing
		indicator_allowing = (chicken->getComponent<StatsComponent>())->myturn;	//check the turn
		
	}
};
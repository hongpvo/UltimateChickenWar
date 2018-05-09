#pragma once

#include "UCW.h"
#include "ECS.h"
#include "Component.h"

class Mouse_Controller : public Component {
public:
	TransformComponent * transform;
	//StatsComponent *stats;
	int chi_row, chi_col, player_num; //chicken position
	double dist[9][16];
	SDL_Rect positionRC[9][16];
	int mouse_x, mouse_y;
	TransformComponent opponent_position;

	Mouse_Controller(int index, TransformComponent opponent) {
		player_num = index;
		opponent_position = opponent;
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		
		//get array of centroids of tiles
		for (int row = 0; row < 9; row++) {
			for (int column = 0; column < 16; column++) {
				positionRC[row][column] = transform->positionRC[row][column];
			}
		}
	}
	void update() override {
		transform->getPosition();
		//Get position of chicken
		chi_row = transform->posRow;
		chi_col = transform->posCol;
		//check if mouse is down
		if (UCW::event.type == SDL_MOUSEBUTTONDOWN) {
			//get mouse state
			std::cout << "Mouse pressed" << std::endl;
			SDL_GetMouseState(&mouse_x, &mouse_y);
			//std::cout << "row: " << mouse_x << ", col: " << mouse_y << std::endl;
			//calculate distance from all the centroids
			for (int row = 0; row < 9; row++) {
				for (int column = 0; column < 16; column++) {
					dist[row][column] = sqrt(pow(mouse_x - positionRC[row][column].x, 2) + pow(mouse_y - positionRC[row][column].y, 2));
					double a = dist[row][column];
				
				}
			}

			double min = dist[0][0];
			int mouse_row = 0;
			int mouse_col = 0;

			//find the closet distance -> belong to that tile
			for (int row = 0; row < 9; row++) {
				for (int column = 0; column < 16; column++) {
					if (dist[row][column] <= min) {
						min = dist[row][column];
						mouse_row = row;
						mouse_col = column;
					}
				}
			}
			std::cout << "row: " << mouse_row << ", col: " << mouse_col << std::endl;
			//valid movement
			if ((chi_row % 2 == 1) && ((mouse_col == chi_col)||(mouse_col == chi_col + 1)) && (abs(mouse_row - chi_row) == 1) ) {
				
					transform->position.x = mouse_col * 108;
					transform->position.y = mouse_row * 68;
				
			}
			else if ((chi_row % 2 == 0) && ((mouse_col == chi_col) || (mouse_col == chi_col - 1)) && (abs(mouse_row - chi_row) == 1)) {
				
					transform->position.x = mouse_col * 108 + 54;
					transform->position.y = mouse_row * 68;
			}
			else if ( ((mouse_col == chi_col +1) || (mouse_col == chi_col-1)) && (mouse_row == chi_row) ){
				if (mouse_row % 2 == 0) {
					transform->position.x = mouse_col * 108;
					transform->position.y = mouse_row * 68;
				}
				else {
					transform->position.x = mouse_col * 108 + 54;
					transform->position.y = mouse_row * 68;
				}
			}
			
			//get other player's position:
			
			//attack movement;
			//if (player_num == 1)
		}
	}
}; 

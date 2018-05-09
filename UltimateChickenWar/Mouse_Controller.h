#pragma once

#include "UCW.h"
#include "ECS.h"
#include "Component.h"
#include<vector>
using namespace std;
class Mouse_Controller : public Component {
public:
	TransformComponent * transform;
	TransformComponent * transform_opponent;
	//StatsComponent *stats;
	int chi_row, chi_col, player_num, opponent_row, opponent_col, opponent_num; //chicken position
	double dist[9][16];
	SDL_Rect positionRC[9][16];
	int mouse_x, mouse_y;
	Entity* opponent= NULL;

	Mouse_Controller(int index, Manager manager) {
		player_num = index;
		if (player_num == 1) {
			opponent = manager.getEntityList().at(1);
			opponent_num = 2;
		}
		else {
			opponent = manager.getEntityList().at(0);
			opponent_num == 1;
		}
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		//if (opponent->hasComponent<TransformComponent>()) cout <<"ok" << endl;
		transform_opponent = &opponent->getComponent<TransformComponent>();
		//get array of centroids of tiles
		for (int row = 0; row < 9; row++) {
			for (int column = 0; column < 16; column++) {
				positionRC[row][column] = transform->positionRC[row][column];
			}
		}
	}
	void update() override {
		static int turn = 0;
		transform->getPosition();
		transform_opponent->getPosition();
		//get other player's position:
		opponent_row = transform_opponent->posRow;
		opponent_col = transform_opponent->posCol;
		
		//Get position of chicken
		chi_row = transform->posRow;
		chi_col = transform->posCol;
		//check if mouse is down
		if (UCW::event.type == SDL_MOUSEBUTTONDOWN) {
			//cout << "chicken" << opponent_num << " row: " << opponent_row << "col: " << opponent_col << endl;
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
			//std::cout << "row: " << mouse_row << ", col: " << mouse_col << std::endl;
			
			//valid movement
			cout << "turn: " << turn << endl;
			TransformComponent* obj = NULL;
			//player to be moved
			int obj_row = 0; 
			int obj_col = 0;
			//player not moving
			int not_obj_row = 0;
			int not_obj_col = 0;

			if (player_num == 1) { //for player1
				if (turn % 2 == 0) {
					//even turn -> this player moves
					obj_row = chi_row;
					obj_col = chi_col;
					not_obj_row = opponent_row;
					not_obj_col = opponent_col;
					obj = transform;
				}
				else {
					//odd turn -> opponent player moves
					obj_row = opponent_row;
					obj_col = opponent_col;
					not_obj_col = chi_col;
					not_obj_row = chi_row;
					obj = transform_opponent;
				}
			}
			if (player_num == 2) {
				if (turn % 2 == 0) {
					//even turn -> opponent player moves
					obj_row = opponent_row;
					obj_col = opponent_col;
					not_obj_col = chi_col;
					not_obj_row = chi_row;
					obj = transform_opponent;
				}
				else {
					//odd turn -> this player moves
					obj_row = chi_row;
					obj_col = chi_col;
					not_obj_row = opponent_row;
					not_obj_col = opponent_col;
					obj = transform;
				}
			}
			std::cout << "not_obj_row: " << not_obj_row << ", not_obj_col: " << not_obj_col << std::endl;
			std::cout << "obj_row: " << obj_row << ", obj_col: " << obj_col << std::endl;
			std::cout << "row: " << mouse_row << ", col: " << mouse_col << std::endl;
			if (not_obj_col != mouse_col || not_obj_row != mouse_row) {
				if ((obj_row % 2 == 1) && ((mouse_col == obj_col) || (mouse_col == obj_col + 1)) && (abs(mouse_row - obj_row) == 1)) {

					obj->position.x = mouse_col * 108;
					obj->position.y = mouse_row * 68;
					turn += 1;

				}
				else if ((obj_row % 2 == 0) && ((mouse_col == chi_col) || (mouse_col == obj_col - 1)) && (abs(mouse_row - obj_row) == 1)) {

					obj->position.x = mouse_col * 108 + 54;
					obj->position.y = mouse_row * 68;
					turn += 1;

				}
				else if (((mouse_col == obj_col + 1) || (mouse_col == obj_col - 1)) && (mouse_row == obj_row)) {

					if (mouse_row % 2 == 0) {
						obj->position.x = mouse_col * 108;
						obj->position.y = mouse_row * 68;
						turn += 1;
					}
					else {
						obj->position.x = mouse_col * 108 + 54;
						obj->position.y = mouse_row * 68;
						turn += 1;
					}

				}
			}
			//valid attack
		}
	}
}; 

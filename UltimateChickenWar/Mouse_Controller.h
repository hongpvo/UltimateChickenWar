#pragma once

//#include "UCW.h"
#include "Player_system.h"
#include "Component.h"
#include "StatsComponent.h"
#include "Map.h"
#include<vector>
#include "vector2D.h"
#include "Popup.h"

using namespace std;
extern SDL_Rect position[9][16];
extern SDL_Rect center_position[9][16];
int* find_mouseRC(int, int);
void find_mouseCenter(int&, int &, int &, int &, int &, int &);
int player_x, player_y;

int player_row, player_col, player_range;
static bool first_time = true;

void Mouse_Controller(int map[9][16], int itemMap[9][16], Popup* attack) {
	here:
	Chicken* chicken[6];
	int mouse_x, mouse_y, mouse_row, mouse_col, mouse_center_y, mouse_center_x;
	static int iterator = 0;
	if (first_time) iterator = 0;
	static int turn;  //which player to move
	static Uint32 moveStart;
	static Uint32 moveTime;
	static bool gettime = true;
	
	if (gettime) {
		moveStart = SDL_GetTicks();
		gettime = false;
		
	}
	TransformComponent * transform_player;
	TransformComponent * transform_opponent[5];
	StatsComponent* stats_player;
	StatsComponent* stats_opponent[5];
	
	int opponent_row[5];
	int opponent_col[5];
	bool moving_allow = 0;
	
	turn = iterator % 6;
	cout << "turn: " << turn << endl;
	int j = 0;
	for (int i = 0; i < 6; i++) {
		chicken[i] = Player::allChickens[i];
		if (i == turn) {//for player
			transform_player = &chicken[i]->getComponent<TransformComponent>();
			stats_player = &chicken[i]->getComponent<StatsComponent>();
			stats_player->myturn = true;
			player_range = stats_player->range;
			transform_player->getPosition();
			player_row = transform_player->posRow;
			player_col = transform_player->posCol;
		}
		if (i != turn) {
			transform_opponent[j] = &chicken[i]->getComponent<TransformComponent>();
			stats_opponent[j] = &chicken[i]->getComponent<StatsComponent>();
			stats_opponent[j]->myturn =false;
			transform_opponent[j]->getPosition();
			opponent_row[j] = transform_opponent[j]->posRow;
			opponent_col[j] = transform_opponent[j]->posCol;
			j++;
		}
	}
	
	SDL_GetMouseState(&mouse_x, &mouse_y);
	find_mouseCenter(mouse_x, mouse_y, mouse_col, mouse_row, mouse_center_x, mouse_center_y);
	
	moveTime = SDL_GetTicks() - moveStart;
 	//turn-based algorithm
	if (moveTime > 500 || first_time) {
		first_time = false;
		if ((map[mouse_row][mouse_col] != 6 || map[mouse_row][mouse_col] != 7 || map[mouse_row][mouse_col] != 8 || map[mouse_row][mouse_col] != 9) || stats_player->choosing) {
			int count = 0;
			static int defender = 0;
			for (int i = 0; i <= 4; i++) {
				if ((opponent_col[i] != mouse_col || opponent_row[i] != mouse_row) && !(stats_player->choosing)) {
					count++;
				}
			}
			player_x = transform_player->position.x + 52;
			player_y = transform_player->position.y + 50;
			
			if (count == 5) moving_allow = true;
			if (moving_allow) {
				if (sqrt(pow(player_x - mouse_center_x, 2) + pow(player_y - mouse_center_y, 2)) <= 104*player_range) {
					if (mouse_row % 2 == 0) {
						transform_player->position.x = mouse_col * 104;
						transform_player->position.y = mouse_row * 68;
					}
					else {
						transform_player->position.x = mouse_col * 104 + 52;
						transform_player->position.y = mouse_row * 68;
					}
					if (itemMap[mouse_row][mouse_col] == 1) {
						stats_player->atk++;
						itemMap[mouse_row][mouse_col] = 0;
					}
					if (itemMap[mouse_row][mouse_col] == 2) {
						stats_player->def++;
						itemMap[mouse_row][mouse_col] = 0;
					}
					if (itemMap[mouse_row][mouse_col] == 3) {
						stats_player->hp++;
						itemMap[mouse_row][mouse_col] = 0;
					}
					while (1) {
						iterator++;
						turn = iterator % 6;
						if (chicken[turn]->getComponent<StatsComponent>().isAlive) {
							gettime = true;
							goto here;
						}
					}
				}
			}

			static bool hit = false;
			//count < 5 means mouse position = defender's position -->attack turn on
			for (int i = 0; i <= 4; i++) {
				if (mouse_col == opponent_col[i] && mouse_row == opponent_row[i]){
					defender = i;
					hit = true;
					
				}
			}
			static bool display = false;
			int defender_x = transform_opponent[defender]->position.x + 52;
			int defender_y = transform_opponent[defender]->position.y + 50;
			//check if close enough 
			if (hit && sqrt(pow(player_x - defender_x, 2) + pow(player_y - defender_y, 2)) <= 104*player_range) {
				stats_player->choosing = 1;
				if (mouse_x > 590 && mouse_x < 831 && mouse_y > 680 && mouse_y < 830) {
					//choosing attack
					if (stats_opponent[defender]->def > 0) {
						stats_opponent[defender]->def -= stats_player->atk;
						if (stats_opponent[defender]->def < 0) {
							stats_opponent[defender]->hp += stats_opponent[defender]->def;
							stats_opponent[defender]->def = 0;
						}
					}
						else if (stats_opponent[defender]->def == 0) stats_opponent[defender]->hp -= 1;
						if (stats_opponent[defender]->hp < 0) {
							stats_opponent[defender]->hp = 0;
						}
						stats_player->choosing = 0;
						if (stats_opponent[defender]->hp == 0) {
							stats_opponent[defender]->isAlive = 0;
							transform_opponent[defender]->position.x = 0;
							transform_opponent[defender]->position.y = 1500;
						}
						while (1) {
							iterator++;
							turn = iterator % 6;
							if (chicken[turn]->getComponent<StatsComponent>().isAlive) goto here;
						}
						hit = false;
				}
					else if (mouse_x > 952 && mouse_x < 1128 && mouse_y > 680 && mouse_y < 830) {
						stats_player->choosing = 0;
						hit = false;
					}
			}
		}
		gettime = true;
	}
		
}

int* find_mouseRC(int mouse_x, int mouse_y) {
	int mouse_row_col[2];
	double dist[9][16];
	int mouse_row = 0;
	int mouse_col = 0;
	//calculate distance from all the centroids
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			dist[row][column] = sqrt(pow(mouse_x - center_position[row][column].x, 2) + pow(mouse_y - center_position[row][column].y, 2));
			double a = dist[row][column];
		}
	}
	double min_dist = dist[0][0];
	//find the closet distance -> belong to that tile
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			if (dist[row][column] <= min_dist) {
				min_dist = dist[row][column];
				mouse_row = row;
				mouse_col = column;
			}
		}
	}
	mouse_row_col[0] = mouse_row;
	mouse_row_col[1] = mouse_col;
	return mouse_row_col;
}

void find_mouseCenter(int &mouse_x,int &mouse_y, int &mouse_col, int &mouse_row, int &mouse_center_x, int &mouse_center_y) {
	mouse_row = find_mouseRC(mouse_x, mouse_y)[0];
	mouse_col = find_mouseRC(mouse_x, mouse_y)[1];
	mouse_center_x = center_position[mouse_row][mouse_col].x ;
	mouse_center_y = center_position[mouse_row][mouse_col].y ;
}

//mouse_center_x = position[mouse_row][mouse_col].x + 52;
//mouse_center_y = position[mouse_row][mouse_col].y + 50;
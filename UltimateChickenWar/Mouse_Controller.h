#pragma once
#include "Player_system.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "Map.h"
#include<vector>
#include "vector2D.h"
#include "Popup.h"
using namespace std;
//these are variables defined in UCW.cpp. We want to use it without passing the reference into the function so we use extern keyword
extern SDL_Rect position[9][16];	
extern SDL_Rect center_position[9][16];
int* find_mouseRC(int, int);	//find which tile is the mouse staying in
void find_mouseCenter(int&, int &, int &, int &, int &, int &);		//find the center of the tiles that the mouse is staying in
int player_x, player_y;	//chicken position in pixels

int player_row, player_col, player_range;	//chicken position in row, column
static bool first_time = true;	//this is the first mouse click

void Mouse_Controller(int map[9][16], int itemMap[9][16], Popup* attack, bool &endgame) {
	here:
	Chicken* chicken[6];	//list of all 6 chickens
	int mouse_x, mouse_y, mouse_row, mouse_col, mouse_center_y, mouse_center_x;	//mouse coordinates in pixels, row,column and mouse_center
	static int iterator = 0;	//iterator will increase after a player make a move or attack
	//if (first_time) iterator = 0;
	if (endgame) {
		iterator = 0;
		endgame = false;
	}
	static int turn;  //which player to move
	static Uint32 moveStart;	//the mark of start counting time 
	static Uint32 moveTime;		//storing the time between 2 mouse clicks
	static bool gettime = true;		//start counting the time. 
	
	if (gettime) {
		moveStart = SDL_GetTicks();		//SDL_GetTicks return the time since the compiling time
		gettime = false;	//stop getting time
		
	}
	TransformComponent * transform_player = nullptr;	//transform component of the chicken having this turn
	TransformComponent * transform_opponent[5];	//transform component of the other 5 chickens
	StatsComponent* stats_player = nullptr;	//stats of the chicken having this turn
	StatsComponent* stats_opponent[5];	//stats of the other 5 chickens
	//position of other 5 chickens
	int opponent_row[5];	
	int opponent_col[5];
	bool moving_allow = 0;	//not allowed to move
	
	turn = iterator % 6;	//turn is calculated by taking the remainder of the division
	cout << "turn: " << turn << endl;
	int j = 0;
	for (int i = 0; i < 6; i++) {
		chicken[i] = Player::allChickens[i];	//get the list of all 6 chickens
		if (i == turn) {	//for player
			transform_player = chicken[i]->getComponent<TransformComponent>();
			stats_player = chicken[i]->getComponent<StatsComponent>();
			stats_player->myturn = true;	//set the turn of this chicken to be true
			player_range = stats_player->range;
			transform_player->getPosition();	//get the current position of the chicken
			player_row = transform_player->posRow;	//get the row coordinate
			player_col = transform_player->posCol;	//get the column coordinate
		}
		if (i != turn) {
			//do the same as abve
			transform_opponent[j] = chicken[i]->getComponent<TransformComponent>();	
			stats_opponent[j] = chicken[i]->getComponent<StatsComponent>();
			stats_opponent[j]->myturn =false;
			transform_opponent[j]->getPosition();
			opponent_row[j] = transform_opponent[j]->posRow;
			opponent_col[j] = transform_opponent[j]->posCol;
			j++;
		}
	}
	
	mouse_x = UCW::event.button.x;
	mouse_y = UCW::event.button.y;	//get the position of the  mouse (in pixels coordinates)
	//calculate the time between 2 mouse clicks
	moveTime = SDL_GetTicks() - moveStart;
	//find the center position of the tiles that the mouse is staying in
	find_mouseCenter(mouse_x, mouse_y, mouse_col, mouse_row, mouse_center_x, mouse_center_y);	
 	//turn-based algorithm
	//to prevent repeated mouse clicks
	if (moveTime > 500 || first_time) {		//if this is the first mouse click or the time between this mouse click and the last mouse click < 500ms
		//if mouse is not clicked on water
		if ((map[mouse_row][mouse_col] != 6 && map[mouse_row][mouse_col] != 7 && map[mouse_row][mouse_col] != 8 && map[mouse_row][mouse_col] != 9) || stats_player->choosing) {
			int count = 0;
			static int defender = 0;	//the index of the chicken being attacked
			//check if the mouse click is on any other 5 chickens
			for (int i = 0; i <= 4; i++) {
				if ((opponent_col[i] != mouse_col || opponent_row[i] != mouse_row) && !(stats_player->choosing)) {
					count++;
				}
			}
			//get the pixel position of the center of the tile that the chicken is in
			player_x = transform_player->position.x + 52;
			player_y = transform_player->position.y + 50;
			if (count == 5) moving_allow = true;	//moving is allowed if mouse click is not on any other chicken
			if (moving_allow) {
				first_time = false;		//next time will not be first time anymore
				//check if move is within the range of that chicken
				if (sqrt(pow(player_x - mouse_center_x, 2) + pow(player_y - mouse_center_y, 2)) <= 104*player_range) {
					//if mouse click is on even row
					if (mouse_row % 2 == 0) {
						transform_player->position.x = mouse_col * 104;
						transform_player->position.y = mouse_row * 68;
					}
					//if mouse click is on odd row
					else {
						transform_player->position.x = mouse_col * 104 + 52;
						transform_player->position.y = mouse_row * 68;
					}
					//if a sword is staying on that tile
					if (itemMap[mouse_row][mouse_col] == 1) {
						stats_player->atk++;
						itemMap[mouse_row][mouse_col] = 0;
					}
					//if a shield is staying on that tile 
					if (itemMap[mouse_row][mouse_col] == 2) {
						stats_player->def++;
						itemMap[mouse_row][mouse_col] = 0;
					}
					//if a heaty is staying on that tile
					if (itemMap[mouse_row][mouse_col] == 3) {
						stats_player->hp++;
						itemMap[mouse_row][mouse_col] = 0;
					}
					//after finish moving
					while (1) {
						iterator++;		//increase the turn
						turn = iterator % 6;
						//check if the next player having the turn is alive or not
						if (chicken[turn]->getComponent<StatsComponent>()->isAlive) {
							gettime = true;		//if true then start counting mouse click time again
							goto here;	//go back to definition
						}
					}
				}
			}

			//Attacking handler
			static bool hit = false;	//this variable inidicate the chicken is attacking another chickens
			//count < 5 means mouse position = defender's position -->attack turn on
			for (int i = 0; i <= 4; i++) {
				if (mouse_col == opponent_col[i] && mouse_row == opponent_row[i]){	//if mouse click is on other chickens
					defender = i;	//get the index if chicken being attacked (we call the attacked chicken is "defender")
					hit = true;		//this chicken is attacking another chicken
					first_time = false;		//next time will not be first time anymore
				}
			}
			//get the center position of the defender
			int defender_x = transform_opponent[defender]->position.x + 52;	
			int defender_y = transform_opponent[defender]->position.y + 50;
			//check if attacking is within the range
			if (hit && sqrt(pow(player_x - defender_x, 2) + pow(player_y - defender_y, 2)) <= 104*player_range) {
				stats_player->choosing = 1;	//now, the attack popup will display, meaning the chicken is choosing the options
				if (mouse_x > 590 && mouse_x < 831 && mouse_y > 680 && mouse_y < 830) {	//if the mouse is clicked on the "attack" option
					cout << "click attack" << endl;
					if (stats_opponent[defender]->def > 0) {	//if defender's def stats is > 0
						stats_opponent[defender]->def -= stats_player->atk;	//subtract the defender's def by the attacker's atk
						if (stats_opponent[defender]->def < 0) {	//else if the above subtraction result in the defender's def < 0
							stats_opponent[defender]->hp += stats_opponent[defender]->def;	//start subtracting the defender's hp
							stats_opponent[defender]->def = 0;	//return the defender's def back to 0
						}
					}
					//if defender's def = 0
					else if (stats_opponent[defender]->def == 0) stats_opponent[defender]->hp -= stats_player->atk; //subtract right at the defender's hp
					if (stats_opponent[defender]->hp < 0) {	//if defender's hp <0
						stats_opponent[defender]->hp = 0;	//bring it back to 0
					}
					stats_player->choosing = 0;		//once choosing attack, we will bring "choosing" back to 0
					//check if defender has run out of hp	
					if (stats_opponent[defender]->hp == 0) {
						stats_opponent[defender]->isAlive = 0;	//then the defender is dead
						transform_opponent[defender]->position.x = 0;	//we then moved the defender out of the map
						transform_opponent[defender]->position.y = 1500;
					}
					//do the same as above: find the next alive player turn
					while (1) {
						iterator++;
						turn = iterator % 6;
						gettime = true;
						if (chicken[turn]->getComponent<StatsComponent>()->isAlive) goto here;
					}
					hit = false;	//since you have already attacked, "hit" is set back to false
				}
				//if you click "not" on attack popup
				else if (mouse_x > 952 && mouse_x < 1128 && mouse_y > 680 && mouse_y < 830) {
					stats_player->choosing = 0;	//you have already choosen, so we set "choosing" back to 0
					hit = false;	//you no longer attack other chickens, so we set it back to false
				}
			}
		}
		gettime = true;	//counting mouse click time again
	}
		
}

//puprpose: find the row, col that the mouse is in
int* find_mouseRC(int mouse_x, int mouse_y) {
	int mouse_row_col[2];
	double dist[9][16];	//distance from the mouse coordinates to the center of all the map tiles
	int mouse_row = 0;
	int mouse_col = 0;
	//calculate distance from all the centroids
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			dist[row][column] = sqrt(pow(mouse_x - center_position[row][column].x, 2) + pow(mouse_y - center_position[row][column].y, 2));	

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

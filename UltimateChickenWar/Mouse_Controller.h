#pragma once

//#include "UCW.h"
//#include "ECS.h"
#include "Component.h"
#include "StatsComponent.h"
#include "Map.h"
#include<vector>
#include "vector2D.h"

#include "Popup.h"
using namespace std;
extern SDL_Rect position[9][16];
int* find_mouseRC(int mouse_x, int mouse_y, SDL_Rect center_position[9][16]);

void Mouse_Controller(Manager* all_player_manager, SDL_Rect center_position[9][16], int map[9][16], Popup* attack) {
	here:
	Entity* player[6];
	static bool first_time = true;
	static int iterator = 0;
	static int turn;  //which player to move
	static Uint32 moveStart;
	static Uint32 moveTime;
	static bool gettime = true;
	//cout << "gettime: " << gettime << endl;
	if (gettime) {
		moveStart = SDL_GetTicks();
		gettime = false;
		
	}
	TransformComponent * transform_player;
	TransformComponent * transform_opponent[5];
	StatsComponent* stats_player;
	StatsComponent* stats_opponent[5];
	int player_row, player_col;
	int opponent_row[5];
	int opponent_col[5];
	bool moving_allow = 0;
	int mouse_x, mouse_y, mouse_row, mouse_col;
	turn = iterator % 6;
	int j = 0;
	for (int i = 0; i < 6; i++) {
		player[i] = all_player_manager->getEntityList().at(i);
		if (i == turn) {//for player
			transform_player = &player[i]->getComponent<TransformComponent>();
			stats_player = &player[i]->getComponent<StatsComponent>();
			stats_player->myturn = true;
			transform_player->getPosition();
			player_row = transform_player->posRow;
			player_col = transform_player->posCol;
		}
		if (i != turn) {
			transform_opponent[j] = &player[i]->getComponent<TransformComponent>();
			stats_opponent[j] = &player[i]->getComponent<StatsComponent>();
			stats_opponent[j]->myturn =false;
			transform_opponent[j]->getPosition();
			opponent_row[j] = transform_opponent[j]->posRow;
			opponent_col[j] = transform_opponent[j]->posCol;
			//cout << "opponent" << j << " col: " << opponent_col[j] << ", row: " << opponent_row[j] << endl;
			j++;
		}
	}
	SDL_GetMouseState(&mouse_x, &mouse_y);
	mouse_row = find_mouseRC(mouse_x, mouse_y, center_position)[0];
	mouse_col = find_mouseRC(mouse_x, mouse_y, center_position)[1];
	
	moveTime = SDL_GetTicks() - moveStart;
 	//turn-based algorithm
	if (moveTime > 500 || first_time) {
		first_time = false;
		if (map[mouse_row][mouse_col] != 5 || stats_player->choosing) {
			int count = 0;
			static int defender = 0;
			if (!(stats_player->isAlive)) {
				iterator += 1;
				goto here; 
			}
			for (int i = 0; i <= 4; i++) {
				if ((opponent_col[i] != mouse_col || opponent_row[i] != mouse_row) && !(stats_player->choosing)) {
					//cout << "opponent" << i << " col: " << opponent_col[i] << ", row: " << opponent_row[i] << endl;
					count++;
				}
			}
			//cout << "mouse_col " << mouse_col << " ,mouse row " << mouse_row << endl;
			int player_x = transform_player->position.x + 52;
			int player_y = transform_player->position.y + 50;
			
			if (count == 5) moving_allow = true;
			if (moving_allow) {
				cout << "turn moving: " << turn << endl;
				/*
				if ((player_row % 2 == 1) && ((mouse_col == player_col) || (mouse_col == player_col + 1)) && (abs(mouse_row - player_row) == 1)) {
					transform_player->position.x = mouse_col * 104;
					transform_player->position.y = mouse_row * 68;
					iterator += 1;
				}
				else if ((player_row % 2 == 0) && ((mouse_col == player_col) || (mouse_col == player_col - 1)) && (abs(mouse_row - player_row) == 1)) {
					transform_player->position.x = mouse_col * 104 + 52;
					transform_player->position.y = mouse_row * 68;					
					iterator += 1;
				}
				else if (((mouse_col == player_col + 1) || (mouse_col == player_col - 1)) && (mouse_row == player_row)) {
					if (mouse_row % 2 == 0) {
						transform_player->position.x = mouse_col * 104;
						transform_player->position.y = mouse_row * 68;
						iterator += 1;
					}
					else {
						transform_player->position.x = mouse_col * 104 + 52;
						transform_player->position.y = mouse_row * 68;
						iterator += 1;
					}
				}
				*/

				//render position of bounding box of mouse_col +52 = mouse_col_center
				int mouse_center_x = position[mouse_row][mouse_col].x + 52;
				int mouse_center_y = position[mouse_row][mouse_col].y + 50;
				if (sqrt(pow(player_x - mouse_center_x, 2) + pow(player_y - mouse_center_y, 2)) <= 104) {
					if (mouse_row % 2 == 0) {
						transform_player->position.x = mouse_col * 104;
						transform_player->position.y = mouse_row * 68;
					}
					else {
						transform_player->position.x = mouse_col * 104 + 52;
						transform_player->position.y = mouse_row * 68;
					}
					iterator += 1;
				}
				//moveTime = 0;
				//moveStart = 0;
			}


			
			static bool hit = false;
			//count < 5 means mouse position = defender's position -->attack turn on
			//if (count < 5 && moveTime > 500 && sqrt(pow(player_x - defender_x, 2) + pow(player_y - defender_y, 2)) <= 104){
			for (int i = 0; i <= 4; i++) {
				if (mouse_col == opponent_col[i] && mouse_row == opponent_row[i]){
					//cout << "called" << endl;
					defender = i;
					cout << "defender: " << defender << endl;
					hit = true;
					
				}
			}
			static bool display = false;
			int defender_x = transform_opponent[defender]->position.x + 52;
			int defender_y = transform_opponent[defender]->position.y + 50;
			//check if close enough 
			if (hit && sqrt(pow(player_x - defender_x, 2) + pow(player_y - defender_y, 2)) <= 104) {
				//cout << "2nd function called" << endl;
				//stats_player->attacking = 1;
				stats_player->choosing = 1;
				//display board -> only subtract health if choose attack option
				if (mouse_x > 590 && mouse_x < 831 && mouse_y > 680 && mouse_y < 830) {
					//while (stats_player->choosing) {
					//choosing attack
						//cout << "running" << endl;
						stats_opponent[defender]->hp -= 1;
						stats_player->choosing = 0;
						//stats_player->attacking = 0;
						iterator++;
						if (stats_opponent[defender]->hp == 0) {
							stats_opponent[defender]->isAlive = 0;
							transform_opponent[defender]->position.x = 0;
							transform_opponent[defender]->position.y = 1500;
							//stats_opponent[defender]->entity->destroy();
						}
						hit = false;
				}
					else if (mouse_x > 952 && mouse_x < 1128 && mouse_y > 680 && mouse_y < 830) {
						//stats_player->attacking = 0;
						stats_player->choosing = 0;
						hit = false;
					}
					//turn off option board;
					//display = false;
					//attack->clean();
			}
			//moveStart = 0;
				//hit = false;
		}
		//gettime = true;
		gettime = true;
	}
		
}
//}


int* find_mouseRC(int mouse_x, int mouse_y, SDL_Rect center_position[9][16]) {
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

/*
class Mouse_Controller : public Component {
public:
TransformComponent * transform;
TransformComponent * transform_opponent;
StatsComponent* player_stats;
StatsComponent* opponent_stats;
//StatsComponent *stats;
int chi_row, chi_col, player_num, opponent_row, opponent_col, opponent_num; //chicken position
double dist[9][16];
SDL_Rect positionRC[9][16];
int mouse_x, mouse_y;
Entity* opponent = NULL;

Mouse_Controller(int index, Manager manager) {
player_num = index;
if (player_num == 1) {
opponent = manager.getEntityList().at(1);
opponent_num = 2;
}
else {
opponent = manager.getEntityList().at(0);
opponent_num = 1;
}
}
//map for obstacle - input file later
int test[9][16] =
{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,
2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,
5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,
5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,
5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0
};




void init() override {
transform = &entity->getComponent<TransformComponent>();
transform_opponent = &opponent->getComponent<TransformComponent>();
player_stats = &entity->getComponent<StatsComponent>();
opponent_stats = &opponent->getComponent<StatsComponent>();
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
TransformComponent* obj_transform = NULL;
TransformComponent* not_obj_transform = NULL;
StatsComponent* obj_stats = NULL;
StatsComponent* not_obj_stats = NULL;
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
obj_transform = transform;
not_obj_transform = transform_opponent;
obj_stats = player_stats;
not_obj_stats = opponent_stats;
}
else {
//odd turn -> opponent player moves
obj_row = opponent_row;
obj_col = opponent_col;
not_obj_col = chi_col;
not_obj_row = chi_row;
obj_transform = transform_opponent;
not_obj_transform = transform;
obj_stats = opponent_stats;
not_obj_stats = player_stats;
}
}
if (player_num == 2) {
if (turn % 2 == 0) {
//even turn -> opponent player moves
obj_row = opponent_row;
obj_col = opponent_col;
not_obj_col = chi_col;
not_obj_row = chi_row;
obj_transform = transform_opponent;
not_obj_transform = transform;
obj_stats = opponent_stats;
not_obj_stats = player_stats;
}
else {
//odd turn -> this player moves
obj_row = chi_row;
obj_col = chi_col;
not_obj_row = opponent_row;
not_obj_col = opponent_col;
obj_transform = transform;
not_obj_transform = transform_opponent;
obj_stats = player_stats;
not_obj_stats = opponent_stats;
}
}

int obj_x = obj_transform->position.x + 52;
int obj_y = obj_transform->position.y + 50;
int not_obj_x = not_obj_transform->position.x + 52;
int not_obj_y = not_obj_transform->position.y + 50;
static Uint32 moveStart, moveTime;
//std::cout << "obj_row: " << obj_row << ", obj_col: " << obj_col << std::endl;
//std::cout << "row: " << mouse_row << ", col: " << mouse_col << std::endl;
if (test[mouse_row][mouse_col] != 5 || obj_stats->attacking) {
if (!(obj_stats->isAlive)) {
obj_transform->position.x = 0;
obj_transform->position.y = 1500;
turn += 1;
}
if ((not_obj_col != mouse_col || not_obj_row != mouse_row) && !(not_obj_stats->choosing || obj_stats->choosing)) {
if ((obj_row % 2 == 1) && ((mouse_col == obj_col) || (mouse_col == obj_col + 1)) && (abs(mouse_row - obj_row) == 1)) {
obj_transform->position.x = mouse_col * 104;
obj_transform->position.y = mouse_row * 68;
turn += 1;

}
else if ((obj_row % 2 == 0) && ((mouse_col == obj_col) || (mouse_col == obj_col - 1)) && (abs(mouse_row - obj_row) == 1)) {
obj_transform->position.x = mouse_col * 104 + 52;
obj_transform->position.y = mouse_row * 68;
turn += 1;

}
else if (((mouse_col == obj_col + 1) || (mouse_col == obj_col - 1)) && (mouse_row == obj_row)) {
if (mouse_row % 2 == 0) {
obj_transform->position.x = mouse_col * 104;
obj_transform->position.y = mouse_row * 68;
turn += 1;
}
else {
obj_transform->position.x = mouse_col * 104 + 52;
obj_transform->position.y = mouse_row * 68;
turn += 1;
}

}
moveTime = 0;
moveStart = 0;
moveStart = SDL_GetTicks();
}

moveTime = SDL_GetTicks() - moveStart;

if (not_obj_col == mouse_col && not_obj_row == mouse_row && moveTime > 500 && sqrt(pow(obj_x-not_obj_x,2) + pow(obj_y - not_obj_y, 2)) <= 104) {
obj_stats->attacking = 1;
obj_stats->choosing = 1;
}

if (obj_stats->attacking){

if (mouse_x > 590 && mouse_x < 831 && mouse_y > 680 && mouse_y < 830) {
cout << "running" << endl;
not_obj_stats->hp -= 1;
obj_stats->choosing = 0;
std::cout << "not_obj_row: " << not_obj_row << ", not_obj_col: " << not_obj_col << " ,hp: " << not_obj_stats->hp << std::endl;
//std::cout << "row: " << mouse_row << ", col: " << mouse_col << std::endl;
obj_stats->attacking = 0;
turn++;
if (not_obj_stats->hp == 0) {
not_obj_stats->isAlive = 0;
not_obj_stats->entity->destroy();
}
}
else if (mouse_x > 952 && mouse_x < 1128 && mouse_y > 680 && mouse_y < 830) {
obj_stats->attacking = 0;
obj_stats->choosing = 0;
}
moveStart = 0;
}
}
}
}
};
*/

	
		
			

			

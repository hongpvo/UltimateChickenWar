#pragma once

#include "Player_system.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

#include "StatsComponent.h"
#include "Vector2D.h"
#include <math.h>
extern SDL_Rect center_position[9][16];
class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;


	int height = 100;
	int width = 104;
	int scale = 1;
	int speed = 3;
	int posRow = 0;
	int posCol = 0;
	double gPosition[9][16];

	TransformComponent() {
		position.Zero();

	}
	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	TransformComponent(SDL_Rect in, int sc) {
		position.x = in.x;
		position.y = in.y;
		width = in.w;
		height = in.h;
		scale = sc;
		
	}

	void update() override {
		getPosition();
	}

	void getPosition() {
		//get distance
		int a = 52;
		int b = 50;
		for (int row = 0; row < 9; row++) {
			for (int column = 0; column < 16; column++) {
				gPosition[row][column] = sqrt((position.x+a - center_position[row][column].x)*(position.x+a - center_position[row][column].x) + (position.y+b - center_position[row][column].y)*(position.y+b - center_position[row][column].y));
			}
		}
		//find the closet distance
		double min = gPosition[0][0];
		int rowindex = 0;
		int columnindex = 0;
		for (int row = 0; row < 9; row++) {
			for (int column = 0; column < 16; column++) {
				if (gPosition[row][column] <= min) {
					min = gPosition[row][column];
					rowindex = row;
					columnindex = column;
				}
			}
		}
		posRow = rowindex;
		posCol = columnindex;
		//test
		//std::cout << "Row: " <<posRow<<std::endl;
		//std::cout << "Column: "<<posCol<<std::endl;
	}


};
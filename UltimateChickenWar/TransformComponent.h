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
	Vector2D position;	//store the position
	int height = 100;	//height of the chicken
	int width = 104;	//width of the chicken
	int scale = 1;		//scale		
	//coordinate in row, column
	int posRow = 0;		
	int posCol = 0;
	double gPosition[9][16];	//distance from the center of the chicken to the center of the tiles

	TransformComponent() {
		position.Zero();	//initialize with position with (0,0)
	}

	//overloading constructor
	TransformComponent(float x, float y, int h, int w, int sc) {
		//set the position,scale of the chicken according to the specified arguments
		position.x = x;	
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	//overloading constructor
	TransformComponent(SDL_Rect in, int sc) {
		//set the position of the chicken the same as the rectangle "in"
		position.x = in.x;
		position.y = in.y;
		width = in.w;
		height = in.h;
		scale = sc;
		
	}
	//overriding the base class method
	void update() override {
		getPosition();
	}

	void getPosition() {
		//get distance
		//a,b are center positions of each tile
		int a = 52;
		int b = 50;
		for (int row = 0; row < 9; row++) {
			for (int column = 0; column < 16; column++) {
				//calculating distance by square root of the sum of squared of coordinates of vector
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
	}
};
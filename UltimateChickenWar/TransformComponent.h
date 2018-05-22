#pragma once

#include "Component.h"
#include "Vector2D.h"
#include <math.h>

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	SDL_Rect positionRC[9][16];
	
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
		//define positionRC[9][16]
		for (int row = 0; row < 9; row++) {
			for (int column = 0; column < 16; column++) {
				positionRC[row][column].h = 100;
				positionRC[row][column].w = 104;
				if (row == 0) {
					positionRC[row][column].x = 52 + 104*column;
					positionRC[row][column].y = 50;
				}
				else if (row % 2 == 0) {
					positionRC[row][column].x = 52 + 104 * column ;
					positionRC[row][column].y = 50 + 68 * row;
				}
				else {
					positionRC[row][column].x = 104 + 104 * column;
					positionRC[row][column].y = 50 + 68 * row;
				}

			}
		}
	}

	void init() override {
		velocity.Zero();

	}

	void update() override {
		getPosition();

		//position.x += velocity.x*speed;
		//position.y += velocity.y*speed;
	}

	void getPosition() {
		//get distance
		int a = 52;
		int b = 50;
		for (int row = 0; row < 9; row++) {
			for (int column = 0; column < 16; column++) {
				gPosition[row][column] = sqrt((position.x+a - positionRC[row][column].x)*(position.x+a - positionRC[row][column].x) + (position.y+b - positionRC[row][column].y)*(position.y+b - positionRC[row][column].y));
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
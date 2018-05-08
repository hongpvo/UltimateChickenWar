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
	int width = 108;
	int scale = 1;
	int speed = 3;
	int posRow = 0;
	int posCol = 0;
	double gPosition[9][16];

	TransformComponent() {
		position.Zero();

	}
	TransformComponent(int sc) {
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
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
				positionRC[row][column].w = 108;
				if (row % 2 == 0) {
					positionRC[row][column].x = (column * 108) / 2;
					positionRC[row][column].y = (row * 100 - 32 * row) / 2;
				}
				else {
					positionRC[row][column].x = (column * 108 + 54) / 2;
					positionRC[row][column].y = (row * 100 - 32 * row) / 2;
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
		for (int row = 0; row < 9; row++) {
			for (int column = 0; column < 16; column++) {
				gPosition[row][column] = sqrt((position.x - positionRC[row][column].x)*(position.x - positionRC[row][column].x) + (position.y - positionRC[row][column].y)*(position.y - positionRC[row][column].y));
			}
		}
		//find the closet distance
		double min = gPosition[0][0];
		int rowindex = 0;
		int columnindex = 0;
		for (int row = 0; row < 9; row++) {
			for (int column = 0; column < 16; column++) {
				if (gPosition[row][column] < min) {
					min = gPosition[row][column];
					rowindex = row;
					columnindex = column;
				}
			}
		}
		posRow = rowindex;
		posCol = columnindex;
		//test
		std::cout << "Row: " <<posRow<<std::endl;
		std::cout << "Column: "<<posCol<<std::endl;
	}


};
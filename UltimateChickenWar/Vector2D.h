#pragma once
#pragma once
#include <iostream>
//This class is use for declaring a vector 2D and calculating with vector 
class Vector2D {
public:
	//Two coordinate represents the vector
	float x;
	float y;

	//Default constructor 
	Vector2D();
	//Constructor which you can define the position of vector
	Vector2D(float x, float y);
	//Basic vector calculation 
	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);
	//operator overloading for basic calculation
	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);
	//operator overloading for basic calculation
	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator*(const int& i);
	//empty the vector
	Vector2D& Zero();
	//operator overloading for print the result to the screen
	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};
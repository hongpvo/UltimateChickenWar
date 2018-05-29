#include "Vector2D.h"

//Default constructor which set x,y value of a vector to be 0
Vector2D::Vector2D() {
	x = 0.0f;
	y = 0.0f;

}
//Constructor using for input the position of vector from beginning
Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}
//Define the way to add, subtract, multiply and divide 2 vector 2D
Vector2D& Vector2D::Add(const Vector2D& vec) {
	this->x += vec.x;
	this->y += vec.y;

	return *this;

}
Vector2D& Vector2D::Subtract(const Vector2D& vec) {
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}
Vector2D& Vector2D::Multiply(const Vector2D& vec) {
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}
Vector2D& Vector2D::Divide(const Vector2D& vec) {
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

//operator overloadding using previous calculation 
Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
	return v1.Add(v2);
}
Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
	return v1.Subtract(v2);
}
Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
	return v1.Multiply(v2);
}
Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
	return v1.Divide(v2);
}

//operator overloadding using previous calculation 
Vector2D& Vector2D::operator+=(const Vector2D& vec) {
	return this->Add(vec);
}
Vector2D& Vector2D::operator-=(const Vector2D& vec) {
	return this->Subtract(vec);
}
Vector2D& Vector2D::operator*=(const Vector2D& vec) {
	return this->Multiply(vec);
}
Vector2D& Vector2D::operator/=(const Vector2D& vec) {
	return this->Divide(vec);
}
Vector2D& Vector2D::operator*(const int& i) {
	this->x *= i;
	this->y *= i;

	return *this;
}
//Empty the vector by setting x = y = 0
Vector2D& Vector2D::Zero() {
	this->x = 0;
	this->y = 0;

	return *this;
}
//print to screen the coordinate of vector by overload operator of ostream <<
std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}
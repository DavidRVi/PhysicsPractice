#pragma once

namespace mvc {

// Implementation of a spatial point. A spatial point is a concept used to define an exact 
// location in space. It has no volume, area or length, making it a zero dimensional object.
// In this case the implementation considers a 3D Euclidean space.
class Point {
public:
	// Default constructor. Empty.
	Point();

	// Copy constructor.
	Point(const Point& p);

	// Constructor to set the Point coordinates, a for X, b for Y, c for Z axis.
	Point(float a, float b, float c);

	// Default destructor. Empty.
	~Point();

	// Operator overlading for cout
	friend std::ostream& operator << (std::ostream& os, Point& p);

	// Operator overlading for adding up two points
	friend Point operator+(Point lhs,Point rhs);

	// Operator overlading for substracting two points
	friend Point operator-(Point lhs,Point rhs);

	// Operator overlading for scaling a point by a factor, lhs
	friend Point operator*(Point lhs, float s);

	// Operator overlading for scaling a point by a factor, rhs
	friend Point operator*(float s, Point rhs);

	// Point coordinates on the X, Y, Z axis
	float x, y, z;
};

// Compute the dot product between two points
float Dot(Point a, Point b);

}
#pragma once

namespace mvc {

// Vector implementation, an object defined by both magnitude and direction
class Vector : public Point {
public:
	// Empty constructor
	Vector();

	// Constructor, create a vector from a point
	Vector(Point& p);

	// Constructor, create a vector from three scalars
	Vector( float a, float b, float c);

	// Empty destructor
	~Vector();

	// Normalize the vector
	void normalilze();

	// Retrieve Y axis rotation in degrees
	double getAngleY();
};

// Cross product between two vectors
Vector Cross(Vector a, Vector b);

}
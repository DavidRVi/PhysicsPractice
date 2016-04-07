#pragma once

namespace mvc {

// Implementation of a sphere, the set of all points in three-dimensional space
// which are at distance r from a fixed point of that space, where r is a positive 
// real number called the radius of the sphere.
class Sphere {
public:
	// Default constructor, sets the sphere centre and radius
	Sphere(Point& center, float radius);

	// Empty default destructor
	~Sphere();

	// Sphere center
    Point c;

	// Sphere radius
    float r;
};

}
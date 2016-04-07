#pragma once

namespace mvc {

// Implementation of a Plane, a two-dimensional manifold or surface that is perfectly flat.
class Plane {
public:
	// Empty default constructor
	Plane();

	// Construct a plane from a plane normal and a pont lying on the plane
	Plane(Vector& normal, Point& pointOnPlane);

	// Empty default destructor
	~Plane();

	// Scales the plane by scale factor
	void operator*=(float scale);

	// Plane normal. Points x on the plane satisfy Dot(n,x) = d
	Vector n;

	// d = dot(n,p) for a given point p on the plane
	float d;
};

}
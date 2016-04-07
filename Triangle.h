#pragma once

namespace mvc {

// Triangle implementation, a polygon with three corners or vertices and 
// three sides or edges which are line segments. In this implementation we
// store the triangle normal as well as those planes lying on edges BC and CA
class Triangle {
public:
	// Empty constructor
	Triangle();

	// Copy constructor
	Triangle(const Triangle& t);

	// Constructor, builds up the triangle data given the triangle vertices
	Triangle(Point& pa, Point& pb, Point& pc);

	// Empty destructor
	~Triangle();

	// Resets the triangle vertices given a new set
	void set(Point& pa, Point& pb, Point& pc);

	// First triangle vertex
	Point A;

	// Second triangle vertex
	Point B;

	// Third triangle vertex
	Point C;

	// Plane normal
	Vector normal;

	// Plane equation for triangle plane
	Plane p;

	// Barycentric weight u (for vertex A)
    Plane edgePlaneBC; 

	// Barycentric weight v (for vertex B)
    Plane edgePlaneCA;
};

}
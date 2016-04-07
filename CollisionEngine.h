#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "Point.h"
#include "Vector.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Utilities.h"

namespace mvc {

// CollisionManager is the class responsible for managing the entire collision system.
// It is possible to add triangles and spheres to the system to later perform 
// Sphere and line segment primitive tests against those primitives stored in the system.
class CollisionManager : public SingletonBase<CollisionManager> {
public:
	// Empty default constructor
	CollisionManager();

	// Empty default destructor
	~CollisionManager();

	// Add a triangle to the collision system
	void addTriangle(Triangle& tri);

	// Remove a triangle from the collision system
	void removeTriangle(Triangle& tri);

	// Add a sphere to the collision system
	void addSphere(Sphere& s);

	// Remove a sphere from the collision system
	void removeSphere(Sphere& s);

	// Tests a line segment against those triangles stored in the system
	bool testSegmentTriangleSoup(Point& p, Point& q, Point& s);

	// Tests an sphere against those triangles stored in the system
	bool testSphereTriangleSoup(Sphere& s, Point &p, Triangle& t);

	// Tests an sphere against those spheres stored in the system
	bool testSphereSphereSoup( Sphere& a, Sphere& r );

	// Triangle vector. Stores those triangles in the system.
	std::vector<Triangle*> triangleSoup;

	// Sphere vector. Stores those spheres in the system.
	std::vector<Sphere*> sphereSoup;

protected:
	// Given segment pq and precomputed triangle tri, returns whether segment intersects
	// triangle. If so, also returns the barycentric coordinates (u,v,w) of the
	// intersection point s, and the parameterized intersection t value
	bool IntersectSegmentTriangle(Point& p, Point& q, Triangle& tri, float &u, float &v, float &w, float &t, Point &s);

	// Finds the closest point to a triangle
	Point ClosestPtPointTriangle(Point p, Point a, Point b, Point c);

	// Returns true if sphere s intersects triangle ABC(tri vertices), false otherwise.
	// The point p on abc closest to the sphere center is also returned
	bool TestSphereTriangle(Sphere s, Triangle& t, Point &p, float &dist2 );

	// Performs a collision test between two spheres
	bool TestSphereSphere( Sphere a, Sphere b, float& dist2 );
};

}
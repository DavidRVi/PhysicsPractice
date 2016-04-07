#include "CollisionEngine.h"

namespace mvc {

Plane::Plane(void)
{
}

Plane::Plane(Vector& normal, Point& pointOnPlane) : 
n(normal), 
d(Dot(normal, pointOnPlane)){
}

Plane::~Plane(void){
}

// Scales the plane by scale factor
void Plane::operator*=(float scale){
	n.x *= scale;
	n.y *= scale;
	n.z *= scale;
	d*=scale;
}

}

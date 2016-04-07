
#include <math.h>
#include "Vector3D.h"

Vector3D::Vector3D()  { }
Vector3D::~Vector3D() { }

Vector3D::Vector3D(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

void Vector3D::Add(Vector3D v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}
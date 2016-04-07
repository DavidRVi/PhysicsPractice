#include "CollisionEngine.h"

namespace mvc {

Point::Point() {
}

Point::Point(const Point& p) { 
	x=p.x;
	y=p.y;
	z=p.z; 
}

Point::Point( float a, float b, float c) {	
	x=a;
	y=b;
	z=c; 
}

Point::~Point() {
}

Point operator+(Point lhs, Point rhs) {
	Point r(
		lhs.x+rhs.x,
		lhs.y+rhs.y,
		lhs.z+rhs.z);
	return r;
}

Point operator-(Point lhs, Point rhs) {
	return Point(
		lhs.x-rhs.x,
		lhs.y-rhs.y,
		lhs.z-rhs.z);
}

Point operator*(Point lhs, float s) {
	return Point(
		lhs.x*s,
		lhs.y*s,
		lhs.z*s);
}

Point operator*(float s,Point rhs) {
	return Point(
		s*rhs.x,
		s*rhs.y,
		s*rhs.z);
}

std::ostream& operator << (std::ostream& os, Point& p) {
	os << "X:";
	os << p.x;
	os << ", Y:";
	os << p.y;
	os << ", Z:";
	os << p.z;
	os << std::endl;
	return os;
}

float Dot(Point a, Point b){
	return (a.x*b.x+a.y*b.y+a.z*b.z);
}

}
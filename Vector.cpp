#include "CollisionEngine.h"
#include "Math.h"

#define PI			3.1415265359

namespace mvc {

Vector::Vector() : 
Point(){

}

Vector::Vector(Point& p) : 
Point(p){

}

Vector::Vector( float a, float b, float c) : 
Point(a,b,c){

}

Vector::~Vector(){

}

void Vector::normalilze(){
	float length = sqrt(x*x+y*y+z*z);
	x/=length;
	y/=length;
	z/=length;
}

double Vector::getAngleY(){
	if(x>0 && z>0)
		return acos(x)*180/PI;
	else if(x<0 && z>0)
		return acos(x)*180/PI;
	else if(x<0 && z<0)
		return 360-acos(x)*180/PI;

	return 360-acos(x)*180/PI;
}

Vector Cross(Vector a, Vector b){
	return Vector(
		a.y*b.z-a.z*b.y,
		a.z*b.x-a.x*b.z,
		a.x*b.y-a.y*b.x
		);
}


}
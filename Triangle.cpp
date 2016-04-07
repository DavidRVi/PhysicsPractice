#include "CollisionEngine.h"

namespace mvc {

Triangle::Triangle(){

}

Triangle::~Triangle(){

}


Triangle::Triangle(const Triangle& t){
	A=t.A;
	B=t.B;
	C=t.C;
	normal=t.normal;
	edgePlaneBC=t.edgePlaneBC;
	edgePlaneCA=t.edgePlaneCA;
	p=t.p;
}

Triangle::Triangle(Point& pa, Point& pb, Point& pc){
	set(pa, pb, pc);
}

void Triangle::set(Point& pa, Point& pb, Point& pc){
	A=pa;
	B=pb;
	C=pc;
	normal = Cross(B-A, C-A);
	normal.normalilze();
	p = Plane(normal, A);
	edgePlaneBC = Plane(Cross(normal, C-B),B);
	edgePlaneCA = Plane(Cross(normal, A-C),C);
	edgePlaneBC *= 1.0f/(Dot(A,edgePlaneBC.n)-edgePlaneBC.d);
	edgePlaneCA *= 1.0f/(Dot(B,edgePlaneCA.n)-edgePlaneCA.d);
}

}
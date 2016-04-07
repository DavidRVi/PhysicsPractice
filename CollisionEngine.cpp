#include "CollisionEngine.h"
#include <limits>

namespace mvc {

CollisionManager singletonCollisionManager;

CollisionManager::CollisionManager(){
}

CollisionManager::~CollisionManager(){
}

void CollisionManager::addTriangle(Triangle& tri){
	triangleSoup.push_back(&tri);
}

void CollisionManager::removeTriangle(Triangle& tri){
	removeElements(triangleSoup,&tri);
}

void CollisionManager::addSphere(Sphere& s){
	sphereSoup.push_back(&s);
}

void CollisionManager::removeSphere(Sphere& s){
	removeElements(sphereSoup,&s);
}

bool CollisionManager::testSegmentTriangleSoup(Point& p, Point& q, Point& s){
	float u,v,w,t;
	size_t size;
	float minDist = std::numeric_limits<float>::max();
	Point ip;

	// Check for the number of triangles in the system
	size = triangleSoup.size();

	// Iterate through all the triangles testing for segment intersection
	for (size_t i=0; i<size; ++i){
		if (IntersectSegmentTriangle(p, q, *triangleSoup[i], u, v, w, t, ip) ){
			if (t<minDist){
				s = ip;
				minDist = t;
			}
		}
	}

	// Return true if an intersection was found
	return (minDist!=std::numeric_limits<float>::max());
}

bool CollisionManager::testSphereTriangleSoup(Sphere& s, Point &p, Triangle& t){
	Point r;
	size_t size;
	float dist2;
	float minDist2 = std::numeric_limits<float>::max();

	// Check for the number of triangles in the system
	size = triangleSoup.size();

	// Iterate through all the triangles testing for sphere intersection
	for (size_t i=0; i<size; ++i){
		if (TestSphereTriangle(s, *triangleSoup[i], r, dist2) ){
			if (dist2<minDist2){
				// In case of intersection store the closest intersection data
				p=r;
				minDist2 = dist2;
				t=*triangleSoup[i];
			}
		}
	}

	// Return true if an intersection was found
	return (minDist2!=std::numeric_limits<float>::max());
}

bool CollisionManager::testSphereSphereSoup( Sphere& a, Sphere& r ){
	size_t size;
	float dist2;
	float minDist2 = std::numeric_limits<float>::max();

	// Check for the number of spheres in the system
	size = sphereSoup.size();

	// Iterate through all the spheres
	for (size_t i=0; i<size; ++i){
		if( &a!=sphereSoup[i] ){
			if (TestSphereSphere(a, *sphereSoup[i], dist2 )){
				if (dist2<minDist2){
					// In case of intersection store the closest intersection data
					r = *sphereSoup[i];
					minDist2 = dist2;
				}
			}
		}
	}

	// Return true if an intersection was found
	return (minDist2!=std::numeric_limits<float>::max());
}

bool CollisionManager::IntersectSegmentTriangle(Point& p, Point& q, Triangle& tri,
                             float &u, float &v, float &w, float &t, Point &s)
{
    // Compute distance of p to triangle plane. Exit if p lies behind plane
    float distp = Dot(p, tri.p.n) - tri.p.d;
    if (distp < 0.0f) return 0;

    // Compute distance of q to triangle plane. Exit if q lies in front of plane
    float distq = Dot(q, tri.p.n);
	distq -= tri.p.d;
    if (distq >= 0.0f) return 0;

    // Compute t value and point s of intersection with triangle plane
    float denom = distp - distq;
    t = distp / denom;
	s = p + t * (q - p);

    // Compute the barycentric coordinate u; exit if outside 0..1 range
    u = Dot(s, tri.edgePlaneBC.n) - tri.edgePlaneBC.d;
    if (u < 0.0f || u > 1.0f) return 0;

    // Compute the barycentric coordinate v; exit if negative
	v = Dot(s, tri.edgePlaneCA.n) - tri.edgePlaneCA.d;
    if (v < 0.0f) return 0;

    // Compute the barycentric coordinate w; exit if negative
	w = 1.0f - u - v;
    if (w < 0.0f) return 0;

    // Segment intersects tri at distance t in position s (s = u*A + v*B + w*C)
    return 1;
}

Point CollisionManager::ClosestPtPointTriangle(Point p, Point a, Point b, Point c)
{
    Vector ab = b - a;
    Vector ac = c - a;
    Vector bc = c - b;

    // Compute parametric position s for projection P' of P on AB,
    // P' = A + s*AB, s = snom/(snom+sdenom)
    float snom = Dot(p - a, ab), sdenom = Dot(p - b, a - b);

    // Compute parametric position t for projection P' of P on AC,
    // P' = A + t*AC, s = tnom/(tnom+tdenom)
    float tnom = Dot(p - a, ac), tdenom = Dot(p - c, a - c);

    if (snom <= 0.0f && tnom <= 0.0f) return a; // Vertex region early out

    // Compute parametric position u for projection P' of P on BC,
    // P' = B + u*BC, u = unom/(unom+udenom)
    float unom = Dot(p - b, bc), udenom = Dot(p - c, b - c);

    if (sdenom <= 0.0f && unom <= 0.0f) return b; // Vertex region early out
    if (tdenom <= 0.0f && udenom <= 0.0f) return c; // Vertex region early out


    // P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
    Vector n = Cross(b - a, c - a);
    float vc = Dot(n, Cross(a - p, b - p));
    // If P outside AB and within feature region of AB,
    // return projection of P onto AB
    if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
        return a + snom / (snom + sdenom) * ab;

    // P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
    float va = Dot(n, Cross(b - p, c - p));
    // If P outside BC and within feature region of BC,
    // return projection of P onto BC
    if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
        return b + unom / (unom + udenom) * bc;

    // P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
    float vb = Dot(n, Cross(c - p, a - p));
    // If P outside CA and within feature region of CA,
    // return projection of P onto CA
    if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
        return a + tnom / (tnom + tdenom) * ac;

    // P must project inside face region. Compute Q using barycentric coordinates
    float u = va / (va + vb + vc);
    float v = vb / (va + vb + vc);
    float w = 1.0f - u - v; // = vc / (va + vb + vc)
    return u * a + v * b + w * c;
}

bool CollisionManager::TestSphereTriangle(Sphere s, Triangle& t, Point &p, float &dist2 ){
	// early discard if the sphere is behind or far from the plane
	float distp = Dot(s.c, t.p.n) - t.p.d;
	if (distp < -s.r)
		return false;
	if (distp > s.r)
		return false;

	// Find point P on triangle ABC closest to sphere center
    p = ClosestPtPointTriangle(s.c, t.A, t.B, t.C);

    // Sphere and triangle intersect if the (squared) distance from sphere
    // center to point p is less than the (squared) sphere radius
    Vector v = p - s.c;
	dist2 = Dot(v, v);
    return dist2 <= s.r * s.r;
}

bool CollisionManager::TestSphereSphere( Sphere a, Sphere b, float& dist2 ){
	// Compute squared distance beween centers
	Vector d = a.c - b.c;
	dist2 = Dot(d,d);

	// Spheres intersect if squared distance is less than squared sum of radii
	float radiusSum=a.r+b.r;
	return dist2 <= radiusSum * radiusSum;
}

}
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "TDSMath.h"
#include "Ray.h"
#include "AABB.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "Line.h"

namespace TDS
{
class DLL_API Geometry
{
public:

    /*************************
    * STATIC COLLISION TESTS *
    *************************/
    // test aabb with aabb
    bool TestAABBAABB(const AABB& aabb1, const AABB& aabb2);
    
    // test sphere with plane
    bool TestSpherePlane(const Sphere& s, const Plane& p);
    // Determine whether sphere s is fully behind plane p
    bool InsideSpherePlane(const Sphere& s, const Plane& p);

    // test AABB with plane
    bool TestAABBPlane(const AABB&b, const Plane& p);

    // test Sphere with AABB
    bool TestSphereAABB(const Sphere&s, const AABB& b);
    // Return the point p on the AABB closest to the sphere center
    bool TestSphereAABB(const Sphere&s, const AABB& b, Vec3 &p);

    // test Triangle with AABB
    bool TestTriAABB(const Tri& tri, const AABB& b);

    // Test Triangle with Triangle
    bool TestTriTri(const Tri& V, const Tri& U);
    
    // tests sphere with sphere
    bool TestSphereSphere(const Sphere& sphere1, const Sphere& sphere2);
    
    // test ray with sphere
    bool IntersectRaySphere(const Ray& ray, const Sphere& sphere, float& tmin, Vec3& q);
    
    // test ray with aabb
    // return tmin and q
    bool IntersectRayAABB(const Ray& ray, const AABB& aabb, float& tmin, Vec3& q);
    
    // intersect segment ab with plane p, if intersected, return t and q
    bool IntersectSegmentPlane(const Vec3& a, const Vec3& b, const Plane& p, float& t, Vec3& q);

    // test if segment p0p1 intersects with aabb b
    bool IntersectSegmentAABB(const Vec3& p0, const Vec3& p1, const AABB& b);

    // given line pq and (ccw) triangle tri, return whether they intersect
    // if intersected, return barrycentric coordinates (intersectPt) of the intersection
    bool IntersectLineTriangle(const Vec3& p, const Vec3& q, const Tri& tri, Vec3& intersectPt);

    // Given ray and (ccw) triangle tri, return whether they intersect
    // if intersected, return barrycentric coordinates (intersectPt) of the intersection and t
    bool IntersectRayTriangle(const Ray& ray, const Tri& tri, Vec3& intersectPt, float& t);

    /**************************
    * DYNAMIC COLLISION TESTS *
    **************************/
    // intersect sphere s0 moving in dir over time interval [t0, t1], against a 
    // stationary sphere s1, if intersected, return time t of collision
    // s0 is the moving sphere, s1 is the stationary sphere
    bool IntersectMovingSphereSphere(const Sphere& s0, const Sphere& s1, const Vec3& dir, float t0, float t1, float& t);
    // both spheres are moving
    bool IntersectMovingSphereSphere(const Sphere& s0, const Sphere& s1, const Vec3& dir0, const Vec3& dir1, float &t);
    // intersect sphere s with movement vector dir with plane p
    // if intersected, return time t of collision and point q of collision of which sphere hits plane
    bool IntersectMovingSpherePlane(const Sphere& s, const Vec3& dir, const Plane& p, float& t, Vec3& q);
    // dynamic test of sphere with radius r moving from a to b, just testing intersection without calculating time of collision
    bool IntersectMovingSpherePlane(const Vec3& a, const Vec3& b, const Sphere& s, const Plane& p);
    
    // intersect sphere s moving in dir with AABB b, return time t of collision
    bool IntersectMovingSphereAABB(const Sphere& s, const Vec3& dir, const AABB& b, float &t); // to be implemented

    // intersect aabb a and b moving in dir va, vb, return tfirst and tlast
    bool IntersectMovingAABBAABB(const AABB& a, const Vec3& va, const AABB& b, const Vec3& vb, float& tfirst, float& tlast);

};

}
#endif // GEOMETRY_H
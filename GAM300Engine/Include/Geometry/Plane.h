#ifndef PLANE_H
#define PLANE_H

#include "dotnet/ImportExport.h"
namespace TDS
{
class DLL_API Plane
{
public:
    Plane();
    Plane(const Vec3& normal, float d);
    Plane(const Vec3& p1, const Vec3& p2, const Vec3& p3);
    ~Plane();

    //Given three noncollinear points (ordered ccw), compute plane equation
    Plane ComputePlane(Vec3 p1, Vec3 p2, Vec3 p3);
    Vec3 ClosestPointOnPlane(Vec3 point, Plane plane);
    float DistanceToPlane(Vec3 point, Plane plane);

    // Get the normal of the plane
    Vec3 getNormal() const { return n; }
    void setNormal(const Vec3& normal) { n = normal; }
    float getD() const { return d; }
	void setD(float newD) { d = newD; }

private:
    float d;
    Vec3 n; // normal of the plane. points x on the plane satisfy Dot(n,x) = d
};





} // namespace TDS

#endif // PLANE_H
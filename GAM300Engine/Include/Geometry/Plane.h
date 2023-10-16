#ifndef PLANE_H
#define PLANE_H

#include "dotnet/ImportExport.h"
namespace TDS
{
class Plane
{
public:
    DLL_API Plane();
    DLL_API  Plane(const Vec3& normal, float d);
    DLL_API Plane(const Vec3& p1, const Vec3& p2, const Vec3& p3);
    DLL_API  ~Plane();

    //Given three noncollinear points (ordered ccw), compute plane equation
    DLL_API  Plane ComputePlane(Vec3 p1, Vec3 p2, Vec3 p3);
    DLL_API Vec3 ClosestPointOnPlane(Vec3 point, Plane plane);
    DLL_API float DistanceToPlane(Vec3 point, Plane plane);

    // Get the normal of the plane
    DLL_API  Vec3 getNormal() const { return n; }
    DLL_API  void setNormal(const Vec3& normal) { n = normal; }
    DLL_API float getD() const { return d; }
    DLL_API void setD(float newD) { d = newD; }

private:
    float d;
    Vec3 n; // normal of the plane. points x on the plane satisfy Dot(n,x) = d
};





} // namespace TDS

#endif // PLANE_H
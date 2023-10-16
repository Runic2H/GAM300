#ifndef RAY_H
#define RAY_H

#include "dotnet/ImportExport.h"

namespace TDS
{
class Ray
{
public:
    DLL_API Ray();
    DLL_API  Ray(const Vec3& origin, const Vec3& direction);
    DLL_API  Ray(const Ray& ray);
    DLL_API  ~Ray();

    // Get the origin of the ray
    DLL_API Vec3 getOrigin() const { return m_origin; }

    // Get the direction of the ray
    DLL_API Vec3 getDirection() const { return m_direction; }

    // Get the point at distance t along the ray
    DLL_API Vec3 getPoint(float t) const { return m_origin + m_direction * t; }

    // Does the point lie along the ray?
    DLL_API  bool contains(const Vec3& point, float* t) const;
private:
    Vec3 m_origin;
    Vec3 m_direction;
};

} // namespace TDS

#endif // RAY_H
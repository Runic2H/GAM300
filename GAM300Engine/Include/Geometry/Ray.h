#ifndef RAY_H
#define RAY_H

#include "dotnet/ImportExport.h"

namespace TDS
{
class DLL_API Ray
{
public:
    Ray();
    Ray(const Vec3& origin, const Vec3& direction);
    Ray(const Ray& ray);
    ~Ray();

    // Get the origin of the ray
    Vec3 getOrigin() const { return m_origin; }

    // Get the direction of the ray
    Vec3 getDirection() const { return m_direction; }

    // Get the point at distance t along the ray
    Vec3 getPoint(float t) const { return m_origin + m_direction * t; }

    // Does the point lie along the ray?
    bool contains(const Vec3& point, float* t) const;
private:
    Vec3 m_origin;
    Vec3 m_direction;
};

} // namespace TDS

#endif // RAY_H
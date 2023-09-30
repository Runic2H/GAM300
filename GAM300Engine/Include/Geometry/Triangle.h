#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "TDSMath.h"
#include "dotnet/ImportExport.h"
namespace TDS
{
class DLL_API Tri
{
  public:
    Tri();
    Tri(const Vec3 &p1, const Vec3 &p2, const Vec3 &p3);
    ~Tri();

    // Get the point at index i
    Vec3 getPoint(int i) const
    {
        return p[i];
    }

    // Set the points
    void setPoints(const Vec3 &p1, const Vec3 &p2, const Vec3 &p3)
    {
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
    }

    // Returns true if the point is inside the triangle
    bool contains(const Vec3 &point) const;

    // Returns the point on the triangle closest to the given point
    Vec3 closestPointOnTri(const Vec3 &point) const;

    static bool TriEdgeEdgeTest(const Vec3& V0, const Vec3& U0, const Vec3& U1, const float Ax, const float Ay, const short i0, const short i1);
    static bool TriEdgeAgainstTriEdge(const Vec3 &tri1_pt1, const Vec3 &tri1_pt2, const Vec3 &tri2_pt1, const Vec3 &tri2_pt2,
                               const Vec3 &tri2_pt3, short i0, short i1);
    static bool TriPointInTri(const Vec3& V0, const Vec3& U0, const Vec3& U1, const Vec3& U2, const short i0, const short i1);
    static bool ComputeInterval(const float &VV0, const float &VV1, const float &VV2, const float &D0, const float &D1,
                         const float &D2, const float &D0D1, const float &D0D2, float &a, float &b, float &c, float &x0,
                         float &x1);
    static bool CoplanarTri(const Vec3 &N1, const Tri &tri1, const Tri &tri2);

  private:
    Vec3 p[3];
};

} // namespace TDS

#endif // TRIANGLE_H
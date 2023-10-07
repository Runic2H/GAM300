#ifndef SPHERE_H
#define SPHERE_H

#include "dotnet/ImportExport.h"

namespace TDS
{
class Sphere
{
public:
    DLL_API Sphere();
    DLL_API Sphere(const Vec3& center, float radius);
    DLL_API  ~Sphere();

    // Extend the sphere to include the given point
    DLL_API void extend(const Vec3& point);

    // Get the center of the sphere
    DLL_API Vec3 getCenter() const { return m_center; }

    // Get the radius of the sphere
    DLL_API float getRadius() const { return m_radius; }
    
    // Set the center of the sphere
    DLL_API void setCenter(const Vec3& center) { m_center = center; }

    // Set the radius of the sphere
    DLL_API void setRadius(float radius) { m_radius = radius; }

    // Returns true if the point is inside the sphere
    DLL_API  bool contains(const Vec3& point) const;

    // Return indices imin and imax of the least and most distant points
    DLL_API void ExtremePointsAlongDirection(const Vec3& dir, const Vec3* points, int numPoints, int *imin, int *imax);

    // Ritter Algorithm:
    // Compute indices to the two most separated points of the (up to) six points
    // defining the AABB encompassing the point set. Return these as min and max.
    DLL_API  void MostSeparatedPointsOnAABB(int& min, int& max, const Vec3* points, int numPoints);
    DLL_API void SphereFromDistantPoints(Sphere& s, const Vec3* points, int numPoints);
    DLL_API  void SphereOfSphereAndPt(Sphere& s, const Vec3& p);
    // Just call this function to get the sphere
    DLL_API void RitterSphere(Sphere& s, const Vec3* points, int numPoints);

    // PCA Algorithm:
    // Compute the variance of a set of 1D points (variance formula)
    DLL_API  float Variance(const float* x, int n);
    // Compute the covariance matrix of a set of 3D points
    DLL_API void CovarianceMatrix(Mat3& cov, const Vec3* points, int numPoints);
    // 2-by-2 Symmetric Schur Decomposition that will serve to form a Jacobi rotation matrix
    DLL_API  void SymSchur2(Mat3& A, int p, int q, float& c, float& s);
    // Jacobi iteration for the 3 by 3 symmetric matrix
    DLL_API void Jacobi(Mat3& a, Mat3& v);
    DLL_API  void EigenSphere(Sphere& eigSphere, const Vec3* points, int numPoints);
    // Call and hope this function works
    DLL_API  void RitterEigenSphere(Sphere& s, const Vec3* points, int numPoints);

private:
    Vec3 m_center;
    float m_radius;
};


} // namespace TDS


#endif // SPHERE_H
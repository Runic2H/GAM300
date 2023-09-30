#ifndef SPHERE_H
#define SPHERE_H

#include "dotnet/ImportExport.h"

namespace TDS
{
class DLL_API Sphere
{
public:
    Sphere();
    Sphere(const Vec3& center, float radius);
    ~Sphere();

    // Extend the sphere to include the given point
    void extend(const Vec3& point);

    // Get the center of the sphere
    Vec3 getCenter() const { return m_center; }

    // Get the radius of the sphere
    float getRadius() const { return m_radius; }
    
    // Set the center of the sphere
    void setCenter(const Vec3& center) { m_center = center; }

    // Set the radius of the sphere
    void setRadius(float radius) { m_radius = radius; }

    // Returns true if the point is inside the sphere
    bool contains(const Vec3& point) const;

    // Return indices imin and imax of the least and most distant points
    void ExtremePointsAlongDirection(const Vec3& dir, const Vec3* points, int numPoints, int *imin, int *imax);

    // Ritter Algorithm:
    // Compute indices to the two most separated points of the (up to) six points
    // defining the AABB encompassing the point set. Return these as min and max.
    void MostSeparatedPointsOnAABB(int& min, int& max, const Vec3* points, int numPoints);
    void SphereFromDistantPoints(Sphere& s, const Vec3* points, int numPoints);
    void SphereOfSphereAndPt(Sphere& s, const Vec3& p);
    // Just call this function to get the sphere
    void RitterSphere(Sphere& s, const Vec3* points, int numPoints);

    // PCA Algorithm:
    // Compute the variance of a set of 1D points (variance formula)
    float Variance(const float* x, int n);
    // Compute the covariance matrix of a set of 3D points
    void CovarianceMatrix(Mat3& cov, const Vec3* points, int numPoints);
    // 2-by-2 Symmetric Schur Decomposition that will serve to form a Jacobi rotation matrix
    void SymSchur2(Mat3& A, int p, int q, float& c, float& s);
    // Jacobi iteration for the 3 by 3 symmetric matrix
    void Jacobi(Mat3& a, Mat3& v);
    void EigenSphere(Sphere& eigSphere, const Vec3* points, int numPoints);
    // Call and hope this function works
    void RitterEigenSphere(Sphere& s, const Vec3* points, int numPoints);

private:
    Vec3 m_center;
    float m_radius;
};


} // namespace TDS


#endif // SPHERE_H
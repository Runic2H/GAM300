#ifndef AABB_H
#define AABB_H


#include "Ray.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	class AABB
	{
	public:
		DLL_API AABB();
		// Builds an AABB that encompasses a sphere
		DLL_API AABB(const Vec3& center, float radius);
		// Builds an AABB that contains the two given points
		DLL_API AABB(const Vec3& p1, const Vec3& p2);
		DLL_API AABB(const AABB& aabb);
		DLL_API ~AABB();

		// Set the AABB as NULL (not set)
		DLL_API void setNull() { m_min = Vec3(1.0); m_max = Vec3(-1.0); }

		// Return true if AABB is NULL (not set)
		DLL_API bool isNull() const { return m_min.x > m_max.x || m_min.y > m_max.y || m_min.z > m_max.z; }
		
		// Extend the bounding box on all sides by value
		DLL_API void extend(float value);
		
		// Expand the AABB to inlude point pt
		DLL_API void extend(const Vec3& pt);

		// Expand the AABB to inlude a sphere centered at pt with radius r
		DLL_API void extend(const Vec3& spherePt, float r);
		
		// Expand the AABB to encompass the given aabb
		DLL_API void extend(const AABB& aabb);
		
		// Expand the AABB to include a disk centered at center, with normal, and radius 
		DLL_API void extendDisk(const Vec3& center, const Vec3& normal, float radius);
		
		// Translate AABB by vector v
		DLL_API void translate(const Vec3& v);

		// Scale the AABB by scale, centered around origin
		DLL_API void scale(const Vec3& scale, const Vec3& origin);

		// Retrives the center of the AABB
		DLL_API Vec3 getCenter() const;
		
		// Retrives the diagonal vector (m_max - m_min)
		DLL_API Vec3 getDiagonal() const;

		// The total size of the AABB
		DLL_API Vec3 getSize() const;

		// The extent of the AABB (half the size of the AABB)
		DLL_API Vec3 getExtent() const;
		
		// Retrives the longest edge
		// If the AABB is NULL, then 0 is returned
		DLL_API float getLongestEdge() const;
		
		// Retrives the shortes edge
		// If the AABB is NULL, then 0 is return
		DLL_API float getShortestEdge() const;

		// Retrives the AABB's minimum point
		DLL_API Vec3 getMin() const { return m_min; }
		
		// Retrives the AABB's maximum point
		DLL_API Vec3 getMax() const { return m_max; }

		// Does point pt contain in AABB
		DLL_API bool contains(const Vec3& pt) const;
		
		// Given point p, return the point q on or in AABB closest to p
		DLL_API void ClosestPtPointAABB(const Vec3&p, AABB box, Vec3& q);

		// Computes the square distance between a point p and an AABB box
		DLL_API float SqrDistPointAABB(const Vec3& p, const AABB& box);

		inline void SetMinMax(const Vec3& min, const Vec3& max)
		{
			m_min = min;
			m_max = max;
		}
	private:
		Vec3 m_min; // minimum point
		Vec3 m_max; // maximum point
	};

}  // namespace TDS

#endif // AABB_H
#include "camera/SphereFrustum.h"

namespace TDS
{
	bool SphereFrustum::CullCheck(Vec3& pos)
	{
		if ((m_Planes[0].x * pos.x) + (m_Planes[0].y * pos.y) + (m_Planes[0].z * pos.z) + m_Planes[0].w <= -m_radius) return false;
		if ((m_Planes[1].x * pos.x) + (m_Planes[1].y * pos.y) + (m_Planes[1].z * pos.z) + m_Planes[1].w <= -m_radius) return false;
		if ((m_Planes[2].x * pos.x) + (m_Planes[2].y * pos.y) + (m_Planes[2].z * pos.z) + m_Planes[2].w <= -m_radius) return false;
		if ((m_Planes[3].x * pos.x) + (m_Planes[3].y * pos.y) + (m_Planes[3].z * pos.z) + m_Planes[3].w <= -m_radius) return false;
		if ((m_Planes[4].x * pos.x) + (m_Planes[4].y * pos.y) + (m_Planes[4].z * pos.z) + m_Planes[4].w <= -m_radius) return false;
		if ((m_Planes[5].x * pos.x) + (m_Planes[5].y * pos.y) + (m_Planes[5].z * pos.z) + m_Planes[5].w <= -m_radius) return false;

		return true;
	}
    void SphereFrustum::Update(Mat4& matrix) 
    {
        Vec4 leftPlane, rightPlane, topPlane, bottomPlane, backPlane, frontPlane;

        leftPlane.x = matrix.m[0][3] + matrix.m[0][0];
        leftPlane.y = matrix.m[1][3] + matrix.m[1][0];
        leftPlane.z = matrix.m[2][3] + matrix.m[2][0];
        leftPlane.w = matrix.m[3][3] + matrix.m[3][0];

        rightPlane.x = matrix.m[0][3] - matrix.m[0][0];
        rightPlane.y = matrix.m[1][3] - matrix.m[1][0];
        rightPlane.z = matrix.m[2][3] - matrix.m[2][0];
        rightPlane.w = matrix.m[3][3] - matrix.m[3][0];

        topPlane.x = matrix.m[0][3] - matrix.m[0][1];
        topPlane.y = matrix.m[1][3] - matrix.m[1][1];
        topPlane.z = matrix.m[2][3] - matrix.m[2][1];
        topPlane.w = matrix.m[3][3] - matrix.m[3][1];

        bottomPlane.x = matrix.m[0][3] + matrix.m[0][1];
        bottomPlane.y = matrix.m[1][3] + matrix.m[1][1];
        bottomPlane.z = matrix.m[2][3] + matrix.m[2][1];
        bottomPlane.w = matrix.m[3][3] + matrix.m[3][1];

        backPlane.x = matrix.m[0][3] + matrix.m[0][2];
        backPlane.y = matrix.m[1][3] + matrix.m[1][2];
        backPlane.z = matrix.m[2][3] + matrix.m[2][2];
        backPlane.w = matrix.m[3][3] + matrix.m[3][2];

        frontPlane.x = matrix.m[0][3] - matrix.m[0][2];
        frontPlane.y = matrix.m[1][3] - matrix.m[1][2];
        frontPlane.z = matrix.m[2][3] - matrix.m[2][2];
        frontPlane.w = matrix.m[3][3] - matrix.m[3][2];

        m_Planes[LEFT] = leftPlane.normalize();
        m_Planes[RIGHT] = rightPlane.normalize();
        m_Planes[TOP] = topPlane.normalize();
        m_Planes[BOTTOM] = bottomPlane.normalize();
        m_Planes[BACK] = backPlane.normalize();
        m_Planes[FRONT] = frontPlane.normalize();
    }

}
#pragma once
#include "pch.h"
#include "MathCommon.h"
namespace TDS
{


	struct SphereFrustum
	{
		enum FrustumSide
		{
			LEFT = 0,
			RIGHT,
			TOP,
			BOTTOM,
			BACK,
			FRONT,
			NUM_OF_SIDES = 6
		};
		std::array<Vec4, NUM_OF_SIDES> m_Planes;
		float						   m_radius = 10.f;
		
		bool						   CullCheck(Vec3& pos);
		void						   Update(Mat4& matrix);


	};
}
#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include "MathCommon.h"
namespace TDS
{
	struct Resource_Ref;

	struct Material
	{
		std::shared_ptr<Resource_Ref> m_ShaderResouceRef;
		Vec3 m_MateriaDiffuseColor = 1.f;
	};




}
#endif
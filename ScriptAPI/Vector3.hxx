#pragma once
#include "../Shared_Libs/Vector3.h"

namespace ScriptAPI
{
	public value class Vector3
	{
	public:
		property float X;
		property float Y;
		property float Z;

		Vector3(float valueX, float valueY, float valueZ);
		Vector3(TDS::Vec3 value);
	};
}
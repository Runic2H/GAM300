#pragma once
#include "../Shared_Libs/Quaternion.h"
#include "../Shared_Libs/Vector4.h"

namespace ScriptAPI
{
	public value class Vector4
	{
	public:
		property float X;
		property float Y;
		property float Z;
		property float W;

		Vector4(float valueX, float valueY, float valueZ, float valueW);
		Vector4(TDS::Vec4 value);
		Vector4(TDS::Quat value);
	};
}
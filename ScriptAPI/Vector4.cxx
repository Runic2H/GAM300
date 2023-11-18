#include "Vector4.hxx"

namespace ScriptAPI
{
	Vector4::Vector4(float valueX, float valueY, float valueZ, float valueW)
	{
		X = valueX;
		Y = valueY;
		Z = valueZ;
		W = valueW;
	}

	Vector4::Vector4(TDS::Vec4 value)
	{
		X = value.x;
		Y = value.y;
		Z = value.z;
		W = value.w;
	}

	Vector4::Vector4(TDS::Quat value)
	{
		X = value.x;
		Y = value.y;
		Z = value.z;
		W = value.w;
	}
}
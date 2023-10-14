#include "Vector3.hxx"

namespace ScriptAPI
{
	Vector3::Vector3(float valueX, float valueY, float valueZ)
	{
		X = valueX;
		Y = valueY;
		Z = valueZ;
	}

	Vector3::Vector3(TDS::Vec3 value)
	{
		X = value.x;
		Y = value.y;
		Z = value.z;
	}
}
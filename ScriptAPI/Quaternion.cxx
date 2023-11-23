#include "Quaternion.hxx"

namespace ScriptAPI
{
	Quaternion::Quaternion(float valueX, float valueY, float valueZ, float valueW)
	{
		X = valueX;
		Y = valueY;
		Z = valueZ;
		W = valueW;
	}
	Quaternion::Quaternion(float angle, Vector3 axis)
	{
		X = axis.X;
		Y = axis.Y;
		Z = axis.Z;
		W = angle;
	}
	Quaternion::Quaternion(Vector3 euler) // Quaternion.Euler
	{
		Vector3 c = Vector3(Mathf::Cos(euler.X * 0.5f), Mathf::Cos(euler.Y * 0.5f), Mathf::Cos(euler.Z * 0.5f));
		Vector3 s = Vector3(Mathf::Sin(euler.X * 0.5f), Mathf::Sin(euler.Y * 0.5f), Mathf::Sin(euler.Z * 0.5f));

		X = s.X * c.Y * c.Z - c.X * s.Y * s.Z;
		Y = c.X * s.Y * c.Z + s.X * c.Y * s.Z;
		Z = c.X * c.Y * s.Z - s.X * s.Y * c.Z;
		W = c.X * c.Y * c.Z + s.X * s.Y * s.Z;
	}
}
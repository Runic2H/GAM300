#include "Vector3.hxx"
#include "Mathf.hxx"

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

	Vector3 Vector3::operator+(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z);
	}

	Vector3 Vector3::operator-(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z);
	}

	Vector3 Vector3::operator*(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z);
	}

	Vector3 Vector3::operator*(Vector3 lhs, float rhs)
	{
		return Vector3(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs);
	}

	void Vector3::Normalize() {
		float mag = Mathf::Sqrt(X * X + Y * Y + Z * Z);
		if (mag > 0.0000000000000001)
		{
			X /= mag;
			Y /= mag;
			Z /= mag;
		}
		else
		{
			X = 0;
			Y = 0;
			Z = 0;
		}
	}

	Vector3 Vector3::normalise() {
		Vector3 v = Vector3(X, Y, Z);
		v.Normalize();
		return v;
	}
}
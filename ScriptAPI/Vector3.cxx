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

	float Vector3::Angle(Vector3 to, Vector3 from)
	{
		TDS::Vec3 toVec3 = TDS::floatsToVec3(to.X, to.Y, to.Z);
		TDS::Vec3 fromVec3 = TDS::floatsToVec3(from.X, from.Y, from.Z);

		float denominator = Mathf::Sqrt((fromVec3.x * fromVec3.x + fromVec3.y * fromVec3.y + fromVec3.z * fromVec3.z) * (toVec3.x * toVec3.x + toVec3.y * toVec3.y + toVec3.z * toVec3.z));
		if (denominator < 1e-15f)
			return 0.f;
		float dot = Mathf::Clamp((fromVec3.x * toVec3.x + fromVec3.y * toVec3.y + fromVec3.z * toVec3.z) / denominator, -1.f, 1.f);
		
		return Mathf::Acos(dot);
		//return TDS::Vec3::Angle(toVec3, fromVec3);
	}

	Vector3 Vector3::Cross(Vector3 to, Vector3 from)
	{
		float x = to.Y * from.Z - to.Z * from.Y;
		float y = to.Z * from.X - to.X * from.Z;
		float z = to.X * from.Y - to.Y * from.X;
		return Vector3(x, y, z);
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
	float Vector3::Dot(Vector3 lhs, Vector3 rhs)
	{
		return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
	}
}
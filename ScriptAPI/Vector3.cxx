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

	// Properties
	float Vector3::Magnitude()
	{
		TDS::Vec3 vector = TDS::floatsToVec3(X, Y, Z);
		return vector.magnitude();
	}
	Vector3 Vector3::Normalize()
	{
		TDS::Vec3 vector = TDS::floatsToVec3(X, Y, Z);
		vector.Normalize();
		return Vector3(vector);
	}
	float Vector3::SquaredMagnitude()
	{
		TDS::Vec3 vector = TDS::floatsToVec3(X, Y, Z);
		return vector.sqrMagnitude();
	}
	bool Vector3::Equals(Vector3 vector)
	{
		return X == vector.X && Y == vector.Y && Z == vector.Z;
	}
	void Vector3::Set(float newX, float newY, float newZ)
	{
		X = newX;
		Y = newY;
		Z = newZ;
	}

	// Static Properties
	Vector3 Vector3::Back()
	{
		return Vector3(TDS::Vec3::back());
	}
	Vector3 Vector3::Down()
	{
		return Vector3(TDS::Vec3::down());
	}
	Vector3 Vector3::Forward()
	{
		return Vector3(TDS::Vec3::forward());
	}
	Vector3 Vector3::Left()
	{
		return Vector3(TDS::Vec3::left());
	}
	Vector3 Vector3::One()
	{
		return Vector3(TDS::Vec3::one());
	}
	Vector3 Vector3::Right()
	{
		return Vector3(TDS::Vec3::right());
	}
	Vector3 Vector3::Up()
	{
		return Vector3(TDS::Vec3::up());
	}
	Vector3 Vector3::Zero()
	{
		return Vector3(TDS::Vec3::zero());
	}
	Vector3 Vector3::PositiveInfinity()
	{
		return Vector3(TDS::Vec3::positiveInfinity());
	}
	Vector3 Vector3::NegativeInfinity()
	{
		return Vector3(TDS::Vec3::negativeInfinity());
	}

	TDS::Vec3 Vector3::toVec3()
	{
		return TDS::floatsToVec3(X, Y, Z);
	}

	float Vector3::Angle(Vector3 from, Vector3 to)
	{
		return TDS::Vec3::Angle(from.toVec3(), to.toVec3());
	}
	Vector3 Vector3::ClampMagnitude(Vector3 vector, float maxLength)
	{
		return Vector3(TDS::Vec3::ClampMagnitude(vector.toVec3(), maxLength));
	}
	Vector3 Vector3::Cross(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(TDS::Vec3::Cross(lhs.toVec3(), rhs.toVec3()));
	}
	float Vector3::Distance(Vector3 a, Vector3 b)
	{
		return TDS::Vec3::Distance(a.toVec3(), b.toVec3());
	}
	float Vector3::Dot(Vector3 lhs, Vector3 rhs)
	{
		return TDS::Vec3::Dot(lhs.toVec3(), rhs.toVec3());
	}
	Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t)
	{
		return Vector3(TDS::Vec3::Lerp(a.toVec3(), b.toVec3(), t));
	}
	Vector3 Vector3::LerpUnclamped(Vector3 a, Vector3 b, float t)
	{
		return Vector3(TDS::Vec3::LerpUnclamped(a.toVec3(), b.toVec3(), t));
	}
	float Vector3::Magnitude(Vector3 vector)
	{
		return TDS::Vec3::Magnitude(vector.toVec3());
	}
	Vector3 Vector3::Max(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(TDS::Vec3::Max(lhs.toVec3(), rhs.toVec3()));
	}
	Vector3 Vector3::Min(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(TDS::Vec3::Min(lhs.toVec3(), rhs.toVec3()));
	}
	Vector3 Vector3::MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
	{
		return Vector3(TDS::Vec3::MoveTowards(current.toVec3(), target.toVec3(), maxDistanceDelta));
	}
	Vector3 Vector3::Normalize(Vector3 value)
	{
		return Vector3(TDS::Vec3::Normalize(value.toVec3()));
	}
	Vector3 Vector3::Orthogonal(Vector3 normal)
	{
		return Vector3(TDS::Vec3::Orthogonal(normal.toVec3()));
	}
	void Vector3::OrthoNormalize(Vector3& normal, Vector3& tangent, Vector3& binormal)
	{
		TDS::Vec3 normalVec3 = normal.toVec3();
		TDS::Vec3 tangentVec3 = tangent.toVec3();
		TDS::Vec3 binormalVec3 = binormal.toVec3();
		TDS::Vec3::OrthoNormalize(normalVec3, tangentVec3, binormalVec3);
		normal = Vector3(normalVec3);
		tangent = Vector3(tangentVec3);
		binormal = Vector3(binormalVec3);
	}
	Vector3 Vector3::Project(Vector3 vector, Vector3 onNormal)
	{
		return Vector3(TDS::Vec3::Project(vector.toVec3(), onNormal.toVec3()));
	}
	Vector3 Vector3::ProjectOnPlane(Vector3 vector, Vector3 planeNormal)
	{
		return Vector3(TDS::Vec3::ProjectOnPlane(vector.toVec3(), planeNormal.toVec3()));
	}
	Vector3 Vector3::Reflect(Vector3 inDirection, Vector3 inNormal)
	{
		return Vector3(TDS::Vec3::Reflect(inDirection.toVec3(), inNormal.toVec3()));
	}
	Vector3 Vector3::RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta)
	{
		return Vector3(TDS::Vec3::RotateTowards(current.toVec3(), target.toVec3(), maxRadiansDelta, maxMagnitudeDelta));
	}
	void Vector3::Scale(Vector3 scale)
	{
		TDS::Vec3 currentVec3 = toVec3();
		currentVec3.Scale(scale.toVec3());
		X = currentVec3.x;
		Y = currentVec3.y;
		Z = currentVec3.z;
	}
	Vector3 Vector3::Scale(Vector3 a, Vector3 b)
	{
		return Vector3(TDS::Vec3::Scale(a.toVec3(), b.toVec3()));
	}
	float Vector3::SignedAngle(Vector3 from, Vector3 to, Vector3 axis)
	{
		return TDS::Vec3::SignedAngle(from.toVec3(), to.toVec3(), axis.toVec3());
	}
	Vector3 Vector3::Slerp(Vector3 a, Vector3 b, float t)
	{
		return Vector3(TDS::Vec3::Slerp(a.toVec3(), b.toVec3(), t));
	}
	Vector3 Vector3::SlerpUnclamped(Vector3 a, Vector3 b, float t)
	{
		return Vector3(TDS::Vec3::SlerpUnclamped(a.toVec3(), b.toVec3(), t));
	}

	Vector3 Vector3::operator+(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z);
	}
	Vector3 Vector3::operator+(Vector3 vector, float scalar)
	{
		return Vector3(vector.X + scalar, vector.Y + scalar, vector.Z + scalar);
	}
	Vector3 Vector3::operator-(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z);
	}
	Vector3 Vector3::operator-(Vector3 vector, float scalar)
	{
		return Vector3(vector.X - scalar, vector.Y - scalar, vector.Z - scalar);
	}
	Vector3 Vector3::operator*(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z);
	}
	Vector3 Vector3::operator*(Vector3 vector, float scalar)
	{
		return Vector3(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
	}
	Vector3 Vector3::operator*(float scalar, Vector3 vector)
	{
		return Vector3(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
	}
	Vector3 Vector3::operator/(Vector3 vector, float scalar)
	{
		if (scalar == 0)
			return Vector3(vector.X, vector.Y, vector.Z);

		return Vector3(vector.X / scalar, vector.Y / scalar, vector.Z / scalar);
	}

	Vector3 Vector3::operator-(Vector3 vector)
	{
		return Vector3(-vector.X, -vector.Y, -vector.Z);
	}

	bool Vector3::operator==(Vector3 lhs, Vector3 rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
	}
	bool Vector3::operator!=(Vector3 lhs, Vector3 rhs)
	{
		return (lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z);
	}
}
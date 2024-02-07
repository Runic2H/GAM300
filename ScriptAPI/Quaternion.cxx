#include "Quaternion.hxx"
#include "Mathf.hxx"

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
		float radianX = euler.X * TDS::Mathf::Deg2Rad;
		float radianY = euler.Y * TDS::Mathf::Deg2Rad;
		float radianZ = euler.Z * TDS::Mathf::Deg2Rad;

		Vector3 c = Vector3(Mathf::Cos(euler.X * 0.5f), Mathf::Cos(euler.Y * 0.5f), Mathf::Cos(euler.Z * 0.5f));
		Vector3 s = Vector3(Mathf::Sin(euler.X * 0.5f), Mathf::Sin(euler.Y * 0.5f), Mathf::Sin(euler.Z * 0.5f));

		X = s.X * c.Y * c.Z - c.X * s.Y * s.Z;
		Y = c.X * s.Y * c.Z + s.X * c.Y * s.Z;
		Z = c.X * c.Y * s.Z - s.X * s.Y * c.Z;
		W = c.X * c.Y * c.Z + s.X * s.Y * s.Z;

	}
	//Quaternion::Quaternion(TDS::Quat value)
	//{
	//	X = value.x;
	//	Y = value.y;
	//	Z = value.z;
	//	W = value.w;
	//}
	TDS::Quat Quaternion::toQuat()
	{
		return TDS::floatsToQuat(X, Y, Z, W);
	}

	float Quaternion::Angle(Quaternion quat)
	{
		return TDS::Quat::angle(quat.toQuat());
	}
	Quaternion Quaternion::AngleAxis(float angle, float x, float y, float z)
	{
		TDS::Quat toReturn = TDS::Quat::angleAxis(angle, x, y, z);
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Quaternion Quaternion::AngleAxis(float angle, Vector3 axis)
	{
		TDS::Quat toReturn = TDS::Quat::angleAxis(angle, axis.X, axis.Y, axis.Z);
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Vector3 Quaternion::Axis(Quaternion quat)
	{
		return Vector3(TDS::Quat::axis(quat.toQuat()));
	}
	Quaternion Quaternion::Conjugate(Quaternion quat)
	{
		TDS::Quat toReturn = TDS::Quat::conjugate(quat.toQuat());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Quaternion Quaternion::Cross(Quaternion quat1, Quaternion quat2)
	{
		TDS::Quat toReturn = TDS::Quat::cross(quat1.toQuat(), quat2.toQuat());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	//Quaternion Quaternion::Cross(Quaternion quat, Vector3 vec)
	//{
	//	TDS::Quat toReturn = TDS::Quat::cross(quat.toQuat(), vec.toVec3());
	//	return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	//}
	//Quaternion Quaternion::Cross(Vector3 vec, Quaternion quat)
	//{
	//	TDS::Quat toReturn = TDS::Quat::cross(vec.toVec3(), quat.toQuat());
	//	return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	//}
	float Quaternion::Dot(Quaternion quat1, Quaternion quat2)
	{
		return TDS::Quat::dot(quat1.toQuat(), quat2.toQuat());
	}
	Vector3 Quaternion::EulerAngle(Quaternion quat)
	{
		return Vector3(TDS::Quat::eulerAngle(quat.toQuat()));
	}
	Quaternion Quaternion::Exponential(Quaternion quat)
	{
		TDS::Quat toReturn = TDS::Quat::exp(quat.toQuat());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	float Quaternion::ExtractRealComponent(Quaternion quat)
	{
		return TDS::Quat::extractRealComponent(quat.toQuat());
	}
	Quaternion Quaternion::FromTo(Vector3 from, Vector3 to)
	{
		TDS::Quat toReturn = TDS::Quat::fromTo(from.toVec3(), to.toVec3());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Quaternion Quaternion::Intermediate(Quaternion previous, Quaternion current, Quaternion next)
	{
		TDS::Quat toReturn = TDS::Quat::intermediate(previous.toQuat(), current.toQuat(), next.toQuat());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Quaternion Quaternion::Inverse(Quaternion quat)
	{
		TDS::Quat toReturn = TDS::Quat::inverse(quat.toQuat());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	float Quaternion::Length(Quaternion quat)
	{
		return TDS::Quat::length(quat.toQuat());
	}
	float Quaternion::LengthSquare(Quaternion quat)
	{
		return TDS::Quat::length2(quat.toQuat());
	}
	Quaternion Quaternion::Log(Quaternion quat)
	{
		TDS::Quat toReturn = TDS::Quat::log(quat.toQuat());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
		return Quaternion();
	}
	Quaternion Quaternion::LookRotation(Vector3 direction, Vector3 up)
	{
		TDS::Quat toReturn = TDS::Quat::lookRotation(direction.toVec3(), up.toVec3());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Quaternion Quaternion::Mix(Quaternion x, Quaternion y, float a)
	{
		TDS::Quat toReturn = TDS::Quat::mix(x.toQuat(), y.toQuat(), a);
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Quaternion Quaternion::NLerp(Quaternion from, Quaternion to, float t)
	{
		TDS::Quat toReturn = TDS::Quat::nlerp(from.toQuat(), to.toQuat(), t);
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Quaternion Quaternion::Normalize(Quaternion quat)
	{
		TDS::Quat toReturn = TDS::Quat::normalize(quat.toQuat());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	float Quaternion::Pitch(Quaternion quat)
	{
		return TDS::Quat::pitch(quat.toQuat());
	}
	Quaternion Quaternion::Pow(Quaternion quat, float exponent)
	{
		TDS::Quat toReturn = TDS::Quat::pow(quat.toQuat(), exponent);
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	float Quaternion::Roll(Quaternion quat)
	{
		return TDS::Quat::roll(quat.toQuat());
	}
	Vector3 Quaternion::Rotate(Quaternion quat, Vector3 v)
	{
		return Vector3(TDS::Quat::rotate(quat.toQuat(), v.toVec3()));
	}
	Vector4 Quaternion::Rotate(Quaternion quat, Vector4 v)
	{
		TDS::Vec4 toReturn = TDS::Quat::rotate(quat.toQuat(), v.toVec4());
		return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Quaternion Quaternion::Rotate(Quaternion quat, float angle, Vector3 axis)
	{
		TDS::Quat toReturn = TDS::Quat::rotate(quat.toQuat(), angle, axis.toVec3());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Quaternion Quaternion::Squad(Quaternion quat1, Quaternion quat2, Quaternion s1, Quaternion s2, float h)
	{
		TDS::Quat toReturn = TDS::Quat::squad(quat1.toQuat(), quat2.toQuat(), s1.toQuat(), s2.toQuat(), h);
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	float Quaternion::Yaw(Quaternion quat)
	{
		return TDS::Quat::yaw(quat.toQuat());
	}
	Quaternion Quaternion::Euler(Vector3 vector)
	{
		TDS::Quat toReturn = TDS::Quat::euler(vector.toVec3());
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}

	Quaternion Quaternion::operator-(Quaternion quat)
	{
		return Quaternion(-quat.X, -quat.Y, -quat.Z, -quat.W);
	}

	Quaternion Quaternion::operator+(Quaternion lhs, Quaternion rhs)
	{
		return Quaternion(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z, lhs.W + rhs.W);
	}

	Quaternion Quaternion::operator-(Quaternion lhs, Quaternion rhs)
	{
		return Quaternion(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z, lhs.W - rhs.W);
	}

	Quaternion Quaternion::operator*(Quaternion lhs, Quaternion rhs)
	{
		TDS::Quat toReturn = lhs.toQuat() * rhs.toQuat();
		return Quaternion(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Vector3 Quaternion::operator*(Quaternion quat, Vector3 vector)
	{
		TDS::Vec3 toReturn = quat.toQuat() * vector.toVec3();
		return Vector3(toReturn.x, toReturn.y, toReturn.z);
	}
	Vector4 Quaternion::operator*(Quaternion quat, Vector4 vector)
	{
		Vector3 toReturn = quat * Vector3(vector.X, vector.Y, vector.Z);
		return Vector4(toReturn.X, toReturn.Y, toReturn.Z, vector.W);
	}
	Vector4 Quaternion::operator*(Vector4 vector, Quaternion quat)
	{
		return Quaternion::Inverse(quat) * vector;
	}
	Quaternion Quaternion::operator*(Quaternion quat, float scalar)
	{
		return Quaternion(quat.X * scalar, quat.Y * scalar, quat.Z * scalar, quat.W * scalar);
	}
	Quaternion Quaternion::operator*(float scalar, Quaternion quat)
	{
		return Quaternion(quat.X * scalar, quat.Y * scalar, quat.Z * scalar, quat.W * scalar);
	}

	Quaternion Quaternion::operator/(Quaternion quat, float scalar)
	{
		if (scalar == 0)
			return quat;

		return Quaternion(quat.X / scalar, quat.Y / scalar, quat.Z / scalar, quat.W / scalar);
	}

	bool Quaternion::operator==(Quaternion lhs, Quaternion rhs)
	{
		return (lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z && lhs.W == rhs.W);
	}
	bool Quaternion::operator!=(Quaternion lhs, Quaternion rhs)
	{
		return (lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z || lhs.W != rhs.W);
	}
}
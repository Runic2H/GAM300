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

	TDS::Vec4 Vector4::toVec4()
	{
		return TDS::floatsToVec4(X, Y, Z, W);
	}
	
	bool Vector4::Equals(Vector4 v)
	{
		return X == v.X && Y == v.Y && Z == v.Z && W == v.W;
	}
	float Vector4::Magnitude()
	{
		TDS::Vec4 vector = TDS::floatsToVec4(X, Y, Z, W);
		return vector.magnitude();
	}
	Vector4 Vector4::Normalize()
	{
		TDS::Vec4 vector = TDS::floatsToVec4(X, Y, Z, W);
		vector.Normalize();
		return Vector4(vector.x, vector.y, vector.z, vector.w);
	}
	float Vector4::SquareMagnitude()
	{
		TDS::Vec4 vector = TDS::floatsToVec4(X, Y, Z, W);
		return vector.sqrMagnitude();
	}
	void Vector4::Set(float newX, float newY, float newZ, float newW)
	{
		X = newX;
		Y = newY;
		Z = newZ;
		W = newW;
	}

	Vector4 Vector4::One()
	{
		TDS::Vec4 toReturn = TDS::Vec4::one();
		return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Vector4 Vector4::Zero()
	{
		TDS::Vec4 toReturn = TDS::Vec4::zero();
		return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Vector4 Vector4::PositiveInfinity()
	{
		TDS::Vec4 toReturn = TDS::Vec4::positiveInfinity();
		return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}
	Vector4 Vector4::NegativeInfinity()
	{
		TDS::Vec4 toReturn = TDS::Vec4::negativeInfinity();
		return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	}

	//// Returns the distance between a and b.
	//float Vector4::Distance(Vector4 a, Vector4 b)
	//{
	//	return TDS::Vec4::Distance(a.toVec4(), b.toVec4());
	//}
	//// Dot Product of two vectors.
	//float Vector4::Dot(Vector4 lhs, Vector4 rhs)
	//{
	//	return TDS::Vec4::Dot(lhs.toVec4(), rhs.toVec4());
	//}
	//// Linearly interpolates between two vectors.
	//Vector4 Vector4::Lerp(Vector4 a, Vector4 b, float t)
	//{
	//	TDS::Vec4 toReturn = TDS::Vec4::Lerp(a.toVec4(), b.toVec4(), t);
	//	return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	//}
	//// Linearly interpolates between two without clamping the interpolant.
	//Vector4 Vector4::LerpUnclamped(Vector4 a, Vector4 b, float t)
	//{
	//	TDS::Vec4 toReturn = TDS::Vec4::LerpUnclamped(a.toVec4(), b.toVec4(), t);
	//	return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	//}
	//// Returns a vector that is made from the largest components of two vectors.
	//Vector4 Vector4::Max(Vector4 lhs, Vector4 rhs)
	//{
	//	TDS::Vec4 toReturn = TDS::Vec4::Max(lhs.toVec4(), rhs.toVec4());
	//	return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	//}
	//// Returns a vector that is made from the smallest components of two vectors.
	//Vector4 Vector4::Min(Vector4 lhs, Vector4 rhs)
	//{
	//	TDS::Vec4 toReturn = TDS::Vec4::Min(lhs.toVec4(), rhs.toVec4());
	//	return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	//}
	//// Moves a point current in a straight line towards a target point.
	//Vector4 Vector4::MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta)
	//{
	//	TDS::Vec4 toReturn = TDS::Vec4::MoveTowards(current.toVec4(), target.toVec4(), maxDistanceDelta);
	//	return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	//}
	//// Makes this vector have a magnitude of 1.
	//Vector4 Vector4::Normalize(Vector4 value)
	//{
	//	TDS::Vec4 toReturn = TDS::Vec4::Normalize(value.toVec4());
	//	return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	//}
	//// Projects a vector onto another vector.
	//Vector4 Vector4::Project(Vector4 vector, Vector4 onNormal)
	//{
	//	TDS::Vec4 toReturn = TDS::Vec4::Project(vector.toVec4(), onNormal.toVec4());
	//	return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	//}
	//// Multiplies two vectors component-wise.
	//Vector4 Vector4::Scale(Vector4 a, Vector4 b)
	//{
	//	TDS::Vec4 toReturn = TDS::Vec4::Project(a.toVec4(), b.toVec4());
	//	return Vector4(toReturn.x, toReturn.y, toReturn.z, toReturn.w);
	//}
	//// Multiplies every component of this vector by the same component of scale.
	//void Vector4::Scale(Vector4 scale)
	//{
	//	TDS::Vec4 currentVec4 = toVec4();
	//	currentVec4.Scale(scale.toVec4());
	//	X = currentVec4.x;
	//	Y = currentVec4.y;
	//	Z = currentVec4.z;
	//	W = currentVec4.w;
	//}
}
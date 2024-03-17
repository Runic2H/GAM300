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
		//Vector4(TDS::Vec4 value);
		//Vector4(TDS::Quat value);
		TDS::Vec4 toVec4();

		bool Equals(Vector4 v);
		float Magnitude();
		Vector4 Normalize();
		float SquareMagnitude();
		void Set(float newX, float newY, float newZ, float newW);

		static Vector4 One();
		static Vector4 Zero();
		static Vector4 PositiveInfinity();
		static Vector4 NegativeInfinity();

		//// Returns the distance between a and b.
		//static float Distance(Vector4 a, Vector4 b);
		//// Dot Product of two vectors.
		//static float Dot(Vector4 lhs, Vector4 rhs);
		// Linearly interpolates between two vectors.
		//static Vector4 Lerp(Vector4 a, Vector4 b, float t);
		//// Linearly interpolates between two without clamping the interpolant.
		//static Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);
		//// Returns a vector that is made from the largest components of two vectors.
		//static Vector4 Max(Vector4 lhs, Vector4 rhs);
		//// Returns a vector that is made from the smallest components of two vectors.
		//static Vector4 Min(Vector4 lhs, Vector4 rhs);
		//// Moves a point current in a straight line towards a target point.
		//static Vector4 MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta);
		//// Makes this vector have a magnitude of 1.
		//static Vector4 Normalize(Vector4 value);
		//// Projects a vector onto another vector.
		//static Vector4 Project(Vector4 vector, Vector4 onNormal);
		//// Multiplies two vectors component-wise.
		//static Vector4 Scale(Vector4 a, Vector4 b);
		//// Multiplies every component of this vector by the same component of scale.
		//void Scale(Vector4 scale);
	};
}
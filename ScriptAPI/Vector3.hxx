#pragma once
#include "../Shared_Libs/Vector3.h"

namespace ScriptAPI
{
	public value class Vector3
	{
	public:
		property float X;
		property float Y;
		property float Z;

		Vector3(float valueX, float valueY, float valueZ);
		Vector3(TDS::Vec3 value);
		TDS::Vec3 toVec3();

		// Properties
		float Magnitude();
		Vector3 Normalize();
		float SquaredMagnitude();
		bool Equals(Vector3 vector);
		void Set(float newX, float newY, float newZ);

		// Static Properties
		static Vector3 Back();
		static Vector3 Down();
		static Vector3 Forward();
		static Vector3 Left();
		static Vector3 One();
		static Vector3 Right();
		static Vector3 Up();
		static Vector3 Zero();
		static Vector3 PositiveInfinity();
		static Vector3 NegativeInfinity();

		static float Angle(Vector3 from, Vector3 to);
		static Vector3 ClampMagnitude(Vector3 vector, float maxLength);
		static Vector3 Cross(Vector3 lhs, Vector3 rhs);
		// Returns the distance between a and b.
		static float Distance(Vector3 a, Vector3 b);
		// Dot Product of two vectors.
		static float Dot(Vector3 lhs, Vector3 rhs);
		// Linearly interpolates between two vectors.
		static Vector3 Lerp(Vector3 a, Vector3 b, float t);
		// Linearly interpolates between two without clamping the interpolant.
		static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);
		// Magnitude of the vector.
		static float Magnitude(Vector3 vector);
		// Returns a vector that is made from the largest components of two vectors.
		static Vector3 Max(Vector3 lhs, Vector3 rhs);
		// Returns a vector that is made from the smallest components of two vectors.
		static Vector3 Min(Vector3 lhs, Vector3 rhs);
		// Moves a point cur`nt in a straight line towards a target point.
		static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta);
		// Makes this vector have a magnitude of 1.
		static Vector3 Normalize(Vector3 value);
		// Return an arbitrary orthogonal vector. This vector is not normalized.
		static Vector3 Orthogonal(Vector3 normal);
		// Makes vectors normalized and orthogonal to each other.
		static void OrthoNormalize(Vector3& normal, Vector3& tangent, Vector3& binormal);
		// Projects a vector onto another vector.
		static Vector3 Project(Vector3 vector, Vector3 onNormal);
		// Projects a vector onto a plane defined by a normal orthogonal to the plane.
		static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal);
		// Reflects a vector off the plane defined by a normal.
		static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal);
		// Rotates a vector current towards target.
		static Vector3 RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta);
		// Multiplies every component of this vector by the same component of scale.
		void Scale(Vector3 scale);
		// Multiplies two vectors component-wise.
		static Vector3 Scale(Vector3 a, Vector3 b);
		// Returns the signed angle in degrees between from and to.
		static float SignedAngle(Vector3 from, Vector3 to, Vector3 axis);
		// Spherically interpolates between two vectors.
		static Vector3 Slerp(Vector3 a, Vector3 b, float t);
		// Spherically interpolates between two vectors.
		static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t);

		static Vector3 operator+(Vector3 lhs, Vector3 rhs);
		static Vector3 operator+(Vector3 vector, float scalar);
		static Vector3 operator-(Vector3 lhs, Vector3 rhs);
		static Vector3 operator-(Vector3 vector, float scalar);
		static Vector3 operator*(Vector3 lhs, Vector3 rhs);
		static Vector3 operator*(Vector3 vector, float scalar);
		static Vector3 operator*(float scalar, Vector3 vector);
		static Vector3 operator/(Vector3 vector, float scalar);

		// Operators (unary arithmetic)
		static Vector3 operator-(Vector3 vector);

		static bool operator==(Vector3 lhs, Vector3 rhs);
		static bool operator!=(Vector3 lhs, Vector3 rhs);
	};
}

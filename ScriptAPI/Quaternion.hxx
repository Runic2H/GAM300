#pragma once
#include "../Shared_Libs/Quaternion.h"
#include "../Shared_Libs/Vector3.h"
#include "Mathf.hxx"
#include "Vector3.hxx"
#include "Vector4.hxx"

namespace ScriptAPI
{
	public value class Quaternion
	{
	public:
		property float X;
		property float Y;
		property float Z;
		property float W;

		Quaternion(float valueX, float valueY, float valueZ, float valueW);
		Quaternion(float angle, Vector3 axis);
		Quaternion(Vector3 euler);
		//Quaternion(TDS::Quat value);
		TDS::Quat toQuat();

		static float Angle(Quaternion quat);
		static Quaternion AngleAxis(float angle, float x, float y, float z);
		static Quaternion AngleAxis(float angle, Vector3 axis);
		static Vector3 Axis(Quaternion quat);
		static Quaternion Conjugate(Quaternion quat);
		static Quaternion Cross(Quaternion quat1, Quaternion quat2);
		//static Quaternion Cross(Quaternion quat, Vector3 vec);
		//static Quaternion Cross(Vector3 vec, Quaternion quat);

		static float Dot(Quaternion quat1, Quaternion quat2);
		static Vector3 EulerAngle(Quaternion quat);
		static Quaternion Exponential(Quaternion quat);
		static float ExtractRealComponent(Quaternion quat);
		static Quaternion FromTo(Vector3 from, Vector3 to);
		static Quaternion Intermediate(Quaternion previous, Quaternion current, Quaternion next);
		static Quaternion Inverse(Quaternion quat);
		static float Length(Quaternion quat);
		static float LengthSquare(Quaternion quat);
		static Quaternion Log(Quaternion quat);
		static Quaternion LookRotation(Vector3 direction, Vector3 to);
		static Quaternion Mix(Quaternion x, Quaternion y, float a);
		static Quaternion NLerp(Quaternion from, Quaternion to, float t);
		static Quaternion Normalize(Quaternion quat);
		static float Pitch(Quaternion quat);
		static Quaternion Pow(Quaternion quat, float exponent);
		static float Roll(Quaternion quat);
		static Vector3 Rotate(Quaternion quat, Vector3 vector);
		static Vector4 Rotate(Quaternion quat, Vector4 vector);
		static Quaternion Rotate(Quaternion quat, float angle, Vector3 axis);
		static Quaternion Squad(Quaternion quat1, Quaternion quat2, Quaternion s1, Quaternion s2, float h);
		static float Yaw(Quaternion quat);
		static Quaternion Euler(Vector3 vector);

		// Operators (unabry bit arithmetic)
		static Quaternion operator-(Quaternion quat);

		// Operators (binary arithmetic)
		static Quaternion operator+(Quaternion lhs, Quaternion rhs);
		static Quaternion operator-(Quaternion lhs, Quaternion rhs);
		static Quaternion operator*(Quaternion lhs, Quaternion rhs);
		static Vector3 operator*(Quaternion quat, Vector3 vector);
		static Vector4 operator*(Quaternion quat, Vector4 vector);
		static Vector4 operator*(Vector4 vector, Quaternion quat);
		static Quaternion operator*(Quaternion quat, float scalar);
		static Quaternion operator*(float scalar, Quaternion quat);
		static Quaternion operator/(Quaternion quat, float scalar);

		// boolean operator
		static bool operator==(Quaternion lhs, Quaternion rhs);
		static bool operator!=(Quaternion lhs, Quaternion rhs);
	};
}
#pragma once
#include "../Shared_Libs/Quaternion.h"
#include "../Shared_Libs/Vector3.h"
#include "Mathf.hxx"
#include "Vector3.hxx"

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

		static float Angle(Quaternion quat);
		static Quaternion AngleAxis(float angle, float x, float y, float z);
		static Quaternion AngleAxis(float angle, Vector3 axis);
		static Vector3 Axis(Quaternion quat);

		//static Quaternion Conjugate(Quaternion quat);
		//static Quaternion Cross(Quaternion quat1, Quaternion quat2);
		//static Quaternion Cross(Quaternion quat, Vector3 vec);
		//static Quaternion Cross(Vector3 vec, Quaternion quat);
		//static Quaternion Dot(Quaternion quat1, Quaternion quat2);

		//static Vector3 EulerAngle(Quaternion quat);
		//static Quaternion Exponential(Quaternion quat);
		//static float ExtractRealComponent(Quaternion quat);
		//static Quaternion FromTo(Vector3 vec1, Vector3 vec2);
		//static Quaternion Intermediate(Quaternion previous, Quaternion current, Quaternion next);
		//static Quaternion Inverse(Quaternion quat);
		//static float Length(Quaternion quat);
		//static float LengthSquare(Quaternion quat);
		//static Quaternion Log(Quaternion quat);
		//static Quaternion LookRotation(Vector3 vec1, Vector3 vec2);

		//static Quaternion Mix(Vector3 direction, Vector3 up);



		//static Quaternion AngleAxis(float angle, Vector3 axis);
	};
}
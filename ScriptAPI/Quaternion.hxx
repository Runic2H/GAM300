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

		static Quaternion AngleAxis(float angle, Vector3 axis);
	};
}
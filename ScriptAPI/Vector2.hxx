#pragma once
#include "../Shared_Libs/Vector2.h"

namespace ScriptAPI
{
	public value class Vector2
	{
	public:
		property float X;
		property float Y;

		Vector2(float valueX, float valueY);

		static float Distance(Vector2 lhs, Vector2 rhs);
		static Vector2 MoveTowards(Vector2 lhs, Vector2 rhs, float maxDistanceDelta);

		int operator==(Vector2 lhs);
	};
}
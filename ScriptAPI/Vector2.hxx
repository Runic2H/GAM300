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

		int operator==(Vector2 lhs);
	};
}
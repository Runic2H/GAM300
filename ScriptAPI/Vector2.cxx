#include "Vector2.hxx"

namespace ScriptAPI
{
	Vector2::Vector2(float valueX, float valueY)
	{
		X = valueX;
		Y = valueY;
	}
	int Vector2::operator==(Vector2 lhs)
	{
		return lhs.X == X && lhs.Y == Y;
	}
}
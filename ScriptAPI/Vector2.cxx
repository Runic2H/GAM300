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
	float Vector2::Distance(Vector2 lhs, Vector2 rhs)
	{
		return TDS::Vec2::Distance(TDS::floatsToVec2(lhs.X, lhs.Y), TDS::floatsToVec2(rhs.X, rhs.Y));
	}
	Vector2 Vector2::MoveTowards(Vector2 lhs, Vector2 rhs, float maxDistanceDelta)
	{
		TDS::Vec2 toReturn = TDS::Vec2::MoveTowards(TDS::floatsToVec2(lhs.X, lhs.Y), TDS::floatsToVec2(rhs.X, rhs.Y), maxDistanceDelta);
		return Vector2(toReturn.x, toReturn.y);
	}
}
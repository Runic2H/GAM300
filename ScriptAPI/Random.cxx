#include "Random.hxx"

namespace ScriptAPI
{
	float Random::Range(float min, float max)
	{
		return TDS::RandomNumber(min, max);
	}
}
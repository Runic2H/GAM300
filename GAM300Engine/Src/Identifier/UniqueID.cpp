#include "Identifier/UniqueID.h"
#include "Random/RandomGen.h"
namespace TDS
{

	std::uint32_t UniqueUID::m_IDGenerationCnt = 0;

	UniqueUID::UniqueUID()
	{
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::mt19937 randomEngine(seed);
		std::uniform_int_distribution<std::uint32_t> dist(0, UINT32_MAX);
		m_ID = dist(randomEngine);

		++m_IDGenerationCnt;

	}
	UniqueUID::UniqueUID(std::uint64_t id):m_ID(id)
	{
	}
	UniqueUID::UniqueUID(const UniqueUID& other):m_ID(other.m_ID)
	{
	}

	UniqueUID::~UniqueUID()
	{
	}

}

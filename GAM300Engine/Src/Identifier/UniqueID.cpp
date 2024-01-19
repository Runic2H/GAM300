#include "Identifier/UniqueID.h"
#include "Random/RandomGen.h"
namespace TDS
{

	std::uint32_t UniqueUID::m_IDGenerationCnt = 0;

	UniqueUID::UniqueUID()
	{
		std::mt19937 randomEngine;
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

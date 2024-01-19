#pragma once
#include <objbase.h>
#include <pch.h>
#include "Logger/Logger.h"
#include "HashID.h"
#include "dotnet/ImportExport.h"
namespace TDS
{

	class UniqueUID
	{
		private:
			std::uint64_t m_ID;
		public:
			DLL_API UniqueUID();
			DLL_API UniqueUID(std::uint64_t id);
			DLL_API UniqueUID(const UniqueUID& other);
			DLL_API ~UniqueUID();

			inline std::uint64_t GetID() const { return m_ID;}

			static std::uint32_t m_IDGenerationCnt;
	};



	

}

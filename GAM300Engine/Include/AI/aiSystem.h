#ifndef AI_SYSTEM
#define AI_SYSTEM

#include "components/components.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	class DLL_API AISystem
	{
	public:
		static void AISystemInit();
		static void AISystemUpdate(const float dt, const std::vector<EntityID>& entities, AI* _ai);
	};
}

#endif
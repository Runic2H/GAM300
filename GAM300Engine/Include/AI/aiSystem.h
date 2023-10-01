/*!*************************************************************************
****
\file aiSystems.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the aiSystem class
****************************************************************************
***/

#ifndef AI_SYSTEM
#define AI_SYSTEM

#include "components/components.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	class DLL_API AISystem
	{
	public:
		/*!*************************************************************************
		Initialization of the AISystem class (to bind in ECS)
		****************************************************************************/
		static void AISystemInit();
		/*!*************************************************************************
		Update of the AISystem class (to bind in ECS)
		****************************************************************************/
		static void AISystemUpdate(const float dt, const std::vector<EntityID>& entities, AI* _ai);
	};
}

#endif
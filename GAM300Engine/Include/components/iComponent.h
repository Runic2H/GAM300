/*!*************************************************************************
****
\file iComponent.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the iComponent abstract class
****************************************************************************
***/

#ifndef ICOMPONENTS
#define ICOMPONENTS

//#include "../GAM300Editor/Include/imguiHelper/ImguiHelper.h"
#include <string>

#include "sceneManager/serialization.h"

namespace TDS
{
	class IComponent : public Serializer
	{
	public:
		/*!*************************************************************************
		Destructor of the abstract IComponent class
		****************************************************************************/
		DLL_API virtual ~IComponent() = default;

		RTTR_ENABLE();
	};
}

#endif
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
	class DLL_API IComponent : public Serializer
	{
	public:
		/*!*************************************************************************
		Destructor of the abstract IComponent class
		****************************************************************************/
		virtual ~IComponent() = default;
		/*!*************************************************************************
		Deserialize function of the abstract IComponent class
		****************************************************************************/
		virtual bool Deserialize(const rapidjson::Value& obj) = 0;
		/*!*************************************************************************
		Serialize function of the abstract IComponent class
		****************************************************************************/
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const = 0;
	};
}

#endif
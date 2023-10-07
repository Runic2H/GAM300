/*!*************************************************************************
****
\file playerAttributes.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the playerAttributes 
		component class
****************************************************************************
***/

#ifndef PLAYERATTRIBUTESCOMPONENT
#define PLAYERATTRIBUTESCOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class PlayerAttributes : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the PlayerAttributes component when created
		****************************************************************************/
		DLL_API PlayerAttributes() { }
		/*!*************************************************************************
		Initializes the PlayerAttributes component when created, given another 
		PlayerAttributes component to move (for ECS)
		****************************************************************************/
		DLL_API PlayerAttributes(PlayerAttributes&& toMove) noexcept { toMove; }
		/*!*************************************************************************
		Destructor for the PlayerAttributes component class
		****************************************************************************/
		DLL_API ~PlayerAttributes() = default;
		/*!*************************************************************************
		Deserializes the PlayerAttributes component
		****************************************************************************/
		DLL_API virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes the PlayerAttributes component
		****************************************************************************/
		DLL_API virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

	private:
	};
}

#endif // PLAYERATTRIBUTESCOMPONENT
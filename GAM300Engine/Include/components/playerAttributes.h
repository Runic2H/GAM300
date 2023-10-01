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
	class DLL_API PlayerAttributes : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the PlayerAttributes component when created
		****************************************************************************/
		PlayerAttributes() { }
		/*!*************************************************************************
		Initializes the PlayerAttributes component when created, given another 
		PlayerAttributes component to move (for ECS)
		****************************************************************************/
		PlayerAttributes(PlayerAttributes&& toMove) noexcept { toMove; }
		/*!*************************************************************************
		Destructor for the PlayerAttributes component class
		****************************************************************************/
		~PlayerAttributes() = default;
		/*!*************************************************************************
		Deserializes the PlayerAttributes component
		****************************************************************************/
		virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes the PlayerAttributes component
		****************************************************************************/
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

	private:
	};
}

#endif // PLAYERATTRIBUTESCOMPONENT
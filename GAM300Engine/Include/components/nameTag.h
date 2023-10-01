/*!*************************************************************************
****
\file nameTag.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the nameTag component class
****************************************************************************
***/

#ifndef NAMETAGCOMPONENT
#define NAMETAGCOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class DLL_API NameTag : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the NameTag component when created
		****************************************************************************/
		NameTag();
		/*!*************************************************************************
		Initializes the NameTag component when created, given another NameTag
		component to move (for ECS)
		****************************************************************************/
		NameTag(NameTag&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the NameTag component class
		****************************************************************************/
		~NameTag() = default;
		/*!*************************************************************************
		Deserializes the NameTag component
		****************************************************************************/
		virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes the NameTag component
		****************************************************************************/
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Getter and setter functions for the variables in the NameTag component class
		****************************************************************************/
		std::string& GetNameTag() { return mName; }
		void SetNameTag(std::string name) { mName = name; }
		
	private:
		std::string mName;
	};
}

#endif // NAMETAGCOMPONENT
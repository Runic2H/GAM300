/*!*************************************************************************
****
\file tag.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the tag component class
****************************************************************************
***/

#ifndef TAGCOMPONENT
#define TAGCOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class Tag : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the Tag component when created
		****************************************************************************/
		DLL_API Tag();
		/*!*************************************************************************
		Initializes the Tag component when created, given another Tag component to
		move (for ECS)
		****************************************************************************/
		DLL_API Tag(Tag&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the Tag component class
		****************************************************************************/
		DLL_API ~Tag() = default;
		/*!*************************************************************************
		Deserializes the Tag component
		****************************************************************************/
		DLL_API virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes the Tag component
		****************************************************************************/
		DLL_API virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Getter and setter functions for the variables in the Tag component class
		****************************************************************************/
		DLL_API std::string GetTag() { return mTag; }
		DLL_API void SetTag(std::string tag) { mTag = tag; }

		DLL_API std::string GetTargetTag() { return mTargetTag; }
		DLL_API void SetTargetTag(std::string target) { mTargetTag = target; }

	private:
		std::string mTag;
		std::string mTargetTag;
	};
}

#endif // TAGCOMPONENT
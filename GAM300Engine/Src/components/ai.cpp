/*!*************************************************************************
****
\file ai.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the AI component class
****************************************************************************
***/

#include "components/ai.h"

namespace TDS
{
	/*!*************************************************************************
	Initializes the AI component when created
	****************************************************************************/
	AI::AI() : mBehaviourTreeIndex	(-1),
			   mEntityCurrentStatus	(NodeStatus::READY),
			   mCurrentNode			(nullptr)
	{ }

	/*!*************************************************************************
	Initializes the AI component when created, given another AI component to
	move (for ECS)
	****************************************************************************/
	AI::AI(AI&& toMove) noexcept : mBehaviourTreeIndex	(toMove.mBehaviourTreeIndex),
								   mEntityCurrentStatus	(toMove.mEntityCurrentStatus),
								   mCurrentNode			(toMove.mCurrentNode)
	{ }

	/*!*************************************************************************
	Deserializes the AI component
	****************************************************************************/
	bool AI::Deserialize(const rapidjson::Value& obj)
	{
		mBehaviourTreeIndex = obj["behaviourTreeIndex"].GetInt();

		return true;
	}

	/*!*************************************************************************
	Serializes the AI component
	****************************************************************************/
	bool AI::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("behaviourTreeIndex");
		writer->Int(mBehaviourTreeIndex);

		return true;
	}
}

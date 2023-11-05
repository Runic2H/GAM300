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

RTTR_REGISTRATION
{
	using namespace TDS;

	//rttr::registration::enumeration<NodeStatus>("NodeStatus")
	//(
	//	rttr::value("READY", NodeStatus::READY),
	//	rttr::value("RUNNING", NodeStatus::RUNNING),
	//	rttr::value("SUCCESS", NodeStatus::SUCCESS),
	//	rttr::value("FAILED", NodeStatus::FAILED)
	//);

	//rttr::registration::class_<Node>("Node")
	//	.property("parent", &Node::parent)
	//	.property("children", &Node::children)
	//	.property("childIndex", &Node::childIndex)
	//	.property("name", &Node::name);

rttr::registration::class_<AI>("AI");
		//.property("BehaviourTreeIndex", &AI::GetBehaviourTreeIndex, &AI::SetBehaviourTreeIndex)
		//.property("EntityCurrentStatus", &AI::GetEntityCurrentStatus, &AI::SetEntityCurrentStatus)
		//.property("CurrentNode", &AI::GetCurrentNode, &AI::SetCurrentNode)
		//.property("Timer", &AI::GetTimer, &AI::SetTimer);
}

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
}

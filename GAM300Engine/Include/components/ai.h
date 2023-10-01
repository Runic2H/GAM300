/*!*************************************************************************
****
\file ai.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the AI component class
****************************************************************************
***/

#ifndef AICOMPONENT
#define AICOMPONENT

#include "AI/behaviourTree.h"

namespace TDS
{
	class DLL_API AI : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the AI component when created
		****************************************************************************/
		AI();
		/*!*************************************************************************
		Initializes the AI component when created, given another AI component to
		move (for ECS)
		****************************************************************************/
		AI(AI&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the AI component class
		****************************************************************************/
		~AI() = default;
		/*!*************************************************************************
		Deserializes the AI component
		****************************************************************************/
		virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes the AI component
		****************************************************************************/
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Getter and setter functions for the variables in the AI component class
		****************************************************************************/
		int& GetBehaviourTreeIndex() { return mBehaviourTreeIndex; }
		void SetBehaviourTreeIndex(int behaviourTreeIndex) { mBehaviourTreeIndex = behaviourTreeIndex; }

		NodeStatus& GetEntityCurrentStatus() { return mEntityCurrentStatus; }
		void SetEntityCurrentStatus(NodeStatus entityCurrentStatus) { mEntityCurrentStatus = entityCurrentStatus; }

		std::shared_ptr<Node> GetCurrentNode() { return mCurrentNode; }
		void SetCurrentNode(std::shared_ptr<Node> currentNode) { mCurrentNode = currentNode; }
		
		float GetTimer() { return mTimer; }
		void SetTimer(float timer) { mTimer = timer; }

	private:
		int mBehaviourTreeIndex;
		NodeStatus mEntityCurrentStatus;
		std::shared_ptr<Node> mCurrentNode;
		float mTimer;
	};
}

#endif // AICOMPONENT
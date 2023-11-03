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
	class AI : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the AI component when created
		****************************************************************************/
		DLL_API AI();
		/*!*************************************************************************
		Initializes the AI component when created, given another AI component to
		move (for ECS)
		****************************************************************************/
		DLL_API AI(AI&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the AI component class
		****************************************************************************/
		DLL_API ~AI() = default;
		/*!*************************************************************************
		Getter and setter functions for the variables in the AI component class
		****************************************************************************/
		DLL_API int GetBehaviourTreeIndex() { return mBehaviourTreeIndex; }
		DLL_API void SetBehaviourTreeIndex(int behaviourTreeIndex) { mBehaviourTreeIndex = behaviourTreeIndex; }

		DLL_API NodeStatus GetEntityCurrentStatus() { return mEntityCurrentStatus; }
		DLL_API void SetEntityCurrentStatus(NodeStatus entityCurrentStatus) { mEntityCurrentStatus = entityCurrentStatus; }

		DLL_API std::shared_ptr<Node> GetCurrentNode() { return mCurrentNode; }
		DLL_API void SetCurrentNode(std::shared_ptr<Node> currentNode) { mCurrentNode = currentNode; }
		
		DLL_API float GetTimer() { return mTimer; }
		DLL_API void SetTimer(float timer) { mTimer = timer; }

		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	private:
		int mBehaviourTreeIndex;
		NodeStatus mEntityCurrentStatus;
		std::shared_ptr<Node> mCurrentNode;
		float mTimer;
	};
}

#endif // AICOMPONENT
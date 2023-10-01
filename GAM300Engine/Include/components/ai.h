#ifndef AICOMPONENT
#define AICOMPONENT

#include "AI/behaviourTree.h"

namespace TDS
{
	class DLL_API AI : public IComponent
	{
	public:
		AI();
		AI(AI&& toMove) noexcept;
		~AI() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

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
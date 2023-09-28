#include "components/ai.h"

namespace TDS
{
	AI::AI() : mBehaviourTreeIndex	(-1),
			   mEntityCurrentStatus	(NodeStatus::READY),
			   mCurrentNode			(nullptr)
	{ }

	AI::AI(AI&& toMove) noexcept : mBehaviourTreeIndex	(toMove.mBehaviourTreeIndex),
								   mEntityCurrentStatus	(toMove.mEntityCurrentStatus),
								   mCurrentNode			(toMove.mCurrentNode)
	{ }

	bool AI::Deserialize(const rapidjson::Value& obj)
	{
		mBehaviourTreeIndex = obj["behaviourTreeIndex"].GetInt();

		return true;
	}

	bool AI::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("behaviourTreeIndex");
		writer->Int(mBehaviourTreeIndex);

		return true;
	}

	void AI::ImGuiDisplay()
	{

	}
}

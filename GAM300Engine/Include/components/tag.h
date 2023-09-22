#ifndef TAGCOMPONENT
#define TAGCOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class Tag : public IComponent
	{
	public:
		Tag();
		~Tag() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		virtual void ImGuiDisplay();

		std::string GetTag() { return mTag; }
		void SetTag(std::string tag) { mTag = tag; }

		std::string GetTargetTag() { return mTargetTag; }
		void SetTargetTag(std::string target) { mTargetTag = target; }

	private:
		std::string mTag;
		std::string mTargetTag;
	};
}

#endif // TAGCOMPONENT
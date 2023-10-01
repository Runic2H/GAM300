#ifndef TAGCOMPONENT
#define TAGCOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class DLL_API Tag : public IComponent
	{
	public:
		Tag();
		Tag(Tag&& toMove) noexcept;
		~Tag() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

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
#ifndef NAMETAGCOMPONENT
#define NAMETAGCOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class NameTag : public IComponent
	{
	public:
		NameTag();
		~NameTag() = default;
		virtual bool Deserialize(const rapidjson::Value& obj) = 0;
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const = 0;

		virtual void ImGuiDisplay();

		std::string& GetNameTag() { return mName; }
		void SetNameTag(std::string name) { mName = name; }
		
	private:
		std::string mName;
	};
}

#endif // NAMETAGCOMPONENT
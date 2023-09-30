#ifndef NAMETAGCOMPONENT
#define NAMETAGCOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class DLL_API NameTag : public IComponent
	{
	public:
		NameTag();
		NameTag(NameTag&& toMove) noexcept;
		~NameTag() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		//NameTag& operator=(NameTag&& toMove) noexcept { return *this; };

		//virtual void ImGuiDisplay();

		std::string& GetNameTag() { return mName; }
		void SetNameTag(std::string name) { mName = name; }
		
	private:
		std::string mName;
	};
}

#endif // NAMETAGCOMPONENT
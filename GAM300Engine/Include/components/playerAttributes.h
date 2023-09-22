#ifndef PLAYERATTRIBUTESCOMPONENT
#define PLAYERATTRIBUTESCOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class PlayerAttributes : public IComponent
	{
	public:
		PlayerAttributes() { };
		~PlayerAttributes() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		virtual void ImGuiDisplay();

	private:
	};
}

#endif // PLAYERATTRIBUTESCOMPONENT
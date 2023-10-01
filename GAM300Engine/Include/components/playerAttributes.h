#ifndef PLAYERATTRIBUTESCOMPONENT
#define PLAYERATTRIBUTESCOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class DLL_API PlayerAttributes : public IComponent
	{
	public:
		PlayerAttributes() { }
		PlayerAttributes(PlayerAttributes&& toMove) noexcept { toMove; }
		~PlayerAttributes() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

	private:
	};
}

#endif // PLAYERATTRIBUTESCOMPONENT
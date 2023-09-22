#ifndef CAMERACOMPONENT
#define CAMERACOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class CameraComponent : public IComponent
	{
	public:
		CameraComponent();
		~CameraComponent() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		virtual void ImGuiDisplay();

	private:
	};
}

#endif // CAMERACOMPONENT
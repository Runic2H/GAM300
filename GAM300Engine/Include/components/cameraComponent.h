#ifndef CAMERACOMPONENT
#define CAMERACOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class DLL_API CameraComponent : public IComponent
	{
	public:
		CameraComponent();
		CameraComponent(CameraComponent&& toMove) noexcept;
		~CameraComponent() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		//CameraComponent& operator=(CameraComponent&& other) noexcept { return *this; };

		//virtual void ImGuiDisplay();

	private:
	};
}

#endif // CAMERACOMPONENT
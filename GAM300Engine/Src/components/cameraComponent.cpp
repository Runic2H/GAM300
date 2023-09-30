#include "components/cameraComponent.h"

namespace TDS {

	/*!*************************************************************************
	Constructor for camera component
	****************************************************************************/
	CameraComponent::CameraComponent()
	{ }

	CameraComponent::CameraComponent(CameraComponent&& toMove) noexcept
	{ }

	/*!*************************************************************************
	Derserialize camera component
	****************************************************************************/
	bool CameraComponent::Deserialize(const rapidjson::Value& obj)
	{
		//UNREFERENCED_PARAMETER(obj);
		return false;
	}

	/*!*************************************************************************
	Serialize camera component
	****************************************************************************/
	bool CameraComponent::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//UNREFERENCED_PARAMETER(writer);
		return false;
	}

	//void CameraComponent::ImGuiDisplay()
	//{

	//}
}
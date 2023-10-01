/*!*************************************************************************
****
\file cameraComponent.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines functions of cameraComponent class
****************************************************************************
***/

#include "components/cameraComponent.h"

namespace TDS 
{
	/*!*************************************************************************
	Initializes the CameraComponent when created
	****************************************************************************/
	CameraComponent::CameraComponent()
	{ }

	/*!*************************************************************************
	Initializes the CameraComponent when created, given another CameraComponent
	to move (for ECS)
	****************************************************************************/
	CameraComponent::CameraComponent(CameraComponent&& toMove) noexcept
	{ }

	/*!*************************************************************************
	Deserializes the CameraComponent
	****************************************************************************/
	bool CameraComponent::Deserialize(const rapidjson::Value& obj)
	{
		//UNREFERENCED_PARAMETER(obj);
		obj;
		return false;
	}

	/*!*************************************************************************
	Serializes the CameraComponent
	****************************************************************************/
	bool CameraComponent::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//UNREFERENCED_PARAMETER(writer);
		writer;
		return false;
	}
}
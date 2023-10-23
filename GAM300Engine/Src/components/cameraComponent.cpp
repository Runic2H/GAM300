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

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::class_<CameraComponent>("Camera Component");
}

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
	{
		(void)toMove;//TODO 
	}
}
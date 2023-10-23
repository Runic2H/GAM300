/*!*************************************************************************
****
\file cameraComponent.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the cameraComponent class
****************************************************************************
***/

#ifndef CAMERACOMPONENT
#define CAMERACOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class CameraComponent : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the CameraComponent when created
		****************************************************************************/
		DLL_API CameraComponent();
		/*!*************************************************************************
		Initializes the CameraComponent when created, given another CameraComponent 
		to move (for ECS)
		****************************************************************************/
		DLL_API CameraComponent(CameraComponent&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the CameraComponent class
		****************************************************************************/
		DLL_API ~CameraComponent() = default;

		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	private:
	};
}

#endif // CAMERACOMPONENT
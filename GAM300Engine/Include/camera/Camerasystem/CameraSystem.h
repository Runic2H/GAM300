/*!*************************************************************************
****
\file CameraSystem.h
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\date 10-11-2023
\brief  This program declares the functions in the CameraSystem class
****************************************************************************
***/

#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "ecs/ecs.h"
#include "components/transform.h"
#include "Logger/Logger.h"
#include "dotnet/ImportExport.h"
#include "components/cameraComponent.h"
#include "camera/camera.h"
#include "Input/Input.h"

namespace TDS 
{
	class DLL_API CameraSystem
	{
		public:
			/*!*************************************************************************
			Initializes the CameraSystem when created
			****************************************************************************/
			static void CameraSystemInit();

			/*!*************************************************************************
			Updates the CameraSystem based on keys and mouse position
			****************************************************************************/
			static void CameraSystemUpdate(const float dt, const std::vector<EntityID>& entities, 
										   Transform* _transform,CameraComponent* _cameracomponent);

			/*!*************************************************************************
			Gets mouse position
			****************************************************************************/
			static void GetMousePosition();

			/*!*************************************************************************
			Calculates the vectors 
			****************************************************************************/
			static void UpdateViewMatrixSystem(CameraComponent* _cameracomponent);

			static bool movingCameraSystem();

			static void ProcessMouseMovementSystem(float mousex, float mousey, CameraComponent* _cameracomponent);

			static void SetUpdate(bool input) { isUpdate = input; }
			static bool GetUpdate() { return isUpdate; }
		private:
			static Vec3 m_Front;
			static Vec3 m_Right;
			static Vec3 m_Up;
			static Vec3 m_Down;

			struct key
			{
				bool left{ false };
				bool right{ false };
				bool up{ false };
				bool down{ false };
			};
			inline static bool isUpdate = false;

	};
}

#endif // !CAMERASYSTEM_H
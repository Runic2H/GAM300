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
#include "Input/InputSystem.h"

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
			static void SetGameCamera(CameraComponent& _camera);

			/*!*************************************************************************
			Calculates the vectors 
			****************************************************************************/
			static bool movingCameraSystem();

			static void SetIsPlaying(bool input) { isPlaying = input; }
			static bool GetIsPlaying() { return isPlaying; }
		private:

			struct key
			{
				bool left{ false };
				bool right{ false };
				bool up{ false };
				bool down{ false };
			};
			inline static bool isPlaying = false;
			static TDSCamera* m_GameCamera;
			
	};
}

#endif // !CAMERASYSTEM_H
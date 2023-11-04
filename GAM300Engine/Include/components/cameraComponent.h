/*!*************************************************************************
****
\file cameraComponent.h
\author Go Ruo Yan, Matthew Cheung
\par DP email: ruoyan.go@digipen.edu, j.cheung@digipen.edu
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

		//DLL_API Mat4 GetViewMatrix() const;

		//DLL_API TDSCamera(float Yaw, float pitch, float zNear = 0.1f, float zFar = 10.f, Vec3 position = { 0.0f, 0.0f, 3.0f }, Vec3 up = { 0.0f, 1.0f, 0.0f });

		/*!*************************************************************************
		Initializes the CameraComponent when created, given another CameraComponent 
		to move (for ECS)
		****************************************************************************/
		DLL_API CameraComponent(CameraComponent&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the CameraComponent class
		****************************************************************************/
		DLL_API ~CameraComponent() = default;

		/*!*************************************************************************
		Getter functions
		****************************************************************************/
		DLL_API float getYaw() { return m_Yaw; }
		DLL_API float getPitch() { return m_Pitch; }
		DLL_API float getzNear() { return m_zNear; }
		DLL_API float getzFar() { return m_zFar; }
		DLL_API Vec3 getPosition() { return m_Position; }
		DLL_API float getSpeed() { return m_Speed; }
		DLL_API Vec3 getmWorldUp() { return m_WorldUp; }
		DLL_API Vec3 getmUp() { return m_Up; }

		DLL_API float getMouseSensitivity() { return m_mouseSensitivity; }
		DLL_API void getMouseSensitivity(float sensitivity) { m_mouseSensitivity = sensitivity; }

		/*!*************************************************************************
		Setter functions
		****************************************************************************/
		DLL_API void setYaw(float yaw) { m_Yaw = yaw; }
		DLL_API void setPitch(float pitch) { m_Pitch = pitch; }
		DLL_API void setzNear(float zNear) {  m_zNear = zNear; }
		DLL_API void setzFar(float zFar) { m_zFar = zFar; }
		DLL_API void setPosition(Vec3 position) { m_Position = position; }
		DLL_API void setSpeed(float speed) { m_Speed = speed; }
		DLL_API void setmWorldUp(Vec3 worldUp) { m_WorldUp = worldUp; }
	
		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND
				
	private:

		//camera attributes
		Vec3	m_Position;
		Vec3	m_Front;
		Vec3	m_Up;
		Vec3	m_Right;
		Vec3	m_Down;
		Vec3	m_WorldUp;

		//Mat4	m_ProjMatrix;
		//euler angles
		float	m_Yaw;
		float	m_Pitch;
		float	m_zNear;
		float	m_zFar;

		float	m_Speed;
		float	m_mouseSensitivity;
		void UpdateViewMatrix();

	};
		DLL_API CameraComponent* GetCameraComponent(EntityID entityID);
}

#endif // CAMERACOMPONENT
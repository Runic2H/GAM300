/*!*************************************************************************
****
\file cameraComponent.cpp
\author Go Ruo Yan, Matthew Cheung
\par DP email: ruoyan.go@digipen.edu, j.cheung@digipen.edu
\date 28-9-2023
\brief  This program defines functions of cameraComponent class
****************************************************************************
***/

#include "components/cameraComponent.h"

RTTR_REGISTRATION
{
	using namespace TDS;

rttr::registration::class_<CameraComponent>("Camera Component")
.method("GetYaw", &CameraComponent::getYaw)
.method("SetYaw", &CameraComponent::setYaw)
.property("Yaw", &CameraComponent::m_Yaw)
.method("GetPitch", &CameraComponent::getPitch)
.method("SetPitch", &CameraComponent::setPitch)
.property("Pitch", &CameraComponent::m_Pitch)
.method("GetzNear", &CameraComponent::getzNear)
.method("SetzNear", &CameraComponent::setzNear)
.property("zNear", &CameraComponent::m_zNear)
.method("GetzFar", &CameraComponent::getzFar)
.method("SetzFar", &CameraComponent::setzFar)
.property("zFar", &CameraComponent::m_zFar)
.method("GetPosition", &CameraComponent::getPosition)
.method("SetPosition", &CameraComponent::setPosition)
.property("Position", &CameraComponent::m_Position)
.method("GetSpeed", &CameraComponent::getSpeed)
.method("SetSpeed", &CameraComponent::setSpeed)
.property("Speed", &CameraComponent::m_Speed)
.method("GetmWorldUp", &CameraComponent::getmWorldUp)
.method("SetmWorldUp", &CameraComponent::setmWorldUp)
.property("mWorldUp", &CameraComponent::m_WorldUp)
.method("GetmUp", &CameraComponent::getmUp)
.property("mUp", &CameraComponent::m_Up);

}

namespace TDS 
{
	/*!*************************************************************************
	Initializes the CameraComponent when created
	****************************************************************************/
	CameraComponent::CameraComponent(): m_Up(Vec3 (0.f, 0.f, 1.f)),
										m_Position(Vec3 (0.f, 0.f, 0.f)),
										m_Front(Vec3(0.f, 0.f, 0.f)),
										m_Right(Vec3(0.f, 0.f, 0.f)),
										m_Down(Vec3(0.f, 0.f, 0.f)),
										m_WorldUp(Vec3(0.f, 0.f, 0.f)),
										m_Yaw(0.f),
										m_Pitch(0.f),
										m_zNear(0.f),
										m_zFar(0.f),
										m_Speed(1.0f),
										m_mouseSensitivity(0.1f)
										
	{ }

	//Mat4 CameraComponent::GetViewMatrix() const
	//{
	//	return Mat4::LookAt(m_Position, m_Position + m_Front, m_Up);
	//}

	/*!*************************************************************************
	Initializes the CameraComponent when created, given another CameraComponent
	to move (for ECS)
	****************************************************************************/
	CameraComponent::CameraComponent(CameraComponent&& toMove) noexcept : m_Up(toMove.m_Up),
																		  m_Position(toMove.m_Position),
																		  m_Front(toMove.m_Front),
																		  m_Right(toMove.m_Right),
																		  m_Down(toMove.m_Down),
																		  m_WorldUp(toMove.m_WorldUp),
																		  m_Yaw(toMove.m_Yaw),
																		  m_Pitch(toMove.m_Pitch),
																		  m_zNear(toMove.m_zNear),
																		  m_zFar(toMove.m_zFar),
																		  m_Speed(toMove.m_Speed),
																		  m_mouseSensitivity(toMove.m_mouseSensitivity)
	{}

	void CameraComponent::UpdateViewMatrix()
	{
			// calculate the new Front vector
			Vec3 front;
			front.x = Mathf::Cos(m_Yaw * Mathf::Deg2Rad) * Mathf::Cos(m_Pitch * Mathf::Deg2Rad);
			front.y = Mathf::Sin(m_Pitch * Mathf::Deg2Rad);
			front.z = Mathf::Sin(m_Yaw * Mathf::Deg2Rad) * Mathf::Cos(m_Pitch * Mathf::Deg2Rad);
			m_Front = Vec3::Normalize(front);
			// also re-calculate the Right and Up vector
			m_Right = Vec3::Normalize(Vec3::Cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			m_Up = Vec3::Normalize(Vec3::Cross(m_Right, m_Front));

			m_Down = -m_Up;
	}

	CameraComponent* GetCameraComponent(EntityID entityID)
	{
		return ecs.getComponent<CameraComponent>(entityID);
	}

}
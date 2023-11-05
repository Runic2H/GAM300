/*!*************************************************************************
****
\file CameraSystem.cpp
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\date  10-11-2023
\brief  This program defines functions of CameraSystem class
****************************************************************************
***/

#include "camera/Camerasystem/CameraSystem.h"
#include "Rendering/GraphicsManager.h"

namespace TDS 
{
	Vec3 CameraSystem::m_Front{};
	Vec3 CameraSystem::m_Right{};
	Vec3 CameraSystem::m_Up{ 0.f,0.f,1.f };
	Vec3 CameraSystem::m_Down{};

	void CameraSystem::CameraSystemInit()
	{

	}

	void CameraSystem::CameraSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, CameraComponent* _cameracomponent)
	{
		if (!GetUpdate)
		{
			//GraphicsManager::getInstance().setCamera(*_cameracomponent);
			SetUpdate(true);
		}
		static Input::mousePosition mouse = Input::mousePosition(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
		
		//only calls when entity has transform and camera component
		for (int i = 0; i < entities.size(); i++)
		{
			UpdateViewMatrixSystem(&_cameracomponent[i]);

			//if (movingCameraSystem())
			//{
			//	float CameraSpeed = _cameracomponent[i].getSpeed() * dt;
			//	key keys;
			//	if (keys.up)
			//	{
			//		_cameracomponent[i].getPosition() += m_Front * CameraSpeed;
			//	}
			//	if (keys.down)
			//		_cameracomponent[i].getPosition() -= m_Front * CameraSpeed;
			//	if (keys.left)
			//		_cameracomponent[i].getPosition() -= m_Front * CameraSpeed;
			//	if (keys.right)
			//		_cameracomponent[i].getPosition() += m_Front * CameraSpeed;
			//}

			if (mouse.x == std::numeric_limits<int>::max() && mouse.y == std::numeric_limits<int>::max())
			{
				mouse = Input::getMousePosition();
			}

			float GetMousex = static_cast<float>(mouse.x);
			float GetMousey = static_cast<float>(mouse.y);

			float getNewMousex = static_cast<float>(Input::getMousePosition().x);
			float getNewMousey = static_cast<float>(Input::getMousePosition().y);

			float offsetx = getNewMousex - GetMousex;
			float offsety = GetMousey - getNewMousey;

			ProcessMouseMovementSystem(offsetx, offsety, &_cameracomponent[i]);

			mouse = Input::getMousePosition();
			
			std::cout << "Mouse x:" << mouse.x << std::endl;
			std::cout << "Mouse y:" << mouse.y << std::endl;
		}
	}

	void CameraSystem::GetMousePosition()
	{

	}

	void CameraSystem::UpdateViewMatrixSystem(CameraComponent* _cameracomponent)
	{
		// calculate the new Front vector
		Vec3 front;
		front.x = Mathf::Cos(_cameracomponent->getYaw() * Mathf::Deg2Rad) * Mathf::Cos(_cameracomponent->getPitch() * Mathf::Deg2Rad);
		front.y = Mathf::Sin(_cameracomponent->getPitch() * Mathf::Deg2Rad);
		front.z = Mathf::Sin(_cameracomponent->getYaw() * Mathf::Deg2Rad) * Mathf::Cos(_cameracomponent->getPitch() * Mathf::Deg2Rad);
		m_Front = Vec3::Normalize(front);
		// also re-calculate the Right and Up vector
		m_Right = Vec3::Normalize(Vec3::Cross(m_Front, _cameracomponent->getmWorldUp()));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = Vec3::Normalize(Vec3::Cross(m_Right, m_Front));

		m_Down = -m_Up;
		TDS_INFO(m_Front);
		TDS_INFO(m_Right);
		TDS_INFO(m_Up);
	}

	bool CameraSystem::movingCameraSystem()
	{
		key keys;
		if (Input::keystatus == Input::KeyStatus::PRESSED || Input::keystatus == Input::KeyStatus::REPEATED)
		{
			switch (Input::keyCode)
			{
			case TDS_W:
				return keys.up = true;
				break;

			case TDS_A:
				return keys.left = true;
				break;

			case TDS_S:
				return keys.down = true;
				break;

			case TDS_D:
				return keys.right = true;

			default:
				return false;
			}
		}
		else
		{
			keys.up = false;
			keys.left = false;
			keys.down = false;
			keys.right = false;
		}
		return false;
	}

	void CameraSystem::ProcessMouseMovementSystem(float offsetX, float offsetY, CameraComponent* _cameracomponent)
	{
		offsetX *= _cameracomponent->getMouseSensitivity();
		offsetY *= _cameracomponent->getMouseSensitivity();

		_cameracomponent->setYaw(_cameracomponent->getYaw() + offsetX);
		_cameracomponent->setPitch(_cameracomponent->getPitch() + offsetY);

		//prevent from out of bound
		if (_cameracomponent->getPitch() > 89.f)
			_cameracomponent->setPitch(89.f);
		if (_cameracomponent->getPitch() < -89.f)
			_cameracomponent->setPitch(-89.f);

		UpdateViewMatrixSystem(_cameracomponent);
	}



}

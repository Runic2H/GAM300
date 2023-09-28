#include "components/components.h"

namespace TDS
{
	IComponent* addComponentByName(std::string componentName, EntityID entityID)
	{
		if (componentName == "AI")
			return ECS::addComponent<AI>(entityID);
		else if (componentName == "Camera Component")
			return ECS::addComponent<CameraComponent>(entityID);
		else if (componentName == "Collider")
			return ECS::addComponent<Collider>(entityID);
		else if (componentName == "Name Tag")
			return ECS::addComponent<NameTag>(entityID);
		else if (componentName == "Player Attributes")
			return ECS::addComponent<PlayerAttributes>(entityID);
		else if (componentName == "Rigid Body")
			return ECS::addComponent<RigidBody>(entityID);
		else if (componentName == "Sprite")
			return ECS::addComponent<Sprite>(entityID);
		else if (componentName == "Tag")
			return ECS::addComponent<Tag>(entityID);
		else if (componentName == "Transform")
			return ECS::addComponent<Transform>(entityID);
		else if (componentName == "Win Data")
			return ECS::addComponent<WinData>(entityID);
		else 
			return nullptr;
	}

	IComponent* getComponentByName(std::string componentName, EntityID entityID)
	{
		if (componentName == "AI")
			return ECS::getComponent<AI>(entityID);
		else if (componentName == "Camera Component")
			return ECS::getComponent<CameraComponent>(entityID);
		else if (componentName == "Collider")
			return ECS::getComponent<Collider>(entityID);
		else if (componentName == "Name Tag")
			return ECS::getComponent<NameTag>(entityID);
		else if (componentName == "Player Attributes")
			return ECS::getComponent<PlayerAttributes>(entityID);
		else if (componentName == "Rigid Body")
			return ECS::getComponent<RigidBody>(entityID);
		else if (componentName == "Sprite")
			return ECS::getComponent<Sprite>(entityID);
		else if (componentName == "Tag")
			return ECS::getComponent<Tag>(entityID);
		else if (componentName == "Transform")
			return ECS::getComponent<Transform>(entityID);
		else if (componentName == "Win Data")
			return ECS::getComponent<WinData>(entityID);
		else
			return nullptr;
	}

	void removeComponentByName(std::string componentName, EntityID entityID)
	{
		if (componentName == "AI")
			ECS::removeComponent<AI>(entityID);
		else if (componentName == "Camera Component")
			ECS::removeComponent<CameraComponent>(entityID);
		else if (componentName == "Collider")
			ECS::removeComponent<Collider>(entityID);
		else if (componentName == "Name Tag")
			ECS::removeComponent<NameTag>(entityID);
		else if (componentName == "Player Attributes")
			ECS::removeComponent<PlayerAttributes>(entityID);
		else if (componentName == "Rigid Body")
			ECS::removeComponent<RigidBody>(entityID);
		else if (componentName == "Sprite")
			ECS::removeComponent<Sprite>(entityID);
		else if (componentName == "Tag")
			ECS::removeComponent<Tag>(entityID);
		else if (componentName == "Transform")
			ECS::removeComponent<Transform>(entityID);
		else if (componentName == "Win Data")
			ECS::removeComponent<WinData>(entityID);
	}
}

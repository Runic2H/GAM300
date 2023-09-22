#include "components/components.h"

namespace TDS
{
	IComponent* addComponentByName(std::string componentName, EntityID entityID)
	{
		if (componentName == "CameraComponent")
			return ECS::addComponent<CameraComponent>(entityID);
		else if (componentName == "Collider")
			return ECS::addComponent<Collider>(entityID);
		else if (componentName == "NameTag")
			return ECS::addComponent<NameTag>(entityID);
		else if (componentName == "PlayerAttributes")
			return ECS::addComponent<PlayerAttributes>(entityID);
		else if (componentName == "RigidBody")
			return ECS::addComponent<RigidBody>(entityID);
		else if (componentName == "Sprite")
			return ECS::addComponent<Sprite>(entityID);
		else if (componentName == "Tag")
			return ECS::addComponent<Tag>(entityID);
		else if (componentName == "Transform")
			return ECS::addComponent<Transform>(entityID);
		else if (componentName == "WinData")
			return ECS::addComponent<WinData>(entityID);
		else 
			return nullptr;
	}

	IComponent* getComponentByName(std::string componentName, EntityID entityID)
	{
		if (componentName == "CameraComponent")
			return ECS::getComponent<CameraComponent>(entityID);
		else if (componentName == "Collider")
			return ECS::getComponent<Collider>(entityID);
		else if (componentName == "NameTag")
			return ECS::getComponent<NameTag>(entityID);
		else if (componentName == "PlayerAttributes")
			return ECS::getComponent<PlayerAttributes>(entityID);
		else if (componentName == "RigidBody")
			return ECS::getComponent<RigidBody>(entityID);
		else if (componentName == "Sprite")
			return ECS::getComponent<Sprite>(entityID);
		else if (componentName == "Tag")
			return ECS::getComponent<Tag>(entityID);
		else if (componentName == "Transform")
			return ECS::getComponent<Transform>(entityID);
		else if (componentName == "WinData")
			return ECS::getComponent<WinData>(entityID);
		else
			return nullptr;
	}
}

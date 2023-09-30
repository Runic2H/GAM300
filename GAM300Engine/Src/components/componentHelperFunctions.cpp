#include "components/components.h"

namespace TDS
{
	IComponent* addComponentByName(std::string componentName, EntityID entityID)
	{
		if (componentName == "AI")
			return ecs.addComponent<AI>(entityID);
		else if (componentName == "Camera Component")
			return ecs.addComponent<CameraComponent>(entityID);
		else if (componentName == "Collider")
			return ecs.addComponent<Collider>(entityID);
		else if (componentName == "Name Tag")
			return ecs.addComponent<NameTag>(entityID);
		else if (componentName == "Player Attributes")
			return ecs.addComponent<PlayerAttributes>(entityID);
		else if (componentName == "Rigid Body")
			return ecs.addComponent<RigidBody>(entityID);
		else if (componentName == "Sprite")
			return ecs.addComponent<Sprite>(entityID);
		else if (componentName == "Tag")
			return ecs.addComponent<Tag>(entityID);
		else if (componentName == "Transform")
			return ecs.addComponent<Transform>(entityID);
		else if (componentName == "Win Data")
			return ecs.addComponent<WinData>(entityID);
		else 
			return nullptr;
	}

	IComponent* getComponentByName(std::string componentName, EntityID entityID)
	{
		if (componentName == "AI")
			return ecs.getComponent<AI>(entityID);
		else if (componentName == "Camera Component")
			return ecs.getComponent<CameraComponent>(entityID);
		else if (componentName == "Collider")
			return ecs.getComponent<Collider>(entityID);
		else if (componentName == "Name Tag")
			return ecs.getComponent<NameTag>(entityID);
		else if (componentName == "Player Attributes")
			return ecs.getComponent<PlayerAttributes>(entityID);
		else if (componentName == "Rigid Body")
			return ecs.getComponent<RigidBody>(entityID);
		else if (componentName == "Sprite")
			return ecs.getComponent<Sprite>(entityID);
		else if (componentName == "Tag")
			return ecs.getComponent<Tag>(entityID);
		else if (componentName == "Transform")
			return ecs.getComponent<Transform>(entityID);
		else if (componentName == "Win Data")
			return ecs.getComponent<WinData>(entityID);
		else
			return nullptr;
	}

	void removeComponentByName(std::string componentName, EntityID entityID)
	{
		if (componentName == "AI")
			ecs.removeComponent<AI>(entityID);
		else if (componentName == "Camera Component")
			ecs.removeComponent<CameraComponent>(entityID);
		else if (componentName == "Collider")
			ecs.removeComponent<Collider>(entityID);
		else if (componentName == "Name Tag")
			ecs.removeComponent<NameTag>(entityID);
		else if (componentName == "Player Attributes")
			ecs.removeComponent<PlayerAttributes>(entityID);
		else if (componentName == "Rigid Body")
			ecs.removeComponent<RigidBody>(entityID);
		else if (componentName == "Sprite")
			ecs.removeComponent<Sprite>(entityID);
		else if (componentName == "Tag")
			ecs.removeComponent<Tag>(entityID);
		else if (componentName == "Transform")
			ecs.removeComponent<Transform>(entityID);
		else if (componentName == "Win Data")
			ecs.removeComponent<WinData>(entityID);
	}
}

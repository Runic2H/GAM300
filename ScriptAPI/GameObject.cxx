#include "GameObject.hxx"

namespace ScriptAPI
{
	BoxColliderComponent GameObject::GetBoxColliderComponent()
	{
		return BoxColliderComponent(entityID);
	}
	CameraComponent GameObject::GetCameraComponent()
	{
		return CameraComponent(entityID);
	}
	CapsuleColliderComponent GameObject::GetCapsuleColliderComponent()
	{
		return CapsuleColliderComponent(entityID);
	}
	NameTagComponent GameObject::GetNameTagComponent()
	{
		return NameTagComponent(entityID);
	}
	SphereColliderComponent GameObject::GetSphereColliderComponent()
	{
		return SphereColliderComponent(entityID);
	}

	TransformComponent GameObject::GetTransformComponent()
	{
		return TransformComponent(entityID);
	}

	int GameObject::GetEntityID()
	{
		return entityID;
	}

	generic <typename T>
	T GameObject::GetComponent()
	{
		System::Type^ type = T::typeid;

		if (type == TransformComponent::typeid)
		{
			return safe_cast<T>(GetTransformComponent());
		}

		return T();
	}

	void GameObject::SetEntityID(TDS::EntityID id)
	{
		entityID = id;
	}
}
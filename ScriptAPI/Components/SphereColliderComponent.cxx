#include "SphereColliderComponent.hxx"
#include "../TypeConversion.hxx"
#include "../EngineInterface.hxx"

namespace ScriptAPI
{
	// ISTRIGGER =============================================================================
	// Private
	bool SphereColliderComponent::IsTrigger::get()
	{
		// May wanna change to a function
		if (!TDS::GetSphereCollider(entityID))
		{
			// throw error instead (not sure how)
			return false;
		}

		return TDS::GetSphereCollider(entityID)->GetIsTrigger();
	}
	void SphereColliderComponent::IsTrigger::set(bool value)
	{
		// May wanna change to a function
		if (!TDS::GetSphereCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		return TDS::GetSphereCollider(entityID)->SetIsTrigger(value);
	}

	// Public
	bool SphereColliderComponent::GetIsTrigger()
	{
		return IsTrigger;
	}
	void SphereColliderComponent::SetIsTrigger(bool value)
	{
		IsTrigger = value;
	}

	// CENTER ================================================================================	
	// Private
	Vector3 SphereColliderComponent::Center::get()
	{
		// May wanna change to a function
		if (!TDS::GetSphereCollider(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetSphereCollider(entityID)->GetColliderCenter());

		//return TDS::GetTransform(entityID)->GetPosition();
	}
	void SphereColliderComponent::Center::set(Vector3 value)
	{
		// May wanna change to a function
		if (!TDS::GetSphereCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetSphereCollider(entityID)->SetColliderCenter(value.X, value.Y, value.Z);
	}

	// Public
	Vector3 SphereColliderComponent::GetCenter()
	{
		return Center;
	}
	void SphereColliderComponent::SetCenter(Vector3 value)
	{
		Center = value;
	}
	void SphereColliderComponent::SetCenterX(float valueX)
	{
		Vector3 oldCenter = Center;
		Center = Vector3(valueX, oldCenter.Y, oldCenter.Z);
	}
	void SphereColliderComponent::SetCenterY(float valueY)
	{
		Vector3 oldCenter = Center;
		Center = Vector3(oldCenter.X, valueY, oldCenter.Z);
	}
	void SphereColliderComponent::SetCenterZ(float valueZ)
	{
		Vector3 oldCenter = Center;
		Center = Vector3(oldCenter.X, oldCenter.Y, valueZ);
	}

	// RADIUS ================================================================================
	// Private
	float SphereColliderComponent::Radius::get()
	{
		// May wanna change to a function
		if (!TDS::GetSphereCollider(entityID))
		{
			// throw error instead (not sure how)
			return 0.f;
		}

		return TDS::GetSphereCollider(entityID)->GetColliderRadius();

		//return TDS::GetTransform(entityID)->GetPosition();
	}
	void SphereColliderComponent::Radius::set(float value)
	{
		// May wanna change to a function
		if (!TDS::GetSphereCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetSphereCollider(entityID)->SetColliderRadius(value);
	}

	// Public
	float SphereColliderComponent::GetRadius()
	{
		return Radius;
	}
	void SphereColliderComponent::SetRadius(float value)
	{
		Radius = value;
	}

	// CONSTRUCTOR ===========================================================================
	SphereColliderComponent::SphereColliderComponent(TDS::EntityID ID) : entityID(ID), transform(TransformComponent(ID))
	{
		gameObject = EngineInterface::GetGameObject(ID);
	}

	void SphereColliderComponent::SetEntityID(TDS::EntityID ID)
	{
		entityID = ID;
		transform = TransformComponent(ID);
		gameObject = EngineInterface::GetGameObject(ID);
	}

	TDS::EntityID SphereColliderComponent::GetEntityID()
	{
		return entityID;
	}

	void SphereColliderComponent::SetEnabled(bool enabled)
	{
		TDS::ecs.setEntityIsEnabled(GetEntityID(), enabled);
	}
}
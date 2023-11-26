#include "BoxColliderComponent.hxx"

namespace ScriptAPI
{
	// ISTRIGGER =============================================================================
	// Private
	bool BoxColliderComponent::IsTrigger::get()
	{
		// May wanna change to a function
		if (!TDS::GetBoxCollider(entityID))
		{
			// throw error instead (not sure how)
			return false;
		}

		return TDS::GetBoxCollider(entityID)->GetIsTrigger();
	}
	void BoxColliderComponent::IsTrigger::set(bool value)
	{
		// May wanna change to a function
		if (!TDS::GetBoxCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetBoxCollider(entityID)->SetIsTrigger(value);
	}

	// Public
	bool BoxColliderComponent::GetIsTrigger()
	{
		return IsTrigger;
	}
	void BoxColliderComponent::SetIsTrigger(bool value)
	{
		IsTrigger = value;
	}

	// CENTER ================================================================================
	// Private
	Vector3 BoxColliderComponent::Center::get()
	{
		// May wanna change to a function
		if (!TDS::GetBoxCollider(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetBoxCollider(entityID)->GetCenter());

		//return TDS::GetTransform(entityID)->GetPosition();
	}
	void BoxColliderComponent::Center::set(Vector3 value)
	{
		// May wanna change to a function
		if (!TDS::GetBoxCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetBoxCollider(entityID)->SetCenter(value.X, value.Y, value.Z);
	}

	// Public
	Vector3 BoxColliderComponent::GetCenter()
	{
		return Center;
	}
	void BoxColliderComponent::SetCenter(Vector3 value)
	{
		Center = value;
	}
	void BoxColliderComponent::SetCenterX(float valueX)
	{
		Vector3 oldCenter = Center;
		Center = Vector3(valueX, oldCenter.Y, oldCenter.Z);
	}
	void BoxColliderComponent::SetCenterY(float valueY)
	{
		Vector3 oldCenter = Center;
		Center = Vector3(oldCenter.X, valueY, oldCenter.Z);
	}
	void BoxColliderComponent::SetCenterZ(float valueZ)
	{
		Vector3 oldCenter = Center;
		Center = Vector3(oldCenter.X, oldCenter.Y, valueZ);
	}

	// SIZE ==================================================================================
	// Private
	Vector3 BoxColliderComponent::Size::get()
	{
		// May wanna change to a function
		if (!TDS::GetBoxCollider(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetBoxCollider(entityID)->GetSize());

		//return TDS::GetTransform(entityID)->GetPosition();
	}
	void BoxColliderComponent::Size::set(Vector3 value)
	{
		// May wanna change to a function
		if (!TDS::GetBoxCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetBoxCollider(entityID)->SetSize(value.X, value.Y, value.Z);
	}

	// Public
	Vector3 BoxColliderComponent::GetSize()
	{
		return Size;
	}
	void BoxColliderComponent::SetSize(Vector3 value)
	{
		Size = value;
	}
	void BoxColliderComponent::SetSizeX(float valueX)
	{
		Vector3 oldSize = Size;
		Size = Vector3(valueX, oldSize.Y, oldSize.Z);
	}
	void BoxColliderComponent::SetSizeY(float valueY)
	{
		Vector3 oldSize = Size;
		Size = Vector3(oldSize.X, valueY, oldSize.Z);
	}
	void BoxColliderComponent::SetSizeZ(float valueZ)
	{
		Vector3 oldSize = Size;
		Size = Vector3(oldSize.X, oldSize.Y, valueZ);
	}

	// CONSTRUCTOR ===========================================================================
	BoxColliderComponent::BoxColliderComponent(TDS::EntityID ID) : entityID(ID), transform(TransformComponent(ID))
	{ }

	void BoxColliderComponent::SetEntityID(TDS::EntityID ID)
	{
		entityID = ID;
		transform = TransformComponent(ID);
	}

	TDS::EntityID BoxColliderComponent::GetEntityID()
	{
		return entityID;
	}
}
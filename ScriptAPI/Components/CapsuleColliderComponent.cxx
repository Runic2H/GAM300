#include "CapsuleColliderComponent.hxx"

namespace ScriptAPI
{
	// ISTRIGGER =============================================================================
	// Private
	bool CapsuleColliderComponent::IsTrigger::get()
	{
		// May wanna change to a function
		if (!TDS::GetCapsuleCollider(entityID))
		{
			// throw error instead (not sure how)
			return false;
		}

		return TDS::GetCapsuleCollider(entityID)->GetIsTrigger();
	}
	void CapsuleColliderComponent::IsTrigger::set(bool value)
	{
		// May wanna change to a function
		if (!TDS::GetCapsuleCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		return TDS::GetCapsuleCollider(entityID)->SetIsTrigger(value);
	}

	// Public
	bool CapsuleColliderComponent::GetIsTrigger()
	{
		return IsTrigger;
	}
	void CapsuleColliderComponent::SetIsTrigger(bool value)
	{
		IsTrigger = value;
	}

	// CENTER ================================================================================
	// Private
	Vector3 CapsuleColliderComponent::Center::get()
	{
		// May wanna change to a function
		if (!TDS::GetCapsuleCollider(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetCapsuleCollider(entityID)->GetCenter());

		//return TDS::GetTransform(entityID)->GetPosition();
	}
	void CapsuleColliderComponent::Center::set(Vector3 value)
	{
		// May wanna change to a function
		if (!TDS::GetCapsuleCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCapsuleCollider(entityID)->SetCenter(value.X, value.Y, value.Z);
	}

	// Public
	Vector3 CapsuleColliderComponent::GetCenter()
	{
		return Center;
	}
	void CapsuleColliderComponent::SetCenter(Vector3 value)
	{
		Center = value;
	}
	void CapsuleColliderComponent::SetCenterX(float valueX)
	{
		Vector3 oldCenter = Center;
		Center = Vector3(valueX, oldCenter.Y, oldCenter.Z);
	}
	void CapsuleColliderComponent::SetCenterY(float valueY)
	{
		Vector3 oldCenter = Center;
		Center = Vector3(oldCenter.X, valueY, oldCenter.Z);
	}
	void CapsuleColliderComponent::SetCenterZ(float valueZ)
	{
		Vector3 oldCenter = Center;
		Center = Vector3(oldCenter.X, oldCenter.Y, valueZ);
	}

	// RADIUS ================================================================================
	// Private
	float CapsuleColliderComponent::Radius::get()
	{
		// May wanna change to a function
		if (!TDS::GetCapsuleCollider(entityID))
		{
			// throw error instead (not sure how)
			return 0.f;
		}

		return TDS::GetCapsuleCollider(entityID)->GetRadius();

		//return TDS::GetTransform(entityID)->GetPosition();
	}
	void CapsuleColliderComponent::Radius::set(float value)
	{
		// May wanna change to a function
		if (!TDS::GetCapsuleCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCapsuleCollider(entityID)->SetRadius(value);
	}

	// Public
	float CapsuleColliderComponent::GetRadius()
	{
		return Radius;
	}
	void CapsuleColliderComponent::SetRadius(float value)
	{
		Radius = value;
	}

	// HEIGHT ================================================================================
	// Private
	float CapsuleColliderComponent::Height::get()
	{
		// May wanna change to a function
		if (!TDS::GetCapsuleCollider(entityID))
		{
			// throw error instead (not sure how)
			return 0.f;
		}

		return TDS::GetCapsuleCollider(entityID)->GetHeight();

		//return TDS::GetTransform(entityID)->GetPosition();
	}
	void CapsuleColliderComponent::Height::set(float value)
	{
		// May wanna change to a function
		if (!TDS::GetCapsuleCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCapsuleCollider(entityID)->SetHeight(value);
	}

	// Public
	float CapsuleColliderComponent::GetHeight()
	{
		return Height;
	}
	void CapsuleColliderComponent::SetHeight(float value)
	{
		Height = value;
	}

	// DIRECTION =============================================================================
	// Private
	CapsuleColliderComponent::Axis CapsuleColliderComponent::Direction::get()
	{
		// May wanna change to a function
		if (!TDS::GetCapsuleCollider(entityID))
		{
			// throw error instead (not sure how)
			return Axis::X;
		}

		return static_cast<Axis>(TDS::GetCapsuleCollider(entityID)->GetDirection());

		//return TDS::GetTransform(entityID)->GetPosition();
	}
	void CapsuleColliderComponent::Direction::set(Axis value)
	{
		// May wanna change to a function
		if (!TDS::GetCapsuleCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCapsuleCollider(entityID)->SetDirection(static_cast<TDS::CapsuleCollider::Direction>(value));
	}

	// Public
	CapsuleColliderComponent::Axis CapsuleColliderComponent::GetDirection()
	{
		return Direction;
	}
	void CapsuleColliderComponent::SetDirection(Axis value)
	{
		Direction = value;
	}

	// CONSTRUCTOR ===========================================================================
	CapsuleColliderComponent::CapsuleColliderComponent(TDS::EntityID ID) : entityID(ID), transform(TransformComponent(ID))
	{ }

	void CapsuleColliderComponent::SetEntityID(TDS::EntityID ID)
	{
		entityID = ID;
		transform = TransformComponent(ID);
	}

	TDS::EntityID CapsuleColliderComponent::GetEntityID()
	{
		return entityID;
	}
}
#include "ColliderComponent.hxx"

namespace ScriptAPI
{
	// COLLIDER TYPE =========================================================================
	// Private
	TDS::Collider::ColliderType ColliderComponent::ColliderType::get()
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return TDS::Collider::ColliderType::NONE;
		}

		return TDS::GetCollider(entityID)->GetColliderType();
	}
	void ColliderComponent::ColliderType::set(TDS::Collider::ColliderType value)
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCollider(entityID)->SetColliderType(value);
	}

	// Public
	TDS::Collider::ColliderType ColliderComponent::GetCollisionType()
	{
		return ColliderType;
	}
	void ColliderComponent::SetCollisionType(TDS::Collider::ColliderType value)
	{
		ColliderType = value;
	}

	// COLLIDER NORMAL =======================================================================
	// Private
	Vector3 ColliderComponent::CollisionNormal::get()
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetCollider(entityID)->GetColliderNormal());
	}
	void ColliderComponent::CollisionNormal::set(Vector3 value)
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCollider(entityID)->SetColliderNormal(value.X, value.Y, value.Z);
	}

	// Public
	Vector3 ColliderComponent::GetCollisionNormal()
	{
		return CollisionNormal;
	}
	void ColliderComponent::SetCollisionNormal(Vector3 value)
	{
		CollisionNormal = value;
	}
	void ColliderComponent::SetCollisionNormalX(float valueX)
	{
		Vector3 oldCollisionNormal = CollisionNormal;
		CollisionNormal = Vector3(valueX, oldCollisionNormal.Y, oldCollisionNormal.Z);
	}
	void ColliderComponent::SetCollisionNormalY(float valueY)
	{
		Vector3 oldCollisionNormal = CollisionNormal;
		CollisionNormal = Vector3(oldCollisionNormal.X, valueY, oldCollisionNormal.Z);
	}
	void ColliderComponent::SetCollisionNormalZ(float valueZ)
	{
		Vector3 oldCollisionNormal = CollisionNormal;
		CollisionNormal = Vector3(oldCollisionNormal.X, oldCollisionNormal.Y, valueZ);
	}

	// MINIMUM ===============================================================================
	// Private
	Vector3 ColliderComponent::Minimum::get()
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetCollider(entityID)->GetMin());
	}
	void ColliderComponent::Minimum::set(Vector3 value)
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCollider(entityID)->SetMin(value.X, value.Y, value.Z);
	}

	// Public
	Vector3 ColliderComponent::GetMinimum()
	{
		return Minimum;
	}
	void ColliderComponent::SetMinimum(Vector3 value)
	{
		Minimum = value;
	}
	void ColliderComponent::SetMinimumX(float valueX)
	{
		Vector3 oldMinimum = Minimum;
		Minimum = Vector3(valueX, oldMinimum.Y, oldMinimum.Z);

	}
	void ColliderComponent::SetMinimumY(float valueY)
	{
		Vector3 oldMinimum = Minimum;
		Minimum = Vector3(oldMinimum.X, valueY, oldMinimum.Z);
	}
	void ColliderComponent::SetMinimumZ(float valueZ)
	{
		Vector3 oldMinimum = Minimum;
		Minimum = Vector3(oldMinimum.X, oldMinimum.Y, valueZ);
	}

	// MAXIMUM ===============================================================================
	// Private
	Vector3 ColliderComponent::Maximum::get()
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetCollider(entityID)->GetMax());
	}
	void ColliderComponent::Maximum::set(Vector3 value)
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCollider(entityID)->SetMax(value.X, value.Y, value.Z);
	}
	
	// Public
	Vector3 ColliderComponent::GetMaximum()
	{
		return Maximum;
	}
	void ColliderComponent::SetMaximum(Vector3 value)
	{
		Maximum = value;
	}
	void ColliderComponent::SetMaximumX(float valueX)
	{
		Vector3 oldMaximum = Maximum;
		Maximum = Vector3(valueX, oldMaximum.Y, oldMaximum.Z);
	}
	void ColliderComponent::SetMaximumY(float valueY)
	{
		Vector3 oldMaximum = Maximum;
		Maximum = Vector3(oldMaximum.X, valueY, oldMaximum.Z);
	}
	void ColliderComponent::SetMaximumZ(float valueZ)
	{
		Vector3 oldMaximum = Maximum;
		Maximum = Vector3(oldMaximum.X, oldMaximum.Y, valueZ);
	}

	// OFFSET ================================================================================
	// Private
	Vector3 ColliderComponent::Offset::get()
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetCollider(entityID)->GetMax());
	}
	void ColliderComponent::Offset::set(Vector3 value)
	{
		TDS::GetCollider(entityID)->SetOffset(value.X, value.Y, value.Z);
	}

	// Public
	Vector3 ColliderComponent::GetOffset()
	{
		return Offset;
	}
	void ColliderComponent::SetOffset(Vector3 value)
	{
		Offset = value;
	}
	void ColliderComponent::SetOffsetX(float valueX)
	{
		Vector3 oldOffset = Offset;
		Offset = Vector3(valueX, oldOffset.Y, oldOffset.Z);
	}
	void ColliderComponent::SetOffsetY(float valueY)
	{
		Vector3 oldOffset = Offset;
		Offset = Vector3(oldOffset.X, valueY, oldOffset.Z);
	}
	void ColliderComponent::SetOffsetZ(float valueZ)
	{
		Vector3 oldOffset = Offset;
		Offset = Vector3(oldOffset.X, oldOffset.Y, valueZ);
	}

	// HIT ===================================================================================
	// Private
	int ColliderComponent::Hit::get()
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return 0;
		}

		return TDS::GetCollider(entityID)->GetHit();
	}
	void ColliderComponent::Hit::set(int value)
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return ;
		}

		TDS::GetCollider(entityID)->SetHit(value);
	}

	// Public
	int ColliderComponent::GetHit()
	{
		return Hit;
	}
	void ColliderComponent::SetHit(int value)
	{
		Hit = value;
	}

	// RADIUS ================================================================================
	// Private
	float ColliderComponent::Radius::get()
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return 0.f;
		}

		return TDS::GetCollider(entityID)->GetRadius();
	}
	void ColliderComponent::Radius::set(float value)
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCollider(entityID)->SetRadius(value);
	}

	// Public
	float ColliderComponent::GetRadius()
	{
		return Radius;
	}
	void ColliderComponent::SetRadius(float value)
	{
		Radius = value;
	}

	// IS ALIVE ==============================================================================
	// Private
	bool ColliderComponent::IsAlive::get()
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return false;
		}

		return TDS::GetCollider(entityID)->GetAlive();
	}
	void ColliderComponent::IsAlive::set(bool value)
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCollider(entityID)->SetAlive(value);
	}

	// Public
	bool ColliderComponent::GetIsAlive()
	{
		return IsAlive;
	}
	void ColliderComponent::SetIsAlive(bool value)
	{
		IsAlive = value;
	}

	// IS COLLIDING ==========================================================================
	// Private
	bool ColliderComponent::IsColliding::get()
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return false;
		}

		return TDS::GetCollider(entityID)->GetCollision();
	}
	void ColliderComponent::IsColliding::set(bool value)
	{
		// May wanna change to a function
		if (!TDS::GetCollider(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetCollider(entityID)->SetCollision(value);
	}

	// Public
	bool ColliderComponent::GetIsColliding()
	{
		return IsColliding;
	}
	void ColliderComponent::SetIsColliding(bool value)
	{
		IsColliding = value;
	}

	// CONSTRUCTOR ===========================================================================
	ColliderComponent::ColliderComponent(TDS::EntityID ID) : entityID (ID)
	{ }
}
#include "TransformComponent.hxx"
#include "../Shared_Libs/Vector4.h"
#include "../Shared_Libs/Matrix4.h"
#include "../GameObject.hxx"

namespace ScriptAPI
{
	// POSITION ==============================================================================
	// Private
	Vector3 TransformComponent::Position::get()
	{
		// May wanna change to a function
		if (!TDS::GetTransform(entityID))
		{		
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetTransform(entityID)->GetPosition());
	}
	void TransformComponent::Position::set(Vector3 value)
	{
		// May wanna change to a function
		if (!TDS::GetTransform(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		Vector3 oldPosition = Position;
		TDS::GetTransform(entityID)->SetPosition(value.X, value.Y, value.Z);
		TDS::EventHandler::postChildTransformationEvent(entityID, TDS::floatsToVec3(oldPosition.X, oldPosition.Y, oldPosition.Z), TDS::GetTransform(entityID)->GetScale(), TDS::GetTransform(entityID)->GetRotation());
	}

	// Public
	Vector3 TransformComponent::GetPosition()
	{
		return Position;
	}
	void TransformComponent::SetPosition(Vector3 value)
	{
		Position = value;
	}
	void TransformComponent::SetPositionX(float valueX)
	{
		Vector3 oldPosition = Position;
		Position = Vector3(valueX, oldPosition.Y, oldPosition.Z);
	}
	void TransformComponent::SetPositionY(float valueY)
	{
		Vector3 oldPosition = Position;
		Position = Vector3(oldPosition.X, valueY, oldPosition.Z);
	}
	void TransformComponent::SetPositionZ(float valueZ)
	{
		Vector3 oldPosition = Position;
		Position = Vector3(oldPosition.X, oldPosition.Y, valueZ);
	}

	// SCALE =================================================================================
	// Private
	Vector3 TransformComponent::Scale::get()
	{
		// May wanna change to a function
		if (!TDS::GetTransform(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetTransform(entityID)->GetScale());
	}
	void TransformComponent::Scale::set(Vector3 value)
	{
		// May wanna change to a function
		if (!TDS::GetTransform(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		Vector3 oldScale = Scale;
		TDS::GetTransform(entityID)->SetScale(value.X, value.Y, value.Z);
		TDS::EventHandler::postChildTransformationEvent(entityID, TDS::GetTransform(entityID)->GetPosition(), TDS::floatsToVec3(oldScale.X, oldScale.Y, oldScale.Z), TDS::GetTransform(entityID)->GetRotation());
	}

	// Public
	Vector3 TransformComponent::GetScale()
	{
		return Scale;
	}
	void TransformComponent::SetScale(Vector3 value)
	{
		Scale = value;
	}
	void TransformComponent::SetScaleX(float valueX)
	{
		Vector3 oldScale = Scale;
		Scale = Vector3(valueX, oldScale.Y, oldScale.Z);
	}
	void TransformComponent::SetScaleY(float valueY)
	{
		Vector3 oldScale = Scale;
		Scale = Vector3(oldScale.X, valueY, oldScale.Z);
	}
	void TransformComponent::SetScaleZ(float valueZ)
	{
		Vector3 oldScale = Scale;
		Scale = Vector3(oldScale.X, oldScale.Y, valueZ);
	}

	// ROTATION ==============================================================================
	// Private
	Vector3 TransformComponent::Rotation::get()
	{
		// May wanna change to a function
		if (!TDS::GetTransform(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		return Vector3(TDS::GetTransform(entityID)->GetRotation());
	}
	void TransformComponent::Rotation::set(Vector3 value)
	{
		// May wanna change to a function
		if (!TDS::GetTransform(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		Vector3 oldRotation = Rotation;
		TDS::GetTransform(entityID)->SetRotation(value.X, value.Y, value.Z);
		TDS::EventHandler::postChildTransformationEvent(entityID, TDS::GetTransform(entityID)->GetPosition(), TDS::GetTransform(entityID)->GetScale(), TDS::floatsToVec3(oldRotation.X, oldRotation.Y, oldRotation.Z));
	}

	// Public
	Vector3 TransformComponent::GetRotation()
	{
		return Rotation;
	}

	void TransformComponent::SetRotation(Vector3 value)
	{
		Rotation = value;
	}

	void TransformComponent::SetRotationX(float valueX)
	{
		Vector3 oldRotation = Rotation;
		Rotation = Vector3(valueX, oldRotation.Y, oldRotation.Z);
	}

	void TransformComponent::SetRotationY(float valueY)
	{
		Vector3 oldRotation = Rotation;
		Rotation = Vector3(oldRotation.X, valueY, oldRotation.Z);
	}

	void TransformComponent::SetRotationZ(float valueZ)
	{
		Vector3 oldRotation = Rotation;
		Rotation = Vector3(oldRotation.X, oldRotation.Y, valueZ);
	}

	Vector3 TransformComponent::TransformDirection(Vector3 direction)
	{
		// May wanna change to a function
		if (!TDS::GetTransform(entityID))
		{
			// throw error instead (not sure how)
			return Vector3(0.f, 0.f, 0.f);
		}

		// A -> x + 1
		// D -> x - 1
		// W -> z + 1
		// S -> z - 1

		Vector3 toReturn = Vector3(0, 0, 0);
		if (direction.X != 0)
		{
			TDS::Vec3 rightVector = TDS::GetTransform(entityID)->getRightVector();
			rightVector.x = -rightVector.x;
			toReturn = Vector3(rightVector) * direction.X;
		}
		if (direction.Y != 0)
		{
			// To Do
		}
		if (direction.Z != 0)
		{
			TDS::Vec3 forwardVector = TDS::GetTransform(entityID)->getForwardVector();
			forwardVector.x = -forwardVector.x;
			toReturn = toReturn + Vector3(forwardVector) * direction.Z;
		}

		return toReturn;
	}

	// CONSTRUCTOR ===========================================================================
	TransformComponent::TransformComponent(TDS::EntityID ID) : entityID (ID)
	{ }

	TransformComponent::TransformComponent(TDS::EntityID ID, GameObject^ _gameObject) : entityID(ID), gameObject(_gameObject)
	{ }

	void TransformComponent::SetEntityID(TDS::EntityID ID)
	{
		entityID = ID;
	}

	TDS::EntityID TransformComponent::GetEntityID()
	{
		return entityID;
	}	
}
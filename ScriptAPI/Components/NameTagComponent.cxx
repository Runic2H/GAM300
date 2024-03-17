#include "NameTagComponent.hxx"
#include "../TypeConversion.hxx"
#include "../EngineInterface.hxx"

namespace ScriptAPI
{
	// NAME ==================================================================================
	// Private
	System::String^ NameTagComponent::Name::get()
	{
		// May wanna change to a function
		if (!TDS::GetNameTag(entityID))
		{
			// throw error instead (not sure how)
			return "";
		}

		return toSystemString(TDS::GetNameTag(entityID)->GetName());

	}
	void NameTagComponent::Name::set(System::String^ value)
	{
		// May wanna change to a function
		if (!TDS::GetNameTag(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetNameTag(entityID)->SetName(toStdString(value));
	}

	// Public
	System::String^ NameTagComponent::GetName()
	{
		return Name;
	}
	void NameTagComponent::SetName(System::String^ value)
	{
		Name = value;
	}

	// TAG ===================================================================================
	// Private
	System::String^ NameTagComponent::Tag::get()
	{
		// May wanna change to a function
		if (!TDS::GetNameTag(entityID))
		{
			// throw error instead (not sure how)
			return "";
		}

		return toSystemString(TDS::GetNameTag(entityID)->GetTag());
	}
	void NameTagComponent::Tag::set(System::String^ value)
	{
		// May wanna change to a function
		if (!TDS::GetNameTag(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetNameTag(entityID)->SetTag(toStdString(value));
	}

	// Public
	System::String^ NameTagComponent::GetTag()
	{
		return Tag;
	}
	void NameTagComponent::SetTag(System::String^ value)
	{
		Tag = value;
	}

	// IS ACTIVE =============================================================================
	// Private
	bool NameTagComponent::IsActive::get()
	{
		// May wanna change to a function
		if (!TDS::GetNameTag(entityID))
		{
			// throw error instead (not sure how)
			return "";
		}

		return TDS::GetNameTag(entityID)->GetIsActive();
	}
	void NameTagComponent::IsActive::set(bool value)
	{
		// May wanna change to a function
		if (!TDS::GetNameTag(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetNameTag(entityID)->SetIsActive(value);
	}

	// Public
	bool NameTagComponent::GetIsActive()
	{
		return IsActive;
	}
	void NameTagComponent::SetIsActive(bool value)
	{
		IsActive = value;
	}

	// CONSTRUCTOR ===========================================================================
	NameTagComponent::NameTagComponent(TDS::EntityID ID) : entityID(ID), transform(TransformComponent(ID))
	{
		gameObject = EngineInterface::GetGameObject(ID);
	}

	void NameTagComponent::SetEntityID(TDS::EntityID ID)
	{
		entityID = ID;
		transform = TransformComponent(ID);
		gameObject = EngineInterface::GetGameObject(ID);
	}

	TDS::EntityID NameTagComponent::GetEntityID()
	{
		return entityID;
	}

	void NameTagComponent::SetEnabled(bool enabled)
	{
		TDS::setComponentIsEnable("Name Tag", GetEntityID(), enabled);
	}
	bool NameTagComponent::GetEnabled()
	{
		return TDS::getComponentIsEnable("Name Tag", GetEntityID());
	}
}
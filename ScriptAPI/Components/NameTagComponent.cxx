#include "NameTagComponent.hxx"

namespace ScriptAPI
{
	// NAME ==================================================================================
	// Private
	std::string NameTagComponent::Name::get()
	{
		// May wanna change to a function
		if (!TDS::GetNameTag(entityID))
		{
			// throw error instead (not sure how)
			return "";
		}

		return TDS::GetNameTag(entityID)->GetName();

	}
	void NameTagComponent::Name::set(std::string value)
	{
		// May wanna change to a function
		if (!TDS::GetNameTag(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetNameTag(entityID)->SetName(value);
	}

	// Public
	std::string NameTagComponent::GetName()
	{
		return Name;
	}
	void NameTagComponent::SetName(std::string value)
	{
		Name = value;
	}

	// TAG ===================================================================================
	// Private
	std::string NameTagComponent::Tag::get()
	{
		// May wanna change to a function
		if (!TDS::GetNameTag(entityID))
		{
			// throw error instead (not sure how)
			return "";
		}

		return TDS::GetNameTag(entityID)->GetTag();
	}
	void NameTagComponent::Tag::set(std::string value)
	{
		// May wanna change to a function
		if (!TDS::GetNameTag(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetNameTag(entityID)->SetTag(value);
	}

	// Public
	std::string NameTagComponent::GetTag()
	{
		return Tag;
	}
	void NameTagComponent::SetTag(std::string value)
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
	NameTagComponent::NameTagComponent(TDS::EntityID ID) : entityID (ID)
	{ }
}
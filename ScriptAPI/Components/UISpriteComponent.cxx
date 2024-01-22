#include "UISpriteComponent.hxx"
#include "../TypeConversion.hxx"
#include "Timestep/Timestep.h"

namespace ScriptAPI
{
	void UISpriteComponent::SetLayerID(int layerID)
	{
		if (!TDS::GetUISprite(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		TDS::GetUISprite(entityID)->SetLayerID(layerID);
	}
	void UISpriteComponent::SetColour(Vector4 value)
	{
		if (!TDS::GetUISprite(entityID))
		{
			// throw error instead (not sure how)
			return;
		}
		TDS::GetUISprite(entityID)->SetColourViaFloat(value.X, value.Y, value.Z, value.W);
	}
	float UISpriteComponent::getColourAlpha() {
		return TDS::GetUISprite(entityID)->m_Color.w;
	}
	void UISpriteComponent::setColourAlpha(float value) {
		TDS::GetUISprite(entityID)->m_Color.w = value;
	}
	void UISpriteComponent::ColorAlphafade(float multiplier) {
		TDS::GetUISprite(entityID)->m_Color.w -= multiplier * TDS::TimeStep::GetDeltaTime();
	}
	bool UISpriteComponent::IsMouseCollided()
	{
		if (!TDS::GetUISprite(entityID))
		{
			// throw error instead (not sure how)
			return false;
		}
		return TDS::GetUISprite(entityID)->IsMouseCollided();
	}
	void UISpriteComponent::SetTextureName(System::String^ textureName)
	{
		if (!TDS::GetUISprite(entityID))
		{
			return;
		}
		TDS::GetUISprite(entityID)->SetTextureName(toStdString(textureName));
	}
	System::String^ UISpriteComponent::GetTextureName()
	{
		if (!TDS::GetUISprite(entityID))
		{
			// throw error instead (not sure how)
			return "";
		}
		return toSystemString(TDS::GetUISprite(entityID)->GetTextureName());
	}
	void UISpriteComponent::SetFontName(System::String^ fontName)
	{
		if (!TDS::GetUISprite(entityID))
		{
			// throw error instead (not sure how)
			return;
		}
		TDS::GetUISprite(entityID)->SetFontName(toStdString(fontName));
	}
	void UISpriteComponent::SetFontMessage(System::String^ message)
	{
		if (!TDS::GetUISprite(entityID))
		{
			// throw error instead (not sure how)
			return;
		}
		TDS::GetUISprite(entityID)->SetFontMessage(toStdString(message));
	}
	void UISpriteComponent::SetIsFont(bool condition)
	{
		if (!TDS::GetUISprite(entityID))
		{
			// throw error instead (not sure how)
			return;
		}
		TDS::GetUISprite(entityID)->SetIsFont(condition);
	}
	bool UISpriteComponent::IsFont()
	{
		if (!TDS::GetUISprite(entityID))
		{
			// throw error instead (not sure how)
			return false;
		}
		return TDS::GetUISprite(entityID)->IsFont();
	}
	void UISpriteComponent::SetFontColour(Vector4 color)
	{
		if (!TDS::GetUISprite(entityID))
		{
			// throw error instead (not sure how)
			return;
		}
		TDS::GetUISprite(entityID)->SetFontColourViaFloat(color.X, color.Y, color.Z, color.W);
	}
	void UISpriteComponent::SetFontBackgroundColor(Vector4 color)
	{
		if (!TDS::GetUISprite(entityID))
		{
			// throw error instead (not sure how)
			return;
		}
		TDS::GetUISprite(entityID)->SetFontBackgroundColourViaFloat(color.X, color.Y, color.Z, color.W);
	}
	void UISpriteComponent::SetEntityID(TDS::EntityID ID)
	{
		entityID = ID;
	}
	UISpriteComponent::UISpriteComponent(TDS::EntityID ID) : entityID(ID), transform(TransformComponent(ID))
	{
	}
	TDS::EntityID UISpriteComponent::GetEntityID()
	{
		return entityID;
	}

	void UISpriteComponent::SetEnabled(bool enabled)
	{
		TDS::ecs.setEntityIsEnabled(GetEntityID(), enabled);
	}
}
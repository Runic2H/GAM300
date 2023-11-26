#include "UISpriteComponent.hxx"
#include "../TypeConversion.hxx"
#include "Timestep/Timestep.h"

namespace ScriptAPI
{
	void UISpriteComponent::SetLayerID(int layerID)
	{
		TDS::GetUISprite(entityID)->SetLayerID(layerID);
	}
	void UISpriteComponent::SetColour(Vector4 value)
	{
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
		return TDS::GetUISprite(entityID)->IsMouseCollided();
	}
	void UISpriteComponent::SetTextureName(System::String^ textureName)
	{
		TDS::GetUISprite(entityID)->SetTextureName(toStdString(textureName));
	}
	void UISpriteComponent::SetFontName(System::String^ fontName)
	{
		TDS::GetUISprite(entityID)->SetFontName(toStdString(fontName));
	}
	void UISpriteComponent::SetFontMessage(System::String^ message)
	{
		TDS::GetUISprite(entityID)->SetFontMessage(toStdString(message));
	}
	void UISpriteComponent::SetIsFont(bool condition)
	{
		TDS::GetUISprite(entityID)->SetIsFont(condition);
	}
	bool UISpriteComponent::IsFont()
	{
		return TDS::GetUISprite(entityID)->IsFont();
	}
	void UISpriteComponent::SetFontColour(Vector4 color)
	{
		TDS::GetUISprite(entityID)->SetFontColourViaFloat(color.X, color.Y, color.Z, color.W);
	}
	void UISpriteComponent::SetFontBackgroundColor(Vector4 color)
	{
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
}
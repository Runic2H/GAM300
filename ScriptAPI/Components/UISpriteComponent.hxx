#pragma once
#include "ComponentBase.hxx"
#include "TransformComponent.hxx"

namespace ScriptAPI
{
	public value class UISpriteComponent : ComponentBase
	{
	public:
		void SetLayerID(int layerID);

		void SetColour(Vector4 value);

		float getColourAlpha();
		void setColourAlpha(float value);
		void ColorAlphafade(float multiplier);
		//normal sprites
		bool IsMouseCollided();

		void SetTextureName(System::String^ textureName);

		System::String^ GetTextureName();

		//Font
		void SetFontName(System::String^ fontName);

		void SetFontMessage(System::String^ message);
		
		void SetIsFont(bool condition);

		bool IsFont();

		void SetFontColour(Vector4 color);

		void SetFontBackgroundColor(Vector4 color);

		virtual TDS::EntityID GetEntityID();
		virtual void SetEntityID(TDS::EntityID ID);

		virtual void SetEnabled(bool enabled);
		virtual bool GetEnabled();

		TransformComponent transform;
		GameObject^ gameObject;
		
	internal:
		UISpriteComponent(TDS::EntityID ID);

	private:
		TDS::EntityID entityID;
	};
}
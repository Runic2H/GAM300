#pragma once
#include "ComponentBase.hxx"
#include "TransformComponent.hxx"

namespace ScriptAPI {
	public value class GraphicComponent : ComponentBase
	{
	public:
		float getColourAlpha();
		void SetColourAlpha(float value);

		virtual TDS::EntityID GetEntityID();
		virtual void SetEntityID(TDS::EntityID);
		virtual void SetEnabled(bool enabled);

		TransformComponent transform;

	internal:
		GraphicComponent(TDS::EntityID ID);

	private:
		TDS::EntityID entityID;
		
		property Vector4 Color {
			Vector4 get();
			void set(Vector4 value);
		}
	};
}
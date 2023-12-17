#pragma once
#include "ComponentBase.hxx"

namespace ScriptAPI {
	public value class GraphicComponent : ComponentBase
	{
	public:
		float getColourAlpha();
		void SetColourAlpha(float value);

		virtual void SetEntityID(TDS::EntityID);
	internal:
		GraphicComponent(TDS::EntityID ID);
		TDS::EntityID GetEntityID();

	private:
		TDS::EntityID entityID;
		
		property Vector4 Color {
			Vector4 get();
			void set(Vector4 value);
		}
	};
}
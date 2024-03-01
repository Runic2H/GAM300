#pragma once

#include "ComponentBase.hxx"
#include "TransformComponent.hxx"

namespace ScriptAPI
{
	public value class DirectionalLightComponent : public ComponentBase
	{
	public:

		Vector4 GetColour();
		void SetColour(Vector4 value);

		Vector4 GetDirection();
		void SetDirection(Vector4 value);

		virtual TDS::EntityID GetEntityID();
		virtual void SetEntityID(TDS::EntityID ID);

		virtual void SetEnabled(bool enabled);
		virtual bool GetEnabled();

		TransformComponent transform;
		GameObject^ gameObject;

	internal:
		DirectionalLightComponent(TDS::EntityID ID);

	private:
		
		property Vector4 colour
		{
			Vector4 get();
			void set(Vector4 value);
		}

		property Vector4 direction
		{
			Vector4 get();
			void set(Vector4 value);
		}

		TDS::EntityID entityID;
	};
}

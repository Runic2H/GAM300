#pragma once

#include "TransformComponent.hxx"
#include "ComponentBase.hxx"

namespace ScriptAPI
{
	public value class SpotlightComponent : ComponentBase
	{
	public:
		Vector4 GetDirection();
		void SetDirection(Vector4 value);

		Vector4 GetColor();
		void SetColor(Vector4 value);

		Vector4 GetAttenuation();
		void SetAttenuation(Vector4 value);

		float GetAngle();

		void SetAngle(float Angle);

		virtual TDS::EntityID GetEntityID();
		virtual void SetEntityID(TDS::EntityID ID);

		virtual void SetEnabled(bool enabled);
		virtual bool GetEnabled();

		GameObject^ gameObject;
		TransformComponent transform;
	internal:
		SpotlightComponent(TDS::EntityID ID);

	private:
		TDS::EntityID entityID;
	};


}
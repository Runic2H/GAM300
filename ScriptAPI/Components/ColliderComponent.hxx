#pragma once

#include "ComponentBase.hxx"
#include "TransformComponent.hxx"

namespace ScriptAPI
{
	ref class GameObject;
	public ref class ColliderComponent : public ComponentBase
	{
	public:
		virtual TDS::EntityID GetEntityID() = 0;
		virtual void SetEntityID(TDS::EntityID ID) = 0;

		virtual bool GetIsTrigger() = 0;
		virtual void SetIsTrigger(bool value) = 0;
		virtual void SetEnabled(bool enabled) = 0;

		GameObject^ gameObject;
	};
}
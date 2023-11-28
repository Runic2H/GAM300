#pragma once

#include "ComponentBase.hxx"
#include "TransformComponent.hxx"

namespace ScriptAPI
{
	public value class SphereColliderComponent : ComponentBase
	{
	public:
		bool GetIsTrigger();
		void SetIsTrigger(bool value);

		bool GetIsInteract();
		void SetIsInteract(bool value);

		System::String^ GetColliderName();

		Vector3 GetCenter();
		void SetCenter(Vector3 value);
		void SetCenterX(float valueX);
		void SetCenterY(float valueY);
		void SetCenterZ(float valueZ);

		float GetRadius();
		void SetRadius(float value);

		virtual void SetEntityID(TDS::EntityID ID);

		TransformComponent^transform;

	internal:
		SphereColliderComponent(TDS::EntityID ID);
		TDS::EntityID GetEntityID();

	private:
		property bool IsInteract
		{
			bool get();
			void set(bool value);
		}
		property bool IsTrigger
		{
			bool get();
			void set(bool value);
		}
		property Vector3 Center
		{
			Vector3 get();
			void set(Vector3 value);
		}
		property float Radius
		{
			float get();
			void set(float value);
		}
		property System::String^ ColliderName
		{
			System::String^ get();
		}
		TDS::EntityID entityID;
	};
}
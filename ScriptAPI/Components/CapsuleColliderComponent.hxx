#pragma once

#include "ColliderComponent.hxx"

namespace ScriptAPI
{
	public ref class CapsuleColliderComponent : ColliderComponent
	{
	public:
		enum class Axis
		{
			X,
			Y,
			Z
		};

		virtual bool GetIsTrigger() override;
		virtual void SetIsTrigger(bool value) override;

		Vector3 GetCenter();
		void SetCenter(Vector3 value);
		void SetCenterX(float valueX);
		void SetCenterY(float valueY);
		void SetCenterZ(float valueZ);

		float GetRadius();
		void SetRadius(float value);

		float GetHeight();
		void SetHeight(float value);

		Axis GetDirection();
		void SetDirection(Axis value);

		virtual TDS::EntityID GetEntityID() override;
		virtual void SetEntityID(TDS::EntityID ID) override;

		virtual void SetEnabled(bool enabled) override;
		virtual bool GetEnabled() override;

		TransformComponent transform;
		GameObject^ gameObject;

	internal:
		CapsuleColliderComponent(TDS::EntityID ID);

	private:
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
		property float Height
		{
			float get();
			void set(float value);
		}
		property Axis Direction
		{
			Axis get();
			void set(Axis value);
		}

		TDS::EntityID entityID;
	};
}
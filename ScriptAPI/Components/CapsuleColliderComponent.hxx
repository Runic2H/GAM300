#pragma once

#include "../IncludeFromEngine.hxx"
#include "../Vector3.hxx"

namespace ScriptAPI
{
	public value class CapsuleColliderComponent
	{
	public:
		enum class Axis
		{
			X,
			Y,
			Z
		};

		bool GetIsTrigger();
		void SetIsTrigger(bool value);

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
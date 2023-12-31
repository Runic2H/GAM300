#pragma once

#include "ComponentBase.hxx"
#include "TransformComponent.hxx"

namespace ScriptAPI
{
	public value class CameraComponent : ComponentBase
	{
	public:
		Vector3 GetCameraOffset();
		void SetCameraOffset(Vector3 value);
		void SetCameraOffsetX(float valueX);
		void SetCameraOffsetY(float valueY);
		void SetCameraOffsetZ(float valueZ);

		float GetYaw();
		void SetYaw(float value);

		float GetPitch();
		void SetPitch(float value);

		float GetSpeed();
		void SetSpeed(float value);

		float GetFieldOfView();
		void SetFieldOfView(float value);

		float GetMouseSensitivity();
		void SetMouseSensitivity(float value);

		bool GetIsEnabled();
		void SetIsEnabled(bool value);

		Vector3 getForwardVector();
		void setForwardVector(float angle);

		virtual void SetEntityID(TDS::EntityID ID);

		TransformComponent transform;

	internal:
		CameraComponent(TDS::EntityID ID);
		TDS::EntityID GetEntityID();

	private:
		property Vector3 CameraOffset
		{
			Vector3 get();
			void set(Vector3 value);
		}
		property float Yaw
		{
			float get();
			void set(float value);
		}
		property float Pitch
		{
			float get();
			void set(float value);
		}
		property float Speed
		{
			float get();
			void set(float value);
		}
		property float FieldOfView
		{
			float get();
			void set(float value);
		}
		property float MouseSensitivity
		{
			float get();
			void set(float value);
		}
		property bool IsEnabled
		{
			bool get();
			void set(bool value);
		}

		TDS::EntityID entityID;
	};
}
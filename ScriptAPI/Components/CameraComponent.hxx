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

		Vector3 getForwardVector();
		void setForwardVector(float angle);

		Vector3 getRightVector();
		void setRightVector(float angle);

		virtual TDS::EntityID GetEntityID();
		virtual void SetEntityID(TDS::EntityID ID);

		virtual void SetEnabled(bool enabled);
		virtual bool GetEnabled();

		TransformComponent transform;
		GameObject^ gameObject;

	internal:
		CameraComponent(TDS::EntityID ID);

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

		TDS::EntityID entityID;
	};
}
#pragma once

#include "../IncludeFromEngine.hxx"
#include "../Vector3.hxx"

namespace ScriptAPI
{
	public value class BoxColliderComponent
	{
	public:
		bool GetIsTrigger();
		void SetIsTrigger(bool value);

		Vector3 GetCenter();
		void SetCenter(Vector3 value);
		void SetCenterX(float valueX);
		void SetCenterY(float valueY);
		void SetCenterZ(float valueZ);

		Vector3 GetSize();
		void SetSize(Vector3 value);
		void SetSizeX(float valueX);
		void SetSizeY(float valueY);
		void SetSizeZ(float valueZ);

	internal:
		BoxColliderComponent(TDS::EntityID ID);
		TDS::EntityID GetEntityID();

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
		property Vector3 Size
		{
			Vector3 get();
			void set(Vector3 value);
		}

		TDS::EntityID entityID;
	};
}
#pragma once

#include "../IncludeFromEngine.hxx"
#include "../Vector3.hxx"

namespace ScriptAPI
{
	public value class ColliderComponent
	{
	public:
		Vector3 GetCollisionNormal();
		void SetCollisionNormal(Vector3 value);
		void SetCollisionNormalX(float valueX);
		void SetCollisionNormalY(float valueY);
		void SetCollisionNormalZ(float valueZ);

		Vector3 GetMinimum();
		void SetMinimum(Vector3 value);
		void SetMinimumX(float valueX);
		void SetMinimumY(float valueY);
		void SetMinimumZ(float valueZ);

		Vector3 GetMaximum();
		void SetMaximum(Vector3 value);
		void SetMaximumX(float valueX);
		void SetMaximumY(float valueY);
		void SetMaximumZ(float valueZ);

		Vector3 GetOffset();
		void SetOffset(Vector3 value);
		void SetOffsetX(float valueX);
		void SetOffsetY(float valueY);
		void SetOffsetZ(float valueZ);

		int GetHit();
		void SetHit(int value);

		float GetRadius();
		void SetRadius(float value);

		bool GetIsAlive();
		void SetIsAlive(bool value);

		bool GetIsColliding();
		void SetIsColliding(bool value);

	internal:
		ColliderComponent(TDS::EntityID ID);

	private:
		property Vector3 CollisionNormal
		{
			Vector3 get();
			void set(Vector3 value);
		}
		property Vector3 Minimum
		{
			Vector3 get();
			void set(Vector3 value);
		}
		property Vector3 Maximum
		{
			Vector3 get();
			void set(Vector3 value);
		}
		property Vector3 Offset
		{
			Vector3 get();
			void set(Vector3 value);
		}
		property int Hit
		{
			int get();
			void set(int value);
		}
		property float Radius
		{
			float get();
			void set(float value);
		}
		property bool IsAlive
		{
			bool get();
			void set(bool value);
		}
		property bool IsColliding
		{
			bool get();
			void set(bool value);
		}

		TDS::EntityID entityID;
	};
}
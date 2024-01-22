#pragma once

#include "ComponentBase.hxx"
#include "TransformComponent.hxx"

namespace ScriptAPI
{
	public value class NameTagComponent : ComponentBase
	{
	public:
		System::String^ GetName();
		void SetName(System::String^ value);

		System::String^ GetTag();
		void SetTag(System::String^ value);

		bool GetIsActive();
		void SetIsActive(bool value);

		virtual TDS::EntityID GetEntityID();
		virtual void SetEntityID(TDS::EntityID ID);
		virtual void SetEnabled(bool enabled);

		TransformComponent transform;

	internal:
		NameTagComponent(TDS::EntityID ID);

	private:
		property System::String^ Name
		{
			System::String^ get();
			void set(System::String^ value);
		}
		property System::String^ Tag
		{
			System::String^ get();
			void set(System::String^ value);
		}
		property bool IsActive
		{
			bool get();
			void set(bool value);
		}

		TDS::EntityID entityID;
	};
}
#pragma once

#include "../IncludeFromEngine.hxx"
#include "../Vector3.hxx"

namespace ScriptAPI
{
	public value class NameTagComponent
	{
	public:
		std::string GetName();
		void SetName(std::string value);

		std::string GetTag();
		void SetTag(std::string value);

		bool GetIsActive();
		void SetIsActive(bool value);

	internal:
		NameTagComponent(TDS::EntityID ID);
	private:
		property std::string Name
		{
			std::string get();
			void set(std::string value);
		}
		property std::string Tag
		{
			std::string get();
			void set(std::string value);
		}
		property bool IsActive
		{
			bool get();
			void set(bool value);
		}

		TDS::EntityID entityID;
	};
}
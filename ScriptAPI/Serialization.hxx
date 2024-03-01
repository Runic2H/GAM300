#pragma once

#include "IncludeFromEngine.hxx"

namespace ScriptAPI
{
	// Static functions used for serialization
	public ref class Serialization
	{
	public:
		static TDS::ScriptValues GetValue(System::Object^ object, System::Reflection::FieldInfo^ variable);
		static void SetValue(System::Object^ object, System::Reflection::FieldInfo^ variable, TDS::ScriptValues variableInfo);
	};
}

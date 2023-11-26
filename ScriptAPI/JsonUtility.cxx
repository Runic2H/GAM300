#include "JsonUtility.hxx"
#include "IncludeFromEngine.hxx"
#include "TypeConversion.hxx"
using namespace System;
using namespace System::Reflection;

namespace ScriptAPI
{
	void JsonUtility::FromJsonOverwrite(System::String^ json, Object^ data)
	{
		Type^ type = data->GetType();
		array<FieldInfo^>^ fields = type->GetFields(BindingFlags::Public | BindingFlags::Instance);

		//Console::WriteLine("Variables in this class:");
		for each (FieldInfo ^ field in fields) 
		{
			//Console::WriteLine(field->Name);

			if (json->Contains(field->Name))
			{
				std::string stdJson = toStdString(json);
				std::string stdFieldName = toStdString(field->Name);
				int foundIndex = stdJson.find(stdFieldName);
				std::string value = stdJson.substr(foundIndex + 2);
				int foundEnd = value.find_first_of(",}");
				value.substr(0, foundEnd);

				//Console::WriteLine(field->FieldType->ToString());
				//Console::WriteLine(value.length());

				if (field->FieldType->ToString() == "System.Boolean")
				{
					bool boolValue;
					if (value.find("True"))
					{
						boolValue = true;
					}
					else
					{
						boolValue = false;
					}
					field->SetValue(data, boolValue);
				}
			}
		}
	}

	System::String^ JsonUtility::ToJson(Object^ data)
	{
		Type^ type = data->GetType();
		array<FieldInfo^>^ fields = type->GetFields(BindingFlags::Public | BindingFlags::Instance);

		System::String^ toReturn = gcnew System::String("{}");
		//for each (FieldInfo ^ field in fields)
		//{
		//	if (!toReturn->CompareTo(gcnew System::String("{")))
		//	{
		//		toReturn->Concat(",");
		//	}

		//	//toReturn->Concat("\"" + field->Name->ToString() + "\":");
		//	toReturn = toReturn + gcnew System::String("\"");

		//	if (field->FieldType->ToString() == "System.Boolean")
		//	{
		//		toReturn->Concat(field->GetValue(data)->ToString());
		//	}
		//	Console::WriteLine(toStdString(toReturn).length());
		//}

		//Console::WriteLine(toStdString(toReturn).length());

		return toReturn;
	}
}
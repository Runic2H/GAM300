#pragma once
#include <iostream>

namespace ScriptAPI
{
	System::String^ toSystemString(const std::string& str);
	std::string toStdString(System::String^ str);
}

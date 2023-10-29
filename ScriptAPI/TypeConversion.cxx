#include "TypeConversion.hxx"
#include <msclr/marshal_cppstd.h>

namespace ScriptAPI
{
    System::String^ toSystemString(const std::string& str)
    {
        if (str.empty())
            return "";
        return msclr::interop::marshal_as<System::String^>(str)
            ->Substring(0, str.length());
    }

    std::string toStdString(System::String^ str)
    {
         return msclr::interop::marshal_as<std::string>(str);
    }
}
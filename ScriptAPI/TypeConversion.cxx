#include "TypeConversion.hxx"
#include <msclr/marshal_cppstd.h>
#include <codecvt>

namespace ScriptAPI
{
    // Function to convert std::string to std::wstring
    std::wstring convertStringToWstring(const std::string& str) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(str);
    }

    System::String^ toSystemString(const std::string& str)
    {
        if (str.empty())
        {
            return "";
        }
        const std::wstring result = convertStringToWstring(str);
        if (result.empty())
            return "";
        return msclr::interop::marshal_as<System::String^>(result.c_str());
    }

    std::string toStdString(System::String^ str)
    {
        msclr::interop::marshal_context context;
         return context.marshal_as<std::string>(str);
    }
}
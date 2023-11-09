#pragma once
#include "IncludeFromEngine.hxx"
#include "../GAM300Engine/Include/Input/Input.h"
#include <algorithm>

#define Mouse_X TDS::Input::getMousePosition()->x
#define Mouse_Y TDS::Input::getMousePosition()->y


namespace ScriptAPI
{
    public ref class Input
    {
    public:
        Input();
        float GetAxisRaw(System::String^ code);
        float GetAxis(System::String^ code);
        bool GetKey(uint32_t keycode);
        bool GetKeyDown(uint32_t keycode);
        bool GetKeyUp(uint32_t keycode);
        bool GetMouseButton(uint32_t button);
        bool GetMouseButtonUp(uint32_t button);
        bool GetMouseButtonDown(uint32_t button);
    private:
        static System::Collections::Generic::Dictionary<System::String^, System::Tuple<uint32_t, uint32_t>^>^ AxisDictionary;
    };
}
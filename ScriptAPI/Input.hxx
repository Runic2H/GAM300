#pragma once
#include "IncludeFromEngine.hxx"
#include "../GAM300Engine/Include/Input/Input.h"
#include <algorithm>

#define Mouse_X TDS::Input::getMousePosition()->x
#define Mouse_Y TDS::Input::getMousePosition()->y


namespace ScriptAPI
{
    public ref class Keycode
    {
    public:
        static uint32_t A = TDS_A;
        static uint32_t B = TDS_B;
        static uint32_t C = TDS_C;
        static uint32_t D = TDS_D;
        static uint32_t E = TDS_E;
        static uint32_t F = TDS_F;
        static uint32_t G = TDS_G;
        static uint32_t H = TDS_H;
        static uint32_t I = TDS_I;
        static uint32_t J = TDS_J;
        static uint32_t K = TDS_K;
        static uint32_t L = TDS_L;
        static uint32_t M = TDS_M;
        static uint32_t N = TDS_N;
        static uint32_t O = TDS_O;
        static uint32_t P = TDS_P;
        static uint32_t Q = TDS_Q;
        static uint32_t R = TDS_R;
        static uint32_t S = TDS_S;
        static uint32_t T = TDS_T;
        static uint32_t U = TDS_U;
        static uint32_t V = TDS_V;
        static uint32_t W = TDS_W;
        static uint32_t X = TDS_X;
        static uint32_t Y = TDS_Y;
        static uint32_t Z = TDS_Z;

        static uint32_t UP = TDS_UP;
        static uint32_t DOWN = TDS_DOWN;
        static uint32_t LEFT = TDS_LEFT;
        static uint32_t RIGHT = TDS_RIGHT;

        static uint32_t ZERO = TDS_0;
        static uint32_t ONE = TDS_1;
        static uint32_t TWO = TDS_2;
        static uint32_t THREE = TDS_3;
        static uint32_t FOUR = TDS_4;
        static uint32_t FIVE = TDS_5;
        static uint32_t SIX = TDS_6;
        static uint32_t SEVEN = TDS_7;
        static uint32_t EIGHT = TDS_8;
        static uint32_t NINE = TDS_9;
        static uint32_t MINUS = TDS_MINUS;
        static uint32_t PLUS = TDS_PLUS;

        static uint32_t SHIFT = TDS_SHIFT;
        static uint32_t CTRL = TDS_CONTROL;
        static uint32_t ALT = TDS_ALT;
        static uint32_t SPACE = TDS_SPACE;
        static uint32_t ESC = TDS_ESCAPE;
        static uint32_t CAPS = TDS_CAPSLOCK;
        static uint32_t TAB = TDS_TAB;
        static uint32_t ENTER = TDS_ENTER;
        static uint32_t BACKSPACE = TDS_BACKSPACE;
        static uint32_t TILDE = TDS_TILDE;
        static uint32_t COMMA = TDS_COMMA;
        static uint32_t PERIOD = TDS_PERIOD;
        static uint32_t SLASH = TDS_SLASH;
        static uint32_t SEMICOLON = TDS_SEMICOLON;

        static uint32_t M1 = TDS_MOUSE_LEFT;
        static uint32_t M2 = TDS_MOUSE_RIGHT;
        static uint32_t MIDDLE = TDS_MOUSE_MIDDLE;
        static uint32_t M4 = TDS_MOUSE_X1;
        static uint32_t M5 = TDS_MOUSE_X2;
        static uint32_t SCROLL = TDS_MOUSE_SCROLL;
    };

    public ref class Input
    {
    public:
        Input();
        static float GetAxisRaw(System::String^ code);
        static float GetAxis(System::String^ code);
        static bool GetKey(uint32_t keycode);
        static bool GetKeyDown(uint32_t keycode);
        static bool GetKeyUp(uint32_t keycode);
        static bool GetMouseButton(uint32_t button);
        static bool GetMouseButtonUp(uint32_t button);
        static bool GetMouseButtonDown(uint32_t button);

    private:
        static System::Collections::Generic::Dictionary<System::String^, System::Tuple<uint32_t, uint32_t>^>^ AxisDictionary;
    };
}
#pragma once
#include <Windows.h>

using namespace System;

namespace ScriptAPI
{
    public enum class CursorLockMode
    {
        None,
        Locked,
        Confined
    };

    public ref class Cursor
    {
    public:
        static property CursorLockMode LockState
        {
            CursorLockMode get()
            {
                return lockMode;
            }

            void set(CursorLockMode value)
            {
                lockMode = value;
                UpdateCursorState();
            }
        }

        static void LockCursor();

        static void UnlockCursor();

        static void ConfineCursor();

        static bool visible;

    private:
        static CursorLockMode lockMode = CursorLockMode::None;

        static void UpdateCursorState()
        {
            switch (LockState)
            {
            case CursorLockMode::None:
                ::ShowCursor(true);
                ::ClipCursor(nullptr);
                break;

            case CursorLockMode::Locked:
                ::ShowCursor(false);
                ::ClipCursor(nullptr);
                break;

            case CursorLockMode::Confined:
                ::ShowCursor(false);

                RECT clientRect;
                HWND hWnd = static_cast<HWND>(System::Diagnostics::Process::GetCurrentProcess()->MainWindowHandle.ToPointer());
                GetClientRect(hWnd, &clientRect);

                POINT topLeft = { clientRect.left, clientRect.top };
                POINT bottomRight = { clientRect.right, clientRect.bottom };

                ClientToScreen(hWnd, &topLeft);
                ClientToScreen(hWnd, &bottomRight);

                clientRect.left = topLeft.x;
                clientRect.top = topLeft.y;
                clientRect.right = bottomRight.x;
                clientRect.bottom = bottomRight.y;

                ::ClipCursor(&clientRect);
                break;
            }

            ::ShowCursor(visible);
        }
    };
}
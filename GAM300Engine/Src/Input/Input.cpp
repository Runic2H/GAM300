/*!*************************************************************************
****
\file Input.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: CSD3400
\par Section: a
\par assignment: M1
\date 01-10-2023
\brief  This file implements the input handling system for the TDS engine.
		Input mapping is implemented via win32 API.
****************************************************************************
***/

#include "Input/Input.h"
namespace TDS
{
	Input::keyboardInputMap Input::keyboard;
	Input::mouseInputMap	Input::mouse;
	Input::KeyStatus		Input::keystatus;
	uint32_t				Input::keyCode;
	short					Input::wheelDelta;
	Vec2					Input::local_MousePos;
	bool					Input::exit_cursor;

	Input::keyState Input::GetKeyState(uint32_t keycode)
	{
		return keyboard.keys[keycode];
	}
	bool Input::isKeyPressed(uint32_t keycode)
	{
		return keyboard.keys[keycode].isPressed;
	}
	bool Input::isKeyHeld(uint32_t keycode)
	{
		return keyboard.keys[keycode].isDown;
	}
	bool Input::isKeyReleased(uint32_t keycode)
	{
		return !keyboard.keys[keycode].isDown;
	}
	bool Input::isMouseScrollUp()
	{
		return mouse.buttons[TDS_MOUSE_SCROLL].isScrollUp;
	}
	bool Input::isMouseScrollDown()
	{
		return mouse.buttons[TDS_MOUSE_SCROLL].isScrollDown;
	}
	bool Input::wasKeyHit(uint32_t keycode) //check if key has just been pressed
	{
		return (!keyboard.keys[keycode].wasDown) && keyboard.keys[keycode].isDown;
	}

	void Input::processKeyboardInput(uint32_t VKcode, bool isPressed, bool isReleased)
	{
			if (VKcode >= 'A' && VKcode <= 'Z')
			{
				uint32_t TDCkeycode = VKcode - 'A';
				keyCode = VKcode - 'A';
				keyboard.keys[TDCkeycode].isPressed  = isPressed;
				keyboard.keys[TDCkeycode].isReleased = isReleased;
			}

			else if (VKcode == VK_UP)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_UP].isPressed = isPressed;
				keyboard.keys[TDS_UP].isReleased = isReleased;
			}

			else if (VKcode == VK_DOWN)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_DOWN].isPressed = isPressed;
				keyboard.keys[TDS_DOWN].isReleased = isReleased;
			}

			else if (VKcode == VK_LEFT)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_LEFT].isPressed = isPressed;
				keyboard.keys[TDS_LEFT].isReleased = isReleased;
			}

			else if (VKcode == VK_RIGHT)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_RIGHT].isPressed = isPressed;
				keyboard.keys[TDS_RIGHT].isReleased = isReleased;
			}

			else if (VKcode >= '0' && VKcode <= '9')
			{
				keyCode = VKcode;
				uint32_t TDS_keycode = VKcode - '0' + TDS_0;
				keyboard.keys[TDS_keycode].isPressed = isPressed;
				keyboard.keys[TDS_keycode].isReleased = isReleased;
			}

			else if (VKcode == VK_OEM_MINUS)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_MINUS].isPressed = isPressed;
				keyboard.keys[TDS_MINUS].isReleased = isReleased;
			}

			else if (VKcode == VK_OEM_PLUS)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_PLUS].isPressed = isPressed;
				keyboard.keys[TDS_PLUS].isReleased = isReleased;
			}

			else if (VKcode == VK_SHIFT)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_SHIFT].isPressed = isPressed;
				keyboard.keys[TDS_SHIFT].isReleased = isReleased;
			}

			else if (VKcode == VK_CONTROL)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_CONTROL].isPressed = isPressed;
				keyboard.keys[TDS_CONTROL].isReleased = isReleased;
			}

			else if (VKcode == VK_MENU)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_ALT].isPressed = isPressed;
				keyboard.keys[TDS_ALT].isReleased = isReleased;
			}

			else if (VKcode == VK_SPACE)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_SPACE].isPressed = isPressed;
				keyboard.keys[TDS_SPACE].isReleased = isReleased;
			}

			else if (VKcode == VK_ESCAPE)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_ESCAPE].isPressed = isPressed;
				keyboard.keys[TDS_ESCAPE].isReleased = isReleased;
			}

			else if (VKcode == VK_CAPITAL)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_CAPSLOCK].isPressed = isPressed;
				keyboard.keys[TDS_CAPSLOCK].isReleased = isReleased;
			}

			else if (VKcode == VK_TAB)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_TAB].isPressed = isPressed;
				keyboard.keys[TDS_TAB].isReleased = isReleased;
			}

			else if (VKcode == VK_RETURN)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_ENTER].isPressed = isPressed;
				keyboard.keys[TDS_ENTER].isReleased = isReleased;
			}

			else if (VKcode == VK_BACK)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_BACKSPACE].isPressed = isPressed;
				keyboard.keys[TDS_BACKSPACE].isReleased = isReleased;
			}

			else if (VKcode == VK_OEM_3)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_TILDE].isPressed = isPressed;
				keyboard.keys[TDS_TILDE].isReleased = isReleased;
			}

			else if (VKcode == VK_OEM_COMMA)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_COMMA].isPressed = isPressed;
				keyboard.keys[TDS_COMMA].isReleased = isReleased;
			}

			else if (VKcode == VK_OEM_PERIOD)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_PERIOD].isPressed = isPressed;
				keyboard.keys[TDS_PERIOD].isReleased = isReleased;
			}

			else if (VKcode == VK_OEM_2)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_SLASH].isPressed = isPressed;
				keyboard.keys[TDS_SLASH].isReleased = isReleased;
			}

			else if (VKcode == VK_OEM_1)
			{
				keyCode = VKcode;
				keyboard.keys[TDS_SEMICOLON].isPressed = isPressed;
				keyboard.keys[TDS_SEMICOLON].isReleased = isReleased;
			}
	}

	Input::mousePosition Input::getMousePosition()
	{
		return mouse.position;
	}

	bool Input::isMouseButtonPressed(unsigned int buttonCode)
	{
		return mouse.buttons[buttonCode].isPressed;
	}

	bool Input::isMouseButtonHeld(unsigned int buttonCode)
	{
		return mouse.buttons[buttonCode].isDown;
	}

	bool Input::isMouseButtonReleased(unsigned int buttonCode)
	{
		return !mouse.buttons[buttonCode].isDown;
	}
	void Input::releaseTheMouse(unsigned int buttonCode)
	{
		mouse.buttons[buttonCode].isDown = false;
	}

	void Input::KeyRelease(uint32_t keycode)
	{
		TDS::Input::releaseTheKey(keycode);
	}

	void Input::InputUpdateLoop()
	{
		for (int i = 0; i < TDS_MAX_KEYS; i++)
		{
			if (keyboard.keys[i].isPressed)
			{
				keyboard.keys[i].isPressed = false;
				keyboard.keys[i].isDown = true;
			}
			if(keyboard.keys[i].isReleased)
			{
				keyboard.keys[i].isDown = false;
			}
		}
	}

	void Input::InputUpdateMouseLoop()
	{
		for (int i = 0; i < TDS_MAX_MOUSE_BUTTONS; i++)
		{
			if (mouse.buttons[i].isPressed)
			{
				mouse.buttons[i].isPressed = false;
				mouse.buttons[i].isDown = true;
			}
			if (mouse.buttons[i].isReleased)
			{
				mouse.buttons[i].isDown = false;
			}
		}
	}

	bool Input::wasMouseButtonHit(unsigned int buttonCode)
	{
		return (!mouse.buttons[buttonCode].wasDown) && mouse.buttons[buttonCode].isDown;
	}

	void Input::processMouseInput(WPARAM wParam, LPARAM lParam)
	{
		//mouse.buttons[TDS_MOUSE_LEFT].wasDown = mouse.buttons[TDS_MOUSE_LEFT].isDown;
		//mouse.buttons[TDS_MOUSE_RIGHT].wasDown = mouse.buttons[TDS_MOUSE_RIGHT].isDown;
		//mouse.buttons[TDS_MOUSE_MIDDLE].wasDown = mouse.buttons[TDS_MOUSE_MIDDLE].isDown;
		//mouse.buttons[TDS_MOUSE_X1].wasDown = mouse.buttons[TDS_MOUSE_X1].isDown;
		//mouse.buttons[TDS_MOUSE_X2].wasDown = mouse.buttons[TDS_MOUSE_X2].isDown;

		//mouse.buttons[TDS_MOUSE_LEFT].isDown = wParam & MK_LBUTTON;
		//mouse.buttons[TDS_MOUSE_RIGHT].isDown = wParam & MK_RBUTTON;
		//mouse.buttons[TDS_MOUSE_MIDDLE].isDown = wParam & MK_MBUTTON;
		//mouse.buttons[TDS_MOUSE_X1].isDown = wParam & MK_XBUTTON1;
		//mouse.buttons[TDS_MOUSE_X2].isDown = wParam & MK_XBUTTON2;
		
		
		if (wParam & MK_LBUTTON)
		{
			mouse.buttons[TDS_MOUSE_LEFT].isPressed = 1;
			mouse.buttons[TDS_MOUSE_LEFT].isReleased = 0;
		}
		else
		{
			mouse.buttons[TDS_MOUSE_LEFT].isPressed = 0;
			mouse.buttons[TDS_MOUSE_LEFT].isReleased = 1;
		}

		updateMousePosition(lParam);

	}

	void Input::processMouseScroll(WPARAM _wParam)
	{
		wheelDelta = GET_WHEEL_DELTA_WPARAM(_wParam);
		if (wheelDelta > 0)
		{
			mouse.buttons[TDS_MOUSE_SCROLL].isScrollUp = true;
			mouse.buttons[TDS_MOUSE_SCROLL].isScrollDown = false;
		}
		else
		{
			mouse.buttons[TDS_MOUSE_SCROLL].isScrollDown = true;
			mouse.buttons[TDS_MOUSE_SCROLL].isScrollUp = false;
		}
	}

	void Input::updateMousePosition(LPARAM lParam)
	{
		//macros that return current position of the cursor relative to the application
		mouse.position.x = GET_X_LPARAM(lParam);
		mouse.position.y = GET_Y_LPARAM(lParam);
	}

	void Input::scrollStop()
	{

		mouse.buttons[TDS_MOUSE_SCROLL].isScrollDown = false;
		mouse.buttons[TDS_MOUSE_SCROLL].isScrollUp = false;
	}

	void Input::releaseTheKey(uint32_t key)
	{
		keyboard.keys[key].isDown = false;
	}

	void Input::setCenteredMouse(float x, float y)
	{
		local_MousePos = Vec2(x, y);
	}

	void Input::setExitCursor(bool input)
	{
		exit_cursor = input;
	}

	bool Input::getExitCursor()
	{
		return exit_cursor;
	}

	void Input::setLocalMousePos(Vec2 mousePos)
	{
		local_MousePos = mousePos;
	}

	Vec2 Input::getLocalMousePos()
	{
		return Vec2(local_MousePos.x, local_MousePos.y);
	}

	float Input::getLocalMousePosX()
	{
		return local_MousePos.x;
	}

	float Input::getLocalMousePosY()
	{
		return local_MousePos.y;
	}

} //end of namespace
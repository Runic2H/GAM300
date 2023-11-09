#include "Input.hxx"

namespace ScriptAPI
{
	Input::Input()
	{
		AxisDictionary->Add("Horizontal", gcnew System::Tuple<uint32_t, uint32_t>(TDS_D, TDS_A));
		AxisDictionary->Add("Vertical", gcnew System::Tuple<uint32_t, uint32_t>(TDS_W, TDS_S));
	}

	float Input::GetAxisRaw(System::String^ code)
	{

		if (GetKeyDown(AxisDictionary[code]->Item1))
		{
			return 1.0f;
		}
		if (GetKeyDown(AxisDictionary[code]->Item2))
		{
			return -1.0f;
		}

		return 0.0f;
	}

	float Input::GetAxis(System::String^ code)
	{
		static float AxisValue = 0.0f;
		float minValue = -1.0f;
		float maxValue = 1.0f;

		if (GetKeyDown(AxisDictionary[code]->Item1))
		{
			AxisValue += 0.05f;
		}
		if (GetKeyDown(AxisDictionary[code]->Item1))
		{
			AxisValue -= 0.05f;
		}

		return std::clamp<float>(AxisValue, minValue, maxValue);
	}

	bool Input::GetKey(uint32_t keycode)
	{
		return TDS::Input::isKeyPressed(keycode);
	}

	bool Input::GetKeyDown(uint32_t keycode)
	{
		return TDS::Input::isKeyPressed(keycode);
	}

	bool Input::GetKeyUp(uint32_t keycode)
	{
		return TDS::Input::isKeyReleased(keycode);
	}

	bool Input::GetMouseButton(uint32_t button)
	{
		return TDS::Input::isMouseButtonPressed(button);
	}

	bool Input::GetMouseButtonDown(uint32_t button)
	{
		return TDS::Input::isMouseButtonPressed(button);
	}

	bool Input::GetMouseButtonUp(uint32_t button)
	{
		return TDS::Input::isMouseButtonReleased(button);
	}
}

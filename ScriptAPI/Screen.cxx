#include "Screen.hxx"

namespace ScriptAPI
{
	Screen::Screen()
	{
		width = TDS::GetScreenWidth();
		height = TDS::GetScreenHeight();
	}
}
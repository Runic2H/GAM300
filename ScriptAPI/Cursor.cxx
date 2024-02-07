#include "Cursor.hxx"

namespace ScriptAPI
{
	void Cursor::LockCursor()
	{
		LockState = CursorLockMode::Locked;
	}

	void Cursor::UnlockCursor()
	{
		LockState = CursorLockMode::None;
	}

	void Cursor::ConfineCursor()
	{
		LockState = CursorLockMode::Confined;
	}
}
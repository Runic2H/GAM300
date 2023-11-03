#include "Script.hxx"
#include "HelperFunctions.hxx"

namespace ScriptAPI
{
	void Script::SetFlags()
	{
		is_Enabled = true;
		is_Awake = false;
		is_Start = false;
	}

	void Script::ToggleScript()
	{
		is_Enabled = !is_Enabled;
		if (is_Enabled)
		{
			OnEnable();
		}
		else
		{
			OnDisable();
		}
	}

	bool Script::isScriptEnabled()
	{
		return is_Enabled;
	}

	void Script::setAwakeFlag()
	{
		is_Awake = !is_Awake;
	}

	bool Script::getAwakeFlag()
	{
		return is_Awake;
	}

	void Script::setStartFlag()
	{
		is_Start = !is_Start;
	}

	bool Script::getStartFlag()
	{
		return is_Start;
	}

	generic <typename TResult>
	IAsyncEnumerable<TResult>^ Script::Coroutine(Func<IAsyncEnumerable<TResult>^>^ func, int duration)
	{
		return ScriptSystem::UnityCoroutineC<TResult>(func, std::chrono::milliseconds(duration));
	}


	GameObject^ Script::GameObjectScriptFind(System::String^ name)
	{
		//System::Console::WriteLine("called");
		return FindGameObjectViaName(name);
	}
}
#include "Script.hxx"
#include "HelperFunctions.hxx"

namespace ScriptAPI
{
	void Script::SetEntityID(TDS::EntityID ID)
	{
		entityID = ID;
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

	BoxColliderComponent Script::GetBoxColliderComponent()
	{
		return BoxColliderComponent(entityID);
	}
	CapsuleColliderComponent Script::GetCapsuleColliderComponent()
	{
		return CapsuleColliderComponent(entityID);
	}
	NameTagComponent Script::GetNameTagComponent()
	{
		return NameTagComponent(entityID);
	}
	SphereColliderComponent Script::GetSphereColliderComponent()
	{
		return SphereColliderComponent(entityID);
	}
	//TDS::EntityID Script::findGameObject(System::String^ gameObjectName)
	//{
	//	gameObjectName = gameObjectName->Trim();
	//	return ScriptSystem::findGameObject(gameObjectName);
	//}

	TransformComponent Script::GetTransformComponent()
	{
		return TransformComponent(entityID);
	}

	int Script::GetEntityID()
	{
		return entityID;
	}

	Script^ Script::GameObjectScriptFind(System::String^ name, System::String^ script)
	{
		System::Console::WriteLine("called");
		return FindGameObjectViaName(name, script);
	}
}
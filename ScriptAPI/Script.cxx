#include "Script.hxx"

namespace ScriptAPI
{
	void Script::SetEntityID(TDS::EntityID ID)
	{
		entityID = ID;
	}

	TransformComponent Script::GetTransformComponent()
	{
		return TransformComponent(entityID);
	}
	ColliderComponent Script::GetColliderComponent()
	{
		return ColliderComponent(entityID);
	}
}
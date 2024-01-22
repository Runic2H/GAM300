#pragma once

#include "../IncludeFromEngine.hxx"
#include "../Vector2.hxx"
#include "../Vector3.hxx"
#include "../Vector4.hxx"
#include "../Quaternion.hxx"

namespace ScriptAPI
{
	private interface class ComponentBase
	{
		virtual TDS::EntityID GetEntityID() = 0;
		virtual void SetEntityID(TDS::EntityID ID) = 0;
		virtual void SetEnabled(bool enabled) = 0;
	};
}
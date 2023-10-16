#pragma once

#include "../IncludeFromEngine.hxx"
#include "../Vector3.hxx"

namespace ScriptAPI
{
	public value class NameTagComponent
	{
	public:


	internal:
		NameTagComponent(TDS::EntityID ID);
	private:

		TDS::EntityID entityID;
	};
}
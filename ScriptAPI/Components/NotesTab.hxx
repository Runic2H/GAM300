#pragma once

#include "ComponentBase.hxx"
#include "ColliderComponent.hxx"
#include "UISpriteComponent.hxx"

/**
 * @brief This is a sub component of an inventory system.
 * Stores notes collected by the player throughout the game.
*/

namespace ScriptAPI
{
	public value class NotesTab : ComponentBase
	{
	public:

		virtual TDS::EntityID GetEntityID();
		virtual void SetEntityID(TDS::EntityID ID);

	internal:
		NotesTab(TDS::EntityID ID);

	private:

		TDS::EntityID id;
	};
}
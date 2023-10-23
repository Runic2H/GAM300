/*!*************************************************************************
****
\file ImguiHierarchy.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions used in the Level Editor Hierarchy
		panel
****************************************************************************
***/

#ifndef IMGUI_HIERARCHY
#define IMGUI_HIERARCHY

#include "sceneManager/sceneManager.h"
#include "ImguiHelper.h"

namespace TDS 
{
	class Hierarchy : public LevelEditorPanel
	{
	public:
		/*!*************************************************************************
		This function initializes the Hierarchy panel
		****************************************************************************/
		Hierarchy();

		void init();

		/*!*************************************************************************
		This function is the update function for Hierarchy panel
		****************************************************************************/
		void update();

		/*!*************************************************************************
		This function is the getter function for selected entity
		****************************************************************************/
		EntityID getSelectedEntity() { return selectedEntity; }
		/*!*************************************************************************
		This function is the setter function for selected entity
		****************************************************************************/
		void setSelectedEntity(EntityID _selectedEntity) { selectedEntity = _selectedEntity; }

		void insetOnHoldEntities(EntityID newParent);

	private:
		struct ImguiHierarchyEntity
		{
			EntityID parent;
			std::vector<ImguiHierarchyEntity> children;
		};

		std::vector<ImguiHierarchyEntity> hierarchyEntities;

		// parent - list of children
		std::map<EntityID, std::vector<EntityID>> entitiesOnHold;
		std::map<EntityID, ImguiHierarchyEntity*> entitiesInputted;

		EntityID selectedEntity;
	};
}

#endif // IMGUI_HIERARCHY

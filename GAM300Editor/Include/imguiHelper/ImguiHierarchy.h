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
		//struct HierarchyInfo
		//{
		//	EntityID parent;
		//	int indexInParent;
		//	std::vector<EntityID> children;
		//};

		/*!*************************************************************************
		This function initializes the Hierarchy panel
		****************************************************************************/
		Hierarchy();

		void init();

		/*!*************************************************************************
		This function is the update function for Hierarchy panel
		****************************************************************************/
		void update();

		void reorderingHierarchy(EntityID payloadEntity, EntityID acceptEntity, bool acceptEntityTreeNode = false);

		void removeEntity(EntityID entityID);

		void makingChildHierarchy(EntityID payloadEntity, EntityID acceptEntity);

		bool searchForChild(EntityID parentEntity, EntityID entityToFind);

		/*!*************************************************************************
		This function is the getter function for selected entity
		****************************************************************************/
		EntityID getSelectedEntity() { return selectedEntity; }
		/*!*************************************************************************
		This function is the setter function for selected entity
		****************************************************************************/
		void setSelectedEntity(EntityID _selectedEntity) { selectedEntity = _selectedEntity; }

		void drawHierarchy(EntityID entityID);

		//std::map<EntityID, HierarchyInfo> hierarchyMap;
		std::vector<EntityID> hierarchyList;
	private:
		ImGuiTextFilter filter;

		bool anyItemHovered;
		bool popupOpened;

		EntityID selectedEntity;
		std::string currentFilename;
	};
}

#endif // IMGUI_HIERARCHY

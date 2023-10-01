/*!*************************************************************************
****
\file ImguiBehaviourTree.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the Level Editor Behaviour
		Tree panel
****************************************************************************
***/

#ifndef IMGUI_BEHAVIOUR_TREE
#define IMGUI_BEHAVIOUR_TREE

#include "ImguiHelper.h"

#include "AI/behaviourTree.h"

namespace TDS
{
	class BehaviourTreePanel : public LevelEditorPanel
	{
	public:
		enum class BehaviourTreeType
		{
			ROOT,
			CONTROL_FLOW,
			DECORATOR,
			LEAF_NODE
		};
		// STRUCTS ======================================================================================
		struct BTENode
		{
			/*!*************************************************************************
			This function is a constructor for the nodes in the behaviorTree editor.
			****************************************************************************/
			BTENode(
				int _id,
				std::string _name,
				BehaviourTreeType _type,
				const Vec2& _position,
				int _inputsCount,
				int _outputsCount);

			/*!*************************************************************************
			This function calculates the position of the input slot id given, based on
			the node position and number of inputs it has.
			****************************************************************************/
			Vec2 getInputSlotPos(int slotNumber) const;

			/*!*************************************************************************
			This function calculates the position of the output slot id given, based on
			the node position and number of outputs it has.
			****************************************************************************/
			Vec2 getOutputSlotPos(int slotNumber) const;

			int id;
			std::string	name;
			BehaviourTreeType type;
			Vec2	position, size;
			int inputsCount, outputsCount;
			std::shared_ptr<Node> pointer;

			int childNumber;

			int childrenNodeCount;
		};

		struct BTELink
		{
			/*!*************************************************************************
			This function connects the 2 nodes together, drawing a bezier curve line,
			joining the input slot with the output slot.
			****************************************************************************/
			BTELink(int inputIndex, int inputSlot, int outputIndex, int outputSlot);

			int InputIdx, InputSlot, OutputIdx, OutputSlot;
		};
		/*!*************************************************************************
		This function checks if the link is colliding with the node.
		****************************************************************************/
		bool nodeLinkButtonCheck(Vec2 nodeLink);

		/*!*************************************************************************
		This function initializes the Behaviour Tree panel
		****************************************************************************/
		BehaviourTreePanel();

		/*!*************************************************************************
		This function is the update function for Behaviour Tree panel
		****************************************************************************/
		void update();

		// 0 - Control Flow
		// 1 - Decorator
		// 2 - Leaf Node
		std::vector<std::unordered_map<std::string, std::shared_ptr<Node>>> allNodeTypes;

		int treeSelectedIndex;
		bool treeRename;

		Vec2 scrolling;
		bool showGrid;

		std::vector<BTENode> nodes;
		std::vector<BTELink> links;

		const float NODE_SLOT_RADIUS = 10.0f;
		const float NODE_SLOT_DRAW_RADIUS = 4.0f;
		const Vec2 NODE_WINDOW_PADDING{ 8.0f, 8.0f };

		int nodeRename;
		int nodeSelected;

		// For joining the Links
		bool dragCheck = false;
		BTENode* currentOutputNode;
		int currentOutputNodeSlot;
		int currentOutputIndex;
		BTENode* currentInputNode;
		std::string linkType;

		std::string connectionType;

	private:
	};
}

#endif // IMGUI_BEHAVIOUR_TREE

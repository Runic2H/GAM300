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
			/*  _________________________________________________________________________*/
			/*! constructor

			@param _id				ID of the node
			@param _name			Name of the node
			@param _type			BehaviorTree type of the node
			@param _position		Position of the node
			@param _inputsCount		Number of inputs of the node
			@param _outputsCount	Number of outputs of the node

			This function is a constructor for the nodes in the behaviorTree editor.
			*/
			BTENode(
				int _id,
				std::string _name,
				BehaviourTreeType _type,
				const Vec2& _position,
				int _inputsCount,
				int _outputsCount);

			/*  _________________________________________________________________________*/
			/*! getInputSlotPos

			@param slotNumber		Input slot id
			@return					Position of the input slot

			This function calculates the position of the input slot id given, based on
			the node position and number of inputs it has.
			*/
			Vec2 getInputSlotPos(int slotNumber) const;

			/*  _________________________________________________________________________*/
			/*! getOutputSlotPos

			@param slotNumber		Output slot id
			@return					Position of the output slot

			This function calculates the position of the output slot id given, based on
			the node position and number of outputs it has.
			*/
			Vec2 getOutputSlotPos(int slotNumber) const;

			int id;
			std::string	name;
			BehaviourTreeType type;
			Vec2	position, size;
			int inputsCount, outputsCount;
			std::shared_ptr<Node> pointer;

			int childrenNodeCount;
		};

		struct BTELink
		{
			/*  _________________________________________________________________________*/
			/*! constructor

			@param inputIndex		Index of the input node in the node list
			@param inputSlot		Index of the input slot
			@param outputIndex		Output of the input node in the node list
			@param outputSlot		Output of the input slot

			This function connects the 2 nodes together, drawing a bezier curve line,
			joining the input slot with the output slot.
			*/
			BTELink(int inputIndex, int inputSlot, int outputIndex, int outputSlot);

			int InputIdx, InputSlot, OutputIdx, OutputSlot;
		};
		/*  _________________________________________________________________________*/
		/*! nodeLinkButtonCheck

		@param nodeLink			Position of the link to check
		@return					If its colliding

		This function checks if the link is colliding with the node.
		*/
		bool nodeLinkButtonCheck(Vec2 nodeLink);
		/*  _________________________________________________________________________*/
		/*! changeBehaviorTree (no longer using)

		@param nodeLink			Index of behaviorTree in list
		@return					None

		This function checks if the link is colliding with the node.
		*/
		//void changeBehaviorTree(int behaviorTreeIndex);

		BehaviourTreePanel();

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
		BTENode* currentInputNode;
		int currentOutputIndex;
		std::string linkType;

	private:
	};
}

#endif // IMGUI_BEHAVIOUR_TREE

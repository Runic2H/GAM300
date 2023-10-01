/*!*************************************************************************
****
\file ImguiBehaviourTree.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines functions of the level editor behaviour tree 
		panel
****************************************************************************
***/

#include "imguiHelper/ImguiBehaviourTree.h"
#include "Logger/Logger.h"

namespace TDS
{
	/*!*************************************************************************
	This function initializes the Behaviour Tree panel
	****************************************************************************/
	BehaviourTreePanel::BehaviourTreePanel()
	{
		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Behaviour Tree Editor";
		windowPadding = ImVec2(10.f, 10.f);

		// Registering all node types
		allNodeTypes.resize(3);

		allNodeTypes[0]["C_Selector"] = std::make_shared<C_Selector>();
		allNodeTypes[0]["C_Sequencer"] = std::make_shared<C_Sequencer>();

		allNodeTypes[1]["D_Inverter"] = std::make_shared<D_Inverter>();
		allNodeTypes[1]["D_Timer"] = std::make_shared<D_Timer>();

		allNodeTypes[2]["L_Chase"] = std::make_shared<L_Chase>();
		allNodeTypes[2]["L_Move"] = std::make_shared<L_Move>();
		allNodeTypes[2]["L_Idle"] = std::make_shared<L_Idle>();

		treeSelectedIndex = 0;
		treeRename = false;

		BTENode newNode(0, "root", BehaviourTreeType::ROOT, Vec2(200.f, 100.f), 0, 1);
		nodes.emplace_back(newNode);
	}

	/*!*************************************************************************
	This function is the helper function to convert from Imgui Vector 2 to Vec2
	****************************************************************************/
	Vec2 convertToVec2(ImVec2 vector)
	{
		return Vec2(vector.x, vector.y);
	}

	/*!*************************************************************************
	This function is the helper function to convert from Vec2 to Imgui Vector 2
	****************************************************************************/
	ImVec2 convertToImVec2(Vec2 vector)
	{
		return ImVec2(vector.x, vector.y);
	}

	/*!*************************************************************************
	This function is the update function for Behaviour Tree panel
	****************************************************************************/
	void BehaviourTreePanel::update()
	{
		ImGuiIO& io = ImGui::GetIO();

		// Draw a list of nodes on the left side
		bool openContextMenu = false;
		int nodeHoveredInList = -1;
		int nodeHoveredInScene = -1;

		auto& behaviourTrees = BehaviourTreeManager::GetInstance()->getBehaviourTrees();

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Save"))
			{
				if (ImGui::MenuItem("Current Tree"))
				{

				}
				if (ImGui::MenuItem("All Trees"))
				{

				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Load"))
			{
				if (ImGui::MenuItem("Current Tree"))
				{

				}
				if (ImGui::MenuItem("All Trees"))
				{

				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Create New"))
			{
				//if (ImGui::MenuItem("Clone Current"))
				//{

				//}
				if (ImGui::MenuItem("New"))
				{
					BehaviourTree newBehvaiourTree;
					newBehvaiourTree.rootChild = nullptr;
					newBehvaiourTree.name = "New Tree";

					behaviourTrees.emplace_back(newBehvaiourTree);

					treeRename = true;
					treeSelectedIndex = static_cast<int>(behaviourTrees.size() - 1);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// Displaying created trees
		ImGui::BeginChild("tree_list", ImVec2(100, 0));
		ImGui::Text("Trees");
		ImGui::Separator();

		for (int i = 0; i < behaviourTrees.size(); ++i)
		{
			if (treeRename && i == treeSelectedIndex)
			{
				ImGui::SetKeyboardFocusHere(0);

				char temp[100];
				strcpy_s(temp, behaviourTrees[i].name.c_str());
				ImGui::InputText(("##name" + std::to_string(i)).c_str(), temp, 100);
				behaviourTrees[i].name = std::string(temp);

				if ((ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsItemHovered()) ||
					ImGui::IsKeyPressed(ImGuiKey_Enter))
				{
					treeRename = false;
				}
			}
			else if (ImGui::Selectable(behaviourTrees[i].name.c_str(), treeSelectedIndex == i))
			{
				treeSelectedIndex = i;
				//changeBehaviorTree(treeSelected);
			}
		}

		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginGroup();

		// Create our child canvas
		ImGui::Text("Hold middle mouse button to scroll (%.2f,%.2f)", -scrolling.x, scrolling.y);
		ImGui::SameLine(ImGui::GetWindowWidth() - 100);
		ImGui::Checkbox("Show grid", &showGrid);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(60, 60, 70, 200));
		ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
		ImGui::PopStyleVar(); // WindowPadding
		ImGui::PushItemWidth(120.0f);

		const Vec2 offset = convertToVec2(ImGui::GetCursorScreenPos()) + scrolling;
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		Vec2 mousePos = convertToVec2(ImGui::GetMousePos());

		// Display grid
		if (showGrid)
		{
			ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
			float GRID_SZ = 64.0f;
			Vec2 winPosition = convertToVec2(ImGui::GetCursorScreenPos());
			Vec2 canvas_sz = convertToVec2(ImGui::GetWindowSize());
			for (float x = fmodf(scrolling.x, GRID_SZ); x < canvas_sz.x; x += GRID_SZ)
			{
				drawList->AddLine(convertToImVec2(Vec2(x, 0.0f) + winPosition), convertToImVec2(Vec2(x, canvas_sz.y) + winPosition), GRID_COLOR);
			}
			for (float y = fmodf(scrolling.y, GRID_SZ); y < canvas_sz.y; y += GRID_SZ)
			{
				drawList->AddLine(convertToImVec2(Vec2(0.0f, y) + winPosition), convertToImVec2(Vec2(canvas_sz.x, y) + winPosition), GRID_COLOR);
			}
		}

		// Display links
		drawList->ChannelsSplit(2);
		drawList->ChannelsSetCurrent(0); // Background
		for (int link_idx = 0; link_idx < links.size(); link_idx++)
		{
			BTELink* link = &links[link_idx];
			BTENode* node_inp = &nodes[link->InputIdx];
			BTENode* node_out = &nodes[link->OutputIdx];
			Vec2 p1 = offset + node_inp->getOutputSlotPos(link->InputSlot);
			Vec2 p2 = offset + node_out->getInputSlotPos(link->OutputSlot);
			drawList->AddLine(convertToImVec2(p1), convertToImVec2(p2), IM_COL32(200, 200, 100, 255), 3.0f);
		}

		// Display nodes
		for (int node_idx = 0; node_idx < nodes.size(); node_idx++)
		{
			BTENode* node = &nodes[node_idx];
			ImGui::PushID(node->id);
			Vec2 node_rect_min = offset + node->position;

			// Display node contents first
			drawList->ChannelsSetCurrent(1); // Foreground
			bool old_any_active = ImGui::IsAnyItemActive();
			ImGui::SetCursorScreenPos(convertToImVec2(node_rect_min + NODE_WINDOW_PADDING));
			ImGui::BeginGroup(); // Lock horizontal position

			ImGui::Text(node->name.c_str());
			ImGui::EndGroup();

			// Save the size of what we have emitted and whether any of the widgets are being used
			//bool node_widgets_active = (!old_any_active && ImGui::IsAnyItemActive());
			node->size = convertToVec2(ImGui::GetItemRectSize()) + NODE_WINDOW_PADDING + NODE_WINDOW_PADDING;
			Vec2 node_rect_max = node_rect_min + node->size;

			// Display node box
			drawList->ChannelsSetCurrent(0); // Background
			ImGui::SetCursorScreenPos(convertToImVec2(node_rect_min));
			ImGui::InvisibleButton("node", convertToImVec2(node->size));

			if (ImGui::IsItemHovered())
			{
				nodeHoveredInScene = node->id;
				openContextMenu |= ImGui::IsMouseClicked(ImGuiMouseButton_Right);
			}

			// Checking for selecting of output
			bool node_moving_active = ImGui::IsItemActive();

			if (node_moving_active && ImGui::IsMouseDragging(ImGuiMouseButton_Left) && !dragCheck)
				node->position = node->position + convertToVec2(io.MouseDelta);

			if (node_moving_active && !dragCheck)
			{
				for (int slot_idx = 0; slot_idx < node->outputsCount; slot_idx++)
				{
					if (nodeLinkButtonCheck(offset + node->getOutputSlotPos(slot_idx)))
					{
						currentOutputNode = node;
						currentOutputNodeSlot = slot_idx;
						currentOutputIndex = node_idx;
						dragCheck = true;
						node_moving_active = false;
						linkType = "link";
						break;
					}
				}
			}

			if (node_moving_active && !dragCheck)
			{
				for (int slot_idx = 0; slot_idx < node->inputsCount; slot_idx++)
				{
					if (nodeLinkButtonCheck(offset + node->getInputSlotPos(slot_idx)))
					{
						bool check = false;
						for (int i = 0; i < links.size(); ++i)
						{
							if (links[i].OutputIdx == node_idx && links[i].OutputSlot == slot_idx)
							{
								currentInputNode = &nodes[links[i].OutputIdx];

								currentOutputNode = &nodes[links[i].InputIdx];
								currentOutputNodeSlot = links[i].InputSlot;
								currentOutputIndex = links[i].InputIdx;

								dragCheck = true;
								node_moving_active = false;
								linkType = "unlink";
								check = true;
								links.erase(links.begin() + i);
								break;
							}
						}
						if (check)
						{
							break;
						}
					}
				}
			}

			ImU32 node_bg_color = (nodeHoveredInList == node->id || nodeHoveredInScene == node->id || (nodeHoveredInList == -1 && nodeSelected == node->id)) ? IM_COL32(50, 50, 50, 255) : IM_COL32(15, 15, 15, 255);
			drawList->AddRectFilled(convertToImVec2(node_rect_min), convertToImVec2(node_rect_max), node_bg_color, 4.0f);
			drawList->AddRect(convertToImVec2(node_rect_min), convertToImVec2(node_rect_max), IM_COL32(100, 100, 100, 255), 4.0f);

			for (int slot_idx = 0; slot_idx < node->inputsCount; slot_idx++)
			{
				drawList->AddCircleFilled(convertToImVec2(offset + node->getInputSlotPos(slot_idx)), NODE_SLOT_DRAW_RADIUS, IM_COL32(150, 150, 150, 150));
			}
			for (int slot_idx = 0; slot_idx < node->outputsCount; slot_idx++)
			{
				drawList->AddCircleFilled(convertToImVec2(offset + node->getOutputSlotPos(slot_idx)), NODE_SLOT_DRAW_RADIUS, IM_COL32(150, 150, 150, 150));
			}

			ImGui::PopID();
		}

		// Joining the lines together
		if (dragCheck)
		{
			if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
			{
				drawList->AddLine(convertToImVec2(offset + currentOutputNode->getOutputSlotPos(currentOutputNodeSlot)), convertToImVec2(mousePos), IM_COL32(200, 200, 100, 255), 3.0f);
			}
			else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
			{
				bool check = false;
				for (int currenInputIndex = 0; currenInputIndex < nodes.size(); currenInputIndex++)
				{
					for (int slot_idx = 0; slot_idx < nodes[currenInputIndex].inputsCount; slot_idx++)
					{
						if (nodeLinkButtonCheck(offset + nodes[currenInputIndex].getInputSlotPos(slot_idx)))
						{
							// Checking to make sure that the node connected to root is either sequencer or selector
							if (nodes[currentOutputIndex].type == BehaviourTreeType::ROOT && nodes[currenInputIndex].type == BehaviourTreeType::CONTROL_FLOW && behaviourTrees[treeSelectedIndex].rootChild == nullptr)
							{
								behaviourTrees[treeSelectedIndex].rootChild = static_pointer_cast<ControlFlow>(nodes[currenInputIndex].pointer);
								links.emplace_back(BTELink(currentOutputIndex, currentOutputNodeSlot, currenInputIndex, slot_idx));
							}
							//else if (behaviourTrees[treeSelectedIndex].rootChild)
							//{
							else if (nodes[currentOutputIndex].type == BehaviourTreeType::DECORATOR && !nodes[currentOutputIndex].pointer->children.size())
							{
								nodes[currentOutputIndex].pointer->children.emplace_back(nodes[currenInputIndex].pointer);
								nodes[currenInputIndex].pointer->parent = nodes[currentOutputIndex].pointer;
								nodes[currenInputIndex].childNumber = static_cast<int>(nodes[currentOutputIndex].pointer->children.size() - 1);
								links.emplace_back(BTELink(currentOutputIndex, currentOutputNodeSlot, currenInputIndex, slot_idx));
							}
							else if (nodes[currentOutputIndex].type != BehaviourTreeType::DECORATOR && nodes[currentOutputIndex].type != BehaviourTreeType::ROOT)
							{
								nodes[currentOutputIndex].pointer->children.emplace_back(nodes[currenInputIndex].pointer);
								nodes[currenInputIndex].pointer->parent = nodes[currentOutputIndex].pointer;
								nodes[currenInputIndex].childNumber = static_cast<int>(nodes[currentOutputIndex].pointer->children.size() - 1);
								links.emplace_back(BTELink(currentOutputIndex, currentOutputNodeSlot, currenInputIndex, slot_idx));
							}
							//}

							check = true;
							break;
						}
					}
					if (check)
					{
						break;
					}
				}

				if (!check && linkType == "unlink")
				{
					switch (currentOutputNode->type)
					{
					case BehaviourTreeType::ROOT:
						behaviourTrees[treeSelectedIndex].rootChild = nullptr;
						break;
					case BehaviourTreeType::CONTROL_FLOW:
						currentOutputNode->pointer->children.erase(currentOutputNode->pointer->children.begin() + currentInputNode->childNumber);
						currentInputNode->pointer->parent = nullptr;
						for (int i = 0; i < currentOutputNode->pointer->children.size(); ++i)
						{
							currentOutputNode->pointer->children[i]->childIndex = i;
						}
						break;
					case BehaviourTreeType::DECORATOR:
						currentOutputNode->pointer->children.erase(currentOutputNode->pointer->children.begin());
						currentInputNode->pointer->parent = nullptr;
						break;
					case BehaviourTreeType::LEAF_NODE:
						break;
					}
				}

				dragCheck = false;
			}
		}

		drawList->ChannelsMerge();

		// Open context menu
		if (ImGui::IsWindowHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
		{
			if (/*ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) || */!ImGui::IsAnyItemHovered() && !ImGui::IsPopupOpen("contextMenu"))
			{
				nodeSelected = nodeHoveredInList = nodeHoveredInScene = -1;
				openContextMenu = true;
			}
		}

		static Vec2 scene_pos;
		if (openContextMenu)
		{
			scene_pos = convertToVec2(ImGui::GetMousePosOnOpeningCurrentPopup()) - offset;
			ImGui::OpenPopup("contextMenu");
			if (nodeHoveredInList != -1)
			{
				nodeSelected = nodeHoveredInList;
			}
			if (nodeHoveredInScene != -1)
			{
				nodeSelected = nodeHoveredInScene;
			}
		}

		// Draw context menu
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
		if (ImGui::BeginPopup("contextMenu"))
		{
			BTENode* node = nodeSelected != -1 ? &nodes[nodeSelected] : nullptr;

			//if (node)
			//{
			//	ImGui::Text(node->name.c_str());
			//	ImGui::Separator();
			//	if (ImGui::MenuItem("Copy", NULL, false, false)) { }
			//	if (ImGui::MenuItem("Delete"))
			//	{

			//	}
			//}
			//else
			//{
			if (ImGui::BeginMenu("Add"))
			{
				if (ImGui::BeginMenu("Control Flow"))
				{
					for (auto& behaviourTreeNode : allNodeTypes[0])
					{
						if (ImGui::MenuItem(behaviourTreeNode.first.c_str()))
						{
							nodes.emplace_back(BTENode(static_cast<int>(nodes.size()), behaviourTreeNode.first, BehaviourTreeType::CONTROL_FLOW, scene_pos, 1, 1));
							nodes[nodes.size() - 1].pointer = std::shared_ptr<ControlFlow>(new ControlFlow(*static_pointer_cast<ControlFlow>(behaviourTreeNode.second)));
						}
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Decorator"))
				{
					for (auto& behaviourTreeNode : allNodeTypes[1])
					{
						if (ImGui::MenuItem(behaviourTreeNode.first.c_str()))
						{
							nodes.emplace_back(BTENode(static_cast<int>(nodes.size()), behaviourTreeNode.first, BehaviourTreeType::DECORATOR, scene_pos, 1, 1));
							nodes[nodes.size() - 1].pointer = std::shared_ptr<Decorator>(new Decorator(*static_pointer_cast<Decorator>(behaviourTreeNode.second)));
						}
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Leaf Node"))
				{
					for (auto& behaviourTreeNode : allNodeTypes[2])
					{
						if (ImGui::MenuItem(behaviourTreeNode.first.c_str()))
						{
							nodes.emplace_back(BTENode(static_cast<int>(nodes.size()), behaviourTreeNode.first, BehaviourTreeType::LEAF_NODE, scene_pos, 1, 0));
							nodes[nodes.size() - 1].pointer = std::shared_ptr<LeafNode>(new LeafNode(*static_pointer_cast<LeafNode>(behaviourTreeNode.second)));
						}
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}
			//if (ImGui::MenuItem("Paste", NULL, false, false)) { }
		//}
			ImGui::EndPopup();
		}
		ImGui::PopStyleVar();

		// Scrolling
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
			scrolling = scrolling + convertToVec2(io.MouseDelta);

		ImGui::PopItemWidth();
		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

		ImGui::EndGroup();
	}

	// STRUCT FUNCTIONS =============================================================================
	/*!*************************************************************************
	This function is a constructor for the nodes in the behaviorTree editor.
	****************************************************************************/
	BehaviourTreePanel::BTENode::BTENode(int _id, std::string _name, BehaviourTreeType _type, const Vec2& _position, int _inputsCount, int _outputsCount)
	{
		id = _id;
		name = _name;
		type = _type;
		position = _position;
		inputsCount = _inputsCount;
		outputsCount = _outputsCount;

		childrenNodeCount = 0;
	}

	/*!*************************************************************************
	This function calculates the position of the input slot id given, based on
	the node position and number of inputs it has.
	****************************************************************************/
	Vec2 BehaviourTreePanel::BTENode::getInputSlotPos(int slotNumber) const
	{
		return Vec2(position.x + size.x * ((float)slotNumber + 1) / ((float)inputsCount + 1), position.y);
	}
	/*!*************************************************************************
	This function calculates the position of the output slot id given, based on
	the node position and number of outputs it has.
	****************************************************************************/
	Vec2 BehaviourTreePanel::BTENode::getOutputSlotPos(int slotNumber) const
	{
		return Vec2(position.x + size.x * ((float)slotNumber + 1) / ((float)outputsCount + 1), position.y + size.y);
	}


	/*!*************************************************************************
	This function connects the 2 nodes together, drawing a bezier curve line,
	joining the input slot with the output slot.
	****************************************************************************/
	BehaviourTreePanel::BTELink::BTELink(int inputIndex, int inputSlot, int outputIndex, int outputSlot)
	{
		InputIdx = inputIndex;
		InputSlot = inputSlot;
		OutputIdx = outputIndex;
		OutputSlot = outputSlot;
	}

	/*!*************************************************************************
	This function checks if the link is colliding with the node.
	****************************************************************************/
	bool BehaviourTreePanel::nodeLinkButtonCheck(Vec2 nodeLink)
	{
		Vec2 mousePos = convertToVec2(ImGui::GetMousePos());

		if (mousePos.x > nodeLink.x - NODE_SLOT_RADIUS && mousePos.x < nodeLink.x + NODE_SLOT_RADIUS &&
			mousePos.y > nodeLink.y - NODE_SLOT_RADIUS && mousePos.y < nodeLink.y + NODE_SLOT_RADIUS)
		{
			return true;
		}
		return false;
	}
}

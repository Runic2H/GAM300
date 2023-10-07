/*!*************************************************************************
****
\file behaviourTree.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the classes behaviourTree and 
		behaviourTreeManager, and all the classes used in the behaviour tree
****************************************************************************
***/

#ifndef BEHAVIOUR_TREE
#define BEHAVIOUR_TREE

#include "dotnet/ImportExport.h"
#include "ecs/ecs.h"

namespace TDS
{
	enum class NodeStatus
	{
		READY,
		RUNNING,
		FAILED,
		SUCCESS
	};

	// Forward declaration
	class AI;

	// Base class for nodes
	class Node
	{
	public:
		/*!*************************************************************************
		Add child to the node
		****************************************************************************/
		DLL_API virtual void addChild(std::shared_ptr<Node> newChild) = 0;
		/*!*************************************************************************
		Get the children of the node
		****************************************************************************/
		DLL_API virtual std::vector<std::shared_ptr<Node>> getChildren() { return children; };

		/*!*************************************************************************
		Runs when this node is first ran
		****************************************************************************/
		DLL_API virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed
		****************************************************************************/
		DLL_API virtual void update(AI& aiComponent, float dt);

		/*!*************************************************************************
		Called by children to inform node of child status change
		****************************************************************************/
		DLL_API virtual void childStatusChange(AI& aiComponent);

		/*!*************************************************************************
		Runs when the node failed
		****************************************************************************/
		DLL_API virtual void failed(AI& aiComponent);
		/*!*************************************************************************
		Runs when the node succeed
		****************************************************************************/
		DLL_API virtual void success(AI& aiComponent);

		std::shared_ptr<DLL_API Node> parent;
		std::vector<DLL_API std::shared_ptr<DLL_API Node>> children;

		int childIndex{};

		std::string name = "Node";
	};

	// Multiple children, 1 parent
	class ControlFlow : public Node
	{
	public:
		/*!*************************************************************************
		Add child to the node (Override)
		****************************************************************************/
		DLL_API virtual void addChild(std::shared_ptr<Node> newChild)
		{
			newChild->childIndex = static_cast<int>(children.size());
			children.emplace_back(newChild);
		}

		std::string name = "ControlFlow";
	};

	class C_Selector : public ControlFlow
	{
	public:
		/*!*************************************************************************
		Runs when this node is first ran (Override)
		****************************************************************************/
		DLL_API virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed (Override)
		****************************************************************************/
		DLL_API virtual void update(AI& aiComponent, float dt = 0);

		/*!*************************************************************************
		Called by children to inform node of child status change (Override)
		****************************************************************************/
		DLL_API virtual void childStatusChange(AI& aiComponent);

		std::string name = "C_Selector";
	};

	class C_Sequencer : public ControlFlow
	{
	public:
		/*!*************************************************************************
		Runs when this node is first ran (Override)
		****************************************************************************/
		DLL_API virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed (Override)
		****************************************************************************/
		DLL_API virtual void update(AI& aiComponent, float dt = 0);

		/*!*************************************************************************
		Called by children to inform node of child status change (Override)
		****************************************************************************/
		DLL_API virtual void childStatusChange(AI& aiComponent);

		std::string name = "C_Sequencer";
	};

	class C_ParallelSelector : public ControlFlow
	{
	public:
		std::string name = "C_ParallelSelector";
	};

	class C_ParallelSequencer : public ControlFlow
	{
	public:
		std::string name = "C_ParallelSequencer";
	};

	// 1 child, 1 parent
	class Decorator : public Node
	{
	public:
		/*!*************************************************************************
		Add child to the node (Override)
		****************************************************************************/
		DLL_API virtual void addChild(std::shared_ptr<Node> newChild) { if (!children.size()) children.emplace_back(newChild); };

		std::string name = "Decorator";
	};

	class D_Inverter : public Decorator			// Maybe shift to scripting
	{
	public:
		//virtual void update(AI& aiComponent);

		std::string name = "D_Inverter";
	};

	class D_Timer : public Decorator				// Maybe shift to scripting
	{
	public:
		//virtual void update(AI& aiComponent);

		 std::string name = "D_Timer";
	};

	// No children, 1 parent
	class LeafNode : public Node
	{
	public:
		/*!*************************************************************************
		Add child to the node (Override)
		****************************************************************************/
		DLL_API virtual void addChild(std::shared_ptr<Node> newChild) { };

		/*!*************************************************************************
		Runs when the node failed (Override)
		****************************************************************************/
		DLL_API virtual void failed(AI& aiComponent);
		/*!*************************************************************************
		Runs when the node succeed (Override)
		****************************************************************************/
		DLL_API virtual void success(AI& aiComponent);

		std::string name = "LeafNode";
	};

	class L_Move : public LeafNode
	{
	public:
		/*!*************************************************************************
		Runs when this node is first ran (Override)
		****************************************************************************/
		DLL_API virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed (Override)
		****************************************************************************/
		DLL_API virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Move";
	};

	class L_Idle : public LeafNode
	{
	public:
		/*!*************************************************************************
		Runs when this node is first ran (Override)
		****************************************************************************/
		DLL_API virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed (Override)
		****************************************************************************/
		DLL_API virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Idle";
	};

	class L_Chase : public LeafNode
	{
	public:
		/*!*************************************************************************
		Runs when this node is first ran (Override)
		****************************************************************************/
		DLL_API virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed (Override)
		****************************************************************************/
		DLL_API virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Chase";
	};

	//
	class  BehaviourTree
	{
	public:
		/*!*************************************************************************
		Constructor of the Behaviour Tree
		****************************************************************************/
		DLL_API BehaviourTree() : rootChild(nullptr) { }

		/*!*************************************************************************
		Runs the behaviour tree from the root node
		****************************************************************************/
		DLL_API void run(AI& aiComponent, float dt);

	    std::shared_ptr<ControlFlow> rootChild;

		std::string name;
	};

	class  BehaviourTreeManager
	{
	public:
		/*!*************************************************************************
		Returns an instance of the BehaviourTreeManager
		****************************************************************************/
		DLL_API static std::unique_ptr<BehaviourTreeManager>& GetInstance();

		/*!*************************************************************************
		Returns all of the behaviour trees
		****************************************************************************/
		DLL_API std::vector<BehaviourTree>& getBehaviourTrees();

	private:
		// Unique pointer to BehaviourTreeManager
		static std::unique_ptr<BehaviourTreeManager> m_instance;

		std::vector<BehaviourTree> behaviourTreeList;			// First node, has to be a control flow
	};
}

#endif
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

#include "ecs/ecs.h"
#include "dotnet/ImportExport.h"

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
	class DLL_API Node
	{
	public:
		/*!*************************************************************************
		Add child to the node
		****************************************************************************/
		virtual void addChild(std::shared_ptr<Node> newChild) = 0;
		/*!*************************************************************************
		Get the children of the node
		****************************************************************************/
		virtual std::vector<std::shared_ptr<Node>> getChildren() { return children; };

		/*!*************************************************************************
		Runs when this node is first ran
		****************************************************************************/
		virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed
		****************************************************************************/
		virtual void update(AI& aiComponent, float dt);

		/*!*************************************************************************
		Called by children to inform node of child status change
		****************************************************************************/
		virtual void childStatusChange(AI& aiComponent);

		/*!*************************************************************************
		Runs when the node failed
		****************************************************************************/
		virtual void failed(AI& aiComponent);
		/*!*************************************************************************
		Runs when the node succeed
		****************************************************************************/
		virtual void success(AI& aiComponent);

		std::shared_ptr<Node> parent;
		std::vector<std::shared_ptr<Node>> children;

		int childIndex;

		std::string name = "Node";
	};

	// Multiple children, 1 parent
	class DLL_API ControlFlow : public Node
	{
	public:
		/*!*************************************************************************
		Add child to the node (Override)
		****************************************************************************/
		virtual void addChild(std::shared_ptr<Node> newChild)
		{
			newChild->childIndex = static_cast<int>(children.size());
			children.emplace_back(newChild);
		}

		std::string name = "ControlFlow";
	};

	class DLL_API C_Selector : public ControlFlow
	{
	public:
		/*!*************************************************************************
		Runs when this node is first ran (Override)
		****************************************************************************/
		virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed (Override)
		****************************************************************************/
		virtual void update(AI& aiComponent, float dt = 0);

		/*!*************************************************************************
		Called by children to inform node of child status change (Override)
		****************************************************************************/
		virtual void childStatusChange(AI& aiComponent);

		std::string name = "C_Selector";
	};

	class DLL_API C_Sequencer : public ControlFlow
	{
	public:
		/*!*************************************************************************
		Runs when this node is first ran (Override)
		****************************************************************************/
		virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed (Override)
		****************************************************************************/
		virtual void update(AI& aiComponent, float dt = 0);

		/*!*************************************************************************
		Called by children to inform node of child status change (Override)
		****************************************************************************/
		virtual void childStatusChange(AI& aiComponent);

		std::string name = "C_Sequencer";
	};

	class DLL_API C_ParallelSelector : public ControlFlow
	{
	public:
		std::string name = "C_ParallelSelector";
	};

	class DLL_API C_ParallelSequencer : public ControlFlow
	{
	public:
		std::string name = "C_ParallelSequencer";
	};

	// 1 child, 1 parent
	class DLL_API Decorator : public Node
	{
	public:
		/*!*************************************************************************
		Add child to the node (Override)
		****************************************************************************/
		virtual void addChild(std::shared_ptr<Node> newChild) { if (!children.size()) children.emplace_back(newChild); };

		std::string name = "Decorator";
	};

	class DLL_API D_Inverter : public Decorator			// Maybe shift to scripting
	{
	public:
		//virtual void update(AI& aiComponent);

		std::string name = "D_Inverter";
	};

	class DLL_API D_Timer : public Decorator				// Maybe shift to scripting
	{
	public:
		//virtual void update(AI& aiComponent);

		std::string name = "D_Timer";
	};

	// No children, 1 parent
	class DLL_API LeafNode : public Node
	{
	public:
		/*!*************************************************************************
		Add child to the node (Override)
		****************************************************************************/
		virtual void addChild(std::shared_ptr<Node> newChild) { };

		/*!*************************************************************************
		Runs when the node failed (Override)
		****************************************************************************/
		virtual void failed(AI& aiComponent);
		/*!*************************************************************************
		Runs when the node succeed (Override)
		****************************************************************************/
		virtual void success(AI& aiComponent);

		std::string name = "LeafNode";
	};

	class DLL_API L_Move : public LeafNode
	{
	public:
		/*!*************************************************************************
		Runs when this node is first ran (Override)
		****************************************************************************/
		virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed (Override)
		****************************************************************************/
		virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Move";
	};

	class DLL_API L_Idle : public LeafNode
	{
	public:
		/*!*************************************************************************
		Runs when this node is first ran (Override)
		****************************************************************************/
		virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed (Override)
		****************************************************************************/
		virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Idle";
	};

	class DLL_API L_Chase : public LeafNode
	{
	public:
		/*!*************************************************************************
		Runs when this node is first ran (Override)
		****************************************************************************/
		virtual void enter(AI& aiComponent);
		/*!*************************************************************************
		Runs until success / failed (Override)
		****************************************************************************/
		virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Chase";
	};

	//
	class DLL_API BehaviourTree
	{
	public:
		/*!*************************************************************************
		Constructor of the Behaviour Tree
		****************************************************************************/
		BehaviourTree() : rootChild(nullptr) { }

		/*!*************************************************************************
		Runs the behaviour tree from the root node
		****************************************************************************/
		void run(AI& aiComponent, float dt);

		std::shared_ptr<ControlFlow> rootChild;

		std::string name;
	};

	class DLL_API BehaviourTreeManager
	{
	public:
		/*!*************************************************************************
		Returns an instance of the BehaviourTreeManager
		****************************************************************************/
		static std::unique_ptr<BehaviourTreeManager>& GetInstance();

		/*!*************************************************************************
		Returns all of the behaviour trees
		****************************************************************************/
		std::vector<BehaviourTree>& getBehaviourTrees();

	private:
		// Unique pointer to BehaviourTreeManager
		static std::unique_ptr<BehaviourTreeManager> m_instance;

		std::vector<BehaviourTree> behaviourTreeList;			// First node, has to be a control flow
	};
}

#endif
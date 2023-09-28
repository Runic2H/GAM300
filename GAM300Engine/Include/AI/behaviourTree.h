#ifndef BEHAVIOUR_TREE
#define BEHAVIOUR_TREE

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
		virtual void addChild(std::shared_ptr<Node> newChild) = 0;
		virtual std::vector<std::shared_ptr<Node>> getChildren() { return children; };

		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt);

		virtual void childStatusChange(AI& aiComponent);

		virtual void failed(AI& aiComponent);
		virtual void success(AI& aiComponent);

		std::shared_ptr<Node> parent;
		std::vector<std::shared_ptr<Node>> children;

		int childIndex;

		std::string name = "Node";
	};

	// Multiple children, 1 parent
	class ControlFlow : public Node
	{
	public:
		virtual void addChild(std::shared_ptr<Node> newChild)
		{
			newChild->childIndex = children.size();
			children.emplace_back(newChild);
		}

		std::string name = "ControlFlow";
	};

	class C_Selector : public ControlFlow
	{
	public:
		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt = 0);

		virtual void childStatusChange(AI& aiComponent);

		std::string name = "C_Selector";
	};

	class C_Sequencer : public ControlFlow
	{
	public:
		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt = 0);

		virtual void childStatusChange(AI& aiComponent);

		std::string name = "C_Sequencer";
	};

	class C_ParallelSelector : public ControlFlow
	{
	public:
		//virtual void update(AI& aiComponent);

		std::string name = "C_ParallelSelector";
	};

	class C_ParallelSequencer : public ControlFlow
	{
	public:
		//virtual void update(AI& aiComponent);

		std::string name = "C_ParallelSequencer";
	};

	// 1 child, 1 parent
	class Decorator : public Node
	{
	public:
		virtual void addChild(std::shared_ptr<Node> newChild) { if (!children.size()) children.emplace_back(newChild); };
		//virtual void update(AI& aiComponent);

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
		virtual void addChild(std::shared_ptr<Node> newChild) { };

		virtual void failed(AI& aiComponent);
		virtual void success(AI& aiComponent);

		std::string name = "LeafNode";
	};

	class L_Move : public LeafNode
	{
	public:
		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Move";
	};

	class L_Idle : public LeafNode
	{
	public:
		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Idle";
	};

	class L_Chase : public LeafNode
	{
	public:
		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Chase";
	};

	//
	class BehaviourTree
	{
	public:
		void run(AI& aiComponent, float dt);

		std::shared_ptr<ControlFlow> rootChild;

		std::string name;
	};

	class BehaviourTreeManager
	{
	public:
		/*!*************************************************************************
		Returns an instance of the BehaviourTreeManager
		****************************************************************************/
		static std::unique_ptr<BehaviourTreeManager>& GetInstance();

		std::vector<BehaviourTree>& getBehaviourTrees();

	private:
		// Unique pointer to BehaviourTreeManager
		static std::unique_ptr<BehaviourTreeManager> m_instance;

		std::vector<BehaviourTree> behaviourTreeList;			// First node, has to be a control flow
	};
}

#endif
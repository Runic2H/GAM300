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
	class DLL_API ControlFlow : public Node
	{
	public:
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
		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt = 0);

		virtual void childStatusChange(AI& aiComponent);

		std::string name = "C_Selector";
	};

	class DLL_API C_Sequencer : public ControlFlow
	{
	public:
		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt = 0);

		virtual void childStatusChange(AI& aiComponent);

		std::string name = "C_Sequencer";
	};

	class DLL_API C_ParallelSelector : public ControlFlow
	{
	public:
		//virtual void update(AI& aiComponent);

		std::string name = "C_ParallelSelector";
	};

	class DLL_API C_ParallelSequencer : public ControlFlow
	{
	public:
		//virtual void update(AI& aiComponent);

		std::string name = "C_ParallelSequencer";
	};

	// 1 child, 1 parent
	class DLL_API Decorator : public Node
	{
	public:
		virtual void addChild(std::shared_ptr<Node> newChild) { if (!children.size()) children.emplace_back(newChild); };
		//virtual void update(AI& aiComponent);

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
		virtual void addChild(std::shared_ptr<Node> newChild) { };

		virtual void failed(AI& aiComponent);
		virtual void success(AI& aiComponent);

		std::string name = "LeafNode";
	};

	class DLL_API L_Move : public LeafNode
	{
	public:
		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Move";
	};

	class DLL_API L_Idle : public LeafNode
	{
	public:
		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Idle";
	};

	class DLL_API L_Chase : public LeafNode
	{
	public:
		virtual void enter(AI& aiComponent);
		virtual void update(AI& aiComponent, float dt);

		std::string name = "L_Chase";
	};

	//
	class DLL_API BehaviourTree
	{
	public:
		BehaviourTree() : rootChild(nullptr) { }

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

		std::vector<BehaviourTree>& getBehaviourTrees();

	private:
		// Unique pointer to BehaviourTreeManager
		static std::unique_ptr<BehaviourTreeManager> m_instance;

		std::vector<BehaviourTree> behaviourTreeList;			// First node, has to be a control flow
	};
}

#endif
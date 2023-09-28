#include "AI/behaviourTree.h"
#include "components/components.h"

namespace TDS
{
	// BEHAVIOUR TREE MANAGER ===================================================================
	// Unique pointer to instance of Scene
	std::unique_ptr<BehaviourTreeManager> BehaviourTreeManager::m_instance;

	/*!*************************************************************************
	Returns an instance of the BehaviourTreeManager
	****************************************************************************/
	std::unique_ptr<BehaviourTreeManager>& BehaviourTreeManager::GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = std::make_unique<BehaviourTreeManager>();
		}
		return m_instance;
	}

	std::vector<BehaviourTree>& BehaviourTreeManager::getBehaviourTrees()
	{
		return behaviourTreeList;
	}

	// BEHAVIOUR TREE ===========================================================================
	void BehaviourTree::run(AI& aiComponent, float dt)
	{
		if (aiComponent.GetEntityCurrentStatus() == NodeStatus::READY)
		{
			aiComponent.GetCurrentNode()->enter(aiComponent);
		}
		if (aiComponent.GetEntityCurrentStatus() == NodeStatus::RUNNING)
		{
			aiComponent.GetCurrentNode()->update(aiComponent, dt);
		}

		if (aiComponent.GetEntityCurrentStatus() == NodeStatus::FAILED)
		{
			aiComponent.GetCurrentNode()->failed(aiComponent);
		}
		else if (aiComponent.GetEntityCurrentStatus() == NodeStatus::SUCCESS)
		{
			aiComponent.GetCurrentNode()->success(aiComponent);
		}
	}



	// NODE (BASE CLASS) ========================================================================
	void Node::enter(AI& aiComponent)
	{
		//std::cout << "Node enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
	}
	void Node::update(AI& aiComponent, float dt)
	{
		// To be overrided
		//std::cout << "Node update" << std::endl;
	}

	void Node::childStatusChange(AI& aiComponent)
	{
		//std::cout << "Node child status change" << std::endl;
	}

	void Node::failed(AI& aiComponent)
	{
		aiComponent.SetEntityCurrentStatus(NodeStatus::FAILED);
	}
	void Node::success(AI& aiComponent)
	{
		aiComponent.SetEntityCurrentStatus(NodeStatus::SUCCESS);
	}

	// CONTROL FLOW =============================================================================
	// ==========================================================================================
	// SELECTOR =================================================================================
	// Runs until success is returned
	void C_Selector::enter(AI& aiComponent)
	{
		//std::cout << "C_Selector enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
	}
	void C_Selector::update(AI& aiComponent, float dt)
	{
		//std::cout << "C_Selector update" << std::endl;
		// Run children
		// if there is a failed, move to next one
		// else if there is a success, return success
		// else just run the child
		if (children.size())
		{
			aiComponent.SetCurrentNode(children[0]);
			aiComponent.SetEntityCurrentStatus(NodeStatus::READY);
		}
		else
		{
			// Error log 
			//std::cout << "No Children!" << std::endl;
		}
	}

	void C_Selector::childStatusChange(AI& aiComponent)
	{
		//std::cout << "C_Selector child status change" << std::endl;

		if (aiComponent.GetEntityCurrentStatus() == NodeStatus::FAILED && childIndex + 1 < children.size())
		{
			aiComponent.SetCurrentNode(children[childIndex + 1]);
			aiComponent.SetEntityCurrentStatus(NodeStatus::READY);
		}
		else
		{
			if (parent)
			{
				parent->childStatusChange(aiComponent);
			}
			else
			{
				update(aiComponent);
			}
		}
	}
	// SEQUENCER ================================================================================
	// Runs until failed is returned
	void C_Sequencer::enter(AI& aiComponent)
	{
		//std::cout << "C_Sequencer enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
	}
	void C_Sequencer::update(AI& aiComponent, float dt)
	{
		//std::cout << "C_Sequencer update" << std::endl;
		// Run children
		// if there is a failed, move to next one
		// else if there is a success, return success
		// else just run the child
		if (children.size())
		{
			aiComponent.SetCurrentNode(children[0]);
			aiComponent.SetEntityCurrentStatus(NodeStatus::READY);
		}
		else
		{
			// Error log 
			//std::cout << "No Children!" << std::endl;
		}
	}

	void C_Sequencer::childStatusChange(AI& aiComponent)
	{
		//std::cout << "C_Sequencer child status change" << std::endl;

		if (aiComponent.GetEntityCurrentStatus() == NodeStatus::SUCCESS && childIndex + 1 < children.size())
		{
			aiComponent.SetCurrentNode(children[childIndex + 1]);
			aiComponent.SetEntityCurrentStatus(NodeStatus::READY);
		}
		else
		{
			if (parent)
			{
				parent->childStatusChange(aiComponent);
			}
			else
			{
				update(aiComponent);
			}
		}
	}

	// LEAF NODE ================================================================================
	void LeafNode::failed(AI& aiComponent)
	{
		aiComponent.SetEntityCurrentStatus(NodeStatus::FAILED);
		parent->childStatusChange(aiComponent);
	}
	void LeafNode::success(AI& aiComponent)
	{
		aiComponent.SetEntityCurrentStatus(NodeStatus::SUCCESS);
		parent->childStatusChange(aiComponent);
	}
	// ==========================================================================================
	// MOVE =====================================================================================
	void L_Move::enter(AI& aiComponent)
	{
		//std::cout << "L_Move enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
		aiComponent.SetTimer(0);
	}
	void L_Move::update(AI& aiComponent, float dt)
	{
		//std::cout << "L_Move update" << std::endl;

		if (aiComponent.GetTimer() > 1)
		{
			success(aiComponent);
		}
		else
		{
			aiComponent.SetTimer(aiComponent.GetTimer() + dt);
		}
	}

	// IDLE =====================================================================================
	void L_Idle::enter(AI& aiComponent)
	{
		//std::cout << "L_Idle enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
		aiComponent.SetTimer(0);
	}
	void L_Idle::update(AI& aiComponent, float dt)
	{
		//std::cout << "L_Idle update" << std::endl;

		if (aiComponent.GetTimer() > 1)
		{
			failed(aiComponent);
		}
		else
		{
			aiComponent.SetTimer(aiComponent.GetTimer() + dt);
		}
	}

	// ATTACK ===================================================================================
	void L_Chase::enter(AI& aiComponent)
	{
		//std::cout << "L_Chase enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
		aiComponent.SetTimer(0);
	}
	void L_Chase::update(AI& aiComponent, float dt)
	{
		//std::cout << "L_Chase update" << std::endl;

		if (aiComponent.GetTimer() > 1)
		{
			success(aiComponent);
		}
		else
		{
			aiComponent.SetTimer(aiComponent.GetTimer() + dt);
		}
	}
}

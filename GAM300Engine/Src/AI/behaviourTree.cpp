/*!*************************************************************************
****
\file behaviourTree.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines functions of the behaviour tree classes
****************************************************************************
***/

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

	/*!*************************************************************************
	Returns all of the behaviour trees
	****************************************************************************/
	std::vector<BehaviourTree>& BehaviourTreeManager::getBehaviourTrees()
	{
		return behaviourTreeList;
	}

	// BEHAVIOUR TREE ===========================================================================
	/*!*************************************************************************
	Runs the behaviour tree from the root node
	****************************************************************************/
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
	/*!*************************************************************************
	Runs when this node is first ran
	****************************************************************************/
	void Node::enter(AI& aiComponent)
	{
		//std::cout << "Node enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
	}
	/*!*************************************************************************
	Runs until success / failed
	****************************************************************************/
	void Node::update(AI& aiComponent, float dt)
	{
		aiComponent;
		dt;
		// To be overrided
		std::cout << "Node update" << std::endl;
	}

	/*!*************************************************************************
	Called by children to inform node of child status change
	****************************************************************************/
	void Node::childStatusChange(AI& aiComponent)
	{
		aiComponent;
		std::cout << "Node child status change" << std::endl;
	}

	/*!*************************************************************************
	Runs when the node failed
	****************************************************************************/
	void Node::failed(AI& aiComponent)
	{
		aiComponent.SetEntityCurrentStatus(NodeStatus::FAILED);
	}
	/*!*************************************************************************
	Runs when the node succeed
	****************************************************************************/
	void Node::success(AI& aiComponent)
	{
		aiComponent.SetEntityCurrentStatus(NodeStatus::SUCCESS);
	}

	// CONTROL FLOW =============================================================================
	// ==========================================================================================
	// SELECTOR =================================================================================
	// Runs until success is returned
	/*!*************************************************************************
	Runs when this node is first ran (Override)
	****************************************************************************/
	void C_Selector::enter(AI& aiComponent)
	{
		std::cout << "C_Selector enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
	}
	/*!*************************************************************************
	Runs until success / failed (Override)
	****************************************************************************/
	void C_Selector::update(AI& aiComponent, float dt)
	{
		dt;
		std::cout << "C_Selector update" << std::endl;
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
			std::cout << "No Children!" << std::endl;
		}
	}

	/*!*************************************************************************
	Called by children to inform node of child status change (Override)
	****************************************************************************/
	void C_Selector::childStatusChange(AI& aiComponent)
	{
		std::cout << "C_Selector child status change" << std::endl;

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
	/*!*************************************************************************
	Runs when this node is first ran (Override)
	****************************************************************************/
	void C_Sequencer::enter(AI& aiComponent)
	{
		std::cout << "C_Sequencer enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
	}
	/*!*************************************************************************
	Runs until success / failed (Override)
	****************************************************************************/
	void C_Sequencer::update(AI& aiComponent, float dt)
	{
		dt;
		std::cout << "C_Sequencer update" << std::endl;
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
			std::cout << "No Children!" << std::endl;
		}
	}

	/*!*************************************************************************
	Called by children to inform node of child status change (Override)
	****************************************************************************/
	void C_Sequencer::childStatusChange(AI& aiComponent)
	{
		std::cout << "C_Sequencer child status change" << std::endl;

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
	/*!*************************************************************************
	Runs when the node failed (Override)
	****************************************************************************/
	void LeafNode::failed(AI& aiComponent)
	{
		aiComponent.SetEntityCurrentStatus(NodeStatus::FAILED);
		parent->childStatusChange(aiComponent);
	}
	/*!*************************************************************************
	Runs when the node succeed (Override)
	****************************************************************************/
	void LeafNode::success(AI& aiComponent)
	{
		aiComponent.SetEntityCurrentStatus(NodeStatus::SUCCESS);
		parent->childStatusChange(aiComponent);
	}
	// ==========================================================================================
	// MOVE =====================================================================================
	/*!*************************************************************************
	Runs when this node is first ran (Override)
	****************************************************************************/
	void L_Move::enter(AI& aiComponent)
	{
		//std::cout << "L_Move enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
		aiComponent.SetTimer(0);
	}
	/*!*************************************************************************
	Runs until success / failed (Override)
	****************************************************************************/
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
	/*!*************************************************************************
	Runs when this node is first ran (Override)
	****************************************************************************/
	void L_Idle::enter(AI& aiComponent)
	{
		std::cout << "L_Idle enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
		aiComponent.SetTimer(0);
	}
	/*!*************************************************************************
	Runs until success / failed (Override)
	****************************************************************************/
	void L_Idle::update(AI& aiComponent, float dt)
	{
		std::cout << "L_Idle update" << std::endl;

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
	/*!*************************************************************************
	Runs when this node is first ran (Override)
	****************************************************************************/
	void L_Chase::enter(AI& aiComponent)
	{
		std::cout << "L_Chase enter" << std::endl;
		aiComponent.SetEntityCurrentStatus(NodeStatus::RUNNING);
		aiComponent.SetTimer(0);
	}
	/*!*************************************************************************
	Runs until success / failed (Override)
	****************************************************************************/
	void L_Chase::update(AI& aiComponent, float dt)
	{
		std::cout << "L_Chase update" << std::endl;

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

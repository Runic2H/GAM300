/*!*************************************************************************
****
\file aiSystem.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines functions of aiSystem class
****************************************************************************
***/

#include "AI/aiSystem.h"

namespace TDS
{
	/*!*************************************************************************
	Initialization of the AISystem class (to bind in ECS)
	****************************************************************************/
	void AISystem::AISystemInit()
	{
		// Selector
		//		> Sequencer
		//				> Move
		//				> Idle
		//		> Attack
		std::unique_ptr<BehaviourTreeManager>& behaviourTreeManagerInstance = BehaviourTreeManager::GetInstance();

		//std::shared_ptr<C_Selector> cSelectorNode = std::make_shared<C_Selector>();

		//std::shared_ptr<C_Sequencer> cSequencerNode= std::make_shared<C_Sequencer>();
		//cSequencerNode->parent = cSelectorNode;
		//cSelectorNode->addChild(cSequencerNode);

		//std::shared_ptr<L_Move> lMoveNode = std::make_shared<L_Move>();
		//lMoveNode->parent = cSequencerNode;
		//std::shared_ptr<L_Idle> lIdleNode = std::make_shared<L_Idle>();
		//lIdleNode->parent = cSequencerNode;
		//cSequencerNode->addChild(lMoveNode);
		//cSequencerNode->addChild(lIdleNode);

		//std::shared_ptr<L_Chase> lChaseNode = std::make_shared<L_Chase>();
		//lChaseNode->parent = cSelectorNode;
		//cSelectorNode->addChild(lChaseNode);

		BehaviourTree newBehvaiourTree;
		//newBehvaiourTree.rootChild = cSelectorNode;
		newBehvaiourTree.name = "Sample Tree";

		//std::shared_ptr<Sequencer> sequencer = std::make_shared<Sequencer>();

		behaviourTreeManagerInstance->getBehaviourTrees().emplace_back(newBehvaiourTree);
	}

	/*!*************************************************************************
	Update of the AISystem class (to bind in ECS)
	****************************************************************************/
	void AISystem::AISystemUpdate(const float dt, const std::vector<EntityID>& entities, AI* _ai)
	{
		std::unique_ptr<BehaviourTreeManager>& behaviourTreeManagerInstance = BehaviourTreeManager::GetInstance();

		auto& behaviourTrees = behaviourTreeManagerInstance->getBehaviourTrees();

		for (int i = 0; i < entities.size(); ++i)
		{
			int& behaviourTreeIndex = _ai[i].GetBehaviourTreeIndex();
			if (behaviourTreeIndex != -1 && behaviourTreeIndex < behaviourTrees.size() && behaviourTrees[behaviourTreeIndex].rootChild)
			{
				if (!_ai[i].GetCurrentNode())
				{
					_ai[i].SetCurrentNode(behaviourTrees[behaviourTreeIndex].rootChild);
				}
				behaviourTrees[behaviourTreeIndex].run(_ai[i], dt);
			}
		}
	}
}
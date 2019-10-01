#pragma once

#include "child_nodes_manager.hpp"


namespace solver
{
	namespace engine
	{
		namespace ka31neo
		{
			constexpr float controlParameter = 0.71f;
			constexpr unsigned threshold = 100;

			class Node
			{
				ChildNodesManager childNodesManager;
				Simulator simulator;
				unsigned numVisited;
				float record;
				float averageReward;

				float UCB1(float averageRewardOfChild, unsigned numVisitedOfChild)
				{
					if(numVisitedOfChild == 0)
					{
						return INFINITY;
					}
					return averageReward + controlParameter * std::sqrt(2.0f * std::log(numVisited)) / numVisitedOfChild;
				}
				float evaluate()
				{
					return simulator.rollout();
				}
				void expand()
				{
					for(ActionID i : ActionID())
					{
						if(!simulator.canAct(i))
						{
							continue;
						}
						childNodesManager.createChild(i, simulator);
					}
				}
				_NODISCARD float play()
				{
					float reward = numVisited < threshold ? evaluate() : select()->play();
					++numVisited;
					record += reward;
					averageReward = record / numVisited;
					return reward;
				}
				Node *select()
				{
					if(isLeafNode())
					{
						expand();
					}
					float maxAverageRewardOfChildren = 0.0f;
					Node *selectedNode = nullptr;
					for(Node *childNode : children)
					{
						if(childNode == nullptr)
						{
							continue;
						}
						float averageRewardOfChild = UCB1(childNode->averageReward, childNode->numVisited);
						if(averageRewardOfChild == INFINITY)
						{
							return childNode;
						}
						if(selectedNode == nullptr || maxAverageRewardOfChildren < averageRewardOfChild)
						{
							maxAverageRewardOfChildren = averageRewardOfChild;
							selectedNode = childNode;
						}
					}
					return selectedNode;
				}

			public:
				Node(const Simulator &simulator)
					: simulator(simulator), children{nullptr}, numChildren(0)
				{

				}
				bool isLeafNode()
				{
					return numChildren == 0;
				}
				void search()
				{
					++numVisited;
					int reward = select()->play();
					record += reward;
					averageReward = static_cast<float>(record) / numVisited;
				}
			};
		}
	}
}
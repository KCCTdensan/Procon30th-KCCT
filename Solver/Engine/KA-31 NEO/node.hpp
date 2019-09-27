#pragma once

#include "simulator.hpp"
#include <array>


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
				Simulator simulator;
				std::array<Node *, numActionID> children;
				unsigned numChildren;
				unsigned numVisited;
				int record;
				float averageReward;

				float UCB1(float averageRewardOfChild, unsigned numVisitedOfChild)
				{
					if(numVisitedOfChild == 0)
					{
						return INFINITY;
					}
					return averageReward + controlParameter * std::sqrt(2.0f * std::log(numVisited)) / numVisitedOfChild;
				}
				int evaluate()
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
						children[static_cast<size_t>(i)] = new Node(simulator.act(i));
						++numChildren;
					}
				}
				int play()
				{
					int reward;
					if(numVisited < threshold)
					{
						reward = evaluate();
					}
					else
					{
						reward = select()->play();
					}
					++numVisited;
					record += reward;
					averageReward = static_cast<float>(record) / numVisited;
					return reward;
				}
				Node *select()
				{
					if(isLeafNode())
					{
						expand();
					}
					float maxAverageRewardOfChildren = -10.0f;
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
						if(maxAverageRewardOfChildren < averageRewardOfChild)
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
					select()->play();
				}
			};
		}
	}
}
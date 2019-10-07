#include "node.hpp"


namespace solver::engine::ka31neo
{
	float Node::UCB1(float averageRewardOfChild, unsigned numVisitedOfChild)const noexcept
	{
		if(numVisitedOfChild == 0)
		{
			return INFINITY;
		}
		return averageReward + controlParameter * std::sqrt(2.0f * std::logf(numVisited)) / numVisitedOfChild;
	}

	float Node::evaluate()
	{
		return simulator.rollout();
	}

	void Node::expand()
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

	float Node::play()
	{
		float reward = numVisited < threshold ? evaluate() : select()->play();
		++numVisited;
		record += reward;
		averageReward = record / numVisited;
		return reward;
	}

	Node *Node::select()
	{
		if(isLeafNode())
		{
			expand();
		}
		float maxAverageRewardOfChildren = 0.0f;
		Node *selectedNode = nullptr;
		for(Node *childNode : childNodesManager)
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

	Node::Node(const Simulator &simulator)
		: simulator(simulator)
	{

	}

	bool Node::isLeafNode()const noexcept
	{
		return childNodesManager.getNumChildren() == 0;
	}

	void Node::search()
	{
		++numVisited;
		int reward = select()->play();
		record += reward;
		averageReward = static_cast<float>(record) / numVisited;
	}
}
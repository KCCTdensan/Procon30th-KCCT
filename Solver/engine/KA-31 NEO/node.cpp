#include "node.hpp"


namespace solver::engine::ka31neo
{
	float Node::UCB1(float averageRewardOfChild, unsigned numVisitedOfChild)const noexcept
	{
		if(numVisitedOfChild == 0)
		{
			return INFINITY;
		}
		return averageReward + controlParameter * std::sqrt(2.0f * std::logf(static_cast<float>(numVisited))) / numVisitedOfChild;
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
		: numVisited(0), record(0.0f), averageReward(0.0f), simulator(simulator)
	{

	}

	bool Node::isLeafNode()const noexcept
	{
		return childNodesManager.getNumChildren() == 0;
	}

	void Node::search()
	{
		++numVisited;
		float reward = select()->play();
		record += reward;
		averageReward = static_cast<float>(record) / numVisited;
	}

	ActionID Node::getBestAction()const noexcept
	{
		unsigned maxNumVisited = 0;
		ActionID selectedActionID = ActionID::null;
		for(ActionID i : ActionID())
		{
			const Node *childNode = childNodesManager[i];
			if(childNode == nullptr)
			{
				continue;
			}
			if(childNode->numVisited > maxNumVisited)
			{
				maxNumVisited = childNode->numVisited;
				selectedActionID = i;
			}
		}
		return selectedActionID;
	}
}
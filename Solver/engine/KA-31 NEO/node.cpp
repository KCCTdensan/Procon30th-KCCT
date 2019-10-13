#include "node.hpp"


namespace solver::engine::ka31neo
{
	constexpr float controlParameter = 3.0f;
	constexpr unsigned threshold = 100;

	float Node::UCB1(float averageRewardOfChild, unsigned numVisitedOfChild)const noexcept
	{
		if(numVisitedOfChild == 0)
		{
			return INFINITY;
		}
		return averageRewardOfChild + controlParameter * std::sqrt(2.0f * std::logf(static_cast<float>(numVisited))) / numVisitedOfChild;
	}

	float Node::evaluate()
	{
		return simulator.rollout();
	}

	void Node::expand()
	{
		for(int i = 0; i < numCommandID; ++i)
		{
			CommandID command = static_cast<CommandID>(i);
			if(!simulator.canAct(command))
			{
				continue;
			}
			childNodesManager.createChild(command, simulator);
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
		float maxAverageRewardOfChildren = -INFINITY;
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
			if(selectedNode == nullptr || averageRewardOfChild > maxAverageRewardOfChildren)
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

	Node::~Node()
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

	CommandID Node::getBestCommand()const noexcept
	{
		unsigned maxNumVisited = 0;
		CommandID selectedcommandID = CommandID::null;
		for(int i = 0; i < numCommandID; ++i)
		{
			CommandID command = static_cast<CommandID>(i);
			const Node *childNode = childNodesManager[command];
			if(childNode == nullptr)
			{
				continue;
			}
			if(childNode->numVisited > maxNumVisited)
			{
				maxNumVisited = childNode->numVisited;
				selectedcommandID = command;
			}
		}
		return selectedcommandID;
	}

	Node *Node::prune(CommandID commandID)
	{
		Node *child = childNodesManager.prune(commandID);
		delete this;
		return child;
	}
}
#include "child_nodes_manager.hpp"
#include "node.hpp"


namespace solver::engine::ka31neo
{
	ChildNodesManager::ChildNodesManager()
		: children{nullptr}, numChildren(0)
	{

	}

	ChildNodesManager::~ChildNodesManager()
	{
		for(Node *node : children)
		{
			if(node == nullptr)
			{
				continue;
			}
			delete node;
		}
	}

	std::array<Node *, numActionID>::iterator ChildNodesManager::begin()noexcept
	{
		return children.begin();
	}

	std::array<Node *, numActionID>::iterator ChildNodesManager::end()noexcept
	{
		return children.end();
	}

	void ChildNodesManager::createChild(ActionID actionID, const Simulator &simulator)
	{
		children[static_cast<size_t>(actionID)] = new Node(simulator.next(actionID));
		++numChildren;
	}

	unsigned ChildNodesManager::getNumChildren()const noexcept
	{
		return numChildren;
	}
}
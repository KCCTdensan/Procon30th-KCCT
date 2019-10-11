#include "child_nodes_manager.hpp"
#include "node.hpp"


namespace solver::engine::ka31neo
{
	ChildNodesManager::ChildNodesManager(ChildNodesManager &&childNodesManager)noexcept
		: children(childNodesManager.children), numChildren(childNodesManager.numChildren)
	{
		std::fill(childNodesManager.children.begin(), childNodesManager.children.end(), nullptr);
	}

	ChildNodesManager::ChildNodesManager()
		: numChildren(0)
	{
		std::fill(children.begin(), children.end(), nullptr);
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

	const Node *ChildNodesManager::operator[](ActionID action_id)const noexcept
	{
		if(action_id == ActionID::null)
		{
			return nullptr;
		}
		return children[static_cast<size_t>(action_id)];
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
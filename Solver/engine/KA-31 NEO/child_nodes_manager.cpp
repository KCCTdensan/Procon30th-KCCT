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

	const Node *ChildNodesManager::operator[](CommandID commandID)const noexcept
	{
		if(commandID == CommandID::null)
		{
			return nullptr;
		}
		return children[static_cast<size_t>(commandID)];
	}

	std::array<Node *, numCommandID>::iterator ChildNodesManager::begin()noexcept
	{
		return children.begin();
	}

	std::array<Node *, numCommandID>::iterator ChildNodesManager::end()noexcept
	{
		return children.end();
	}

	void ChildNodesManager::createChild(CommandID commandID, const Simulator &simulator)
	{
		children[static_cast<size_t>(commandID)] = new Node(simulator.next(commandID));
		++numChildren;
	}

	unsigned ChildNodesManager::getNumChildren()const noexcept
	{
		return numChildren;
	}

	Node *ChildNodesManager::prune(CommandID commandID)
	{
		Node *selectedChild = children[static_cast<size_t>(commandID)];
		children[static_cast<size_t>(commandID)] = nullptr;
		return selectedChild;
	}
}
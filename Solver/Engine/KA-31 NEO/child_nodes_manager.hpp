#pragma once

#include "simulator.hpp"
#include <array>


namespace solver::engine::ka31neo
{
	class Node;

	class ChildNodesManager
	{
		std::array<Node *, numCommandID> children;
		unsigned numChildren;

	public:
		ChildNodesManager(const ChildNodesManager &) = delete;
		ChildNodesManager &operator=(const ChildNodesManager &) = delete;
		ChildNodesManager(ChildNodesManager &&childNodesManager)noexcept;
		ChildNodesManager();
		~ChildNodesManager();
		const Node *operator[](CommandID commandID)const noexcept;
		std::array<Node *, numCommandID>::iterator begin()noexcept;
		std::array<Node *, numCommandID>::iterator end()noexcept;
		void createChild(CommandID commandID, const Simulator &simulator);
		unsigned getNumChildren()const noexcept;
		Node *prune(CommandID commandID);
	};
}
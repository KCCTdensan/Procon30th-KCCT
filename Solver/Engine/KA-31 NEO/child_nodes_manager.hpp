#pragma once

#include "simulator.hpp"
#include <array>


namespace solver::engine::ka31neo
{
	class Node;

	class ChildNodesManager
	{
		std::array<Node *, numActionID> children;
		unsigned numChildren;

	public:
		ChildNodesManager(const ChildNodesManager &) = delete;
		ChildNodesManager &operator=(const ChildNodesManager &) = delete;
		ChildNodesManager(ChildNodesManager &&childNodesManager)noexcept;
		ChildNodesManager();
		~ChildNodesManager();
		const Node *operator[](ActionID action_id)const noexcept;
		std::array<Node *, numActionID>::iterator begin()noexcept;
		std::array<Node *, numActionID>::iterator end()noexcept;
		void createChild(ActionID actionID, const Simulator &simulator);
		unsigned getNumChildren()const noexcept;
		Node *prune(ActionID action_id);
	};
}
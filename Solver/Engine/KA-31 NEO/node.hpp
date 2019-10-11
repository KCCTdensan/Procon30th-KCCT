#pragma once

#include "child_nodes_manager.hpp"


namespace solver::engine::ka31neo
{
	constexpr float controlParameter = 0.71f;
	constexpr unsigned threshold = 10;

	class Node
	{
		ChildNodesManager childNodesManager;
		Simulator simulator;
		unsigned numVisited;
		float record;
		float averageReward;

		float UCB1(float averageRewardOfChild, unsigned numVisitedOfChild)const noexcept;
		float evaluate();
		void expand();
		_NODISCARD float play();
		Node *select();

	public:
		Node(const Simulator &simulator);
		~Node();
		bool isLeafNode()const noexcept;
		void search();
		ActionID getBestAction()const noexcept;
		_NODISCARD Node *prune(ActionID action_id);
	};
}
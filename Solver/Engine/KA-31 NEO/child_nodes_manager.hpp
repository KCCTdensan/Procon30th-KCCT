#pragma once

#include "node.hpp"
#include "simulator.hpp"
#include <array>


namespace solver
{
	namespace engine
	{
		namespace ka31neo
		{
			class ChildNodesManager
			{
				std::array<Node *, numActionID> children;
				unsigned numChildren;

			public:
				void createChild(ActionID actionID, const Simulator &simulator)
				{
					children[static_cast<size_t>(actionID)] = new Node(simulator.next(actionID));
					++numChildren;
				}
			};
		}
	}
}
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
				ChildNodesManager()
					: children{nullptr}, numChildren(0)
				{

				}
				~ChildNodesManager()
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
				auto begin()noexcept
				{
					return children.begin();
				}
				auto end()noexcept
				{
					return children.end();
				}
				void createChild(ActionID actionID, const Simulator &simulator)
				{
					children[static_cast<size_t>(actionID)] = new Node(simulator.next(actionID));
					++numChildren;
				}
				unsigned getNumChildren()const noexcept
				{
					return numChildren;
				}
			};
		}
	}
}
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
				Node *begin()noexcept
				{
					auto ret = children.begin();
					while(ret != children.end() && *ret == nullptr)ret++;
					return *ret;
				}
				Node *end()noexcept
				{
					auto ret = children.end();
					while(ret != children.begin() && *ret == nullptr)ret--;
					return *ret;
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